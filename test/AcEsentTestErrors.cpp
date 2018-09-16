#include "AcEsentTest.h"

void test_jet_error() {
    std::error_code ec_success = make_esent_error_code(JET_errSuccess);
    std::error_code ec_nyi = make_esent_error_code(JET_wrnNyi);
    std::error_code ec_with_undo = make_esent_error_code(JET_wrnFinishWithUndo);
    std::error_code ec_file_close = make_esent_error_code(JET_errFileClose);
    std::error_code ec_too_many_io = make_esent_error_code(JET_errTooManyIO);

    std::cout << "ec_success: " << ec_success << " \"" << ec_success.message() << "\"" << std::endl;
    std::cout << "ec_nyi: " << ec_nyi << " \"" << ec_nyi.message() << "\"" << std::endl;
    std::cout << "ec_with_undo: " << ec_with_undo << " \"" << ec_with_undo.message() << "\"" << std::endl;
    std::cout << "ec_file_close: " << ec_file_close << " \"" << ec_file_close.message() << "\"" << std::endl;
    std::cout << "ec_too_many_io: " << ec_too_many_io << " \"" << ec_too_many_io.message() << "\"" << std::endl;

    std::error_code ec_success2 = make_error_code(ac::esent_err::errSuccess);
    std::error_code ec_nyi2 = make_error_code(ac::esent_err::wrnNyi);
    std::error_code ec_with_undo2 = make_error_code(ac::esent_err::wrnFinishWithUndo);
    std::error_code ec_file_close2 = make_error_code(ac::esent_err::errFileClose);

    JET_CODDING_ERROR_IF_NOT(ec_success2 == ec_success);
    JET_CODDING_ERROR_IF_NOT(ec_nyi2 == ec_nyi);
    JET_CODDING_ERROR_IF_NOT(ec_with_undo2 == ec_with_undo);
    JET_CODDING_ERROR_IF_NOT(ec_file_close2 == ec_file_close);

    std::error_condition ec_success_dec = ec_success.category().default_error_condition(ec_success.value());
    std::error_condition ec_nyi_dec = ec_nyi.category().default_error_condition(ec_nyi.value());
    std::error_condition ec_with_undo_dec = ec_with_undo.category().default_error_condition(ec_with_undo.value());
    std::error_condition ec_file_close_dec = ec_file_close.category().default_error_condition(ec_file_close.value());
    std::error_condition ec_too_many_io_dec = ec_too_many_io.category().default_error_condition(ec_too_many_io.value());

    JET_CODDING_ERROR_IF_NOT(ec_success_dec == ec_success);
    JET_CODDING_ERROR_IF_NOT(ec_success == ec_success_dec);
    JET_CODDING_ERROR_IF_NOT(ec_nyi_dec == ec_nyi);
    JET_CODDING_ERROR_IF_NOT(ec_nyi == ec_nyi_dec);
    JET_CODDING_ERROR_IF_NOT(ec_with_undo_dec == ec_with_undo);
    JET_CODDING_ERROR_IF_NOT(ec_with_undo == ec_with_undo_dec);
    JET_CODDING_ERROR_IF_NOT(ec_file_close_dec == ec_file_close);
    JET_CODDING_ERROR_IF_NOT(ec_file_close == ec_file_close_dec);
    JET_CODDING_ERROR_IF_NOT(ec_too_many_io_dec == ec_too_many_io);
    JET_CODDING_ERROR_IF_NOT(ec_too_many_io == ec_too_many_io_dec);

    std::cout << "ec_success_dec: " << ec_success_dec.value() << " \"" << ec_success_dec.message() << "\"" << std::endl;
    std::cout << "ec_nyi_dec: " << ec_nyi_dec.value() << " \"" << ec_nyi_dec.message() << "\"" << std::endl;
    std::cout << "ec_with_undo_dec: " << ec_with_undo_dec.value() << " \"" << ec_with_undo_dec.message() << "\"" << std::endl;
    std::cout << "ec_file_close_dec: " << ec_file_close_dec.value() << " \"" << ec_file_close_dec.message() << "\"" << std::endl;
    std::cout << "ec_too_many_io_dec: " << ec_too_many_io_dec.value() << " \"" << ec_too_many_io_dec.message() << "\"" << std::endl;   

    std::error_condition cat_err = make_error_condition(ac::esent_err_category::error);
    std::error_condition cat_disk = make_error_condition(ac::esent_err_category::disk);

    std::cout << "cat_err: " << cat_err.value() << " \"" << cat_err.message() << "\"" << std::endl;
    std::cout << "cat_disk: " << cat_disk.value() << " \"" << cat_disk.message() << "\"" << std::endl;

    std::error_condition sev_success = make_error_condition(ac::esent_err_severity::success);
    std::error_condition sev_warning = make_error_condition(ac::esent_err_severity::warning);
    std::error_condition sev_error = make_error_condition(ac::esent_err_severity::error);

    std::cout << "sev_success: " << sev_success.value() << " \"" << sev_success.message() << "\"" << std::endl;
    std::cout << "sev_warning: " << sev_warning.value() << " \"" << sev_warning.message() << "\"" << std::endl;
    std::cout << "sev_error: " << sev_error.value() << " \"" << sev_error.message() << "\"" << std::endl;

    JET_CODDING_ERROR_IF_NOT(ec_success == sev_success);
    JET_CODDING_ERROR_IF_NOT(sev_success == ec_success);
    JET_CODDING_ERROR_IF(ec_success == sev_warning);
    JET_CODDING_ERROR_IF(sev_warning == ec_success);
    JET_CODDING_ERROR_IF(ec_success == sev_error);
    JET_CODDING_ERROR_IF(sev_error == ec_success);

    JET_CODDING_ERROR_IF_NOT(ec_with_undo == sev_warning);
    JET_CODDING_ERROR_IF_NOT(sev_warning == ec_with_undo);
    JET_CODDING_ERROR_IF(ec_with_undo == sev_success);
    JET_CODDING_ERROR_IF(sev_success == ec_with_undo);
    JET_CODDING_ERROR_IF(ec_with_undo == sev_error);
    JET_CODDING_ERROR_IF(sev_error == ec_with_undo);

    JET_CODDING_ERROR_IF_NOT(ec_file_close == sev_error);
    JET_CODDING_ERROR_IF_NOT(sev_error == ec_file_close);
    JET_CODDING_ERROR_IF(ec_file_close == sev_success);
    JET_CODDING_ERROR_IF(sev_success == ec_file_close);
    JET_CODDING_ERROR_IF(ec_file_close == sev_warning);
    JET_CODDING_ERROR_IF(sev_warning == ec_file_close);

    JET_CODDING_ERROR_IF_NOT(ec_nyi == sev_error);
    JET_CODDING_ERROR_IF_NOT(sev_error == ec_nyi);
    JET_CODDING_ERROR_IF(ec_nyi == sev_success);
    JET_CODDING_ERROR_IF(sev_success == ec_nyi);
    JET_CODDING_ERROR_IF(ec_nyi == sev_warning);
    JET_CODDING_ERROR_IF(sev_warning == ec_file_close);
}
