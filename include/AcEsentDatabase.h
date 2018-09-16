#pragma once

namespace ac {

    class esent_database {
    public:

        esent_database() noexcept {
        }

        esent_database(esent_database &&other) noexcept
            : db_id_{other.db_id_} 
            , session_id_(other.session_id_) {
            other.db_id_ = JET_dbidNil;
            other.session_id_ = JET_sesidNil;
        }

        esent_database &operator= (esent_database &&other) noexcept {
            if (this != &other) {
                try_close();
                session_id_ = other.session_id_;
                db_id_ = other.db_id_;
                other.db_id_ = JET_dbidNil;
                other.session_id_ = JET_sesidNil;
            }
            return *this;
        }

        ~esent_database() noexcept {
            std::error_code err = try_close();
        }

        bool is_valid() const noexcept {
            return JET_dbidNil != db_id_;
        }

        explicit operator bool() const noexcept {
            return is_valid();
        }

        void attach(JET_DBID db_id, JET_SESID session_id) noexcept {
            if (db_id == JET_dbidNil) {
                JET_CODDING_ERROR_IF_NOT(JET_dbidNil == session_id);
            } else {
                JET_CODDING_ERROR_IF(session_id_ == session_id);
                JET_CODDING_ERROR_IF(JET_dbidNil == session_id);
            }
            try_close();
            db_id_ = db_id;
            session_id_ = session_id;
        }

        JET_SESID get_session() {
            return session_id_;
        }

        JET_DBID get_db() {
            return db_id_;
        }

        std::error_code try_close() noexcept {
            std::error_code err = esent_err::errSuccess;
            if (is_valid()) {
                err = make_esent_error_code(
                    JetCloseDatabase(session_id_, 
                                     db_id_, 
                                     0));

                JET_CODDING_ERROR_IF(esent_err::errDatabaseNotFound == err || 
                                     esent_err::errInvalidDatabaseId == err);
                db_id_ = JET_dbidNil;
                session_id_ = JET_sesidNil;
            }
            return err;
        }

        void close() {
            std::error_code err = try_close();
            ESENT_THROW_ON_ERROR(err, 
                                 "JetCloseDatabase failed");
        }

        std::error_code try_get_object_info(TCHAR const *object_name,
                                            unsigned long information_level,
                                            JET_OBJECTINFO *info) noexcept {
            JET_CODDING_ERROR_IF_NOT(JET_ObjInfo == information_level ||
                                     JET_ObjInfoNoStats == information_level);
            std::error_code err = make_esent_error_code(
                JetGetObjectInfo(session_id_,
                                 db_id_,
                                 JET_objtypTable,
                                 nullptr,
                                 object_name,
                                 reinterpret_cast<void *>(info),
                                 sizeof(&info),
                                 information_level));
            return err;
        }

        JET_OBJECTINFO get_object_info(TCHAR const *object_name,
                                       unsigned long information_level) {
            JET_OBJECTINFO object_info{};
            std::error_code err = try_get_object_info(object_name,
                                                      information_level,
                                                      &object_info);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetObjectInfo(%s, %u, %u) failed",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(object_name)).c_str(),
                                     information_level,
                                     sizeof(object_info));
            return object_info;
        }

        std::error_code try_get_object_list(TCHAR const *object_name,
                                            unsigned long information_level,
                                            JET_OBJECTLIST *info,
                                            esent_table &table) noexcept {
            JET_CODDING_ERROR_IF_NOT(JET_ObjInfoList == information_level ||
                                     JET_ObjInfoListNoStats == information_level);
            std::error_code err = make_esent_error_code(
                JetGetObjectInfo(session_id_,
                                 db_id_,
                                 JET_objtypTable,
                                 nullptr,
                                 object_name,
                                 reinterpret_cast<void *>(info),
                                 sizeof(*info),
                                 information_level));
            if (esent_err_severity::error != err) {
                table.attach(info->tableid, 
                             session_id_);
            }
            return err;
        }

        std::pair<esent_table, JET_OBJECTLIST> get_object_list(TCHAR const *object_name,
                                                                unsigned long information_level) {
            JET_OBJECTLIST object_list{};
            esent_table table;
            std::error_code err = try_get_object_list(object_name,
                                                      information_level,
                                                      &object_list,
                                                      table);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetObjectInfo(%s, %u, %u) failed",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(object_name)).c_str(),
                                     information_level,
                                     sizeof(object_list));
            return std::make_pair(std::move(table), 
                                  object_list);
        }

        std::error_code try_delete_table(TCHAR const *table_name) noexcept {
            std::error_code err = make_esent_error_code(
                JetDeleteTable(session_id_,
                               db_id_,
                               table_name));
            return err;
        }

        void delete_table(TCHAR const *table_name) {
            std::error_code err = try_delete_table(table_name);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetDeleteTable(%s)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(table_name)).c_str());
        }

        std::error_code try_rename_table(TCHAR const *old_table_name,
                                         TCHAR const *new_table_name) noexcept {
            std::error_code err = make_esent_error_code(
                JetRenameTable(session_id_,
                               db_id_,
                               old_table_name,
                               new_table_name));
            return err;
        }

        void rename_table(TCHAR const *old_table_name,
                          TCHAR const *new_table_name) {
            std::error_code err = try_rename_table(old_table_name,
                                                   new_table_name);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetRenameTable(%s, %s)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(old_table_name)).c_str(),
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(new_table_name)).c_str());
        }

        std::error_code try_create_table(TCHAR const *table_name,
                                         unsigned long pages,
                                         unsigned long density,
                                         esent_table &table) noexcept {
            JET_TABLEID table_id = JET_tableidNil;
            std::error_code err = make_esent_error_code(
                JetCreateTable(session_id_,
                               db_id_,
                               table_name,
                               pages,
                               density,
                               &table_id));
            if (esent_err_severity::error != err) {
                table.attach(table_id, session_id_);
            }
            return err;
        }

        esent_table create_table(TCHAR const *table_name,
                                 unsigned long pages,
                                 unsigned long density) {
            esent_table table;
            std::error_code err = try_create_table(table_name,
                                                   pages,
                                                   density,
                                                   table);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetCreateTable(%s, %u, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(table_name)).c_str(),
                                     pages,
                                     density);
            
            return table;
        }

        std::error_code try_open_table(TCHAR const *table_name,
                                       JET_GRBIT grbits,
                                       esent_table &table) noexcept {
            JET_TABLEID table_id = JET_tableidNil;
            std::error_code err = make_esent_error_code(
                JetOpenTable(session_id_,
                             db_id_,
                             table_name,
                             nullptr,
                             0,
                             grbits,
                             &table_id));
            if (esent_err_severity::error != err) {
                table.attach(table_id, session_id_);
            }
            return err;
        }

        esent_table open_table(TCHAR const *table_name,
                               JET_GRBIT grbits = JET_bitNil) {
            esent_table table;
            std::error_code err = try_open_table(table_name,
                                                 grbits,
                                                 table);
            ESENT_THROW_IF_FMT(esent_err::errSuccess != err,
                               err,
                               "JetOpenTable(%s, %u)",
                               t_to_a(SANITIZE_CSTR_FOR_PRINTF(table_name)).c_str(),
                               grbits);
            
            return table;
        }

        std::error_code try_create_table_column_index(JET_TABLECREATE &create_info, 
                                                      esent_table &table) noexcept {
            std::error_code err = make_esent_error_code(
                JetCreateTableColumnIndex(session_id_,
                                          db_id_,
                                          &create_info));
            if (esent_err_severity::error != err) {
                table.attach(create_info.tableid, session_id_);
            }
            return err;
        }

        esent_table create_table_column_index(JET_TABLECREATE &create_info) {
            esent_table table;
            std::error_code err = try_create_table_column_index(create_info, table);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetCreateTableColumnIndex failed");
            return table;
        }

        std::error_code try_create_table_column_index(JET_TABLECREATE2 &create_info, 
                                                      esent_table &table) noexcept {
            std::error_code err = make_esent_error_code(
                JetCreateTableColumnIndex2(session_id_,
                                           db_id_,
                                           &create_info));
            if (esent_err_severity::error != err) {
                table.attach(create_info.tableid, session_id_);
            }
            return err;
        }

        esent_table create_table_column_index(JET_TABLECREATE2 &create_info) {
            esent_table table;
            std::error_code err = try_create_table_column_index(create_info, table);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetCreateTableColumnIndex2 failed");
            return table;
        }

        std::error_code try_create_table_column_index(JET_TABLECREATE3 &create_info, 
                                                      esent_table &table) noexcept {
            std::error_code err = make_esent_error_code(
                JetCreateTableColumnIndex3(session_id_,
                                           db_id_,
                                           &create_info));
            if (esent_err_severity::error != err) {
                table.attach(create_info.tableid, session_id_);
            }
            return err;
        }

        esent_table create_table_column_index(JET_TABLECREATE3 &create_info) {
            esent_table table;
            std::error_code err = try_create_table_column_index(create_info, table);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetCreateTableColumnIndex3 failed");
            return table;
        }

        std::error_code try_create_table_column_index(JET_TABLECREATE4 &create_info, 
                                                      esent_table &table) noexcept {
            std::error_code err = make_esent_error_code(
                JetCreateTableColumnIndex4(session_id_,
                                           db_id_,
                                           &create_info));
            if (esent_err_severity::error != err) {
                table.attach(create_info.tableid, session_id_);
            }
            return err;
        }

        esent_table create_table_column_index(JET_TABLECREATE4 &create_info) {
            esent_table table;
            std::error_code err = try_create_table_column_index(create_info, table);
            ESENT_THROW_ON_ERROR(err, 
                                 "JetCreateTableColumnIndex4 failed");
            return table;
        }

        std::error_code try_get_column_info(unsigned long info_level,
                                            TCHAR const *table_name,
                                            TCHAR const *column_or_id,
                                            void *buffer,
                                            unsigned long buffer_size) noexcept {
            return make_esent_error_code(
                JetGetColumnInfo(session_id_,
                                 db_id_,
                                 table_name,
                                 column_or_id,
                                 buffer,
                                 buffer_size,
                                 info_level));
        }

        bool get_column_info(unsigned long info_level,
                             TCHAR const *table_name,
                             TCHAR const *column_or_id,
                             void *buffer,
                             unsigned long buffer_size) {
            std::error_code err = try_get_column_info(info_level,
                                                      table_name,
                                                      column_or_id,
                                                      buffer,
                                                      buffer_size);
            ESENT_THROW_IF_FMT(esent_err::errSuccess != err && esent_err::errBufferTooSmall != err,
                               err, 
                               "JetGetColumnInfo(%u, %s, %s, %u) failed",
                               info_level,
                               t_to_a(SANITIZE_CSTR_FOR_PRINTF(table_name)).c_str(),
                               t_to_a(SANITIZE_CSTR_FOR_PRINTF(column_or_id)).c_str(),
                               buffer_size);
            return esent_err::errSuccess != err ? true : false;
        }

        std::error_code try_set_column_default_value(TCHAR const *table_name,
                                                     TCHAR const *column_name,
                                                     void *buffer,
                                                     unsigned long buffer_size,
                                                     JET_GRBIT grbit) noexcept {
            return make_esent_error_code(
                JetSetColumnDefaultValue(session_id_,
                                         db_id_,
                                         table_name,
                                         column_name,
                                         buffer,
                                         buffer_size,
                                         grbit));
        }

        bool set_column_default_value(TCHAR const *table_name,
                                      TCHAR const *column_name,
                                      void *buffer,
                                      unsigned long buffer_size,
                                      JET_GRBIT grbit) {
            std::error_code err = try_set_column_default_value(table_name,
                                                               column_name,
                                                               buffer,
                                                               buffer_size,
                                                               grbit);
            ESENT_THROW_IF_FMT(esent_err::errSuccess != err && esent_err::errBufferTooSmall != err,
                               err, 
                               "JetSetColumnDefaultValue(%s, %s, %u, %u) failed",
                               t_to_a(SANITIZE_CSTR_FOR_PRINTF(table_name)).c_str(),
                               t_to_a(SANITIZE_CSTR_FOR_PRINTF(column_name)).c_str(),
                               buffer_size,
                               grbit);
            return esent_err::errSuccess != err ? true : false;
        }

        std::error_code try_get_index_info(unsigned long info_level, 
                                           TCHAR const *table_name,
                                           TCHAR const *index_name,
                                           void *buffer,
                                           unsigned long buffer_size) noexcept {
            return make_esent_error_code(
                JetGetIndexInfo(session_id_,
                                db_id_,
                                table_name,
                                index_name,
                                buffer,
                                buffer_size,
                                info_level));
        }

        bool get_index_info(unsigned long info_level,
                            TCHAR const *table_name,
                            TCHAR const *index_name,
                            void *buffer,
                            unsigned long buffer_size) {
            std::error_code err = try_get_index_info(info_level,
                                                     table_name,
                                                     index_name,
                                                     buffer,
                                                     buffer_size);
            ESENT_THROW_IF_FMT(esent_err::errSuccess != err && esent_err::errBufferTooSmall != err,
                               err, 
                               "JetGetIndexInfo(%u, %s, %s, %u) failed",
                               info_level,
                               t_to_a(SANITIZE_CSTR_FOR_PRINTF(table_name)).c_str(),
                               t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str(),
                               buffer_size);
            return esent_err::errSuccess != err ? true : false;
        }

        std::error_code try_get_info(unsigned long info_level,
                                     void *buffer,
                                     unsigned long buffer_size) noexcept {
            return make_esent_error_code(
                JetGetDatabaseInfo(session_id_,
                                   db_id_,
                                   buffer,
                                   buffer_size,
                                   info_level));
        }

        bool get_info(unsigned long info_level,
                      void *buffer,
                      unsigned long buffer_size) {
            std::error_code err = try_get_info(info_level,
                                               buffer,
                                               buffer_size);
            ESENT_THROW_IF_FMT(esent_err::errSuccess != err && esent_err::errBufferTooSmall != err,
                               err, 
                               "JetGetDatabaseInfo(%u, %u) failed",
                               info_level,
                               buffer_size);
            return esent_err::errSuccess != err ? true : false;
        }

        std::error_code try_defragment(TCHAR const *table_name,
                                       unsigned long *passes,
                                       unsigned long *seconds,
                                       JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetDefragment(session_id_,
                              db_id_,
                              table_name,
                              passes,
                              seconds,
                              grbit));
            return err;
        }

        void defragment(TCHAR const *database_name,
                        TCHAR const *table_name,
                        unsigned long *passes,
                        unsigned long *seconds,
                        JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_defragment(table_name,
                                                 passes,
                                                 seconds,
                                                 grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetDefragment(%s, %s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(database_name)).c_str(),
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(table_name)).c_str(),
                                     grbit);
        }

        std::error_code try_defragment(TCHAR const *table_name,
                                       unsigned long *passes,
                                       unsigned long *seconds,
                                       JET_CALLBACK callback,
                                       JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetDefragment2(session_id_,
                               db_id_,
                               table_name,
                               passes,
                               seconds,
                               callback,
                               grbit));
            return err;
        }

        void defragment(TCHAR const *database_name,
                        TCHAR const *table_name,
                        unsigned long *passes,
                        unsigned long *seconds,
                        JET_CALLBACK callback,
                        JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_defragment(table_name,
                                                 passes,
                                                 seconds,
                                                 callback,
                                                 grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetDefragment2(%s, %s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(database_name)).c_str(),
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(table_name)).c_str(),
                                     grbit);
        }

        std::error_code try_grow(unsigned long cpg,
                                 unsigned long *cpg_returned) noexcept {
            std::error_code err = make_esent_error_code(
                JetGrowDatabase(session_id_,
                                db_id_,
                                cpg,
                                cpg_returned));
            return err;
        }

        unsigned long defragment(unsigned long cpg) {
            unsigned long cpg_returned = 0;
            std::error_code err = try_grow(cpg,
                                           &cpg_returned);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGrowDatabase(%u)",
                                     cpg);
            return cpg_returned;
        }

        std::error_code try_resize(unsigned long cpg,
                                   unsigned long *cpg_returned,
                                   JET_GRBIT grbit) noexcept {
            std::error_code err = make_esent_error_code(
                JetResizeDatabase(session_id_,
                                  db_id_,
                                  cpg,
                                  cpg_returned,
                                  grbit));
            return err;
        }

        unsigned long defragment(unsigned long cpg,
                                 JET_GRBIT grbit) {
            unsigned long cpg_returned = 0;
            std::error_code err = try_resize(cpg,
                                             &cpg_returned,
                                             grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetResizeDatabase(%u, %u)",
                                     cpg,
                                     grbit);
            return cpg_returned;
        }

    private:

        JET_SESID session_id_{ JET_sesidNil };
        JET_DBID db_id_{ JET_dbidNil };
    };
}
