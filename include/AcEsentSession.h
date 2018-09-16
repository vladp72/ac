#pragma once

namespace ac {

    class esent_session {
    public:

        esent_session() noexcept {
        }

        esent_session(esent_session &&other) noexcept
            : session_id_{ other.session_id_ } {
            other.session_id_ = JET_sesidNil;
        }

        esent_session &operator=(esent_session &&other) noexcept {
            if (this != &other) {
                close();
                session_id_ = other.session_id_;
                other.session_id_ = JET_sesidNil;
            }
            return *this;
        }

        ~esent_session() noexcept {
            close();
        }

        bool is_valid() const noexcept {
            return session_id_ != JET_sesidNil;
        }

        explicit operator bool() const noexcept {
            return is_valid();
        }

        JET_SESID get_session() noexcept {
            return session_id_;
        }

        void attach(JET_SESID session_id) noexcept {
            if (session_id != JET_sesidNil) {
                JET_CODDING_ERROR_IF(session_id == session_id_);
            }
            close();
            session_id_ = session_id;
        }

        JET_SESID detach() noexcept {
            JET_SESID session_id = session_id_;
            session_id_ = JET_sesidNil;
            return session_id;
        }

        std::error_code try_duplicate(esent_session &session) noexcept {
            JET_SESID session_id = JET_sesidNil;
            std::error_code err = make_esent_error_code(
                JetDupSession(session_id_,
                              &session_id));
            if (esent_err::errSuccess == err) {
                session.attach(session_id);
            }
            return err;
        }

        esent_session duplicate() {
            esent_session session;
            std::error_code err = try_duplicate(session);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetDupSession failed");
            return session;
        }

        std::error_code try_end() noexcept {
            std::error_code err = esent_err::errSuccess;
            if (is_valid()) {
                err = make_esent_error_code(JetEndSession(session_id_, 0));
                if (esent_err_severity::error != err) {
                    session_id_ = JET_sesidNil;
                } else {
                    JET_CODDING_ERROR_IF(esent_err::errInvalidParameter == err ||
                                         esent_err::errInvalidSesid == err ||
                                         esent_err::errNotInitialized == err ||
                                         esent_err::errSessionInUse == err ||
                                         esent_err::errRestoreInProgress == err ||
                                         esent_err::errTermInProgress == err);
                }
            }
            return err;
        }

        void end() {
            std::error_code err = try_end();
            ESENT_THROW_ON_ERROR(err, 
                                 "JetEndSession failed");
        }

        void close() noexcept {
            std::error_code err = try_end();
            JET_CODDING_ERROR_IF(is_valid());
        }

        std::error_code try_set_system_parameter(unsigned long parameter_id,
                                                 JET_API_PTR number_value,
                                                 esent_set_mode set_mode = esent_set_mode::default) noexcept {
            return esent_library::try_set_system_parameter(JET_instanceNil,
                                                           session_id_,
                                                           parameter_id,
                                                           number_value,
                                                           nullptr,
                                                           set_mode);
        }

        std::error_code try_set_system_parameter(unsigned long parameter_id,
                                                 TCHAR const *string_value,
                                                 esent_set_mode set_mode = esent_set_mode::default) noexcept {
            return esent_library::try_set_system_parameter(JET_instanceNil,
                                                           session_id_,
                                                           parameter_id,
                                                           0,
                                                           string_value,
                                                           set_mode);
        }

        void set_system_parameter(unsigned long parameter_id,
                                  JET_API_PTR number_value = 0,
                                  esent_set_mode set_mode = esent_set_mode::default) {
            esent_library::set_system_parameter(JET_instanceNil,
                                                session_id_,
                                                parameter_id,
                                                number_value,
                                                nullptr,
                                                 set_mode);
        }

        void set_system_parameter(unsigned long parameter_id,
                                  TCHAR const *string_value,
                                  esent_set_mode set_mode = esent_set_mode::default) {
            esent_library::set_system_parameter(JET_instanceNil,
                                                session_id_,
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
                    JetGetSystemParameter(JET_instanceNil,
                                          session_id_,
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
                    JetGetSystemParameter(JET_instanceNil,
                                          session_id_,
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
            std::error_code err = try_get_system_parameter(parameter_id,
                                                           param,
                                                           buffer_size);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetSystemParameter(%u, %Iu, %u) failed",
                                     parameter_id,
                                     param,
                                     buffer_size);
        }

        void get_system_parameter(unsigned long parameter_id,
                                  TCHAR *param,
                                  unsigned long buffer_size = 0) {
            std::error_code err = try_get_system_parameter(parameter_id,
                                                           param,
                                                           buffer_size);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetSystemParameter(%u, %Iu, %u) failed",
                                     parameter_id,
                                     param,
                                     buffer_size);        
        }

        std::error_code try_get_version(unsigned long *version) noexcept {
            return make_esent_error_code(JetGetVersion(session_id_, version));
        }

        unsigned long get_version() {
            unsigned long version = 0;
            std::error_code err = try_get_version(&version);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetGetVersion failed");
            return version;
        }

        std::error_code try_idle(JET_GRBIT grbit) noexcept {
            return make_esent_error_code(JetIdle(session_id_, grbit));
        }

        void idle(JET_GRBIT grbit) {
            std::error_code err = try_idle(grbit);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetIdle(%u) failed",
                                     grbit);
        }
        //
        // esent_err::wrnDatabaseAttached A nonfatal warning indicating that the database 
        //                         file has already been attached by this session.
        // esent_err::wrnFileOpenReadOnly indicates that the file was attached read-only, but
        //                         JetCreateDatabase did not pass JET_bitDbReadOnly. 
        //                         The database is still opened with read-only access.
        //
        std::error_code try_create_database(TCHAR const *file_name,
                                            esent_database &database,
                                            JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = esent_err::errSuccess;
            JET_DBID db_id = JET_dbidNil;
            err = make_esent_error_code(
                JetCreateDatabase(session_id_,
                                  file_name,
                                  nullptr,
                                  &db_id,
                                  grbit));
            if (esent_err_severity::error != err) {
                database.attach(db_id, session_id_);
            }

            return err;
        }

        std::pair<esent_database, std::error_code> create_database(TCHAR const *file_name,
                                                                   JET_GRBIT grbit = JET_bitNil) {
            esent_database database;
            std::error_code err = try_create_database(file_name,
                                                      database,
                                                      grbit);
            if (!database.is_valid()) {
                ESENT_THROW_FMT(err,
                                "JetCreateDatabase(%s, %u)",
                                t_to_a(SANITIZE_CSTR_FOR_PRINTF(file_name)).c_str(),
                                grbit);
            }
            return std::make_pair(std::move(database), err);
        }
        //
        // esent_err::wrnDatabaseAttached A nonfatal warning indicating that the database 
        //                         file has already been attached by this session.
        // esent_err::wrnFileOpenReadOnly indicates that the file was attached read-only, but
        //                         JetCreateDatabase did not pass JET_bitDbReadOnly. 
        //                         The database is still opened with read-only access.
        //
        std::error_code try_create_database(TCHAR const *file_name,
                                            unsigned long database_size,
                                            esent_database &database,
                                            JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = esent_err::errSuccess;
            JET_DBID db_id = JET_dbidNil;
            err = make_esent_error_code(
                JetCreateDatabase2(session_id_,
                                   file_name,
                                   database_size,
                                   &db_id,
                                   grbit));
            if (esent_err_severity::error != err) {
                database.attach(db_id, session_id_);
            }

            return err;
        }

        std::pair<esent_database, std::error_code> create_database(TCHAR const *file_name,
                                                                   unsigned long database_size,
                                                                   JET_GRBIT grbit = JET_bitNil) {
            esent_database database;
            std::error_code err = try_create_database(file_name,
                                                      database_size,
                                                      database,
                                                      grbit);
            if (!database.is_valid()) {
                ESENT_THROW_FMT(err,
                                "JetCreateDatabase2(%s, %u, %u)",
                                t_to_a(SANITIZE_CSTR_FOR_PRINTF(file_name)).c_str(),
                                database_size,
                                grbit);
            }
            return std::make_pair(std::move(database), err);
        }

        //
        // esent_err::wrnFileOpenReadOnly indicates that the file was attached read-only, but
        //                         JetCreateDatabase did not pass JET_bitDbReadOnly. 
        //                         The database is still opened with read-only access.
        //
        std::error_code try_open_database(TCHAR const *file_name,
                                          esent_database &database,
                                          JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = esent_err::errSuccess;
            JET_DBID db_id = JET_dbidNil;
            err = make_esent_error_code(
                JetOpenDatabase(session_id_,
                                file_name,
                                nullptr,
                                &db_id,
                                grbit));
            if (esent_err_severity::error != err) {
                database.attach(db_id, session_id_);
            }

            return err;
        }

        std::pair<esent_database, std::error_code> open_database(TCHAR const *file_name,
                                                                 JET_GRBIT grbit = JET_bitNil) {
            esent_database database;
            std::error_code err = try_open_database(file_name,
                                                    database,
                                                    grbit);
            if (!database.is_valid()) {
                ESENT_THROW_FMT(err,
                                "JetOpenDatabase(%s, %u)",
                                t_to_a(SANITIZE_CSTR_FOR_PRINTF(file_name)).c_str(),
                                grbit);
            }
            return std::make_pair(std::move(database), err);
        }
        //
        // esent_err::wrnDatabaseAttached A nonfatal warning indicating that the database 
        //                         file has already been attached by this session.
        //
        std::error_code try_attach_database(TCHAR const *file_name,
                                            JET_GRBIT grbit = JET_bitNil,
                                            void const * = nullptr) noexcept {
            std::error_code err = make_esent_error_code(
                JetAttachDatabase(session_id_,
                                  file_name,
                                  grbit));
            return err;
        }

        std::error_code attach_database(TCHAR const *file_name,
                                        JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_attach_database(file_name,
                                                      grbit,
                                                      nullptr);
            if (esent_err_severity::error == err) {
                ESENT_THROW_FMT(err,
                                "JetAttachDatabase(%s, %u)",
                                t_to_a(SANITIZE_CSTR_FOR_PRINTF(file_name)).c_str(),
                                grbit);
            }
            return err;
        }
        //
        // esent_err::wrnDatabaseAttached A nonfatal warning indicating that the database 
        //                         file has already been attached by this session.
        //
        std::error_code try_attach_database(TCHAR const *file_name,
                                            unsigned long database_size_max,
                                            JET_GRBIT grbit) noexcept {
            std::error_code err = make_esent_error_code(
                JetAttachDatabase2(session_id_,
                                  file_name,
                                  database_size_max,
                                  grbit));
            return err;
        }

        std::error_code attach_database(TCHAR const *file_name,
                                        unsigned long database_size_max,
                                        JET_GRBIT grbit) {
            std::error_code err = try_attach_database(file_name,
                                                      database_size_max,
                                                      grbit);
            if (esent_err_severity::error != err) {
                ESENT_THROW_FMT(err,
                                "JetAttachDatabase2(%s, %u, %u)",
                                t_to_a(SANITIZE_CSTR_FOR_PRINTF(file_name)).c_str(),
                                database_size_max,
                                grbit);
            }
            return err;
        }

        std::error_code try_detach_database(TCHAR const *file_name,
                                            void const * = nullptr) noexcept {
            std::error_code err = make_esent_error_code(
                JetDetachDatabase(session_id_,
                                  file_name));
            return err;
        }

        std::error_code detach_database(TCHAR const *file_name) {
            std::error_code err = try_detach_database(file_name);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetDetachDatabase(%s)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(file_name)).c_str());
            return err;
        }

        std::error_code try_detach_database(TCHAR const *file_name,
                                            JET_GRBIT grbit) noexcept {
            std::error_code err = make_esent_error_code(
                JetDetachDatabase2(session_id_,
                                   file_name,
                                   grbit));
            return err;
        }

        std::error_code detach_database(TCHAR const *file_name,
                                        JET_GRBIT grbit) {
            std::error_code err = try_detach_database(file_name, grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetDetachDatabase2(%s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(file_name)).c_str(),
                                     grbit);
            return err;
        }

        std::error_code try_begin_transaction( esent_transaction &transaction) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(
                JetBeginTransaction(session_id_));
            if (esent_err_severity::error != err) {
                transaction.attach(session_id_);
            }
            return err;
        }

        esent_transaction begin_transaction() {
            esent_transaction transaction;
            std::error_code err = try_begin_transaction(transaction);
            if (!transaction.is_valid()) {
                ESENT_THROW(err,
                            "JetBeginTransaction");
            }
            return transaction;
        }

        std::error_code try_begin_transaction( esent_transaction &transaction,
                                               JET_GRBIT grbit) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(
                JetBeginTransaction2(session_id_, grbit));
            if (esent_err_severity::error != err) {
                transaction.attach(session_id_);
            }
            return err;
        }

        esent_transaction begin_transaction(JET_GRBIT grbit) {
            esent_transaction transaction;
            std::error_code err = try_begin_transaction(transaction, grbit);
            if (!transaction.is_valid()) {
                ESENT_THROW_FMT(err,
                                "JetBeginTransaction2(%u)",
                                grbit);
            }
            return transaction;
        }

        std::error_code try_begin_transaction( esent_transaction &transaction,
                                               long long trxid, 
                                               JET_GRBIT grbit) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(
                JetBeginTransaction3(session_id_, trxid, grbit));
            if (esent_err_severity::error != err) {
                transaction.attach(session_id_);
            }
            return err;
        }

        esent_transaction begin_transaction(long long trxid,
                                            JET_GRBIT grbit) {
            esent_transaction transaction;
            std::error_code err = try_begin_transaction(transaction, trxid, grbit);
            if (!transaction.is_valid()) {
                ESENT_THROW_FMT(err,
                                "JetBeginTransaction3(%I64i, %u)",
                                trxid,
                                grbit);
            }
            return transaction;
        }

        std::error_code try_reset() noexcept {
            std::error_code err = make_esent_error_code(
                JetResetSessionContext(session_id_));
        }

        void reset() {
            std::error_code err = try_reset();
            ESENT_THROW_ON_ERROR(err,
                                 "JetResetSessionContext");
        }

        std::error_code try_set_context(JET_API_PTR context) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetSessionContext(session_id_, context));
        }

        void set_context(JET_API_PTR context) {
            std::error_code err = try_set_context(context);
            ESENT_THROW_ON_ERROR(err,
                                 "JetSetSessionContext");
        }

        std::error_code try_compact(TCHAR const *database_source,
                                    TCHAR const *database_destination,
                                    JET_PFNSTATUS status_fn = nullptr,
                                    JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetCompact(session_id_,
                           database_source,
                           database_destination,
                           status_fn,
                           nullptr,
                           grbit));
            return err;
        }

        void compact(TCHAR const *database_source,
                     TCHAR const *database_destination,
                     JET_PFNSTATUS status_fn = nullptr,
                     JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_compact(database_source,
                                              database_destination,
                                              status_fn,
                                              grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetCompact(%s, %s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(database_source)).c_str(),
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(database_destination)).c_str(),
                                     grbit);
        }

        std::error_code try_defragment(TCHAR const *database_name,
                                       TCHAR const *table_name,
                                       unsigned long *passes,
                                       unsigned long *seconds,
                                       JET_CALLBACK callback_fn = nullptr,
                                       void *context = nullptr,
                                       JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetDefragment3(session_id_,
                               database_name,
                               table_name,
                               passes,
                               seconds,
                               callback_fn,
                               context,
                               grbit));
            return err;
        }

        void defragment(TCHAR const *database_name,
                        TCHAR const *table_name,
                        unsigned long *passes,
                        unsigned long *seconds,
                        JET_CALLBACK callback_fn = nullptr,
                        void *context = nullptr,
                        JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_defragment(database_name,
                                                 table_name,
                                                 passes,
                                                 seconds,
                                                 callback_fn,
                                                 context,
                                                 grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetDefragment3(%s, %s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(database_name)).c_str(),
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(table_name)).c_str(),
                                     grbit);
        }

        std::error_code try_set_database_size(TCHAR const *database_name,
                                              unsigned long cpg,
                                              unsigned long *cpg_returned) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetDatabaseSize(session_id_,
                                   database_name,
                                   cpg,
                                   cpg_returned));
            return err;
        }

        unsigned long set_database_size(TCHAR const *database_name,
                                         unsigned long cpg) {
            unsigned long cpg_returned = 0;
            std::error_code err = try_set_database_size(database_name,
                                                 cpg,
                                                 &cpg_returned);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetDatabaseSize(%s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(database_name)).c_str(),
                                     cpg);
            return cpg_returned;
        }
        
        std::error_code try_intersect_indexes(JET_INDEXRANGE *index_range,
                                              unsigned long index_range_count,
                                              JET_RECORDLIST &record_list,
                                              JET_GRBIT grbit,
                                              esent_table &table) noexcept {
            std::error_code err = make_esent_error_code(
                JetIntersectIndexes(session_id_,
                                    index_range,
                                    index_range_count,
                                    &record_list,
                                    grbit));
            if (esent_err_severity::error != err) {
                table.attach(record_list.tableid, session_id_);
            }
            return err;
        }

        esent_table intersect_indexes(JET_INDEXRANGE *index_range,
                                      unsigned long index_range_count,
                                      JET_RECORDLIST &record_list,
                                      JET_GRBIT grbit = JET_bitNil) {
            esent_table table;
            std::error_code err = try_intersect_indexes(index_range,
                                                        index_range_count,
                                                        record_list,
                                                        grbit,
                                                        table);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetIntersectIndexes(%u, %u) failed",
                                     index_range_count,
                                     grbit);
            return table;
        }

        std::error_code try_open_temporary_table(JET_COLUMNDEF const *column_definition,
                                                 unsigned long column_count,
                                                 JET_COLUMNID *column_id,
                                                 JET_GRBIT grbit,
                                                 esent_table &table) noexcept {
            JET_TABLEID table_id = JET_tableidNil;
            std::error_code err = make_esent_error_code(
                JetOpenTempTable(session_id_,
                                 column_definition,
                                 column_count,
                                 grbit,
                                 &table_id,
                                 column_id));
            if (esent_err_severity::error != err) {
                table.attach(table_id, session_id_);
            }
            return err;
        }

        esent_table open_temporary_table(JET_COLUMNDEF const *column_definition,
                                         unsigned long column_count,
                                         JET_COLUMNID *column_id,
                                         JET_GRBIT grbit = JET_bitNil) {
            esent_table table;
            std::error_code err = try_open_temporary_table(column_definition,
                                                           column_count,
                                                           column_id,
                                                           grbit,
                                                           table);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetOpenTempTable(%u, %u) failed",
                                     column_count,
                                     grbit);
            return table;
        }

        std::error_code try_open_temporary_table(JET_COLUMNDEF const *column_definition,
                                                 unsigned long column_count,
                                                 JET_COLUMNID *column_id,
                                                 unsigned long lcid,
                                                 JET_GRBIT grbit,
                                                 esent_table &table) noexcept {
            JET_TABLEID table_id = JET_tableidNil;
            std::error_code err = make_esent_error_code(
                JetOpenTempTable2(session_id_,
                                  column_definition,
                                  column_count,
                                  lcid,
                                  grbit,
                                  &table_id,
                                  column_id));
            if (esent_err_severity::error != err) {
                table.attach(table_id, session_id_);
            }
            return err;
        }

        esent_table open_temporary_table(JET_COLUMNDEF const *column_definition,
                                         unsigned long column_count,
                                         JET_COLUMNID *column_id,
                                         unsigned long lcid,
                                         JET_GRBIT grbit = JET_bitNil) {
            esent_table table;
            std::error_code err = try_open_temporary_table(column_definition,
                                                           column_count,
                                                           column_id,
                                                           lcid,
                                                           grbit,
                                                           table);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetOpenTempTable2(%u, %u) failed",
                                     column_count,
                                     grbit);
            return table;
        }

        std::error_code try_open_temporary_table(JET_COLUMNDEF const *column_definition,
                                                 unsigned long column_count,
                                                 JET_COLUMNID *column_id,
                                                 JET_UNICODEINDEX *idx_unicode,
                                                 JET_GRBIT grbit,
                                                 esent_table &table) noexcept {
            JET_TABLEID table_id = JET_tableidNil;
            std::error_code err = make_esent_error_code(
                JetOpenTempTable3(session_id_,
                                  column_definition,
                                  column_count,
                                  idx_unicode,
                                  grbit,
                                  &table_id,
                                  column_id));
            if (esent_err_severity::error != err) {
                table.attach(table_id, session_id_);
            }
            return err;
        }

        esent_table open_temporary_table(JET_COLUMNDEF const *column_definition,
                                         unsigned long column_count,
                                         JET_COLUMNID *column_id,
                                         JET_UNICODEINDEX *idx_unicode,
                                         JET_GRBIT grbit = JET_bitNil) {
            esent_table table;
            std::error_code err = try_open_temporary_table(column_definition,
                                                           column_count,
                                                           column_id,
                                                           idx_unicode,
                                                           grbit,
                                                           table);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetOpenTempTable3(%u, %u) failed",
                                     column_count,
                                     grbit);
            return table;
        }

        std::error_code try_open_temporary_table(JET_OPENTEMPORARYTABLE &open_info,
                                                 esent_table &table) noexcept {
            std::error_code err = make_esent_error_code(
                JetOpenTemporaryTable(session_id_,
                                      &open_info));
            if (esent_err_severity::error != err) {
                table.attach(open_info.tableid, session_id_);
            }
            return err;
        }

        esent_table open_temporary_table(JET_OPENTEMPORARYTABLE &open_info) {
            esent_table table;
            std::error_code err = try_open_temporary_table(open_info, table);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetOpenTemporaryTable failed");
            return table;
        }

        std::error_code try_open_temporary_table(JET_OPENTEMPORARYTABLE2 &open_info,
                                                 esent_table &table) noexcept {
            std::error_code err = make_esent_error_code(
                JetOpenTemporaryTable2(session_id_,
                                       &open_info));
            if (esent_err_severity::error != err) {
                table.attach(open_info.tableid, session_id_);
            }
            return err;
        }

        esent_table open_temporary_table(JET_OPENTEMPORARYTABLE2 &open_info) {
            esent_table table;
            std::error_code err = try_open_temporary_table(open_info, table);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetOpenTemporaryTable2 failed");
            return table;
        }

        std::error_code try_set_parameter(unsigned long parameter_id,
                                          void *buffer,
                                          unsigned long buffer_size) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetSessionParameter(session_id_,
                                       parameter_id,
                                       buffer,
                                       buffer_size));
            return err;
        }

        void set_parameter(unsigned long parameter_id,
                           void *buffer,
                           unsigned long buffer_size) {
            std::error_code err = try_set_parameter(parameter_id,
                                                    buffer,
                                                    buffer_size);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                      "JetSetSessionParameter(%u, %u) failed",
                                      parameter_id,
                                      buffer_size);
        }

        std::error_code try_get_parameter(unsigned long parameter_id,
                                          void *buffer,
                                          unsigned long buffer_size,
                                          unsigned long *bytes_returned) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetSessionParameter(session_id_,
                                       parameter_id,
                                       buffer,
                                       buffer_size,
                                       bytes_returned));
            return err;
        }

        void get_parameter(unsigned long parameter_id,
                           void *buffer,
                           unsigned long buffer_size,
                           unsigned long *bytes_returned) {
            std::error_code err = try_get_parameter(parameter_id,
                                                    buffer,
                                                    buffer_size,
                                                    bytes_returned);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                      "JetGetSessionParameter(%u, %u) failed",
                                      parameter_id,
                                      buffer_size);
        }

    private:

        JET_SESID session_id_{ JET_sesidNil };
    };
}
