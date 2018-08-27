#include "CxlEsent.h"

namespace cxl {

    esent_error_severity_category_t const esent_error_severity_category_t::esent_error_condition_severity_singleton;

    std::string esent_error_severity_category_t::message(int e) const {
        std::string msg;
        switch (static_cast<esent_err_severity>(e)) {
        case esent_err_severity::success: msg = "succes"; break;
        case esent_err_severity::warning: msg = "warning"; break;
        case esent_err_severity::error: msg = "error"; break;
        default: msg = make_string("%i_unrecognized_esent_error_severity", e); break;
        }
        return msg;
    }

    bool esent_error_severity_category_t::is_error_severity(int err, int severity) {
        switch (static_cast<esent_err_severity>(severity)) {
        case esent_err_severity::success: return err == JET_errSuccess;
        case esent_err_severity::warning: return err > 0;
        case esent_err_severity::error: return err < 0;
        }
        return false;
    }

    esent_error_condition_category_t const esent_error_condition_category_t::esent_error_condition_category_singleton;

    std::string esent_error_condition_category_t::message(int e) const {
        std::string msg;
        switch (static_cast<esent_err_category>(e)) {
        case esent_err_category::unknown: msg = "JET_errcatUnknown. Unknown, error retrieving err category"; break;
        case esent_err_category::error: msg = "JET_errcatError. Top level (no errors should be of this class)"; break;
        case esent_err_category::operation: msg = "JET_errcatOperation"; break;
        case esent_err_category::fatal: msg = "JET_errcatFatal"; break;
        case esent_err_category::io: msg = "JET_errcatIO. Bad IO issues, may or may not be transient."; break;
        case esent_err_category::resource: msg = "JET_errcatResource"; break;
        case esent_err_category::memory: msg = "JET_errcatMemory. Out of memory (all variants)"; break;
        case esent_err_category::quota: msg = "JET_errcatQuota"; break;
        case esent_err_category::disk: msg = "JET_errcatDisk. Out of disk space (all variants)"; break;
        case esent_err_category::data: msg = "JET_errcatData"; break;
        case esent_err_category::corruption: msg = "JET_errcatCorruption"; break;
        case esent_err_category::inconsistent: msg = "JET_errcatInconsistent. Typically caused by user mishandling"; break;
        case esent_err_category::fragmentation: msg = "JET_errcatFragmentation"; break;
        case esent_err_category::api: msg = "JET_errcatApi"; break;
        case esent_err_category::usage: msg = "JET_errcatUsage"; break;
        case esent_err_category::state: msg = "JET_errcatState"; break;
        case esent_err_category::obsolete: msg = "JET_errcatObsolete"; break;
        case esent_err_category::max: msg = "JET_errcatMax"; break;
        default: msg = make_string("%i_unrecognized_esent_error_category", e); break;
        }
        return msg;
    }

    JET_ERRINFOBASIC_W esent_error_condition_category_t::get_erorr_info(JET_ERR error) {

        JET_ERRINFOBASIC_W info;

        JET_ERR err = JetGetErrorInfoW(reinterpret_cast<void *>(&error),
                                       &info,
                                       sizeof(info),
                                       JET_ErrorInfoSpecificErr,
                                       0);

        if (JET_errSuccess != err) {
            memset(&info, 0, sizeof(info));
        }

        return info;
    }

    bool esent_error_condition_category_t::is_error_condition(int err, int cond) {
        JET_ERRINFOBASIC_W errInfo = get_erorr_info(err);
        if (cond == errInfo.errcatMostSpecific) {
            return true;
        } else {
            for (size_t i = 0;
                i < std::size(errInfo.rgCategoricalHierarchy) &&
                JET_errcatUnknown != errInfo.rgCategoricalHierarchy[i];
                ++i) {

                if (cond == errInfo.rgCategoricalHierarchy[i]) {
                    return true;
                }
            }
        }
        return false;
    }


    std::string esent_error_category_t::message_short(esent_err e) {
        switch (e) {
#define ESENT_STRINGIFY(s) #s
#define ESENT_SUCCESS_ENTRY(symbol, code, str) case esent_err::err##symbol : return std::string(ESENT_STRINGIFY(JET_err##symbol));
#define ESENT_ERR_ENTRY(symbol, code, str) case esent_err::err##symbol : return std::string(ESENT_STRINGIFY(JET_err##symbol));
#define ESENT_WRN_ENTRY(symbol, code, str) case esent_err::wrn##symbol : return std::string(ESENT_STRINGIFY(JET_wrn##symbol));
#define ESENT_WRN_ENTRY_SHORT(symbol, code, str) case esent_err::wrns##symbol : return std::string(ESENT_STRINGIFY(wrn##symbol));
#define ESENT_ALIASE_ERR_ENTRY(symbol1, symbol2)
#define ESENT_ALIASE_WRN_ENTRY(symbol1, symbol2)
#include "CxlEsentErrors.inc"
#undef ESENT_SUCCESS_ENTRY
#undef ESENT_ERR_ENTRY
#undef ESENT_WRN_ENTRY
#undef ESENT_WRN_ENTRY_SHORT
#undef ESENT_ALIASE_ERR_ENTRY
#undef ESENT_ALIASE_WRN_ENTRY
#undef ESENT_STRINGIFY
        }
        return make_string("%i_unrecognized_esent_error", static_cast<int>(e));
    }

    std::string esent_error_category_t::message_human(esent_err e) {
        switch (e) {
#define ESENT_STRINGIFY(s) #s
#define ESENT_SUCCESS_ENTRY(symbol, code, str) case esent_err::err##symbol : return std::string(str);
#define ESENT_ERR_ENTRY(symbol, code, str) case esent_err::err##symbol : return std::string(str);
#define ESENT_WRN_ENTRY(symbol, code, str) case esent_err::wrn##symbol : return std::string(str);
#define ESENT_WRN_ENTRY_SHORT(symbol, code, str) case esent_err::wrns##symbol : return std::string(str);
#define ESENT_ALIASE_ERR_ENTRY(symbol1, symbol2)
#define ESENT_ALIASE_WRN_ENTRY(symbol1, symbol2)
#include "CxlEsentErrors.inc"
#undef ESENT_SUCCESS_ENTRY
#undef ESENT_ERR_ENTRY
#undef ESENT_WRN_ENTRY
#undef ESENT_WRN_ENTRY_SHORT
#undef ESENT_ALIASE_ERR_ENTRY
#undef ESENT_ALIASE_WRN_ENTRY
#undef ESENT_STRINGIFY
        }
        return make_string("%i_unrecognized_esent_error", static_cast<int>(e));
    }

    std::string esent_error_category_t::message_long(esent_err e) {
        switch (e) {
#define ESENT_STRINGIFY(s) #s
#define ESENT_SUCCESS_ENTRY(symbol, code, str) case esent_err::err##symbol : return std::string(ESENT_STRINGIFY(JET_err##symbol) ". " str);
#define ESENT_ERR_ENTRY(symbol, code, str) case esent_err::err##symbol : return std::string(ESENT_STRINGIFY(JET_err##symbol) ". " str);
#define ESENT_WRN_ENTRY(symbol, code, str) case esent_err::wrn##symbol : return std::string(ESENT_STRINGIFY(JET_wrn##symbol) ". " str);
#define ESENT_WRN_ENTRY_SHORT(symbol, code, str) case esent_err::wrns##symbol : return std::string(ESENT_STRINGIFY(wrn##symbol) ". " str);
#define ESENT_ALIASE_ERR_ENTRY(symbol1, symbol2)
#define ESENT_ALIASE_WRN_ENTRY(symbol1, symbol2)
#include "CxlEsentErrors.inc"
#undef ESENT_SUCCESS_ENTRY
#undef ESENT_ERR_ENTRY
#undef ESENT_WRN_ENTRY
#undef ESENT_WRN_ENTRY_SHORT
#undef ESENT_ALIASE_ERR_ENTRY
#undef ESENT_ALIASE_WRN_ENTRY
#undef ESENT_STRINGIFY
        }
        return make_string("%i_unrecognized_esent_error", static_cast<int>(e));
    }

    HRESULT esent_error_category_t::to_hr(long err) {
        long const FACILITY_JET_ERR{ 0xE5E };
        HRESULT hr = S_OK;
        if (err != JET_errSuccess) {
            if (err == JET_errOutOfMemory) {
                hr = E_OUTOFMEMORY;
            } else {
                hr = MAKE_HRESULT(err < 0 ? SEVERITY_ERROR 
                                          : SEVERITY_SUCCESS,
                                  FACILITY_JET_ERR,
                                  (err < 0 ? - err : err) & 0xFFFF);
            }
        }
        return hr;
    }

    esent_error_category_t const esent_error_category_t::esent_error_category_singleton;
}

std::error_category const &esent_error_severity_category() noexcept {
    return cxl::esent_error_severity_category_t::esent_error_condition_severity_singleton;
}

std::error_category const &esent_error_condition_category() noexcept {
    return cxl::esent_error_condition_category_t::esent_error_condition_category_singleton;
}

std::error_category const &esent_error_category() noexcept {
    return cxl::esent_error_category_t::esent_error_category_singleton;
}


