#pragma once

namespace ac {

    class esent_file {
    public:

        esent_file() noexcept {
        }

        esent_file(esent_file &&other) noexcept
            : file_{other.file_} 
            , instance_(other.instance_) {
            other.file_ = 0;
            other.instance_ = JET_instanceNil;
        }

        esent_file &operator= (esent_file &&other) noexcept {
            if (this != &other) {
                try_close();
                instance_ = other.instance_;
                file_ = other.file_;
                other.file_ = 0;
                other.instance_ = JET_instanceNil;
            }
            return *this;
        }

        ~esent_file() noexcept {
            std::error_code err = try_close();
        }

        bool is_valid() const noexcept {
            return 0 != file_;
        }

        explicit operator bool() const noexcept {
            return is_valid();
        }

        void attach(JET_HANDLE file, JET_INSTANCE instance) noexcept {
            if (file == 0) {
                JET_CODDING_ERROR_IF(JET_instanceNil == instance);
            } else {
                JET_CODDING_ERROR_IF(file == file_);
                JET_CODDING_ERROR_IF_NOT(JET_instanceNil == instance);
            }
            try_close();
            file_ = file;
            instance_ = instance;
        }

        JET_HANDLE get_handle() {
            return file_;
        }

        std::error_code try_close() noexcept {
            std::error_code err = esent_err::errSuccess;
            if (is_valid()) {
                err = make_esent_error_code(JetCloseFileInstance(instance_, file_));
                JET_CODDING_ERROR_IF(esent_err::errInvalidParameter == err ||
                                     esent_err::errRunningInMultiInstanceMode == err);
                file_ = 0;
                instance_ = JET_instanceNil;
            }
            return err;
        }

        void close() {
            std::error_code err = try_close();
            ESENT_THROW_ON_ERROR(err, 
                                 "JetCloseFileInstance failed");
        }

        std::error_code try_read_file (void *buffer,
                               unsigned long buffer_size,
                               unsigned long *bytes_returned) noexcept {
            std::error_code err = make_esent_error_code(
                JetReadFileInstance(instance_,
                                    file_,
                                    buffer,
                                    buffer_size,
                                    bytes_returned));
        }

        unsigned long read_file (void *buffer,
                           unsigned long buffer_size) {
            unsigned long bytes_returned = 0;
            std::error_code err = try_read_file(buffer,
                                        buffer_size,
                                        &bytes_returned);
            ESENT_THROW_ON_ERROR_FMT(err, 
                                     "JetReadFileInstance(%u) failed",
                                     buffer_size);
        }

    private:
        JET_INSTANCE instance_{ JET_instanceNil };
        JET_HANDLE file_{ 0 };
    };
}
