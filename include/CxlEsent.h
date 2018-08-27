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
namespace cxl {
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

#include "CxlEsentUtil.h"
#include "CxlEsentErrors.h"
#include "CxlEsentLibrary.h"
#include "CxlEsentFile.h"
#include "CxlEsentSnapshot.h"
#include "CxlEsentCallbackId.h"
#include "CxlEsentTable.h"
#include "CxlEsentDatabase.h"
#include "CxlEsentTransaction.h"
#include "CxlEsentSession.h"
#include "CxlEsentInstance.h"
#include "CxlEsentSchema.h"
