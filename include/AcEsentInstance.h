#pragma once

namespace ac {
    //
    // 1. create_instance creates a handle
    // 2. set parameters
    // 3. init_instance. Failing init might close handle.
    // 4. use it
    // 5. terminate or close destroys the handle
    //
    class esent_instance {
    public:

        esent_instance() noexcept {
        }

        esent_instance(esent_instance &&other) noexcept 
            : instance_{other.instance_} {
            other.instance_ = JET_instanceNil;
        }

        esent_instance &operator=(esent_instance &&other) noexcept {
            if (this != &other) {
                close();
                instance_ = other.instance_;
                other.instance_ = JET_instanceNil;
            }
            return *this;
        }

        ~esent_instance() noexcept {
            close();
        }

        bool is_valid() const noexcept {
            return instance_ != JET_instanceNil;
        }

        explicit operator bool() const noexcept {
            return is_valid();
        }

        JET_INSTANCE get_instance() noexcept {
            return instance_;
        }

        void attach(JET_INSTANCE instance) noexcept {
            if (instance != JET_instanceNil) {
                JET_CODDING_ERROR_IF(instance_ == instance);
            }
            close();
            instance_ = instance;
        }

        JET_INSTANCE detach() noexcept {
            JET_INSTANCE instance = instance_;
            instance_ = JET_instanceNil;
            return instance;
        }

        std::error_code try_create(TCHAR const * instance_name = _T(""),
                                   TCHAR const * display_name = _T(""),
                                   JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = try_terminate(grbit);
            //
            // Some terminate errors are informational
            // while other terminte error mean that
            // instance cannot be terminated. 
            // Continue with create only if instance was
            // terminated
            //
            if (!is_valid()) {
                err = make_esent_error_code(
                    JetCreateInstance2(&instance_,
                                       instance_name,
                                       display_name,
                                       0 /*grbit*/));
            }
            return err;
         }

        void create(TCHAR const * instance_name = _T(""),
                    TCHAR const * display_name = _T(""),
                    JET_GRBIT grbit = JET_bitNil) {
        
            terminate(grbit);
            //
            // Some terminate errors are informational
            // while other terminte error mean that
            // instance cannot be terminated. 
            // Continue with create only if instance was
            // terminated
            //
            if (!is_valid()) {
                std::error_code err = make_esent_error_code(
                    JetCreateInstance2(&instance_,
                                       instance_name,
                                       display_name,
                                       0 /*grbit*/));

                ESENT_THROW_ON_ERROR_FMT(err, 
                                         "JetCreateInstance2(%s, %s) failed",
                                         t_to_a(SANITIZE_CSTR_FOR_PRINTF(instance_name)).c_str(),
                                         t_to_a(SANITIZE_CSTR_FOR_PRINTF(display_name)).c_str());
            }
        }

        std::error_code try_init() noexcept {
            std::error_code err = esent_err::errInvalidInstance;
            //
            // we always operate in multiinstance mode so 
            // we must have handle
            //
            if (is_valid()) {
                err = make_esent_error_code(JetInit(&instance_));
                //
                // According to MSDN failing init implicitly
                // closes instance handle. Bad design.
                // from experiments they set handle to null,
                // and we treat JET_instanceNil as an invalid
                // value. 
                //
                if (instance_ == 0) {
                    instance_ = JET_instanceNil;
                }
            }
            return err;
        }

        void init() {
            std::error_code err = try_init();
            ESENT_THROW_ON_ERROR(err, 
                                 "JetInit failed");
        }

        std::error_code try_init(JET_GRBIT grbit) noexcept {
            std::error_code err = esent_err::errInvalidInstance;
            //
            // we always operate in multiinstance mode so 
            // we must have handle
            //
            if (is_valid()) {
                err = make_esent_error_code(JetInit2(&instance_, grbit));
                //
                // According to MSDN failing init implicitly
                // closes instance handle. Bad design.
                // from experiments they set handle to null,
                // and we treat JET_instanceNil as an invalid
                // value. 
                //
                if (instance_ == 0) {
                    instance_ = JET_instanceNil;
                }

            }
            return err;
        }

        void init(JET_GRBIT grbit) {
            std::error_code err = try_init(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetInit2(%u) failed",
                                     grbit);
        }

        std::error_code try_init(JET_RSTINFO* reset_info,
                                 JET_GRBIT grbit ) noexcept {
            std::error_code err = esent_err::errInvalidInstance;
            //
            // we always operate in multiinstance mode so 
            // we must have handle
            //
            if (is_valid()) {
                err = make_esent_error_code(
                    JetInit3(&instance_,
                             reset_info,
                             grbit));
                //
                // According to MSDN failing init implicitly
                // closes instance handle. Bad design.
                // from experiments they set handle to null,
                // and we treat JET_instanceNil as an invalid
                // value. 
                //
                if (instance_ == 0) {
                    instance_ = JET_instanceNil;
                }
            }
            return err;
        }

        void init(JET_RSTINFO* reset_info,
                  JET_GRBIT grbit) {
            std::error_code err = try_init(reset_info,
                                   grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetInit3(%p, %u) failed",
                                     reset_info,
                                     grbit);
        }

        std::error_code try_stop() noexcept {
            return make_esent_error_code(JetStopServiceInstance(instance_));
        }

        void stop() {
            std::error_code err = try_stop();
            ESENT_THROW_ON_ERROR(err,
                                 "JetStopServiceInstance failed");
        }

        std::error_code try_stop(JET_GRBIT grbit) noexcept {
            return make_esent_error_code(JetStopServiceInstance2(instance_, grbit));
        }

        void stop(JET_GRBIT grbit) {
            std::error_code err = try_stop(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetStopServiceInstance2(%u) failed",
                                     grbit);
        }

        void set_log_file_path(TCHAR const *path) {
            set_system_parameter(JET_paramLogFilePath,
                                 path);
        }

        void set_system_path(TCHAR const *path) {
            set_system_parameter(JET_paramSystemPath,
                                 path);
        }

        std::error_code try_set_system_parameter(unsigned long parameter_id,
                                                 JET_API_PTR number_value = 0,
                                                 esent_set_mode set_mode = esent_set_mode::default) noexcept {
            return esent_library::try_set_system_parameter(instance_,
                                                           JET_sesidNil,
                                                           parameter_id,
                                                           number_value,
                                                           nullptr,
                                                           set_mode);
        }

        std::error_code try_set_system_parameter(unsigned long parameter_id,
                                                 TCHAR const *string_value,
                                                 esent_set_mode set_mode = esent_set_mode::default) noexcept {
            return esent_library::try_set_system_parameter(instance_,
                                                           JET_sesidNil,
                                                           parameter_id,
                                                           0,
                                                           string_value,
                                                           set_mode);
        }

        void set_system_parameter(unsigned long parameter_id,
                                  JET_API_PTR number_value = 0,
                                  esent_set_mode set_mode = esent_set_mode::default) {
            esent_library::set_system_parameter(instance_,
                                                JET_sesidNil,
                                                parameter_id,
                                                number_value,
                                                nullptr,
                                                 set_mode);
        }

        void set_system_parameter(unsigned long parameter_id,
                                  TCHAR const *string_value,
                                  esent_set_mode set_mode = esent_set_mode::default) {
            esent_library::set_system_parameter(instance_,
                                                JET_sesidNil,
                                                parameter_id,
                                                0,
                                                string_value,
                                                set_mode);
        }

        std::error_code try_get_system_parameter(unsigned long parameter_id,
                                                 JET_API_PTR *param,
                                                 unsigned long buffer_size = 0) noexcept {
            std::error_code err = esent_err::errInvalidInstance;
            if (is_valid()) {
                err = make_esent_error_code(
                    JetGetSystemParameter(instance_,
                                          JET_sesidNil,
                                          parameter_id,
                                          param,
                                          nullptr,
                                          buffer_size));
                JET_CODDING_ERROR_IF(esent_err::errAlreadyInitialized == err ||
                                     esent_err::errInvalidInstance == err ||
                                     esent_err::errInvalidSesid == err);
            }
            return err;
        }

        std::error_code try_get_system_parameter(unsigned long parameter_id,
                                                 TCHAR *param,
                                                 unsigned long buffer_size = 0) noexcept {
            std::error_code err = esent_err::errInvalidInstance;
            if (is_valid()) {
                err = make_esent_error_code(
                    JetGetSystemParameter(instance_,
                                          JET_sesidNil,
                                          parameter_id,
                                          nullptr,
                                          param,
                                          buffer_size));
                JET_CODDING_ERROR_IF(esent_err::errAlreadyInitialized == err ||
                                     esent_err::errInvalidInstance == err ||
                                     esent_err::errInvalidSesid == err);
            }
            return err;
        }


        void get_system_parameter(unsigned long parameter_id,
                                  JET_API_PTR *param,
                                  unsigned long buffer_size = 0) {
            get_system_parameter(parameter_id,
                                 param,
                                 buffer_size);
        }

        void get_system_parameter(unsigned long parameter_id,
                                  TCHAR *param,
                                  unsigned long buffer_size = 0) {
            get_system_parameter(parameter_id,
                                 param,
                                 buffer_size);
        }

        std::error_code try_get_misc_info(unsigned long info_level,
                                          void *buffer,
                                          unsigned long buffer_size) noexcept {
            return make_esent_error_code(
                JetGetInstanceMiscInfo(instance_,
                                       buffer,
                                       buffer_size,
                                       info_level));
        }

        bool get_misc_info(unsigned long info_level,
                           void *buffer,
                           unsigned long buffer_size) {
            std::error_code err = try_get_misc_info(info_level,
                                                    buffer,
                                                    buffer_size);
            ESENT_THROW_IF_FMT(esent_err::errSuccess != err && esent_err::errBufferTooSmall != err,
                               err, 
                               "JetGetInstanceMiscInfo(%u) failed",
                               buffer_size);
            return esent_err::errSuccess != err ? true : false;
        }

        cbuffer get_misc_info(unsigned long info_level,
                              unsigned long initial_size = 256,
                              unsigned long max_size = 1024*1024) {
            cbuffer buffer;

            if (buffer.size()!= initial_size) {
                buffer.resize(initial_size);
            }

            for ( ; ; ) {
                if (get_misc_info(info_level,
                                  reinterpret_cast<void *>(&buffer[0]),
                                  static_cast<unsigned long>(buffer.size()))) {
                    break;
                }

                ESENT_THROW_IF_FMT(buffer.size() * 2 > max_size,
                                   esent_err::errOutOfMemory,
                                   "JetGetInstanceMiscInfo(%u) max %u failed",
                                   buffer.size(),
                                   max_size);

                buffer.resize(buffer.size() * 2);
            }

            return buffer;
        }

        std::error_code try_terminate() noexcept {
            std::error_code err = esent_err::errSuccess;
            if (is_valid()) {
                err = make_esent_error_code(JetTerm(instance_));
                if (esent_err_severity::error != err) {
                    instance_ = JET_instanceNil;
                } else {
                    //
                    // invalid handle or one of the parameters
                    //
                    JET_CODDING_ERROR_IF_NOT(esent_err::errInvalidParameter != err &&
                                             esent_err::errNotInitialized != err);
                }
            }
            return err;
        }

        void terminate() {
            if (is_valid()) {
                std::error_code err = try_terminate();
                ESENT_THROW_ON_ERROR(err, 
                                     "JetTerm failed");
                JET_CODDING_ERROR_IF(is_valid());
            }
        }

        std::error_code try_terminate(JET_GRBIT grbit) noexcept {
            std::error_code err = esent_err::errSuccess;
            if (is_valid()) {
                err = make_esent_error_code(JetTerm2(instance_, grbit));
                if (esent_err_severity::error != err) {
                    instance_ = JET_instanceNil;
                } else {
                    //
                    // invalid handle or one of the parameters
                    //
                    JET_CODDING_ERROR_IF_NOT(esent_err::errInvalidParameter != err &&
                                             esent_err::errNotInitialized != err);
                }
            }
            return err;
        }

        void terminate(JET_GRBIT grbit) {
            std::error_code err = try_terminate(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetTerm2(%u) failed",
                                     grbit);
            JET_CODDING_ERROR_IF(is_valid());
        }

        void close() noexcept {
            //
            // First attempt gracefull shutdown
            //
            std::error_code err = try_terminate();
            //
            // If gracefull shutdown failed then
            // attempt crash consistent shutdown
            //
            err = try_terminate(JET_bitTermAbrupt | JET_bitTermStopBackup | JET_bitTermDirty);
            //
            // if that failed then default policy is 
            // to fail-fast
            //
            JET_CODDING_ERROR_IF(is_valid());
        }

        std::error_code try_truncate_log() noexcept {
            return make_esent_error_code(JetTruncateLogInstance(instance_));
        }

        void truncate_log() {
            std::error_code err = try_truncate_log();
            ESENT_THROW_ON_ERROR(err, 
                                 "JetTruncateLogInstance failed");
        }

        std::error_code try_open_file(TCHAR const *file_name,
                                      esent_file &file,
                                      unsigned long long* file_size) noexcept {

            JET_HANDLE file_handle = 0;
            unsigned long file_size_low = 0;
            unsigned long file_size_high = 0;
            std::error_code err = make_esent_error_code(
                JetOpenFileInstance(instance_,
                                    file_name,
                                    &file_handle,
                                    &file_size_low,
                                    &file_size_high));
            if (file_handle != 0) {
                file.attach(file_handle, instance_);
                *file_size = ac_MakeQWORD(file_size_low, file_size_high);
            }
            return err;
        }

        std::pair<esent_file, unsigned long long> open_file(TCHAR const * file_name) {
            std::pair<esent_file, unsigned long long> result;
            std::error_code err = try_open_file(file_name, result.first, &result.second);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetOpenFileInstance(%s) failed",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(file_name)).c_str());
             return std::move(result);
        }

        std::error_code try_begin_external_backup(JET_GRBIT grbit = JET_bitNil) noexcept {
            return make_esent_error_code(JetBeginExternalBackupInstance(instance_, grbit));
        }

        void begin_external_backup(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_begin_external_backup(grbit);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetBeginExternalBackupInstance failed");
        }

        std::error_code try_stop_backup() noexcept {
            return make_esent_error_code(JetStopBackupInstance(instance_));
        }

        void stop_backup() {
            std::error_code err = try_stop_backup();
            ESENT_THROW_ON_ERROR(err, 
                                 "JetStopBackupInstance failed");
        }

        std::error_code try_end_external_backup() noexcept {
            return make_esent_error_code(JetEndExternalBackupInstance(instance_));
        }

        void end_external_backup() {
            std::error_code err = try_end_external_backup();
            ESENT_THROW_ON_ERROR(err, 
                                 "JetEndExternalBackupInstance failed");
        }

        std::error_code try_get_attach_info(TCHAR* buffer,
                                    unsigned long buffer_size,
                                    unsigned long *bytes_returned) noexcept {
            return make_esent_error_code(
                JetGetAttachInfoInstance(instance_,
                                         buffer,
                                         buffer_size,
                                         bytes_returned));
        }

        unsigned long get_attach_info(TCHAR* buffer,
                                      unsigned long buffer_size) {
            unsigned long bytes_returned = 0;
            std::error_code err = try_get_attach_info(buffer,
                                              buffer_size,
                                              &bytes_returned);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetAttachInfoInstance(%u) failed",
                                     buffer_size);
            return bytes_returned;
        }

        std::error_code try_get_log_info(TCHAR* buffer,
                                         unsigned long buffer_size,
                                         unsigned long *bytes_returned) noexcept {
            return make_esent_error_code(
                JetGetLogInfoInstance(instance_,
                                      buffer,
                                      buffer_size,
                                      bytes_returned));
        }

        unsigned long get_log_info(TCHAR* buffer,
                                   unsigned long buffer_size) {
            unsigned long bytes_returned = 0;
            std::error_code err = try_get_log_info(buffer,
                                           buffer_size,
                                           &bytes_returned);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetLogInfoInstance(%u) failed",
                                     buffer_size);
            return bytes_returned;
        }

        std::error_code try_get_log_info(TCHAR* buffer,
                                          unsigned long buffer_size,
                                          unsigned long *bytes_returned,
                                          JET_LOGINFO *log_info) noexcept {
            return make_esent_error_code(
                JetGetLogInfoInstance2(instance_,
                                       buffer,
                                       buffer_size,
                                       bytes_returned,
                                       log_info));
        }

        unsigned long get_log_info(TCHAR* buffer,
                                   unsigned long buffer_size,
                                   JET_LOGINFO *log_info) {
            unsigned long bytes_returned = 0;
            std::error_code err = try_get_log_info(buffer,
                                           buffer_size,
                                           &bytes_returned,
                                           log_info);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetLogInfoInstance2(%u) failed",
                                     buffer_size);
            return bytes_returned;
        }

        std::error_code try_get_truncate_log_info(TCHAR* buffer,
                                                   unsigned long buffer_size,
                                                   unsigned long *bytes_returned) noexcept {
            return make_esent_error_code(
                JetGetTruncateLogInfoInstance(instance_,
                                              buffer,
                                              buffer_size,
                                              bytes_returned));
        }

        unsigned long get_truncate_log_info(TCHAR* buffer,
                                            unsigned long buffer_size) {
            unsigned long bytes_returned = 0;
            std::error_code err = try_get_truncate_log_info(buffer,
                                                    buffer_size,
                                                    &bytes_returned);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetTruncateLogInfoInstance(%u) failed",
                                     buffer_size);
            return bytes_returned;
        }

        std::error_code try_backup(TCHAR const *path,
                                   JET_GRBIT grbit,
                                   JET_PFNSTATUS status_fn) noexcept {

            return make_esent_error_code(
                JetBackupInstance(instance_,
                                  path,
                                  grbit,
                                  status_fn));
        }

        void backup(TCHAR const *path,
                    JET_GRBIT grbit,
                    JET_PFNSTATUS status_fn) {
            std::error_code err = try_backup(path,
                                     grbit,
                                     status_fn);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetBackupInstance(%s, %u) failed",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(path)).c_str(),
                                     grbit);
        }

        std::error_code try_restore(TCHAR const *path,
                                    TCHAR const *destination,
                                    JET_PFNSTATUS status_fn) noexcept {

            return make_esent_error_code(
                JetRestoreInstance(instance_,
                                   path,
                                   destination,
                                   status_fn));
        }

        void restore(TCHAR const *path,
                     TCHAR const *destination,
                     JET_PFNSTATUS status_fn) {
            std::error_code err = try_restore(path,
                                      destination,
                                      status_fn);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetRestoreInstance(%s, %s) failed",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(path)).c_str(),
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(destination)).c_str());
        }

        std::error_code try_begin_session(esent_session &session) noexcept {
            JET_SESID session_id = JET_sesidNil;
            std::error_code err = make_esent_error_code(
                JetBeginSession(instance_,
                                &session_id,
                                nullptr,
                                nullptr));
            if (esent_err::errSuccess == err) {
                session.attach(session_id);
            }
            return err;
        }

        esent_session begin_session() {
            esent_session session;
            std::error_code err = try_begin_session(session);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetBeginSession failed");
            return session;
        }

    private:

        JET_INSTANCE instance_{ JET_instanceNil };
    };
}
