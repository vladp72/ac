#pragma once

//
// TODO:
//
#define JET_CODDING_ERROR() {DebugBreak();}
#define JET_CODDING_ERROR_IF(cond) if(!(cond)) {} else {DebugBreak();}
#define JET_CODDING_ERROR_IF_NOT(cond) if(cond) {} else {DebugBreak();}
#define SANITIZE_CSTR_FOR_PRINTF(s) (s ? s : _T(""))
#define cxl_MakeQWORD(l, h) ((static_cast<unsigned long long>(h) << 32Ull) | static_cast<unsigned long long>(l))
#define CPPBOOL(v) ((v) ? true : false)
#define WINBOOL(v) ((v) ? TRUE : FALSE)

namespace cxl {

    typedef std::vector<TCHAR> tbuffer;
    typedef std::vector<char> cbuffer;
    typedef std::vector<wchar_t> wbuffer;

#ifdef _UNICODE
    using tstring = std::wstring;
#else
    using tstring = std::string;
#endif

    inline
        void a_to_u(char const *str,
            std::wstring *dst,
            UINT codepage,
            DWORD flags) {
        DWORD size = ::MultiByteToWideChar(codepage, flags, str, -1, NULL, 0);
        if (size) {
            wbuffer buffer(size + 2, L'\0');
            size = ::MultiByteToWideChar(codepage, flags, str, -1, &buffer[0], size + 1);
            if (size) {
                *dst = &buffer[0];
            }
        }
        if (!size) {
            throw std::exception("MultiByteToWideChar");
        }
    }

    inline
        void a_to_u(std::string const &str,
            std::wstring *dst,
            UINT codepage,
            DWORD flags) {
        a_to_u(str.c_str(),
            dst,
            codepage,
            flags);
    }

    inline
        void u_to_a(wchar_t const *str,
            std::string *dst,
            UINT codepage,
            DWORD flags,
            char const *default_char,
            bool *is_default_used)
    {

        BOOL is_default_used_tmp = FALSE;
        DWORD size = ::WideCharToMultiByte(codepage, flags, str, -1, NULL, 0, NULL, NULL);
        if (size) {
            cbuffer buffer(size + 2, '\0');
            size = ::WideCharToMultiByte(codepage, flags, str, -1, &buffer[0], size + 1, default_char, &is_default_used_tmp);
            if (size) {
                *dst = &buffer[0];
            }
        }
        if (!size) {
            throw std::exception("WideCharToMultiByte");
        }
        if (is_default_used) {
            *is_default_used = CPPBOOL(is_default_used_tmp);
        }
    }

    inline
        void u_to_a(std::wstring const &str,
            std::string *dst,
            UINT codepage,
            DWORD flags,
            char const *default_char,
            bool *is_default_used) {
        u_to_a(str.c_str(),
            dst,
            codepage,
            flags,
            default_char,
            is_default_used);
    }

    inline
        std::wstring a_to_u(char const *str,
            UINT codepage = CP_ACP,
            DWORD flags = 0) {
        std::wstring dst;
        a_to_u(str, &dst, codepage, flags);
        return dst;
    }

    inline
        std::wstring a_to_u(std::string const &str,
            UINT codepage = CP_ACP,
            DWORD flags = 0) {
        std::wstring dst;
        a_to_u(str, &dst, codepage, flags);
        return dst;
    }

    inline
        std::string u_to_a(wchar_t const *str,
            UINT codepage = CP_ACP,
            DWORD flags = 0,
            char const *default_char = NULL,
            bool *is_default_used = NULL) {
        std::string dst;
        u_to_a(str, &dst, codepage, flags, default_char, is_default_used);
        return dst;
    }

    inline
        std::string u_to_a(std::wstring const &str,
            UINT codepage = CP_ACP,
            DWORD flags = 0,
            char const *default_char = NULL,
            bool *is_default_used = NULL) {
        std::string dst;
        u_to_a(str, &dst, codepage, flags, default_char, is_default_used);
        return dst;
    }

#ifdef _UNICODE

    inline
        std::string t_to_a(TCHAR const *str) {
        return u_to_a(str);
    }

    inline
        std::string t_to_a(tstring const &str) {
        return u_to_a(str);
    }

    inline
        tstring a_to_t(char const *str) {
        return a_to_u(str);
    }

    inline
        tstring a_to_t(std::string const &str) {
        return a_to_u(str);
    }


    inline
        std::wstring t_to_w(TCHAR const *str) {
        return str ? std::wstring{ str } : std::wstring{};
    }

    inline
        std::wstring t_to_w(tstring const &str) {
        return str;
    }

    inline
        tstring w_to_t(wchar_t const *str) {
        return str ? tstring{ str } : tstring{};
    }

    inline
        tstring w_to_t(std::wstring const &str) {
        return str;
    }

#else

    inline
        std::wstring t_to_w(TCHAR const *str) {
        return a_to_u(str);
    }

    inline
        std::wstring t_to_w(tstring const &str) {
        return a_to_u(str);
    }

    inline
        tstring w_to_t(wchar_t const *str) {
        return u_to_a(str);
    }

    inline
        tstring a_to_t(std::wstring const &str) {
        return u_to_a(str);
    }

    inline
        std::string t_to_a(TCHAR const *str) {
        return str ? std::string{ str } : std::string{};
    }

    inline
        std::string t_to_a(tstring const &str) {
        return str;
    }

    inline
        tstring a_to_t(char const *str) {
        return str ? tstring{ str } : tstring{};
    }

    inline
        tstring a_to_t(std::string const &str) {
        return str;
    }

#endif

    inline
        void make_lower_case(std::wstring &str) {
        wchar_t* buffer = &str[0];
        size_t count = str.size();
        for (size_t i = 0; i < count; ++i) {
            buffer[i] = towlower(buffer[i]);
        }
    }


    inline
        std::string v_make_string(char const *format, va_list argptr) {
        size_t buffer_size = _vscprintf(format, argptr);

        cbuffer buffer(buffer_size + 1, 0);

        _vsnprintf_s(&buffer[0],
            buffer.size(),
            _TRUNCATE,
            format,
            argptr);

        return std::string(&buffer[0]);
    }

    inline
        std::string make_string(char const *format, ...) {
        va_list argptr;
        va_start(argptr, format);
        return v_make_string(format, argptr);
    }

    inline
        std::wstring v_make_wstring(wchar_t const *format, va_list argptr) {
        size_t buffer_size = _vscwprintf(format, argptr);

        wbuffer buffer(buffer_size + 1, 0);

        _vsnwprintf_s(&buffer[0],
            buffer.size(),
            _TRUNCATE,
            format,
            argptr);

        return std::wstring(&buffer[0]);
    }

    inline
        std::wstring make_wstring(wchar_t const *format, ...) {
        va_list argptr;
        va_start(argptr, format);
        return v_make_wstring(format, argptr);
    }

#ifdef _UNICODE
    inline
        tstring make_tstring(wchar_t const *format, ...) {
        va_list argptr;
        va_start(argptr, format);
        return v_make_wstring(format, argptr);
    }
#else
    inline
        tstring make_tstring(char const *format, ...) {
        va_list argptr;
        va_start(argptr, format);
        return v_make_string(format, argptr);
    }
#endif


    inline
        std::string time_to_string(SYSTEMTIME const &st) {
        return make_string("%04hu\\%02hu\\%02hu %02hu:%02hu:%02hu.%03hu",
            st.wYear,
            st.wMonth,
            st.wDay,
            st.wHour,
            st.wMinute,
            st.wSecond,
            st.wMilliseconds);
    }

    inline
        std::string time_to_string(FILETIME const &ft) {
        SYSTEMTIME st = {};
        FileTimeToSystemTime(&ft, &st);
        return time_to_string(st);
    }

    inline
        std::string time_to_string(LARGE_INTEGER const &l) {
        FILETIME ft = {};
        ft.dwLowDateTime = l.LowPart;
        ft.dwHighDateTime = l.HighPart;
        return time_to_string(ft);
    }

    inline
        std::string time_to_string(long long const &l) {
        LARGE_INTEGER v = {};
        v.QuadPart = l;
        return time_to_string(v);
    }

    inline
        std::string current_time_as_string() {
        FILETIME t;
        GetSystemTimeAsFileTime(&t);
        return time_to_string(t);
    }

    inline
        std::wstring time_to_wstring(SYSTEMTIME const &st) {
        return make_wstring(L"%04hu\\%02hu\\%02hu %02hu:%02hu:%02hu.%03hu",
            st.wYear,
            st.wMonth,
            st.wDay,
            st.wHour,
            st.wMinute,
            st.wSecond,
            st.wMilliseconds);
    }

    inline
        std::wstring time_to_wstring(FILETIME const &ft) {
        SYSTEMTIME st = {};
        FileTimeToSystemTime(&ft, &st);
        return time_to_wstring(st);
    }

    inline
        std::wstring time_to_wstring(LARGE_INTEGER const &l) {
        FILETIME ft = {};
        ft.dwLowDateTime = l.LowPart;
        ft.dwHighDateTime = l.HighPart;
        return time_to_wstring(ft);
    }

    inline
        std::wstring time_to_wstring(long long const &l) {
        LARGE_INTEGER v = {};
        v.QuadPart = l;
        return time_to_wstring(v);
    }

    inline
        std::wstring current_time_as_wstring() {
        FILETIME t;
        GetSystemTimeAsFileTime(&t);
        return time_to_wstring(t);
    }
}

namespace cxl {

    class crt_allocator_base {
    public:

        static void *try_allocate(size_t size) noexcept {
            return ::malloc(size);
        }

        static void *allocate(size_t size) {
            void *block = ::malloc(size);
            if (!block) {
                throw std::bad_alloc{};
            }
            return block;
        }

        static void free(void *block) noexcept {
            ::free(block);
        }

        static void *try_reallocate(void *block, size_t size) noexcept {
            return ::realloc(block, size);
        }

        static void *reallocate(void *block, size_t size) {
            void *new_block = ::realloc(block, size);
            if (!new_block) {
                throw std::bad_alloc{};
            }
            return new_block;
        }
    };

    //
    // TODO:
    //
    using cbuffer = std::vector<char>;

    struct esent_buffer_deleter {
        void operator () (void const *buffer) {
            if (buffer) {
                JET_ERR err = JetFreeBuffer(reinterpret_cast<char *>(const_cast<void *>(buffer)));
                JET_CODDING_ERROR_IF_NOT(JET_errSuccess == err);
            }
        }
    };

    using ecent_instance_info_ptr = std::unique_ptr<JET_INSTANCE_INFO, esent_buffer_deleter>;
    using ecent_instance_info_cptr = std::unique_ptr<JET_INSTANCE_INFO const, esent_buffer_deleter>;

    struct crt_deleter {
        void operator () (void const *buffer) {
            if (buffer) {
                crt_allocator_base::free(reinterpret_cast<void *>(const_cast<void *>(buffer)));
            }
        }
    };

    template <typename T>
    using crt_unique_ptr = std::unique_ptr<T, crt_deleter>;

    struct ecent_instances_info {
        unsigned long count{ 0 };
        ecent_instance_info_cptr info;
    };

    using ecent_error_info_ptr = std::unique_ptr<JET_ERRINFOBASIC_W>;
    using ecent_error_info_cptr = std::unique_ptr<JET_ERRINFOBASIC_W const>;

    struct esent_empty_t {};

    __declspec(selectany) esent_empty_t esent_empty;

    template <typename T> struct remove_optional { using type = T; };
    template <typename T> struct remove_optional<std::optional<T>> { using type = T; };

    template <typename T>
    using remove_optional_t = typename remove_optional<T>::type;

    template <typename T> struct esent_remove_uptr { using type = T; };
    template <typename T> struct esent_remove_uptr<std::unique_ptr<T>> { using type = T; };

    template <typename T>
    using esent_remove_uptr_t = typename esent_remove_uptr<T>::type;

    template <typename T> struct esent_nullable_type : public std::false_type {
        enum { value = 0 };
        static inline T const default_value{};
    };
    template <typename T> struct esent_nullable_type<std::optional<T>> : public std::true_type {
        enum { value = 1 };
        static inline std::nullopt_t const null_value;
        static inline std::optional<T> const default_value;
    };
    template <typename T> struct esent_nullable_type<std::unique_ptr<T>> : public std::true_type {
        enum { value = 1 };
        static inline std::unique_ptr<T> const null_value;
        static inline std::unique_ptr<T> const default_value;
    };
    template <> struct esent_nullable_type<std::string> : public std::true_type {
        enum { value = 1 };
        static inline std::string const null_value;
        static inline std::string const default_value;
    };
    template <> struct esent_nullable_type<std::wstring> : public std::true_type {
        enum { value = 1 };
        static inline std::wstring const null_value;
        static inline std::wstring const default_value;
    };
    template <> struct esent_nullable_type<cxl::cbuffer> : public std::true_type {
        enum { value = 1 };
        static inline cxl::cbuffer const null_value;
        static inline cxl::cbuffer const default_value;
    };

    template <typename T >
    bool esent_nullable_type_v = esent_nullable_type<T>::value;
}

