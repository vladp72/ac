#pragma once

namespace cxl {

    using esent_column_info_ptr = crt_unique_ptr<JET_ENUMCOLUMN>;

    class esent_table {
    public:

        esent_table() noexcept {
        }

        esent_table(esent_table &&other) noexcept
            : table_id_{other.table_id_}
            , session_id_(other.session_id_) {
            other.table_id_ = JET_tableidNil;
            other.session_id_ = JET_sesidNil;
        }

        esent_table &operator= (esent_table &&other) noexcept {
            if (this != &other) {
                try_close();
                session_id_ = other.session_id_;
                table_id_ = other.table_id_;
                other.table_id_ = JET_tableidNil;
                other.session_id_ = JET_sesidNil;
            }
            return *this;
        }

        ~esent_table() noexcept {
            std::error_code err = try_close();
            JET_CODDING_ERROR_IF_NOT(esent_err::errSuccess != err);
        }

        bool is_valid() const noexcept {
            return 0 != table_id_;
        }

        explicit operator bool() const noexcept {
            return is_valid();
        }

        void attach(JET_TABLEID table_id, JET_SESID session_id) noexcept {
            if (table_id != JET_tableidNil) {
                JET_CODDING_ERROR_IF(table_id == table_id_);
                JET_CODDING_ERROR_IF(JET_tableidNil == session_id);
            } else {
                JET_CODDING_ERROR_IF_NOT(JET_tableidNil == session_id);
            }
            try_close();
            table_id_ = table_id;
            session_id_ = session_id;
        }

        JET_SESID get_session() noexcept {
            return session_id_;
        }

        JET_TABLEID get_table() noexcept {
            return table_id_;
        }

        std::error_code try_close() noexcept {
            std::error_code err = make_esent_error_code(
                JetCloseTable(session_id_,
                              table_id_));
            //
            // TODO: find what errors should trigger codding error
            //
            table_id_ = JET_tableidNil;
            return err;
        }

        void close() {
            std::error_code err = try_close();
            ESENT_THROW_ON_ERROR(err,
                                 "JetCloseTable");
        }

        std::error_code try_set_sequential(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetTableSequential(session_id_,
                                      table_id_,
                                      grbit));
        }

        void set_sequential(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_set_sequential(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetTableSequential(%u)",
                                     grbit);
        }

        std::error_code try_reset_sequential(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetResetTableSequential(session_id_,
                                        table_id_,
                                        grbit));
        }

        void reset_sequential(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_reset_sequential(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetResetTableSequential(%u)",
                                     grbit);
        }

        std::error_code try_delete_row() noexcept {
            std::error_code err = make_esent_error_code(
                JetDelete(session_id_,
                          table_id_));
        }

        void delete_row() {
            std::error_code err = try_delete_row();
            ESENT_THROW_ON_ERROR(err,
                                 "JetDelete");
        }

        std::error_code try_update_row(void *bookmarks,
                                       unsigned long bookmarks_count,
                                       unsigned long *actual_bookmarks_count) noexcept {
            std::error_code err = make_esent_error_code(
                JetUpdate(session_id_,
                          table_id_,
                          bookmarks,
                          bookmarks_count,
                          actual_bookmarks_count));
        }

        void update_row(void *bookmarks,
                        unsigned long bookmarks_count,
                        unsigned long *actual_bookmarks_count) {
            std::error_code err = try_update_row(bookmarks,
                                                 bookmarks_count,
                                                 actual_bookmarks_count);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetUpdate(%u)",
                                     bookmarks_count);
        }

        std::error_code try_update_row(JET_GRBIT grbit,
                                       void *bookmarks,
                                       unsigned long bookmarks_count,
                                       unsigned long *actual_bookmarks_count) noexcept {
            std::error_code err = make_esent_error_code(
                JetUpdate2(session_id_,
                           table_id_,
                           bookmarks,
                           bookmarks_count,
                           actual_bookmarks_count,
                           grbit));
        }

        void update_row(JET_GRBIT grbit,
                        void *bookmarks,
                        unsigned long bookmarks_count,
                        unsigned long *actual_bookmarks_count) {
            std::error_code err = try_update_row(grbit,
                                                 bookmarks,
                                                 bookmarks_count,
                                                 actual_bookmarks_count);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetUpdate2(%u, %u)",
                                     bookmarks_count,
                                     grbit);
        }

        std::error_code try_escrow_update(JET_COLUMNID column_id,
                                          void *new_value,
                                          unsigned long new_value_size,
                                          void *old_value = nullptr,
                                          unsigned long old_value_size = 0,
                                          unsigned long *old_value_size_returned = nullptr,
                                          JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetEscrowUpdate(session_id_,
                           table_id_,
                           column_id,
                           new_value,
                           new_value_size,
                           old_value,
                           old_value_size,
                           old_value_size_returned,
                           grbit));
        }
        
        void escrow_update(JET_COLUMNID column_id,
                           void *new_value,
                           unsigned long new_value_size,
                           void *old_value = nullptr,
                           unsigned long old_value_size = 0,
                           unsigned long *old_value_size_returned = nullptr,
                           JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_escrow_update(column_id,
                                                    new_value,
                                                    new_value_size,
                                                    old_value,
                                                    old_value_size,
                                                    old_value_size_returned,
                                                    grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetEscrowUpdate(%u, %u)",
                                     new_value_size,
                                     grbit);
        }

        std::error_code try_retrieve_column(JET_COLUMNID column_id,
                                            void *value,
                                            unsigned long value_size,
                                            unsigned long *value_size_returned,
                                            JET_GRBIT grbit = JET_bitNil,
                                            JET_RETINFO *result_info = nullptr) noexcept {
            std::error_code err = make_esent_error_code(
                JetRetrieveColumn(session_id_,
                                  table_id_,
                                  column_id,
                                  value,
                                  value_size,
                                  value_size_returned,
                                  grbit,
                                  result_info));
        }
 
        void retrieve_column(JET_COLUMNID column_id,
                             void *value,
                             unsigned long value_size,
                             unsigned long *value_size_returned,
                             JET_GRBIT grbit = JET_bitNil,
                             JET_RETINFO *result_info = nullptr) {
            std::error_code err = try_retrieve_column(column_id,
                                                      value,
                                                      value_size,
                                                      value_size_returned,
                                                      grbit,
                                                      result_info);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetRetrieveColumn(%u, %u, %u)",
                                     column_id,
                                     value_size,
                                     grbit);
        }
 
        std::error_code try_retrieve_columns(JET_RETRIEVECOLUMN *column_info,
                                             unsigned long column_count) noexcept {
            std::error_code err = make_esent_error_code(
                JetRetrieveColumns(session_id_,
                                   table_id_,
                                   column_info,
                                   column_count));
        }

        bool retrieve_columns(JET_RETRIEVECOLUMN *column_info,
                              unsigned long column_count) {
            std::error_code err = try_retrieve_columns(column_info,
                                                       column_count);
            if (err == esent_err::wrnBufferTruncated) {
                return false;
            }
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetRetrieveColumns(%u)",
                                     column_count);
            return true;
        }

        static void * JET_API enumerate_columns_reallocate(void *, void *block, unsigned long size) {
            return crt_allocator_base::try_reallocate(block, size);
        }

        std::error_code try_enumerate_columns(unsigned long enum_column_id_count,
                                              JET_ENUMCOLUMNID *enum_column_id,
                                              unsigned long *enum_column_count,
                                              JET_ENUMCOLUMN **enum_column,
                                              JET_GRBIT grbit = JET_bitNil,
                                              unsigned long data_max_size = 0,
                                              JET_PFNREALLOC realloc_fn = &esent_table::enumerate_columns_reallocate,
                                              void *realloc_context = nullptr) noexcept {
            std::error_code err = make_esent_error_code(
                JetEnumerateColumns(session_id_,
                                    table_id_,
                                    enum_column_id_count,
                                    enum_column_id,
                                    enum_column_count,
                                    enum_column,
                                    realloc_fn,
                                    realloc_context,
                                    data_max_size,
                                    grbit));
            return err;
        }

        std::error_code try_enumerate_columns(unsigned long *enum_column_count,
                                              JET_ENUMCOLUMN **enum_column,
                                              JET_GRBIT grbit = JET_bitNil,
                                              unsigned long data_max_size = 0,
                                              JET_PFNREALLOC realloc_fn = &esent_table::enumerate_columns_reallocate,
                                              void *realloc_context = nullptr) noexcept {
            return try_enumerate_columns(0,
                                         nullptr,
                                         enum_column_count,
                                         enum_column,
                                         grbit,
                                         data_max_size,
                                         realloc_fn,
                                         realloc_context);
        }

        std::pair<unsigned long, esent_column_info_ptr> enumerate_columns(unsigned long enum_column_id_count,
                                                                          JET_ENUMCOLUMNID *enum_column_id,
                                                                          JET_GRBIT grbit = JET_bitNil,
                                                                          unsigned long data_max_size = 0,
                                                                          JET_PFNREALLOC realloc_fn = &esent_table::enumerate_columns_reallocate,
                                                                          void *realloc_context = nullptr) {
            unsigned long enum_column_count{0};
            JET_ENUMCOLUMN *enum_column{ nullptr };
            std::error_code err = try_enumerate_columns(enum_column_id_count,
                                                        enum_column_id,
                                                        &enum_column_count,
                                                        &enum_column,
                                                        grbit,
                                                        data_max_size,
                                                        realloc_fn,
                                                        realloc_context);

            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetEnumerateColumns(%u, %u, %u)",
                                     enum_column_id_count,
                                     grbit,
                                     data_max_size);


            esent_column_info_ptr column_info{ enum_column };

            return std::make_pair(enum_column_count, std::move(column_info));
        }

        std::pair<unsigned long, esent_column_info_ptr> enumerate_columns(JET_GRBIT grbit = JET_bitNil,
                                                                          unsigned long data_max_size = 0,
                                                                          JET_PFNREALLOC realloc_fn = &esent_table::enumerate_columns_reallocate,
                                                                          void *realloc_context = nullptr) noexcept {
            return enumerate_columns(grbit,
                                     data_max_size,
                                     realloc_fn,
                                     realloc_context);
        }

        std::error_code try_get_record_size(JET_RECSIZE *record_size,
                                            JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetRecordSize(session_id_,
                                 table_id_,
                                 record_size,
                                 grbit));
            return err;
        }

        JET_RECSIZE get_record_size(JET_GRBIT grbit = JET_bitNil) {
            JET_RECSIZE record_size{ };
            std::error_code err = try_get_record_size(&record_size,
                                                      grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetRecordSize(%u)",
                                     grbit);
            return record_size;
        }

        std::error_code try_get_record_size(JET_RECSIZE2 *record_size,
                                            JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetRecordSize2(session_id_,
                                  table_id_,
                                  record_size,
                                  grbit));
            return err;
        }

        JET_RECSIZE2 get_record_size2(JET_GRBIT grbit = JET_bitNil) {
            JET_RECSIZE2 record_size{ };
            std::error_code err = try_get_record_size(&record_size,
                                                      grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetRecordSize2(%u)",
                                     grbit);
            return record_size;
        }

        std::error_code try_set_column(JET_COLUMNID column_id,
                                       void const *data,
                                       unsigned long data_size,
                                       JET_GRBIT grbit = JET_bitNil,
                                       JET_SETINFO *set_info = nullptr) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetColumn(session_id_,
                             table_id_,
                             column_id,
                             data,
                             data_size,
                             grbit,
                             set_info));
            return err;
        }

        JET_SETINFO set_column(JET_COLUMNID column_id,
                               void const *data,
                               unsigned long data_size,
                               JET_GRBIT grbit = JET_bitNil) {
            JET_SETINFO set_info{ };
            std::error_code err = try_set_column(column_id,
                                                 data,
                                                 data_size,
                                                 grbit,
                                                 &set_info);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetColumn(%u, %u)",
                                     data_size,
                                     grbit);
            return set_info;
        }

        std::error_code try_set_column(JET_SETCOLUMN *set_column,
                                       unsigned long column_count) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetColumns(session_id_,
                              table_id_,
                              set_column,
                              column_count));
            return err;
        }

        void set_column(JET_SETCOLUMN *set_column,
                        unsigned long column_count) {
            std::error_code err = try_set_column(set_column,
                                                 column_count);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetColumns(%u)",
                                     column_count);
        }

        std::error_code try_prepare_update(unsigned long prepare = 0) noexcept {
            std::error_code err = make_esent_error_code(
                JetPrepareUpdate(session_id_,
                                 table_id_,
                                 prepare));
            return err;
        }

        void prepare_update(unsigned long prepare = 0) {
            std::error_code err = try_prepare_update(prepare);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetPrepareUpdate(%u)",
                                     prepare);
        }

        std::error_code try_get_record_position(JET_RECPOS *record_position,
                                                unsigned long record_position_count) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetRecordPosition(session_id_,
                                     table_id_,
                                     record_position,
                                     record_position_count));
            return err;
        }

        void get_record_position(JET_RECPOS *record_position,
                                 unsigned long record_position_count) {
            std::error_code err = try_get_record_position(record_position,
                                                          record_position_count);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetRecordPosition(%u)",
                                     record_position_count);
        }

        std::error_code try_goto_record_position(JET_RECPOS &record_position) noexcept {
            std::error_code err = make_esent_error_code(
                JetGotoPosition(session_id_,
                                table_id_,
                                &record_position));
            return err;
        }

        void goto_record_position(JET_RECPOS &record_position) {
            std::error_code err = try_goto_record_position(record_position);
            ESENT_THROW_ON_ERROR(err,
                                 "JetGotoPosition");
        }

        std::error_code try_get_cursor_info(unsigned long info_level,
                                            void *buffer,
                                            unsigned long buffer_size) noexcept {
            return make_esent_error_code(
                JetGetCursorInfo(session_id_,
                                 table_id_,
                                 buffer,
                                 buffer_size,
                                 info_level));
        }

        void get_cursor_info(unsigned long info_level,
                             void *buffer,
                             unsigned long buffer_size) {
            std::error_code err = try_get_cursor_info(info_level,
                                                     buffer,
                                                     buffer_size);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetCursorInfo(%u, %u) failed",
                                     info_level,
                                     buffer_size);
        }

        std::error_code try_duplicate_cursor(esent_table &table,
                                             JET_GRBIT grbit = JET_bitNil) noexcept {
            JET_TABLEID table_id{ JET_tableidNil };
            std::error_code err = make_esent_error_code(
                JetDupCursor(session_id_,
                             table_id_,
                             &table_id,
                             grbit));
            if (esent_err_severity::error != err) {
                table.attach(table_id, session_id_);
            }
            return err;
        }

        esent_table duplicate_cursor(JET_GRBIT grbit = JET_bitNil) {
            esent_table table;
            std::error_code err = try_duplicate_cursor(table,
                                                       grbit);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetDupCursor(%u) failed",
                                     grbit);
            return table;
        }

        std::error_code try_get_current_index(TCHAR *index_name,
                                              unsigned long index_name_size) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetCurrentIndex(session_id_,
                                   table_id_,
                                   index_name,
                                   index_name_size));
            return err;
        }

        void get_current_index(TCHAR *index_name,
                               unsigned long index_name_size) {
            std::error_code err = try_get_current_index(index_name,
                                                        index_name_size);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetCurrentIndex(%u)",
                                     index_name_size);
        }

        std::error_code try_set_current_index(TCHAR const *index_name) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetCurrentIndex(session_id_,
                                   table_id_,
                                   index_name));
            return err;
        }

        void set_current_index(TCHAR const *index_name) {
            std::error_code err = try_set_current_index(index_name);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetCurrentIndex(%s)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str());
        }

        std::error_code try_set_current_index(TCHAR const *index_name,
                                              JET_GRBIT grbit) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetCurrentIndex2(session_id_,
                                    table_id_,
                                    index_name,
                                    grbit));
            return err;
        }

        void set_current_index(TCHAR const *index_name,
                               JET_GRBIT grbit) {
            std::error_code err = try_set_current_index(index_name,
                                                        grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetCurrentIndex2(%s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str(),
                                     grbit);
        }

        std::error_code try_set_current_index(TCHAR const *index_name,
                                              JET_GRBIT grbit,
                                              unsigned long itag_sequence) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetCurrentIndex3(session_id_,
                                    table_id_,
                                    index_name,
                                    grbit,
                                    itag_sequence));
            return err;
        }

        void set_current_index(TCHAR const *index_name,
                               JET_GRBIT grbit,
                               unsigned long itag_sequence) {
            std::error_code err = try_set_current_index(index_name,
                                                        grbit,
                                                        itag_sequence);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetCurrentIndex3(%s, %u, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str(),
                                     grbit,
                                     itag_sequence);
        }

        std::error_code try_set_current_index(JET_INDEXID &index_id,
                                              JET_GRBIT grbit,
                                              unsigned long itag_sequence) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetCurrentIndex4(session_id_,
                                    table_id_,
                                    nullptr,
                                    &index_id,
                                    grbit,
                                    itag_sequence));
            return err;
        }

        void set_current_index(JET_INDEXID &index_id,
                               JET_GRBIT grbit,
                               unsigned long itag_sequence) {
            std::error_code err = try_set_current_index(index_id,
                                                        grbit,
                                                        itag_sequence);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetCurrentIndex4(%u, %u)",
                                     grbit,
                                     itag_sequence);
        }

        std::error_code try_move(long row,
                                 JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetMove(session_id_,
                        table_id_,
                        row,
                        grbit));
            return err;
        }

        void move(long row,
                  JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_move(row,
                                           grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetMove(%i, %u)",
                                     row,
                                     grbit);
        }

        std::error_code try_get_lock(JET_GRBIT grbit) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetLock(session_id_,
                           table_id_,
                           grbit));
            return err;
        }

        bool get_lock(JET_GRBIT grbit) {
            std::error_code err = try_get_lock(grbit);
            ESENT_THROW_IF_FMT(esent_err::errSuccess != err && 
                               esent_err::errTransReadOnly != err &&
                               esent_err::errWriteConflict != err,
                               err, 
                               "JetGetLock(%u) failed",
                               grbit);
            return esent_err::errSuccess != err ? true : false;

        }

        std::error_code try_seek(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetSeek(session_id_,
                        table_id_,
                        grbit));
            return err;
        }

        void seek(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_seek(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSeek(%u)",
                                     grbit);
        }

        std::error_code try_compute_stats() noexcept {
            std::error_code err = make_esent_error_code(
                JetComputeStats(session_id_,
                                table_id_));
            return err;
        }

        void compute_stats() {
            std::error_code err = try_compute_stats();
            ESENT_THROW_ON_ERROR(err,
                                 "JetComputeStats");
        }

        std::error_code try_set_index_range(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetIndexRange(session_id_,
                                 table_id_,
                                 grbit));
            return err;
        }

        void set_index_range(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_set_index_range(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetIndexRange(%u)",
                                     grbit);
        }

        std::error_code try_set_ls(JET_LS ls,
                                   JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetLS(session_id_,
                         table_id_,
                         ls,
                         grbit));
            return err;
        }

        void set_ls(JET_LS ls,
                    JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_set_ls(ls,
                                             grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetLS(0x%p, %u)",
                                     ls,
                                     grbit);
        }

        std::error_code try_get_ls(JET_LS *ls,
                                   JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetLS(session_id_,
                         table_id_,
                         ls,
                         grbit));
            return err;
        }

        void get_ls(JET_LS *ls,
                    JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_get_ls(ls,
                                             grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetLS(%u)",
                                     grbit);
        }

        std::error_code try_set_cursor_filter(JET_INDEX_COLUMN *column_filter,
                                              unsigned long column_filter_count,
                                              JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetSetCursorFilter(session_id_,
                                   table_id_,
                                   column_filter,
                                   column_filter_count,
                                   grbit));
            return err;
        }

        void set_cursor_filter(JET_INDEX_COLUMN *column_filter,
                               unsigned long column_filter_count,
                               JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_set_cursor_filter(column_filter,
                                                        column_filter_count,
                                                        grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetSetCursorFilter(%u, %u)",
                                     column_filter_count,
                                     grbit);
        }

        std::error_code try_make_key(void *data,
                                     unsigned long data_size,
                                     JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetMakeKey(session_id_,
                           table_id_,
                           data,
                           data_size,
                           grbit));
            return err;
        }

        void make_key(void *data,
                      unsigned long data_size,
                      JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_make_key(data,
                                               data_size,
                                               grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetMakeKey(%u, %u)",
                                     data_size,
                                     grbit);
        }

        std::error_code try_prepare_keys(void const **key_ptr_array,
                                         unsigned long const *key_legth_array,
                                         long key_count,
                                         long *keys_prepared,
                                         JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetPrereadKeys(session_id_,
                               table_id_,
                               key_ptr_array,
                               key_legth_array,
                               key_count,
                               keys_prepared,
                               grbit));
            return err;
        }

        long prepare_keys(void const **key_ptr_array,
                          unsigned long const *key_legth_array,
                          long key_count,
                          JET_GRBIT grbit = JET_bitNil) {
            long keys_prepared{ 0 };
            std::error_code err = try_prepare_keys(key_ptr_array,
                                                   key_legth_array,
                                                   key_count,
                                                   &keys_prepared,
                                                   grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetPrereadKeys(%u, %u)",
                                     key_count,
                                     grbit);
            return keys_prepared;
        }

        std::error_code try_prepare_index_ranges(JET_INDEX_RANGE const *index_ranges,
                                                 unsigned long index_ranges_count,
                                                 unsigned long *ranges_prepared,
                                                 JET_COLUMNID const *column_id_prepared,
                                                 unsigned long column_id_count,
                                                 JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetPrereadIndexRanges(session_id_,
                                      table_id_,
                                      index_ranges,
                                      index_ranges_count,
                                      ranges_prepared,
                                      column_id_prepared,
                                      column_id_count,
                                      grbit));
            return err;
        }

        long prepare_index_ranges(JET_INDEX_RANGE const *index_ranges,
                                  unsigned long index_ranges_count,
                                  unsigned long *ranges_prepared,
                                  JET_COLUMNID const *column_id_prepared,
                                  unsigned long column_id_count,
                                  JET_GRBIT grbit = JET_bitNil) {
            long keys_prepared{ 0 };
            std::error_code err = try_prepare_index_ranges(index_ranges,
                                                           index_ranges_count,
                                                           ranges_prepared,
                                                           column_id_prepared,
                                                           column_id_count,
                                                           grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetPrereadIndexRanges(%u, %u, %u)",
                                     index_ranges_count,
                                     column_id_count,
                                     grbit);
            return keys_prepared;
        }

        std::error_code try_get_bookmark(void *bookmark,
                                         unsigned long size,
                                         unsigned long *actual_size) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetBookmark(session_id_,
                               table_id_,
                               bookmark,
                               size,
                               actual_size));
            return err;
        }

        long get_bookmark(void *bookmark,
                          unsigned long size) {
            unsigned long actual_size{ 0 };
            std::error_code err = try_get_bookmark(bookmark,
                                                   size,
                                                   &actual_size);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetBookmark(%u)",
                                     size);
            return actual_size;
        }

        std::error_code try_goto_bookmark(void *bookmark,
                                          unsigned long size) noexcept {
            std::error_code err = make_esent_error_code(
                JetGotoBookmark(session_id_,
                                table_id_,
                                bookmark,
                                size));
            return err;
        }

        void goto_bookmark(void *bookmark,
                           unsigned long size) {
            std::error_code err = try_goto_bookmark(bookmark,
                                                    size);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGotoBookmark(%u)",
                                     size);
        }

        std::error_code try_get_secondary_index_bookmark(void *secondary_key,
                                                         unsigned long secondary_key_size,
                                                         unsigned long *secondary_key_actual_size,
                                                         void *primary_bookmark,
                                                         unsigned long primary_bookmark_size,
                                                         unsigned long *primary_bookmark_actual_size,
                                                         JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetGetSecondaryIndexBookmark(session_id_,
                                             table_id_,
                                             secondary_key,
                                             secondary_key_size,
                                             secondary_key_actual_size,
                                             primary_bookmark,
                                             primary_bookmark_size,
                                             primary_bookmark_actual_size,
                                             grbit));
            return err;
        }

        long get_secondary_index_bookmark(void *secondary_key,
                                          unsigned long secondary_key_size,
                                          unsigned long *secondary_key_actual_size,
                                          void *primary_bookmark,
                                          unsigned long primary_bookmark_size,
                                          unsigned long *primary_bookmark_actual_size,
                                          JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_get_secondary_index_bookmark(secondary_key,
                                                                   secondary_key_size,
                                                                   secondary_key_actual_size,
                                                                   primary_bookmark,
                                                                   primary_bookmark_size,
                                                                   primary_bookmark_actual_size,
                                                                   grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGetSecondaryIndexBookmark(%u, %u, %u)",
                                     secondary_key_size,
                                     primary_bookmark_size,
                                     grbit);
        }

        std::error_code try_goto_secondary_index_bookmark(void *secondary_key,
                                                         unsigned long secondary_key_size,
                                                         void *primary_bookmark,
                                                         unsigned long primary_bookmark_size,
                                                         JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetGotoSecondaryIndexBookmark(session_id_,
                                              table_id_,
                                              secondary_key,
                                              secondary_key_size,
                                              primary_bookmark,
                                              primary_bookmark_size,
                                              grbit));
            return err;
        }
        
        long goto_secondary_index_bookmark(void *secondary_key,
                                           unsigned long secondary_key_size,
                                           void *primary_bookmark,
                                           unsigned long primary_bookmark_size,
                                           JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_goto_secondary_index_bookmark(secondary_key,
                                                                    secondary_key_size,
                                                                    primary_bookmark,
                                                                    primary_bookmark_size,
                                                                    grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetGotoSecondaryIndexBookmark(%u, %u, %u)",
                                     secondary_key_size,
                                     primary_bookmark_size,
                                     grbit);
        }

        std::error_code try_count_index_records(unsigned long *count,
                                                unsigned long count_limit = 0) noexcept {
            std::error_code err = make_esent_error_code(
                JetIndexRecordCount(session_id_,
                                    table_id_,
                                    count,
                                    count_limit));
            return err;
        }

        unsigned long count_index_records(unsigned long count_limit = 0) {
            unsigned long count{ 0 };
            std::error_code err = try_count_index_records(&count,
                                                          count_limit);
            ESENT_THROW_ON_ERROR(err,
                                 "JetIndexRecordCount(%u)");
            return count;
        }

        std::error_code try_retrieve_key(void *key,
                                         unsigned long size,
                                         unsigned long *actual_size,
                                         JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetRetrieveKey(session_id_,
                               table_id_,
                               key,
                               size,
                               actual_size,
                               grbit));
            return err;
        }

        unsigned long retrieve_key(void *key,
                                   unsigned long size,
                                   unsigned long *actual_size,
                                   JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_retrieve_key(key,
                                                   size,
                                                   actual_size,
                                                   grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetRetrieveKey(%u, %u)",
                                     size,
                                     grbit);
        }

        std::error_code try_register_callback(JET_CBTYP callback_filter,
                                              JET_CALLBACK callback,
                                              void *callback_context,
                                              esent_callback_id &callback_id) noexcept {
            JET_HANDLE callback_id_handle{ 0 };
            std::error_code err = make_esent_error_code(
                JetRegisterCallback(session_id_,
                                    table_id_,
                                    callback_filter,
                                    callback,
                                    callback_context,
                                    &callback_id_handle));
            if (esent_err_severity::error != err) {
                callback_id.attach(callback_id_handle, 
                                   callback_filter, 
                              table_id_, session_id_);
            }
            return err;
        }

        esent_callback_id register_callback(JET_CBTYP callback_filter,
                                            JET_CALLBACK callback,
                                            void *callback_context) {
            esent_callback_id callback_id;
            std::error_code err = try_register_callback(callback_filter,
                                                        callback,
                                                        callback_context,
                                                        callback_id);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetRegisterCallback(%u, %p)",
                                     callback_filter,
                                     callback_context);
            return callback_id;
        }

        std::error_code try_get_table_info(unsigned long info_level,
                                           void *buffer,
                                           unsigned long buffer_size) noexcept {
            return make_esent_error_code(
                JetGetTableInfo(session_id_,
                                table_id_,
                                buffer,
                                buffer_size,
                                info_level));
        }

        void get_table_info(unsigned long info_level,
                            void *buffer,
                            unsigned long buffer_size) {
            std::error_code err = try_get_table_info(info_level,
                                                     buffer,
                                                     buffer_size);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetTableInfo(%u, %u) failed",
                                     info_level,
                                     buffer_size);
        }

        std::error_code try_get_table_column_info(TCHAR const *column_name,
                                                  unsigned long info_level,
                                                  void *buffer,
                                                  unsigned long buffer_size) noexcept {
            return make_esent_error_code(
                JetGetTableColumnInfo(session_id_,
                                      table_id_,
                                      column_name,
                                      buffer,
                                      buffer_size,
                                      info_level));
        }

        void get_table_column_info(TCHAR const *column_name,
                                   unsigned long info_level,
                                   void *buffer,
                                   unsigned long buffer_size) {
            std::error_code err = try_get_table_column_info(column_name,
                                                            info_level,
                                                            buffer,
                                                            buffer_size);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetGetTableColumnInfo(%s, %u, %u) failed",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(column_name)).c_str(),
                                     info_level,
                                     buffer_size);
        }

        std::error_code try_add_column(TCHAR const *column_name,
                                       JET_COLUMNDEF &column_definition,
                                       void const *default_value,
                                       unsigned long default_value_size,
                                       JET_COLUMNID &column_id) noexcept {
            return make_esent_error_code(
                JetAddColumn(session_id_,
                             table_id_,
                             column_name,
                             &column_definition,
                             default_value,
                             default_value_size,
                             &column_id));
        }

        JET_COLUMNID add_column(TCHAR const *column_name,
                                       JET_COLUMNDEF &column_definition,
                                       void const *default_value,
                                       unsigned long default_value_size) {
            JET_COLUMNID column_id{ 0 };
            std::error_code err = try_add_column(column_name,
                                                 column_definition,
                                                 default_value,
                                                 default_value_size,
                                                 column_id);
            //
            //JET_errColumnDuplicate when column already exists
            //
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetAddColumn(%s, %u) failed",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(column_name)).c_str(),
                                     default_value_size);

            
            return column_id;
        }

        std::error_code try_delete_column(TCHAR const *column_name) noexcept {
            std::error_code err = make_esent_error_code(
                JetDeleteColumn(session_id_,
                               table_id_,
                               column_name));
            return err;
        }

        void delete_column(TCHAR const *column_name) {
            std::error_code err = try_delete_column(column_name);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetDeleteColumn(%s)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(column_name)).c_str());
        }

        std::error_code try_rename_column(TCHAR const *old_name,
                                          TCHAR const *new_name,
                                          JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetRenameColumn(session_id_,
                                table_id_,
                                old_name,
                                new_name,
                                grbit));
            return err;
        }

        void rename_column(TCHAR const *old_name,
                           TCHAR const *new_name,
                           JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_rename_column(old_name,
                                                    new_name,
                                                    grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetRenameColumn(%s, %s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(old_name)).c_str(),
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(new_name)).c_str(),
                                     grbit);
        }

        std::error_code try_get_index_info(unsigned long info_level, 
                                           TCHAR const *index_name,
                                           void *buffer,
                                           unsigned long buffer_size) noexcept {
            return make_esent_error_code(
                JetGetTableIndexInfo(session_id_,
                                     table_id_,
                                     index_name,
                                     buffer,
                                     buffer_size,
                                     info_level));
        }

        bool get_index_info(unsigned long info_level,
                            TCHAR const *index_name,
                            void *buffer,
                            unsigned long buffer_size) {
            std::error_code err = try_get_index_info(info_level,
                                                     index_name,
                                                     buffer,
                                                     buffer_size);
            ESENT_THROW_IF_FMT(esent_err::errSuccess != err && esent_err::errBufferTooSmall != err,
                               err, 
                               "JetGetTableIndexInfo(%u, %s, %u) failed",
                               info_level,
                               t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str(),
                               buffer_size);
            return esent_err::errSuccess != err ? true : false;
        }

        std::error_code try_create_index(TCHAR const *index_name,
                                         JET_GRBIT grbit,
                                         TCHAR const *key,
                                         unsigned long key_length,
                                         unsigned long density) noexcept {
            std::error_code err = make_esent_error_code(
                JetCreateIndex(session_id_,
                               table_id_,
                               index_name,
                               grbit,
                               key,
                               key_length,
                               density));
            return err;
        }

        void create_index(TCHAR const *index_name,
                          JET_GRBIT grbit,
                          TCHAR const *key,
                          unsigned long key_length,
                          unsigned long density) {
            std::error_code err = try_create_index(index_name,
                                                   grbit,
                                                   key,
                                                   key_length,
                                                   density);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetCreateIndex(%s, %u, %u, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str(),
                                     grbit,
                                     key_length,
                                     density);
        }

        std::error_code try_create_index(TCHAR const *index_name,
                                         JET_INDEXCREATE &index_info,
                                         unsigned long index_create) noexcept {
            std::error_code err = make_esent_error_code(
                JetCreateIndex2(session_id_,
                                table_id_,
                                &index_info,
                                index_create));
            return err;
        }

        void create_index(TCHAR const *index_name,
                          JET_INDEXCREATE &index_info,
                          unsigned long index_create) {
            std::error_code err = try_create_index(index_name,
                                                   index_info,
                                                   index_create);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetCreateIndex2(%s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str(),
                                     index_create);
        }

        std::error_code try_create_index(TCHAR const *index_name,
                                         JET_INDEXCREATE2 &index_info,
                                         unsigned long index_create) noexcept {
            std::error_code err = make_esent_error_code(
                JetCreateIndex3(session_id_,
                                table_id_,
                                &index_info,
                                index_create));
            return err;
        }

        void create_index(TCHAR const *index_name,
                          JET_INDEXCREATE2 &index_info,
                          unsigned long index_create) {
            std::error_code err = try_create_index(index_name,
                                                   index_info,
                                                   index_create);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetCreateIndex3(%s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str(),
                                     index_create);
        }

        std::error_code try_create_index(TCHAR const *index_name,
                                         JET_INDEXCREATE3 &index_info,
                                         unsigned long index_create) noexcept {
            std::error_code err = make_esent_error_code(
                JetCreateIndex4(session_id_,
                                table_id_,
                                &index_info,
                                index_create));
            return err;
        }

        void create_index(TCHAR const *index_name,
                          JET_INDEXCREATE3 &index_info,
                          unsigned long index_create) {
            std::error_code err = try_create_index(index_name,
                                                   index_info,
                                                   index_create);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetCreateIndex4(%s, %u)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str(),
                                     index_create);
        }

        std::error_code try_delete_index(TCHAR const *index_name) noexcept {
            std::error_code err = make_esent_error_code(
                JetDeleteIndex(session_id_,
                               table_id_,
                               index_name));
            return err;
        }

        void delete_index(TCHAR const *index_name) {
            std::error_code err = try_delete_index(index_name);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetDeleteIndex(%s)",
                                     t_to_a(SANITIZE_CSTR_FOR_PRINTF(index_name)).c_str());
        }

    private:

        JET_SESID session_id_{ JET_sesidNil };
        JET_TABLEID table_id_{ JET_tableidNil };
    };
}
