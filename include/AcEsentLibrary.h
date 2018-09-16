#pragma once

namespace ac {

    enum class esent_set_mode : int {
        default,
        must_succeed,                   // Setting this parameter must succeed (including not have been previously set)
        failure_ok_if_equal,            // Setting this parameter must succeed (doesn't matter if previously set to same value, only allowed for numeric values, not strings)
        failure_ok_if_equal_or_greater, // Setting this parameter must succeed (doesn't matter if previously set to same or larger value, only allowed for numeric values, not strings)
        ignore_failure,                 // Don't care if setting this parameter succeeds
    };

    struct esent_parameter : JET_SETSYSPARAM {
        esent_parameter() = default;
        esent_parameter(esent_parameter const &) = default;
        esent_parameter(esent_parameter &&) = default;
        esent_parameter &operator= (esent_parameter const &) = default;
        esent_parameter &operator= (esent_parameter &&) = default;

        static unsigned long const max_sessions{ 32 };
        static unsigned long const max_cursors{ 40 };              // Only allow nesting of 40 transaction layers
        static unsigned long const database_page_size{ 8 * 1024 }; // 8k page size
        static unsigned long const log_file_size_in_kb{ 512 };     // 512k log files
        static unsigned long const cache_size{ 512 };              // 512k cache size (in db pages)
        static unsigned long const max_jet_sessions = 30000;
        static unsigned long const max_jet_open_tables = (max_jet_sessions * 10);


        esent_parameter(unsigned long parameter_id,
                        JET_API_PTR number_value,
                        TCHAR const *string_value) 
        : JET_SETSYSPARAM{ parameter_id,
                           number_value,
                           string_value,
                           JET_errSuccess} {
        }

        esent_parameter(unsigned long parameter_id,
                        JET_API_PTR number_value) 
        : JET_SETSYSPARAM{ parameter_id,
                           number_value,
                           nullptr,
                           JET_errSuccess} {
        }

        esent_parameter(unsigned long parameter_id,
                        TCHAR const *string_value)
        : JET_SETSYSPARAM{ parameter_id,
                           0,
                           string_value,
                           JET_errSuccess} {
        }
    };

    //using esent_system_parameter_value = std::variant<unsigned long, tstring>;

    //
    // By default Esent is in single instance mode.
    // always call this function to enable multiinstance 
    // optionally set ste-sys-param if you want to set some
    // parameters that should apply to all instances.
    // Only sys-params from first caller are stored.
    //
    class esent_library {
    public:

        esent_library() = delete;
        ~esent_library() = delete;

        static std::error_code try_init();
        static void init();

        static std::error_code try_enable_multiple_instances(JET_SETSYSPARAM* psetsysparam = nullptr,
                                                             unsigned long csetsysparam = 0,
                                                             unsigned long* pcsetsucceed = nullptr) noexcept {

            std::error_code err = make_esent_error_code(
                JetEnableMultiInstance(psetsysparam,
                                       csetsysparam,
                                       pcsetsucceed ));
            return err;
        }

        static bool enable_multiple_instances(JET_SETSYSPARAM* psetsysparam = nullptr,
                                              unsigned long csetsysparam = 0,
                                              unsigned long* pcsetsucceed = nullptr) {

            std::error_code err = make_esent_error_code(
                JetEnableMultiInstance(psetsysparam,
                                       csetsysparam,
                                       pcsetsucceed ));

            if (esent_err::errSystemParamsAlreadySet == err) {
                return false;
            }

            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetEnableMultiInstance(%u) failed",
                                     csetsysparam);
            return true;
        }

       static std::error_code try_get_instances_info(ecent_instances_info &info) noexcept {
            unsigned long count{ 0 };
            JET_INSTANCE_INFO *ptr{ nullptr };
            std::error_code err = make_esent_error_code(JetGetInstanceInfo(&count, &ptr));
            if (esent_err::errSuccess == err) {
                info.count = count;
                info.info.reset(ptr);
            }
            return err;
        }
         
        static ecent_instances_info get_instances_info() {
            ecent_instances_info info;
            std::error_code err = try_get_instances_info(info);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetGetInstanceInfo failed");
            return info;
        }

        static std::error_code try_set_system_parameter(JET_INSTANCE instance_id,
                                                        JET_SESID session_id,
                                                        ULONG const parameter_id,
                                                        JET_API_PTR number_value,
                                                        TCHAR const *string_value,
                                                        esent_set_mode set_mode = esent_set_mode::default);

        static void set_system_parameter(JET_INSTANCE instance_id,
                                         JET_SESID session_id,
                                         ULONG parameter_id,
                                         JET_API_PTR number_value,
                                         TCHAR const *string_value,
                                         esent_set_mode set_mode = esent_set_mode::default) {

            std::error_code err = try_set_system_parameter(instance_id,
                                                           session_id,
                                                           parameter_id,
                                                           number_value,
                                                           string_value,
                                                           set_mode);

            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetSetSystemParameter(0x%p, 0x%p, %u, %Iu, %s) set mode %u, failed",
                                     instance_id,
                                     session_id,
                                     parameter_id,
                                     number_value,
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(string_value)).c_str(),
                                     set_mode);

        }

        static std::error_code try_set_system_parameter(unsigned long parameter_id,
                                                        JET_API_PTR number_value = 0,
                                                        esent_set_mode set_mode = esent_set_mode::default) noexcept {
            return try_set_system_parameter(JET_instanceNil,
                                            JET_sesidNil,
                                            parameter_id,
                                            number_value,
                                            nullptr,
                                            set_mode);
        }

        static std::error_code try_set_system_parameter(unsigned long parameter_id,
                                                        TCHAR const *string_value,
                                                        esent_set_mode set_mode = esent_set_mode::default) noexcept {
            return try_set_system_parameter(JET_instanceNil,
                                            JET_sesidNil,
                                            parameter_id,
                                            0,
                                            string_value,
                                            set_mode);
        }

        static void set_system_parameter(unsigned long parameter_id,
                                         JET_API_PTR number_value = 0,
                                         esent_set_mode set_mode = esent_set_mode::default) {
            set_system_parameter(JET_instanceNil,
                                 JET_sesidNil,
                                 parameter_id,
                                 number_value,
                                 nullptr,
                                 set_mode);
        }

        static void set_system_parameter(unsigned long parameter_id,
                                         TCHAR const *string_value,
                                         esent_set_mode set_mode = esent_set_mode::default) {
            set_system_parameter(JET_instanceNil,
                                 JET_sesidNil,
                                 parameter_id,
                                 0,
                                 string_value,
                                 set_mode);
        }

        static std::error_code try_get_system_parameter(unsigned long parameter_id,
                                                        JET_API_PTR *param) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetSystemParameter(JET_instanceNil,
                                      JET_sesidNil,
                                      parameter_id,
                                      param,
                                      nullptr,
                                      sizeof(JET_API_PTR)));
                JET_CODDING_ERROR_IF(esent_err::errAlreadyInitialized == err ||
                                     esent_err::errInvalidInstance == err ||
                                     esent_err::errInvalidSesid == err);
            return err;
        }

        static std::error_code try_get_system_parameter(unsigned long parameter_id,
                                                        TCHAR *param,
                                                        unsigned long buffer_size = 0) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetSystemParameter(JET_instanceNil,
                                      JET_sesidNil,
                                      parameter_id,
                                      nullptr,
                                      param,
                                      buffer_size));
            JET_CODDING_ERROR_IF(esent_err::errAlreadyInitialized == err ||
                                    esent_err::errInvalidInstance == err ||
                                    esent_err::errInvalidSesid == err);
            return err;
        }

        static JET_API_PTR get_system_parameter_as_long(unsigned long parameter_id) {
            JET_API_PTR param{ 0 };
            std::error_code err = try_get_system_parameter(parameter_id,
                                                           &param);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetSystemParameter(%u) failed",
                                     parameter_id);
            return param;
        }

        static tstring get_system_parameter_as_string(unsigned long parameter_id) {
            tbuffer buffer{ 1024+8, _T('\0') };
            std::error_code err = try_get_system_parameter(parameter_id,
                                                           &buffer[0],
                                                           static_cast<unsigned long>(buffer.size() - sizeof(TCHAR)));
            tstring value{ &buffer[0] };
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetSystemParameter(%u, %s) failed",
                                     parameter_id,
                                     value.c_str());
            return value;
        }

        static std::error_code try_get_thread_stats(JET_THREADSTATS &thread_stats) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetThreadStats(&thread_stats, 
                                  sizeof(thread_stats)));
            return err;
        }

        static JET_THREADSTATS get_thread_stats() {
            JET_THREADSTATS thread_stats{};
            std::error_code err = try_get_thread_stats(thread_stats);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetThreadStats(%u) failed",
                                     sizeof(thread_stats));
        }

    private :
    };

    struct esent_thread_stats {
    public:

        esent_thread_stats() noexcept {
            std::error_code err = try_reset();
        }

        esent_thread_stats(esent_thread_stats const &other) noexcept
        : error_(other.error_)
        , stats_(other.stats_) {
        }

        esent_thread_stats operator= (esent_thread_stats const &other) noexcept {
            error_ = other.error_;
            stats_ = other.stats_;
            return *this;
        }

        std::error_code const &try_reset() noexcept {
            error_ = esent_library::try_get_thread_stats(stats_);
            return error_;
        }

        void reset() noexcept {
            std::error_code error = try_reset();
        }

        std::error_code get_reset_error() const noexcept {
            return error_;
        }

        bool is_valid() const {
            return (error_ == esent_err::errSuccess);
        }

        explicit operator bool() const noexcept {
            return is_valid();
        }

        std::error_code try_now(JET_THREADSTATS &diff) const noexcept {
            std::error_code error = esent_err::errSuccess;
            if (error_ == esent_err::errSuccess) {
                error = esent_library::try_get_thread_stats(diff);
                if (error == esent_err::errSuccess) {
                    if (diff.cPageReferenced >= stats_.cPageReferenced) {
                        diff.cPageReferenced -= stats_.cPageReferenced;
                    } else {
                        diff.cPageReferenced = 0;
                    }
                    if (diff.cPageRead >= stats_.cPageRead) {
                        diff.cPageRead -= stats_.cPageRead;
                    } else {
                        diff.cPageRead = 0;
                    }
                    if (diff.cPagePreread >= stats_.cPagePreread) {
                        diff.cPagePreread -= stats_.cPagePreread;
                    } else {
                        diff.cPagePreread = 0;
                    }
                    if (diff.cPageDirtied >= stats_.cPageDirtied) {
                        diff.cPageDirtied -= stats_.cPageDirtied;
                    } else {
                        diff.cPageDirtied = 0;
                    }
                    if (diff.cPageRedirtied >= stats_.cPageRedirtied) {
                        diff.cPageRedirtied -= stats_.cPageRedirtied;
                    } else {
                        diff.cPageRedirtied = 0;
                    }
                    if (diff.cLogRecord >= stats_.cLogRecord) {
                        diff.cLogRecord -= stats_.cLogRecord;
                    } else {
                        diff.cLogRecord = 0;
                    }
                    if (diff.cbLogRecord >= stats_.cbLogRecord) {
                        diff.cbLogRecord -= stats_.cbLogRecord;
                    } else {
                        diff.cbLogRecord = 0;
                    }
                }
            } else {
                error = error_;
            }
            return error;
        }

        void now(JET_THREADSTATS &diff) const noexcept {
            std::error_code err = try_now(diff);
            if (err != esent_err::errSuccess) {
                memset(&diff, 0, sizeof(diff));
                diff.cbStruct = sizeof(diff);
            }
        }

        JET_THREADSTATS now() const noexcept {
            JET_THREADSTATS diff;
            now(diff);
            return diff;
        }

        tstring now_as_tstring() const {
            tstring str;
            JET_THREADSTATS diff;
            std::error_code err = try_now(diff);
            if (err == esent_err::errSuccess) {
                str = make_tstring(_T("thread_stats={page_referenced=%u, page_read=%u, page_preread=%u, page_dirtied=%u, page_redirtied=%u, log_records=%u, log_records_size=%u}"),
                                   diff.cPageReferenced,
                                   diff.cPageRead,
                                   diff.cPagePreread,
                                   diff.cPageDirtied,
                                   diff.cPageRedirtied,
                                   diff.cLogRecord,
                                   diff.cbLogRecord);
            } 
            return str;
        }

        std::string now_as_string() const {
            std::string str;
            JET_THREADSTATS diff;
            std::error_code err = try_now(diff);
            if (err == esent_err::errSuccess) {
                str = make_string("thread_stats={page_referenced=%u, page_read=%u, page_preread=%u, page_dirtied=%u, page_redirtied=%u, log_records=%u, log_records_size=%u}",
                                      diff.cPageReferenced,
                                      diff.cPageRead,
                                      diff.cPagePreread,
                                      diff.cPageDirtied,
                                      diff.cPageRedirtied,
                                      diff.cLogRecord,
                                      diff.cbLogRecord);
            }
            return str;
        }

        std::wstring now_as_wstring() const {
            std::wstring str;
            JET_THREADSTATS diff;
            std::error_code err = try_now(diff);
            if (err == esent_err::errSuccess) {
                str = make_wstring(L"thread_stats={page_referenced=%u, page_read=%u, page_preread=%u, page_dirtied=%u, page_redirtied=%u, log_records=%u, log_records_size=%u}",
                                   diff.cPageReferenced,
                                   diff.cPageRead,
                                   diff.cPagePreread,
                                   diff.cPageDirtied,
                                   diff.cPageRedirtied,
                                   diff.cLogRecord,
                                   diff.cbLogRecord);
            }
            return str;
        }

    private:
        std::error_code error_{ esent_err::errNotInitialized };
        JET_THREADSTATS stats_{};
    };
}
