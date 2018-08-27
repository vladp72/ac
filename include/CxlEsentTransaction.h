#pragma once

namespace cxl {

    class esent_transaction {
    public:

        esent_transaction() noexcept {
        }

        esent_transaction(esent_transaction &&other) noexcept
            : session_id_{ other.session_id_ } {
            other.session_id_ = JET_sesidNil;
        }

        esent_transaction &operator=(esent_transaction &&other) noexcept {
            if (this != &other) {
                if (is_valid()) {
                    try_rollback();
                }
                session_id_ = other.session_id_;
                other.session_id_ = JET_sesidNil;
            }
            return *this;
        }

        ~esent_transaction() {
            std::error_code err;
            if (is_valid()) {
                err = try_rollback();
            }
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
            if (is_valid()) {
                try_rollback();
            }
            session_id_ = session_id;
        }

        JET_SESID detach() noexcept {
            JET_SESID session_id = session_id_;
            session_id_ = JET_sesidNil;
            return session_id;
        }

        std::error_code try_commit(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetCommitTransaction(session_id_, 
                                     grbit));
            JET_CODDING_ERROR_IF(esent_err::errNotInitialized == err ||
                                 esent_err::errSessionSharingViolation == err ||
                                 esent_err::errRestoreInProgress == err);
            session_id_ = JET_sesidNil;
            return err;
        }

        void commit(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_commit(grbit);
            if (is_valid()) {
                ESENT_THROW_ON_ERROR_FMT(err,
                                        "JetCommitTransaction(%u) failed",
                                        grbit);
            }
        }

        std::error_code try_commit(JET_GRBIT grbit,
                                   unsigned long msec_durable_commit,
                                   JET_COMMIT_ID *commit_id ) noexcept {
            std::error_code err = make_esent_error_code(
                JetCommitTransaction2(session_id_, 
                                      grbit,
                                      msec_durable_commit,
                                      commit_id));
            JET_CODDING_ERROR_IF(esent_err::errNotInitialized == err ||
                                 esent_err::errSessionSharingViolation == err ||
                                 esent_err::errRestoreInProgress == err);
            session_id_ = JET_sesidNil;
            return err;
        }

        JET_COMMIT_ID commit(JET_GRBIT grbit,
                             unsigned long msec_durable_commit) {
            JET_COMMIT_ID commit_id{ 0 };
            std::error_code err = try_commit(grbit, 
                                             msec_durable_commit,
                                             &commit_id);
            ESENT_THROW_ON_ERROR_FMT(err,
                                        "JetCommitTransaction2(%u, %u) failed",
                                        grbit,
                                        msec_durable_commit);
            return commit_id;
        }

        std::error_code try_rollback(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = make_esent_error_code(
                JetRollback(session_id_, 
                            grbit));
            JET_CODDING_ERROR_IF(esent_err::errNotInitialized == err ||
                                 esent_err::errSessionSharingViolation == err ||
                                 esent_err::errRestoreInProgress == err);
            session_id_ = JET_sesidNil;
            return err;
        }

        void rollback(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_rollback(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                    "JetRollback(%u) failed",
                                    grbit);
        }

    private:

        JET_SESID session_id_{ JET_sesidNil };
    };
}
