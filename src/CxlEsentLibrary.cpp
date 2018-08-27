#include "CxlEsent.h"

namespace cxl {

    std::error_code esent_library::try_init() {
        std::error_code err = try_enable_multiple_instances();
        //ESENT_RETURN_ON_ERROR(err);
        //err = esent_default_parameters::try_init();
        return err;
    }

    void esent_library::init() {
        enable_multiple_instances();
        //esent_default_parameters::init();
    }

    std::error_code esent_library::try_set_system_parameter(JET_INSTANCE instance_id,
                                                            JET_SESID session_id,
                                                            ULONG parameter_id,
                                                            JET_API_PTR number_value,
                                                            TCHAR const *string_value,
                                                            esent_set_mode set_mode) {
        std::error_code err = esent_err::errSuccess;

        if (esent_set_mode::default == set_mode) {
            set_mode = string_value 
                ? esent_set_mode::failure_ok_if_equal
                : esent_set_mode::must_succeed;
        }

        err = make_esent_error_code(
            JetSetSystemParameter(&instance_id,
                                  session_id,
                                  parameter_id,
                                  number_value,
                                  string_value));

        JET_CODDING_ERROR_IF(esent_err::errAlreadyInitialized == err ||
                             esent_err::errInvalidInstance == err ||
                             esent_err::errInvalidSesid == err);
        //
        // On error, check set mode to see if it is an acceptable error
        //
        if (err == esent_err_severity::error) {
            switch (set_mode) {
                case esent_set_mode::ignore_failure : {
                    //
                    // Nothing to do here, failures are ignored
                    //
                    err = esent_err::errSuccess;
                    break;
                }
                case esent_set_mode::must_succeed : {
                    //
                    // Failed, return failure to caller.
                    //
                    break;
                }
                case esent_set_mode::failure_ok_if_equal_or_greater:
                case esent_set_mode::failure_ok_if_equal: {
                    //
                    // Testing existing value only applies to numeric values, not string values.
                    //
                    JET_CODDING_ERROR_IF_NOT(nullptr == string_value);
                    //
                    // Get the current parameter to compare with respect to set mode
                    //
                    JET_API_PTR number_value2{ 0 };
                    if (JET_errSuccess == ::JetGetSystemParameter(instance_id,
                                                                  session_id, 
                                                                  parameter_id,
                                                                  &number_value2,
                                                                  nullptr,
                                                                  0) &&
                        (number_value == number_value2 ||
                            set_mode == esent_set_mode::failure_ok_if_equal_or_greater &&
                            number_value > number_value2)
                        ) {
                        err = esent_err::errSuccess;
                        break;
                    }
                    //
                    // We failed to either retrieve the current value, 
                    // or the value is invalid, so we pass out the original err
                    //
                    break;
                }
                case esent_set_mode::default :
                    [[fallthrough]];
                default : {
                    //
                    // Not a valid case
                    //
                    JET_CODDING_ERROR();
                    break;
                }
            }
        }
        return err;
    }
}