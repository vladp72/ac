#include "AcEsentTest.h"

int main() {
    int err = 0;
    try {
        printf("-----------test_jet_error---------\n");
        test_jet_error();
        printf("-----------test_jet_schema--------\n");
        test_jet_schema();
        printf("-----------test_jet_instance------\n");
        test_jet_instance();
        printf("-------completed with no errors---\n");
    } catch (std::system_error const &e) {
        std::error_code const ec = e.code();
        err = ec.value();
        printf("\nstd::system_error %i, \"%s\"", ec.value(), e.what());
    } catch (std::exception const &e) {
        err = -1;
        printf("\nstd::exception \"%s\"", e.what());
    }
    printf("---------------exiting------------\n");
    return err;
}
