#pragma once
//
// Define enumiration in jet namespace
//
namespace ac {
    //
    // error code enumiration
    //
    enum class esent_err : int {
#define ESENT_SUCCESS_ENTRY(symbol, code, str) err##symbol = JET_err##symbol,
#define ESENT_ERR_ENTRY(symbol, code, str) err##symbol = JET_err##symbol,
#define ESENT_WRN_ENTRY(symbol, code, str) wrn##symbol = JET_wrn##symbol,
#define ESENT_WRN_ENTRY_SHORT(symbol, code, str) wrns##symbol = wrn##symbol,
#define ESENT_ALIASE_ERR_ENTRY(symbol1, symbol2)
#define ESENT_ALIASE_WRN_ENTRY(symbol1, symbol2)
#include "AcEsentErrors.inc"
#undef ESENT_SUCCESS_ENTRY
#undef ESENT_ERR_ENTRY
#undef ESENT_WRN_ENTRY
#undef ESENT_WRN_ENTRY_SHORT
#undef ESENT_ALIASE_ERR_ENTRY
#undef ESENT_ALIASE_WRN_ENTRY
    };
    //
    // Error conditions enumeration
    //
    // JET_errcatError
    //    |
    //    |-- JET_errcatOperation
    //    |     |-- JET_errcatFatal
    //    |     |-- JET_errcatIO                //  bad IO issues, may or may not be transient.
    //    |     |-- JET_errcatResource
    //    |           |-- JET_errcatMemory      //  out of memory (all variants)
    //    |           |-- JET_errcatQuota   
    //    |           |-- JET_errcatDisk        //  out of disk space (all variants)
    //    |-- JET_errcatData
    //    |     |-- JET_errcatCorruption
    //    |     |-- JET_errcatInconsistent      //  typically caused by user Mishandling
    //    |     |-- JET_errcatFragmentation
    //    |-- JET_errcatApi
    //          |-- JET_errcatUsage
    //          |-- JET_errcatState
    //
    // Or
    //
    // parentCategory      --> childCategory
    // JET_errcatError     --> JET_errcatOperation
    // JET_errcatError     --> JET_errcatData
    // JET_errcatError     --> JET_errcatApi
    // JET_errcatOperation --> JET_errcatFatal
    // JET_errcatOperation --> JET_errcatIO
    // JET_errcatOperation --> JET_errcatResource
    // JET_errcatResource  --> JET_errcatMemory
    // JET_errcatResource  --> JET_errcatQuota
    // JET_errcatResource  --> JET_errcatDisk
    // JET_errcatData      --> JET_errcatCorruption
    // JET_errcatData      --> JET_errcatMishandling
    // JET_errcatData      --> JET_errcatFragmentation
    // JET_errcatApi       --> JET_errcatUsage
    // JET_errcatApi       --> JET_errcatState
    // JET_errcatApi       --> JET_errcatObsolete
    //
    enum class esent_err_category : int {
        unknown       = JET_errcatUnknown, // unknown, error retrieving err category
        error         = JET_errcatError,   // top level (no errors should be of this class)
        operation     = JET_errcatOperation,
        fatal         = JET_errcatFatal,
        io            = JET_errcatIO,      // bad IO issues, may or may not be transient.
        resource      = JET_errcatResource,
        memory        = JET_errcatMemory,  // out of memory (all variants)
        quota         = JET_errcatQuota,
        disk          = JET_errcatDisk,    // out of disk space (all variants)
        data          = JET_errcatData,
        corruption    = JET_errcatCorruption,
        inconsistent  = JET_errcatInconsistent, //  typically caused by user Mishandling
        fragmentation = JET_errcatFragmentation,
        api           = JET_errcatApi,
        usage         = JET_errcatUsage,
        state         = JET_errcatState,
        obsolete      = JET_errcatObsolete,
        max           = JET_errcatMax,
    };

    enum class esent_err_severity : int {
        success = 0, // JET_errSuccess
        warning = 1, // JET_wrn*, excluding JET_wrnNyi
        error   = 3, // JET_err*, including JET_wrnNyi
    };
}

//
// Mapping of enumerations to error code or error condition
//
namespace std {
    //
    // declare that enumiration is an error code, NOT an
    // error condition
    //
    template <>
    struct is_error_code_enum<ac::esent_err> : public true_type {};
    //
    // JET_ERR is defined as long
    // 
    // template <>
    // struct is_error_code_enum<JET_ERR> : public true_type {};

    template <>
    struct is_error_condition_enum<JET_ERRCAT> : public true_type {};

    template <>
    struct is_error_condition_enum<ac::esent_err_category> : public true_type {};

    template <>
    struct is_error_condition_enum<ac::esent_err_severity> : public true_type {};
}

std::error_category const &esent_error_category() noexcept;
std::error_category const &esent_error_condition_category() noexcept;
std::error_category const &esent_error_severity_category() noexcept;

namespace ac {

    class esent_error_severity_category_t
        : public std::error_category {
    public:

        virtual char const* name() const noexcept override {
            return "ac_esent_error_severity";
        }

        static bool is_error_severity(int err, int severity);

        virtual std::string message(int e) const override;
        //
        // Maping between this error condition and any error category
        //
        virtual bool equivalent(const std::error_code& e, int cond) const noexcept {
            return e.category() == esent_error_category() &&
                   is_error_severity(e.value(), cond);
        }

        static esent_error_severity_category_t const esent_error_condition_severity_singleton;
    };

    inline
    std::error_condition make_error_condition(esent_err_severity e) {
        return std::error_condition(static_cast<int>(e),
                                    esent_error_severity_category());
    }

    /*inline 
    bool is_esent_severity(int err, esent_err_severity severity) {
        return esent_error_severity_category_t::is_error_severity(err, static_cast<int>(severity));
    }*/

    inline
    bool is_esent_severity(std::error_code const &err, esent_err_severity severity) {
        return esent_error_severity_category_t::is_error_severity(err.value(), static_cast<int>(severity));
    }
    
    class esent_error_condition_category_t
        : public std::error_category {
    public:

        virtual char const* name() const noexcept override {
            return "ac_esent_error_category";
        }
        //
        // query information about Jet error category
        //
        static JET_ERRINFOBASIC_W get_erorr_info(JET_ERR error);

        static JET_ERRINFOBASIC_W get_erorr_info(esent_err error) {
            return get_erorr_info(static_cast<int>(error));
        }

        static bool is_error_condition(int err, int cond);

        virtual std::string message(int e) const override;
        //
        // Maping between this error condition and any error category
        //
        virtual bool equivalent(const std::error_code& e, int cond) const noexcept {
            return e.category() == esent_error_category() && 
                   is_error_condition(e.value(), cond);
        }

        static esent_error_condition_category_t const esent_error_condition_category_singleton;
    };

    inline
    std::error_condition make_error_condition(esent_err_category e) {
        return std::error_condition(static_cast<int>(e),
                                    esent_error_condition_category());
    }

    inline
    std::error_condition make_error_condition(JET_ERRCAT e) {
        return std::error_condition(static_cast<int>(e),
                                    esent_error_condition_category());
    }

    //
    // Define error category for Esent errors
    //
    class esent_error_category_t 
        : public std::error_category {
    public:

        virtual char const* name() const noexcept override {
            return "ac_esent_error";
        }
        //
        // Converts Jet error to HRESULT
        //
        static HRESULT to_hr(long err);

        static HRESULT to_hr(esent_err e) {
            return static_cast<long>(e);
        }

        //
        // Returns a string with symbolic name of error 
        // for instance "JET_wrnUniqueKey"
        //
        static std::string message_short(esent_err e);
        //
        // Returns human readable string for an error
        // for instance "seek on non-unique index yielded a unique key"
        //
        static std::string message_human(esent_err e);
        //
        // Returns a streans that us a combination of human readable 
        // streang and symbolic name for an error.
        // for instance "JET_wrnUniqueKey. seek on non-unique index yielded a unique key"
        //
        static std::string message_long(esent_err e);

        virtual std::string message(int e) const override {
            return message_long(static_cast<esent_err>(e));
        }
        //
        // Mapping to default error conditions
        //
        virtual std::error_condition default_error_condition(int e) const noexcept override {
            JET_ERRINFOBASIC_W errInfo = esent_error_condition_category_t::get_erorr_info(e);
            return std::error_condition(static_cast<int>(errInfo.errcatMostSpecific), 
                                        esent_error_condition_category());
        }
        //
        // Mapping between error codes in this error category with any error conditions
        //
        virtual bool equivalent(int e, const std::error_condition& cond) const noexcept {
            return (cond.category() == esent_error_condition_category() && 
                    esent_error_condition_category_t::is_error_condition(e, cond.value())) 
                    || 
                   (cond.category() == esent_error_severity_category() &&
                    esent_error_severity_category_t::is_error_severity(e, cond.value()));
        }

        static esent_error_category_t const esent_error_category_singleton;
    };

    inline
    std::error_code make_error_code(esent_err e) {
        return std::error_code(static_cast<JET_ERR>(e), 
                               esent_error_category());
    }
}

inline
std::error_code make_esent_error_code(JET_ERR e) {
    return std::error_code(e, esent_error_category());
}

inline
std::error_code make_esent_error_condition(ac::esent_err_category e) {
    return std::error_code(static_cast<int>(e), 
                           esent_error_condition_category());
}

inline
std::error_code make_esent_error_condition(JET_ERRCAT e) {
    return std::error_code(static_cast<int>(e), 
                           esent_error_condition_category());
}

inline
std::error_code make_esent_error_severity(ac::esent_err_severity e) {
    return std::error_code(static_cast<int>(e),
                           esent_error_severity_category());
}

//
// Helpers to raise std::system_error with esent_error_category
//
#define ESENT_THROW(__err, __reason) \
    throw std::system_error{(__err), (__reason)}

#define ESENT_THROW_FMT(__err, __fmt, ...) \
    throw std::system_error{(__err), ac::make_string((__fmt), __VA_ARGS__).c_str()}

#define ESENT_THROW_IF(__condition, __err, __reason) \
    if (!(__condition)) ; else throw std::system_error{(__err), (__reason)}

#define ESENT_THROW_IF_FMT(__condition, __err, __fmt, ...) \
    if (!(__condition)) ; else throw std::system_error{(__err), ac::make_string((__fmt), __VA_ARGS__).c_str()};

#define ESENT_THROW_ON_ERROR(__err, __reason) \
    if (!ac::is_esent_severity((__err), ac::esent_err_severity::error)) ; else throw std::system_error{(__err), (__reason)}

#define ESENT_THROW_ON_ERROR_FMT(__err, __fmt, ...) \
    if (!ac::is_esent_severity((__err), ac::esent_err_severity::error)) ; else throw std::system_error{(__err), ac::make_string((__fmt), __VA_ARGS__).c_str()}

#define ESENT_RETURN_ON_ERROR(__err) if ((__err) == esent_err_severity::error) {return (__err);} else {}
