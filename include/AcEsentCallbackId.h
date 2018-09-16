#pragma once

namespace ac {

    class esent_callback_id {
    public:

        esent_callback_id() noexcept {
        }

        esent_callback_id(esent_callback_id &&other) noexcept
            : callback_id_(other.callback_id_)
            , session_id_(other.session_id_)
            , table_id_(other.table_id_) {
            other.callback_id_ = 0;
            other.session_id_ = JET_sesidNil;
            other.table_id_ = JET_tableidNil;
            other.callback_filter_ = 0;
        }

        esent_callback_id &operator= (esent_callback_id &&other) noexcept {
            if (this != &other) {
                try_unregister();
                callback_id_ = other.callback_id_;
                session_id_ = other.session_id_;
                table_id_ = other.table_id_;
                callback_filter_ = other.callback_filter_;
                other.callback_id_ = 0;
                other.session_id_ = JET_sesidNil;
                other.table_id_ = JET_tableidNil;
                other.callback_filter_ = 0;
            }
            return *this;
        }

        ~esent_callback_id() noexcept {
            std::error_code err = try_unregister();
        }

        bool is_valid() const noexcept {
            return 0 != callback_id_;
        }

        explicit operator bool() const noexcept {
            return is_valid();
        }

        void attach(JET_HANDLE callback_id,
                    JET_CBTYP callback_filter,
                    JET_TABLEID table_id,
                    JET_SESID session_id) noexcept {
            if (0 == callback_id) {
                JET_CODDING_ERROR_IF(table_id == JET_tableidNil);
                JET_CODDING_ERROR_IF(session_id == JET_sesidNil);
            } else {
                JET_CODDING_ERROR_IF(callback_id_ == callback_id);
                JET_CODDING_ERROR_IF_NOT(table_id == JET_tableidNil);
                JET_CODDING_ERROR_IF_NOT(session_id == JET_sesidNil);
            }
            try_unregister();
            callback_id_ = callback_id;
            session_id_ = session_id;
            table_id_ = table_id;
            callback_filter_ = callback_filter;
        }

        JET_HANDLE get_handle() {
            return callback_id_;
        }

        std::error_code try_unregister() noexcept {
            std::error_code err = esent_err::errSuccess;
            if (is_valid()) {
                err = make_esent_error_code(JetUnregisterCallback(session_id_, 
                                                                  table_id_, 
                                                                  callback_filter_, 
                                                                  callback_id_));
                callback_id_ = 0;
                session_id_ = JET_sesidNil;
                table_id_ = JET_tableidNil;
                callback_filter_ = 0;
            }
            return err;
        }

        void unregister() {
            std::error_code err = try_unregister();
            ESENT_THROW_ON_ERROR(err, 
                                 "JetUnregisterCallback failed");
        }

    private:
        JET_CBTYP callback_filter_{0};
        JET_HANDLE callback_id_{0};
        JET_SESID session_id_{ JET_sesidNil };
        JET_TABLEID table_id_{ JET_tableidNil };

    };
}
