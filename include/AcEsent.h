#pragma once

#include <windows.h>
#include <tchar.h>
#include <esent.h>

#include <vector>
#include <string>
#include <set>
#include <optional>
#include <variant>

#pragma comment( lib, "esent.lib" )

//
// Forward declarations
//
namespace ac {
    class esent_library;
    class esent_error_condition_category_t;
    class esent_error_category_t;
    class esent_file;
    class esent_snapshot;
    class esent_database;
    class esent_table;
    class esent_session;
    class esent_transaction;
    class esent_instance;
    class esent_callback_id;
}

#include "AcEsentUtil.h"
#include "AcEsentErrors.h"
#include "AcEsentLibrary.h"
#include "AcEsentFile.h"
#include "AcEsentSnapshot.h"
#include "AcEsentCallbackId.h"
#include "AcEsentTable.h"
#include "AcEsentDatabase.h"
#include "AcEsentTransaction.h"
#include "AcEsentSession.h"
#include "AcEsentInstance.h"
#include "AcEsentSchema.h"
