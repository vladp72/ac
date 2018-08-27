#pragma once

namespace cxl {

    class esent_snapshot {
    public:

        esent_snapshot() noexcept {
        }

        esent_snapshot(esent_snapshot &&other) noexcept
            : snapshot_id_{ other.snapshot_id_ } {
            other.snapshot_id_ = 0;
        }

        esent_snapshot &operator=(esent_snapshot &&other) noexcept {
            if (this != &other) {
                close();
                snapshot_id_ = other.snapshot_id_;
                other.snapshot_id_ = 0;
            }
            return *this;
        }

        ~esent_snapshot() noexcept {
            close();
        }

        bool is_valid() const noexcept {
            return snapshot_id_ != 0;
        }

        explicit operator bool() const noexcept {
            return is_valid();
        }

        JET_OSSNAPID get_snapshot_id() noexcept {
            return snapshot_id_;
        }

        void attach(JET_OSSNAPID snapshot_id) noexcept {
            if (0 != snapshot_id) {
                JET_CODDING_ERROR_IF(snapshot_id == snapshot_id_);
            }
            close();
            snapshot_id_ = snapshot_id;
        }

        JET_OSSNAPID detach() noexcept {
            JET_OSSNAPID snapshot_id = snapshot_id_;
            snapshot_id_ = 0;
            return snapshot_id;
        }

        std::error_code try_prepare(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = try_end(JET_bitAbortSnapshot);
            if (!is_valid()) {
                err = make_esent_error_code(JetOSSnapshotPrepare(&snapshot_id_, grbit));
            }
            return err;
        }

        void prepare(JET_GRBIT grbit = JET_bitNil) {
            end(JET_bitAbortSnapshot);
            if (!is_valid()) {
                std::error_code err = make_esent_error_code(JetOSSnapshotPrepare(&snapshot_id_, grbit));
                ESENT_THROW_ON_ERROR_FMT(err,
                                         "JetOSSnapshotPrepare(%u) failed",
                                         grbit);

            }
        }

        std::error_code try_end(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = esent_err::errSuccess;
            if (is_valid()) {
                err = make_esent_error_code(JetOSSnapshotEnd(snapshot_id_, grbit));
                if (esent_err_severity::error == err) {
                    snapshot_id_ = 0;
                } else {
                    JET_CODDING_ERROR_IF(esent_err::errInvalidGrbit == err ||
                                         esent_err::errOSSnapshotInvalidSequence == err ||
                                         esent_err::errOSSnapshotInvalidSnapId == err);
                }
            }
            return err;
        }

        bool end(JET_GRBIT grbit = JET_bitNil) {
            if (is_valid()) {
                std::error_code err = try_end(grbit);
                ESENT_THROW_IF_FMT(esent_err::errSuccess != err && esent_err::errOSSnapshotTimeOut != err,
                                   err,
                                   "JetOSSnapshotEnd(%u) failed",
                                   grbit);
                return (esent_err::errSuccess != err);
            }
        }

        void close() noexcept {
            std::error_code err = try_end();
            err = try_end(JET_bitAbortSnapshot);
            JET_CODDING_ERROR_IF(is_valid());
        }

        std::error_code try_abort(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(JetOSSnapshotAbort(snapshot_id_, grbit));
            JET_CODDING_ERROR_IF_NOT(esent_err::errSuccess == err);
            return err;
        }

        void abort(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_abort(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetOSSnapshotAbort(%u) failed",
                                     grbit);
        }

        std::error_code try_taw(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(JetOSSnapshotThaw(snapshot_id_, grbit));
            JET_CODDING_ERROR_IF_NOT(esent_err::errSuccess == err);
            return err;
        }

        void taw(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_taw(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetOSSnapshotThaw(%u) failed",
                                     grbit);
        }

        std::error_code try_truncate_log(JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(JetOSSnapshotTruncateLog(snapshot_id_, grbit));
            JET_CODDING_ERROR_IF_NOT(esent_err::errSuccess == err);
            return err;
        }

        void truncate_log(JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_truncate_log(grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetOSSnapshotTruncateLog(%u) failed",
                                     grbit);
        }

        std::error_code try_add_instance(JET_INSTANCE instance,
                                 JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(JetOSSnapshotPrepareInstance(snapshot_id_, instance, grbit));
            JET_CODDING_ERROR_IF_NOT(esent_err::errSuccess == err);
            return err;
        }

        void add_instance(JET_INSTANCE instance,
                          JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_add_instance(instance, grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetOSSnapshotPrepareInstance(%u) failed",
                                     grbit);
        }

        std::error_code try_truncate_instance_log(JET_INSTANCE instance,
                                          JET_GRBIT grbit = JET_bitNil) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(JetOSSnapshotTruncateLogInstance(snapshot_id_, instance, grbit));
            JET_CODDING_ERROR_IF_NOT(esent_err::errSuccess == err);
            return err;
        }

        void truncate_instance_log(JET_INSTANCE instance,
                                   JET_GRBIT grbit = JET_bitNil) {
            std::error_code err = try_truncate_instance_log(instance, grbit);
            ESENT_THROW_ON_ERROR_FMT(err,
                                     "JetOSSnapshotTruncateLogInstance(%u) failed",
                                     grbit);
        }

        std::error_code try_freze(unsigned long *instance_info_count,
                          JET_INSTANCE_INFO_W **instance_info) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(JetOSSnapshotFreeze(snapshot_id_, instance_info_count, instance_info, 0));
            return err;
        }

        void freze(unsigned long *instance_info_count,
                   JET_INSTANCE_INFO_W **instance_info) {
            std::error_code err = try_freze(instance_info_count, instance_info);
            ESENT_THROW_ON_ERROR(err,
                                 "JetOSSnapshotFreeze failed");
        }

        std::error_code try_get_freze(unsigned long *instance_info_count,
                              JET_INSTANCE_INFO_W **instance_info) noexcept {
            std::error_code err = esent_err::errSuccess;
            err = make_esent_error_code(JetOSSnapshotGetFreezeInfoW(snapshot_id_, instance_info_count, instance_info, 0));
            return err;
        }

        void get_freze(unsigned long *instance_info_count,
                       JET_INSTANCE_INFO_W **instance_info) {
            std::error_code err = try_freze(instance_info_count, instance_info);
            ESENT_THROW_ON_ERROR( err,
                                  "JetOSSnapshotGetFreezeInfoW failed");
        }

    private:

        JET_OSSNAPID snapshot_id_{ 0 };
    };
}
