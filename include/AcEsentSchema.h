#pragma once

namespace ac {

    //#define JET_coltypNil               0
    //#define JET_coltypBit               1    /* True, False, or NULL */
    //#define JET_coltypUnsignedByte      2    /* 1-byte integer, unsigned */
    //#define JET_coltypShort             3    /* 2-byte integer, signed */
    //#define JET_coltypLong              4    /* 4-byte integer, signed */
    //#define JET_coltypCurrency          5    /* 8 byte integer, signed */
    //#define JET_coltypIEEESingle        6    /* 4-byte IEEE single precision */
    //#define JET_coltypIEEEDouble        7    /* 8-byte IEEE double precision */
    //#define JET_coltypDateTime          8    /* Integral date, fractional time */
    //#define JET_coltypBinary            9    /* Binary data, < 255 bytes */
    //#define JET_coltypText             10    /* ANSI text, case insensitive, < 255 bytes */
    //#define JET_coltypLongBinary       11    /* Binary data, long value */
    //#define JET_coltypLongText         12    /* ANSI text, long value */
    //#define JET_coltypUnsignedLong     14    /* 4-byte unsigned integer */
    //#define JET_coltypLongLong         15    /* 8-byte signed integer */
    //#define JET_coltypGUID             16    /* 16-byte globally unique identifier */
    //#define JET_coltypUnsignedShort    17    /* 2-byte unsigned integer */
    //#define JET_coltypUnsignedLongLong 18    /* 8-byte unsigned integer */

    #define JET_coltypEmpty      0xFFFFFFFF

    template<int ESENT_COL_TYPE_IT> struct esent_col_type_id;
    template<> struct esent_col_type_id<JET_coltypEmpty>            { using type = esent_empty_t; };      // 
    template<> struct esent_col_type_id<JET_coltypNil>              { using type = std::nullptr_t; };     // 
    template<> struct esent_col_type_id<JET_coltypBit>              { using type = bool; };               // True, False, or NULL
    template<> struct esent_col_type_id<JET_coltypUnsignedByte>     { using type = unsigned char; };      // 1-byte integer, unsigned
    template<> struct esent_col_type_id<JET_coltypShort>            { using type = short; };              // 2-byte integer, signed
    template<> struct esent_col_type_id<JET_coltypLong>             { using type = long; };               // 4-byte integer, signed
    template<> struct esent_col_type_id<JET_coltypCurrency>         { using type = long long; };          // 8 byte integer, signed
    template<> struct esent_col_type_id<JET_coltypIEEESingle>       { using type = double; };             // 4-byte IEEE single precision
    template<> struct esent_col_type_id<JET_coltypIEEEDouble>       { using type = float; };              // 8-byte IEEE double precision
    template<> struct esent_col_type_id<JET_coltypBinary>           { using type = cbuffer; };            // Binary data, < 255 bytes
    template<> struct esent_col_type_id<JET_coltypText>             { using type = std::string; };        // ANSI text, case insensitive, < 255 bytes
    template<> struct esent_col_type_id<JET_coltypLongBinary>       { using type = cbuffer; };            // Binary data, long value
    template<> struct esent_col_type_id<JET_coltypLongText>         { using type = std::string;};         // ANSI text, long value
    template<> struct esent_col_type_id<JET_coltypUnsignedLong>     { using type = unsigned long; };      // 4-byte unsigned integer
    template<> struct esent_col_type_id<JET_coltypLongLong>         { using type = long long; };          // 8-byte signed integer
    template<> struct esent_col_type_id<JET_coltypGUID>             { using type = GUID; };               // 16-byte globally unique identifier
    template<> struct esent_col_type_id<JET_coltypUnsignedShort>    { using type = unsigned short; };     // 2-byte unsigned integer
    template<> struct esent_col_type_id<JET_coltypUnsignedLongLong> { using type = unsigned long long; }; // 8-byte unsigned integer
    // SYSTEMTIME st; VariantTimeToSystemTime(data, &st), E_FAIL);
    template<> struct esent_col_type_id<JET_coltypDateTime>         { using type = DATE; };               // Integral date, fractional time

    template<typename T> struct esent_cpp_type;
    template<> struct esent_cpp_type<esent_empty_t>      { enum { id = JET_coltypEmpty }; };
    template<> struct esent_cpp_type<std::nullptr_t>     { enum { id = JET_coltypNil }; };
    template<> struct esent_cpp_type<bool>               { enum { id = JET_coltypBit }; };
    template<> struct esent_cpp_type<char>               { enum { id = JET_coltypUnsignedByte }; };
    template<> struct esent_cpp_type<unsigned char>      { enum { id = JET_coltypUnsignedByte }; };
    template<> struct esent_cpp_type<short>              { enum { id = JET_coltypShort }; };
    template<> struct esent_cpp_type<long>               { enum { id = JET_coltypLong }; };
    //template<> struct esent_cpp_type<long long>        { enum { id = JET_coltypCurrency }; };
    template<> struct esent_cpp_type<double>             { enum { id = JET_coltypIEEESingle }; };
    template<> struct esent_cpp_type<float>              { enum { id = JET_coltypIEEEDouble }; };
    template<> struct esent_cpp_type<cbuffer>            { enum { id = JET_coltypBinary }; };
    template<> struct esent_cpp_type<std::string>        { enum { id = JET_coltypText }; };
    template<> struct esent_cpp_type<unsigned long>      { enum { id = JET_coltypUnsignedLong }; };
    template<> struct esent_cpp_type<long long>          { enum { id = JET_coltypLongLong }; };
    template<> struct esent_cpp_type<GUID>               { enum { id = JET_coltypGUID }; };
    template<> struct esent_cpp_type<unsigned short>     { enum { id = JET_coltypUnsignedShort }; };
    template<> struct esent_cpp_type<unsigned long long> { enum { id = JET_coltypUnsignedLongLong }; };
    
    template <typename T> 
    struct esent_cpp_type<std::optional<T>>              { enum { id = esent_cpp_type<T>::id }; };

    template <typename T> using esent_optional = std::optional<T>;
    
    using esent_variant = std::variant<esent_empty_t,
                                       std::nullptr_t,
                                       bool,
                                       char,
                                       short,
                                       long,
                                       long long,
                                       unsigned char,
                                       unsigned short,
                                       unsigned long,
                                       unsigned long long,
                                       float,
                                       double,
                                       GUID,
                                       cbuffer,
                                       std::string>;

    using esent_ovariant = std::variant<esent_empty_t,
                                        std::nullptr_t,
                                        std::optional<bool>,
                                        std::optional<char>,
                                        std::optional<short>,
                                        std::optional<long>,
                                        std::optional<long long>,
                                        std::optional<unsigned char>,
                                        std::optional<unsigned short>,
                                        std::optional<unsigned long>,
                                        std::optional<unsigned long long>,
                                        std::optional<float>,
                                        std::optional<double>,
                                        std::optional<GUID>,
                                        std::optional<cbuffer>,
                                        std::optional<std::string>>;

    using esent_optional_variant = std::optional<esent_variant>;

    struct esent_value_buf {
        int col_type_id{ JET_coltypNil };
        unsigned long buffer_size{ 0 };
        void *buffer{ nullptr };
    };

    typedef void(*esent_set_value_fn_t)(void *container);

    class esent_default_value_buf {
    public:
        esent_default_value_buf() = default;
        esent_default_value_buf(esent_default_value_buf const &) = default;
        esent_default_value_buf(esent_default_value_buf &&) = default;

        esent_default_value_buf(void *container, 
                                esent_set_value_fn_t set_value_fn) 
        : container_(container)
        , set_value_fn_(set_value_fn) {
        }

        esent_default_value_buf &operator= (esent_default_value_buf const &) = default;
        esent_default_value_buf &operator= (esent_default_value_buf &&) = default;

        void clear() {
            container_ = nullptr;
            set_value_fn_ = nullptr;
        }

        void operator()() {
            set_value_fn_(container_);
        }

    private:
        void *container_{ nullptr };
        esent_set_value_fn_t set_value_fn_{ nullptr };

    };

    struct esent_cvalue_buf {
        int col_type_id{ JET_coltypNil };
        unsigned long buffer_size{ 0 };
        void const *buffer{ nullptr };
    };

    template<typename T> 
    struct esent_value {

        static T value(T &v) {
            return v;
        }

        static T &value(T const &v) {
            return v;
        }

        static T &value(T &&v) {
            return std::move(v);
        }

        template <typename V>
        static T value_or(T &v, V &&) {
            return v;
        }

        template <typename V>
        static T &value_or(T const &v, V &&) {
            return v;
        }

        template <typename V>
        static T &value_or(T &&v, V &&) {
            return std::move(v);
        }

        static esent_value_buf value_buffer(T &v) {
            using t_t = std::remove_cv_t<
                            std::remove_reference_t<decltype(v)>
                        >;
            if constexpr (std::is_same_v<T, cbuffer> ||
                          std::is_same_v<T, std::string>) {
                return esent_value_buf{
                    esent_cpp_type<t_t>::id,
                    static_cast<unsigned long>(v.size() * sizeof(v[0])),
                    v.size() ? reinterpret_cast<void *>(&v[0]) : nullptr
                };
            } else if constexpr (std::is_same_v<T, esent_empty_t> ||
                                 std::is_same_v<T, std::nullptr_t>) {
                return esent_value_buf{
                    esent_cpp_type<t_t>::id,
                    0,
                    nullptr
                };
            } else {
                return esent_value_buf{
                    esent_cpp_type<t_t>::id,
                    static_cast<unsigned long>(sizeof(v)),
                    reinterpret_cast<void *>(&v)
                };
            }
        }

        static esent_cvalue_buf value_buffer(T const &v) {
            using t_t = std::remove_cv_t<
                            std::remove_reference_t<decltype(v)>
                        >;
            if constexpr (std::is_same_v<T, cbuffer> ||
                          std::is_same_v<T, std::string>) {
                return esent_cvalue_buf{
                    esent_cpp_type<t_t>::id,
                    static_cast<unsigned long>(v.size() * sizeof(v[0])),
                    v.size() ? reinterpret_cast<void const *>(&v[0]) : nullptr
                };
            } else if constexpr (std::is_same_v<T, esent_empty_t> ||
                                 std::is_same_v<T, std::nullptr_t>) {
                return esent_cvalue_buf{
                    esent_cpp_type<t_t>::id,
                    0,
                    nullptr
                };
            } else {
                return esent_cvalue_buf{
                    esent_cpp_type<t_t>::id,
                    static_cast<unsigned long>(sizeof(v)),
                    reinterpret_cast<void const *>(&v)
                };
            }
        }
    };

    template<typename T>
    struct esent_value<std::optional<T>> {

        static T value(std::optional<T> &v) {
            return v.value();
        }

        static T &value(std::optional<T> const &v) {
            return v.value();
        }

        static T &value(std::optional<T> &&v) {
            return std::move(v).value();
        }

        template <typename V>
        static T value_or(std::optional<T> &v, V &&deault_value) {
            return v.value_or(std::forward(deault_value));
        }

        template <typename V>
        static T &value_or(std::optional<T> const &v, V &&deault_value) {
            return v.value_or(std::forward(deault_value));
        }

        template <typename V>
        static T &value_or(std::optional<T> &&v, V &&deault_value) {
            return std::move(v).value_or(std::forward(deault_value));
        }

        static esent_value_buf value_buffer(std::optional<T> &v) {
            using t_t = std::remove_cv_t<
                            std::remove_reference_t<decltype(v)>
                        >;
            if constexpr (std::is_same_v<T, esent_empty_t> ||
                          std::is_same_v<T, std::nullptr_t>) {
                return esent_cvalue_buf{ esent_cpp_type<t_t>::id,
                                         0,
                                         nullptr};
            } else {
                if (v) {
                    return esent_value<T>::value_buffer(v.value());
                }
            }
            return esent_value_buf{ JET_coltypNil };
        }

        static esent_cvalue_buf value_buffer(std::optional<T> const &v) {
            using t_t = std::remove_cv_t<
                            std::remove_reference_t<decltype(v)>
                        >;
            if constexpr (std::is_same_v<T, esent_empty_t> ||
                          std::is_same_v<T, std::nullptr_t>) {
                return esent_cvalue_buf{ esent_cpp_type<t_t>::id,
                                         0,
                                         nullptr };
            } else {
                if (v) {
                    return esent_value<T>::value_buffer(v.value());
                }
            }
            return esent_cvalue_buf{ JET_coltypNil };
        }

    };

    inline
    int esent_variant_to_col_type_id(esent_variant const &v) {
        int col_type_id{ JET_coltypNil };
        std::visit([&col_type_id](auto const &v) {
            using t_t = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
            col_type_id = esent_cpp_type<t_t>::id;
        },
        v);
        return col_type_id;
    }

    inline
    int esent_variant_to_col_type_id(esent_ovariant const &v) {
        int col_type_id{ JET_coltypNil };
        std::visit([&col_type_id](auto const &v) {
            using t_t = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
            col_type_id = esent_cpp_type<t_t>::id;
        },
        v);
        return col_type_id;
    }

    template <typename T>
    esent_cvalue_buf get_esent_value_buf(T const &v) {
        using t_t = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
        return esent_value<t_t>::value_buffer(v);
    }

    template <typename T>
    esent_value_buf get_esent_value_buf(T &v) {
        using t_t = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
        return esent_value<std::remove_cv_t<std::remove_reference_t<decltype(v)>>>::value_buffer(v);
    }

    inline
    esent_cvalue_buf get_esent_value_buf(esent_variant const &var) {
        esent_cvalue_buf value_buf;
        std::visit([&value_buf](auto const &val) {
            value_buf = get_esent_value_buf(val);
        },
        var);
        return value_buf;
    }

    inline
    esent_value_buf get_esent_value_buf(esent_variant &var) {
        esent_value_buf value_buf;
        std::visit([&value_buf](auto &val) {
            value_buf = get_esent_value_buf(val);
        },
        var);
        return value_buf;
    }

    inline
    esent_cvalue_buf get_esent_value_buf(esent_ovariant const &var) {
        esent_cvalue_buf value_buf;
        std::visit([&value_buf](auto const &val) {
            value_buf = get_esent_value_buf(val);
        },
        var);
        return value_buf;
    }

    inline
    esent_value_buf get_esent_value_buf(esent_ovariant &var) {
        esent_value_buf value_buf;
        std::visit([&value_buf](auto &val) {
            value_buf = get_esent_value_buf(val);
        },
        var);
        return value_buf;
    }
}

#define ESENT_INIT_DEFAULT_VALUE_BUFFER(CONTAINER, VALUE) \
[&CONTAINER]()->ac::esent_default_value_buf { \
    using esent_container_ptr_t = decltype(std::addressof(CONTAINER)); \
    return ac::esent_default_value_buf{ \
        reinterpret_cast<void *>(std::addressof(CONTAINER)), \
        static_cast<ac::esent_set_value_fn_t>([](void *container) { \
            *reinterpret_cast<esent_container_ptr_t>(container) = (VALUE); \
        }) \
    }; \
}()
