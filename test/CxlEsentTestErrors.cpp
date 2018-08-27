#include "CxlEsentTest.h"

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

    std::error_code ec_success2 = make_error_code(cxl::esent_err::errSuccess);
    std::error_code ec_nyi2 = make_error_code(cxl::esent_err::wrnNyi);
    std::error_code ec_with_undo2 = make_error_code(cxl::esent_err::wrnFinishWithUndo);
    std::error_code ec_file_close2 = make_error_code(cxl::esent_err::errFileClose);

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

    std::error_condition cat_err = make_error_condition(cxl::esent_err_category::error);
    std::error_condition cat_disk = make_error_condition(cxl::esent_err_category::disk);

    std::cout << "cat_err: " << cat_err.value() << " \"" << cat_err.message() << "\"" << std::endl;
    std::cout << "cat_disk: " << cat_disk.value() << " \"" << cat_disk.message() << "\"" << std::endl;

    std::error_condition sev_success = make_error_condition(cxl::esent_err_severity::success);
    std::error_condition sev_warning = make_error_condition(cxl::esent_err_severity::warning);
    std::error_condition sev_error = make_error_condition(cxl::esent_err_severity::error);

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

void test_jet_instance() {
    cxl::esent_library::set_system_parameter(JET_paramEnableAdvanced, TRUE);
    cxl::esent_library::set_system_parameter(JET_paramDatabasePageSize, cxl::esent_parameter::database_page_size);
    cxl::esent_library::set_system_parameter(JET_paramEnableIndexChecking, TRUE);
    //cxl::esent_library::set_system_parameter(JET_paramOneDatabasePerSession, static_cast<JET_API_PTR>(FALSE));
    //cxl::esent_library::set_system_parameter(JET_paramOneDatabasePerSession, TRUE);
    cxl::esent_library::set_system_parameter(JET_paramEnableViewCache, TRUE);
    cxl::esent_library::set_system_parameter(JET_paramEnableFileCache, 10000);
    cxl::esent_library::set_system_parameter(JET_paramOutstandingIOMax, 128, cxl::esent_set_mode::failure_ok_if_equal_or_greater);
    cxl::esent_library::set_system_parameter(JET_paramMaxCoalesceReadSize, 1048576);
    cxl::esent_library::set_system_parameter(JET_paramMaxCoalesceWriteSize, 1048576);
    cxl::esent_library::set_system_parameter(JET_paramMaxCoalesceReadGapSize, 1048576);
    cxl::esent_library::set_system_parameter(JET_paramMaxCoalesceWriteGapSize, 524288);

    cxl::esent_library::init();
    printf("Enabled multiple instances\n");
    
    cxl::esent_instance inst;
    inst.create(_T("Instance1"), _T("Display name for instance 1"));

    printf("Created instance\n");

    cxl::esent_thread_stats stats;
    {
        inst.set_system_parameter(JET_paramRecovery, _T("On"));
        inst.set_system_parameter(JET_paramMaxOpenTables, cxl::esent_parameter::max_jet_open_tables);
        inst.set_system_parameter(JET_paramMaxCursors, cxl::esent_parameter::max_jet_open_tables);
        inst.set_system_parameter(JET_paramMaxSessions, cxl::esent_parameter::max_jet_sessions);
        inst.set_system_parameter(JET_paramDbExtensionSize, 256);
        inst.set_system_parameter(JET_paramDatabasePageSize, cxl::esent_parameter::database_page_size);

        //inst.set_log_file_path(L"should fail");

        cxl::tstring working_directory{ _T("c:\\#\\testdb") };
        cxl::tstring logs_directory{ working_directory + _T("\\log") };
        cxl::tstring db1_path{ working_directory + _T("\\db1\\testdb1") };
        cxl::tstring db2_path{ working_directory + _T("\\db2\\testdb2") };

        inst.set_log_file_path(logs_directory.c_str());
        printf("Set log file path to %ls\n", logs_directory.c_str());

        inst.set_system_path(working_directory.c_str());
        printf("Set system path %ls\n", working_directory.c_str());

        inst.init();
        printf("Initialized instance\n");

        cxl::esent_session sess{ inst.begin_session() };
        printf("Created session instance\n");

        std::error_code db_err;
        cxl::esent_database db1;
        //
        // First attempt to attach, create if DB does not exist
        //
        db_err = sess.try_attach_database(db1_path.c_str());
        if (cxl::esent_err::errFileNotFound == db_err) {
            JET_CODDING_ERROR_IF(db1.is_valid());
            printf("Database %s does not exist. Creating database.  %i, %s\n",
                   cxl::t_to_a(db1_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());

            std::tie(db1, db_err) = sess.create_database(db1_path.c_str());
            printf("Create database %s completed with %i, %s\n",
                   cxl::t_to_a(db1_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());
            JET_CODDING_ERROR_IF_NOT(db1.is_valid());

        } else {
            if (cxl::esent_err_category::corruption == db_err) {
                printf("Database %s is corrupted. Need to recove by either salvaging databse or recreating database\n",
                       cxl::t_to_a(db1_path).c_str());
            }
            //
            // Any other failure is terminal
            //
            ESENT_THROW_ON_ERROR_FMT(db_err,
                                     "try_attach_database(%s) failed",
                                     cxl::t_to_a(db1_path).c_str());

            printf("Attach database %s completed with %i, %s\n",
                   cxl::t_to_a(db1_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());

            std::tie(db1, db_err) = sess.open_database(db1_path.c_str());
            printf("Open database %s completed with %i, %s\n",
                   cxl::t_to_a(db1_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());
            JET_CODDING_ERROR_IF_NOT(db1.is_valid());
        }
        //
        // Try double attach same database
        //
        db_err = sess.try_attach_database(db1_path.c_str());
        printf("Second attempt to attach database %s completed with %i, %s\n",
               cxl::t_to_a(db1_path).c_str(),
               db_err.value(),
               db_err.message().c_str());
        JET_CODDING_ERROR_IF_NOT(cxl::esent_err::wrnDatabaseAttached == db_err);
        //
        // Try create existing attached database
        //
        cxl::esent_database db1_tmp;
        db_err = sess.try_create_database(db1_path.c_str(),
                                          db1_tmp);
        printf("Attempt to create attached database %s completed with %i, %s\n",
               cxl::t_to_a(db1_path).c_str(),
               db_err.value(),
               db_err.message().c_str());
        JET_CODDING_ERROR_IF(db1_tmp.is_valid());
        //
        // Try create database first, and attach if it already exists
        //
        cxl::esent_database db2;
        db_err = sess.try_create_database(db2_path.c_str(),
                                          db2);
        if (cxl::esent_err_severity::error == db_err) {
            printf("Create database %s completed with %i, %s\n",
                   cxl::t_to_a(db2_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());
            JET_CODDING_ERROR_IF(db2.is_valid());

            db_err = sess.attach_database(db2_path.c_str());
            printf("Attach database %s completed with %i, %s\n",
                   cxl::t_to_a(db2_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());

            std::tie(db2, db_err) = sess.open_database(db2_path.c_str());
            printf("Open database %s completed with %i, %s\n",
                   cxl::t_to_a(db2_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());
            JET_CODDING_ERROR_IF_NOT(db2.is_valid());
        } else {
            printf("Create database %s completed with %i, %s\n",
                   cxl::t_to_a(db2_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());
            JET_CODDING_ERROR_IF_NOT(db2.is_valid());
        }

        //_getch();

        printf("About to destroy scoped objects ...\n");
    }

    if (stats) {
        printf("%s\n", stats.now_as_string().c_str());
    } else {
        std::error_code stats_err = stats.get_reset_error();
        printf("Thread stat reset error %i, %s\n",
               stats_err.value(),
               stats_err.message().c_str());
    }
}

void test_jet_schema() {

    cxl::esent_variant v11{ true };
    cxl::esent_variant v12{ 'a' };
    cxl::esent_variant v13{ 1.0 };
    cxl::esent_variant v14{ cxl::cbuffer{1,2,3} };
    cxl::esent_variant v15{ std::string{'a','b','c'} };
    cxl::esent_variant v16{ nullptr };
    cxl::esent_variant v17{ cxl::esent_empty };
    cxl::esent_variant v18{ cxl::cbuffer{} };
    cxl::esent_variant v19{ std::string{} };

    cxl::esent_ovariant v21{ std::make_optional(true) };
    cxl::esent_ovariant v22{ std::make_optional('a') };
    cxl::esent_ovariant v23{ std::make_optional(1.0) };
    cxl::esent_ovariant v24{ std::make_optional(cxl::cbuffer{1,2,3}) };
    cxl::esent_ovariant v25{ std::make_optional(std::string{'a','b','c'}) };
    cxl::esent_ovariant v26{ nullptr };
    cxl::esent_ovariant v27{ cxl::esent_empty };
    cxl::esent_ovariant v28{ std::make_optional(cxl::cbuffer{}) };
    cxl::esent_ovariant v29{ std::make_optional(std::string{}) };

    bool               v31{ true };
    char               v32{ 'a' };
    double             v33{ 1.0 };
    cxl::cbuffer       v34{1,2,3};
    std::string        v35{'a','b','c'};
    std::nullptr_t     v36;
    cxl::esent_empty_t v37;
    cxl::cbuffer       v38;
    std::string        v39;

    std::optional<bool>         v41{ true };
    std::optional<char>         v42{ 'a' };
    std::optional<double>       v43{ 1.0 };
    std::optional<cxl::cbuffer> v44{ cxl::cbuffer{1,2,3} };
    std::optional<std::string>  v45{ std::string{'a','b','c'} };
    std::optional<cxl::cbuffer> v48;
    std::optional<std::string>  v49;

    cxl::esent_value_buf buf11 = cxl::get_esent_value_buf(v11);
    cxl::esent_value_buf buf12 = cxl::get_esent_value_buf(v12);
    cxl::esent_value_buf buf13 = cxl::get_esent_value_buf(v13);
    cxl::esent_value_buf buf14 = cxl::get_esent_value_buf(v14);
    cxl::esent_value_buf buf15 = cxl::get_esent_value_buf(v15);
    cxl::esent_value_buf buf16 = cxl::get_esent_value_buf(v16);
    cxl::esent_value_buf buf17 = cxl::get_esent_value_buf(v17);
    cxl::esent_value_buf buf18 = cxl::get_esent_value_buf(v18);
    cxl::esent_value_buf buf19 = cxl::get_esent_value_buf(v19);

    cxl::esent_value_buf buf21 = cxl::get_esent_value_buf(v21);
    cxl::esent_value_buf buf22 = cxl::get_esent_value_buf(v22);
    cxl::esent_value_buf buf23 = cxl::get_esent_value_buf(v23);
    cxl::esent_value_buf buf24 = cxl::get_esent_value_buf(v24);
    cxl::esent_value_buf buf25 = cxl::get_esent_value_buf(v25);
    cxl::esent_value_buf buf26 = cxl::get_esent_value_buf(v26);
    cxl::esent_value_buf buf27 = cxl::get_esent_value_buf(v27);
    cxl::esent_value_buf buf28 = cxl::get_esent_value_buf(v28);
    cxl::esent_value_buf buf29 = cxl::get_esent_value_buf(v29);

    cxl::esent_value_buf buf31 = cxl::get_esent_value_buf(v31);
    cxl::esent_value_buf buf32 = cxl::get_esent_value_buf(v32);
    cxl::esent_value_buf buf33 = cxl::get_esent_value_buf(v33);
    cxl::esent_value_buf buf34 = cxl::get_esent_value_buf(v34);
    cxl::esent_value_buf buf35 = cxl::get_esent_value_buf(v35);
    cxl::esent_value_buf buf36 = cxl::get_esent_value_buf(v36);
    cxl::esent_value_buf buf37 = cxl::get_esent_value_buf(v37);
    cxl::esent_value_buf buf38 = cxl::get_esent_value_buf(v38);
    cxl::esent_value_buf buf39 = cxl::get_esent_value_buf(v39);

    cxl::esent_value_buf buf41 = cxl::get_esent_value_buf(v41);
    cxl::esent_value_buf buf42 = cxl::get_esent_value_buf(v42);
    cxl::esent_value_buf buf43 = cxl::get_esent_value_buf(v43);
    cxl::esent_value_buf buf44 = cxl::get_esent_value_buf(v44);
    cxl::esent_value_buf buf45 = cxl::get_esent_value_buf(v45);
    cxl::esent_value_buf buf48 = cxl::get_esent_value_buf(v48);
    cxl::esent_value_buf buf49 = cxl::get_esent_value_buf(v49);

    cxl::esent_default_value_buf def_v11{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v11, false) };
    cxl::esent_default_value_buf def_v12{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v12, 'b') };
    cxl::esent_default_value_buf def_v13{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v13, 2.0 ) };
    cxl::esent_default_value_buf def_v14{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v14, (cxl::cbuffer{4,5,6})) };
    cxl::esent_default_value_buf def_v15{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v15, (std::string{'d','e','f'})) };
    cxl::esent_default_value_buf def_v16{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v16, 3UL) };
    cxl::esent_default_value_buf def_v17{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v17, nullptr) };
    cxl::esent_default_value_buf def_v18{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v18, cxl::esent_empty) };
    cxl::esent_default_value_buf def_v19{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v19, std::string{}) };

    def_v11();
    def_v12();
    def_v13();
    def_v14();
    def_v15();
    def_v16();
    def_v17();
    def_v18();
    def_v19();

    cxl::esent_default_value_buf def_v21{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v21, std::make_optional(false)) };
    cxl::esent_default_value_buf def_v22{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v22, std::make_optional('b')) };
    cxl::esent_default_value_buf def_v23{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v23, std::make_optional(2.0)) };
    cxl::esent_default_value_buf def_v24{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v24, std::make_optional(cxl::cbuffer{4,5,6})) };
    cxl::esent_default_value_buf def_v25{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v25, std::make_optional(std::string{'d','e','f'})) };
    cxl::esent_default_value_buf def_v26{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v26, std::make_optional(3UL)) };
    cxl::esent_default_value_buf def_v27{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v27, nullptr) };
    cxl::esent_default_value_buf def_v28{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v28, cxl::esent_empty) };
    cxl::esent_default_value_buf def_v29{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v29, std::optional<std::string>{}) };

    def_v21();
    def_v22();
    def_v23();
    def_v24();
    def_v25();
    def_v26();
    def_v27();
    def_v28();
    def_v29();

    cxl::esent_default_value_buf def_v31{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v31, false) };
    cxl::esent_default_value_buf def_v32{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v32, 'b') };
    cxl::esent_default_value_buf def_v33{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v33, 2.0) };
    cxl::esent_default_value_buf def_v34{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v34, (cxl::cbuffer{4,5,6})) };
    cxl::esent_default_value_buf def_v35{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v35, (std::string{'d','e','f'})) };
    cxl::esent_default_value_buf def_v36{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v36, nullptr) };
    cxl::esent_default_value_buf def_v37{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v37, cxl::esent_empty) };
    cxl::esent_default_value_buf def_v38{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v38, cxl::cbuffer{}) };
    cxl::esent_default_value_buf def_v39{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v39, std::string{}) };

    def_v31();
    def_v32();
    def_v33();
    def_v34();
    def_v35();
    def_v36();
    def_v37();
    def_v38();
    def_v39();

    cxl::esent_default_value_buf def_v41{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v41, false) };
    cxl::esent_default_value_buf def_v42{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v42, 'b') };
    cxl::esent_default_value_buf def_v43{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v43, 2.0) };
    cxl::esent_default_value_buf def_v44{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v44, (cxl::cbuffer{4,5,6})) };
    cxl::esent_default_value_buf def_v45{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v45, (std::string{'d','e','f'})) };
    cxl::esent_default_value_buf def_v48{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v48, cxl::cbuffer{}) };
    cxl::esent_default_value_buf def_v49{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v49, std::string{}) };

    def_v41();
    def_v42();
    def_v43();
    def_v44();
    def_v45();
    def_v48();
    def_v49();
}
