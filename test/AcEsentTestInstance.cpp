#include "AcEsentTest.h"

void test_jet_instance() {
    ac::esent_library::set_system_parameter(JET_paramEnableAdvanced, TRUE);
    ac::esent_library::set_system_parameter(JET_paramDatabasePageSize, ac::esent_parameter::database_page_size);
    ac::esent_library::set_system_parameter(JET_paramEnableIndexChecking, TRUE);
    //ac::esent_library::set_system_parameter(JET_paramOneDatabasePerSession, static_cast<JET_API_PTR>(FALSE));
    //ac::esent_library::set_system_parameter(JET_paramOneDatabasePerSession, TRUE);
    ac::esent_library::set_system_parameter(JET_paramEnableViewCache, TRUE);
    ac::esent_library::set_system_parameter(JET_paramEnableFileCache, 10000);
    ac::esent_library::set_system_parameter(JET_paramOutstandingIOMax, 128, ac::esent_set_mode::failure_ok_if_equal_or_greater);
    ac::esent_library::set_system_parameter(JET_paramMaxCoalesceReadSize, 1048576);
    ac::esent_library::set_system_parameter(JET_paramMaxCoalesceWriteSize, 1048576);
    ac::esent_library::set_system_parameter(JET_paramMaxCoalesceReadGapSize, 1048576);
    ac::esent_library::set_system_parameter(JET_paramMaxCoalesceWriteGapSize, 524288);

    ac::esent_library::init();
    printf("Enabled multiple instances\n");
    
    ac::esent_instance inst;
    inst.create(_T("Instance1"), _T("Display name for instance 1"));

    printf("Created instance\n");

    ac::esent_thread_stats stats;
    {
        inst.set_system_parameter(JET_paramRecovery, _T("On"));
        inst.set_system_parameter(JET_paramMaxOpenTables, ac::esent_parameter::max_jet_open_tables);
        inst.set_system_parameter(JET_paramMaxCursors, ac::esent_parameter::max_jet_open_tables);
        inst.set_system_parameter(JET_paramMaxSessions, ac::esent_parameter::max_jet_sessions);
        inst.set_system_parameter(JET_paramDbExtensionSize, 256);
        inst.set_system_parameter(JET_paramDatabasePageSize, ac::esent_parameter::database_page_size);

        //inst.set_log_file_path(L"should fail");

        ac::tstring working_directory{ _T("c:\\#\\testdb") };
        ac::tstring logs_directory{ working_directory + _T("\\log") };
        ac::tstring db1_path{ working_directory + _T("\\db1\\testdb1") };
        ac::tstring db2_path{ working_directory + _T("\\db2\\testdb2") };

        inst.set_log_file_path(logs_directory.c_str());
        printf("Set log file path to %ls\n", logs_directory.c_str());

        inst.set_system_path(working_directory.c_str());
        printf("Set system path %ls\n", working_directory.c_str());

        inst.init();
        printf("Initialized instance\n");

        ac::esent_session sess{ inst.begin_session() };
        printf("Created session instance\n");

        std::error_code db_err;
        ac::esent_database db1;
        //
        // First attempt to attach, create if DB does not exist
        //
        db_err = sess.try_attach_database(db1_path.c_str());
        if (ac::esent_err::errFileNotFound == db_err) {
            JET_CODDING_ERROR_IF(db1.is_valid());
            printf("Database %s does not exist. Creating database.  %i, %s\n",
                   ac::t_to_a(db1_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());

            std::tie(db1, db_err) = sess.create_database(db1_path.c_str());
            printf("Create database %s completed with %i, %s\n",
                   ac::t_to_a(db1_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());
            JET_CODDING_ERROR_IF_NOT(db1.is_valid());

        } else {
            if (ac::esent_err_category::corruption == db_err) {
                printf("Database %s is corrupted. Need to recove by either salvaging databse or recreating database\n",
                    ac::t_to_a(db1_path).c_str());
            }
            //
            // Any other failure is terminal
            //
            ESENT_THROW_ON_ERROR_FMT(db_err,
                                     "try_attach_database(%s) failed",
                                     ac::t_to_a(db1_path).c_str());

            printf("Attach database %s completed with %i, %s\n",
                   ac::t_to_a(db1_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());

            std::tie(db1, db_err) = sess.open_database(db1_path.c_str());
            printf("Open database %s completed with %i, %s\n",
                   ac::t_to_a(db1_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());
            JET_CODDING_ERROR_IF_NOT(db1.is_valid());
        }
        //
        // Try double attach same database
        //
        db_err = sess.try_attach_database(db1_path.c_str());
        printf("Second attempt to attach database %s completed with %i, %s\n",
               ac::t_to_a(db1_path).c_str(),
               db_err.value(),
               db_err.message().c_str());
        JET_CODDING_ERROR_IF_NOT(ac::esent_err::wrnDatabaseAttached == db_err);
        //
        // Try create existing attached database
        //
        ac::esent_database db1_tmp;
        db_err = sess.try_create_database(db1_path.c_str(),
                                          db1_tmp);
        printf("Attempt to create attached database %s completed with %i, %s\n",
               ac::t_to_a(db1_path).c_str(),
               db_err.value(),
               db_err.message().c_str());
        JET_CODDING_ERROR_IF(db1_tmp.is_valid());
        //
        // Try create database first, and attach if it already exists
        //
        ac::esent_database db2;
        db_err = sess.try_create_database(db2_path.c_str(),
                                          db2);
        if (ac::esent_err_severity::error == db_err) {
            printf("Create database %s completed with %i, %s\n",
                   ac::t_to_a(db2_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());
            JET_CODDING_ERROR_IF(db2.is_valid());

            db_err = sess.attach_database(db2_path.c_str());
            printf("Attach database %s completed with %i, %s\n",
                   ac::t_to_a(db2_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());

            std::tie(db2, db_err) = sess.open_database(db2_path.c_str());
            printf("Open database %s completed with %i, %s\n",
                   ac::t_to_a(db2_path).c_str(),
                   db_err.value(),
                   db_err.message().c_str());
            JET_CODDING_ERROR_IF_NOT(db2.is_valid());
        } else {
            printf("Create database %s completed with %i, %s\n",
                   ac::t_to_a(db2_path).c_str(),
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
