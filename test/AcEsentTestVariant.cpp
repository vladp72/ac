#include "AcEsentTest.h"

void test_jet_schema() {

    ac::esent_variant v11{ true };
    ac::esent_variant v12{ 'a' };
    ac::esent_variant v13{ 1.0 };
    ac::esent_variant v14{ ac::cbuffer{1,2,3} };
    ac::esent_variant v15{ std::string{'a','b','c'} };
    ac::esent_variant v16{ nullptr };
    ac::esent_variant v17{ ac::esent_empty };
    ac::esent_variant v18{ ac::cbuffer{} };
    ac::esent_variant v19{ std::string{} };

    ac::esent_ovariant v21{ std::make_optional(true) };
    ac::esent_ovariant v22{ std::make_optional('a') };
    ac::esent_ovariant v23{ std::make_optional(1.0) };
    ac::esent_ovariant v24{ std::make_optional(ac::cbuffer{1,2,3}) };
    ac::esent_ovariant v25{ std::make_optional(std::string{'a','b','c'}) };
    ac::esent_ovariant v26{ nullptr };
    ac::esent_ovariant v27{ ac::esent_empty };
    ac::esent_ovariant v28{ std::make_optional(ac::cbuffer{}) };
    ac::esent_ovariant v29{ std::make_optional(std::string{}) };

    bool               v31{ true };
    char               v32{ 'a' };
    double             v33{ 1.0 };
    ac::cbuffer       v34{1,2,3};
    std::string        v35{'a','b','c'};
    std::nullptr_t     v36;
    ac::esent_empty_t v37;
    ac::cbuffer       v38;
    std::string        v39;

    std::optional<bool>         v41{ true };
    std::optional<char>         v42{ 'a' };
    std::optional<double>       v43{ 1.0 };
    std::optional<ac::cbuffer> v44{ ac::cbuffer{1,2,3} };
    std::optional<std::string>  v45{ std::string{'a','b','c'} };
    std::optional<ac::cbuffer> v48;
    std::optional<std::string>  v49;

    ac::esent_value_buf buf11 = ac::get_esent_value_buf(v11);
    ac::esent_value_buf buf12 = ac::get_esent_value_buf(v12);
    ac::esent_value_buf buf13 = ac::get_esent_value_buf(v13);
    ac::esent_value_buf buf14 = ac::get_esent_value_buf(v14);
    ac::esent_value_buf buf15 = ac::get_esent_value_buf(v15);
    ac::esent_value_buf buf16 = ac::get_esent_value_buf(v16);
    ac::esent_value_buf buf17 = ac::get_esent_value_buf(v17);
    ac::esent_value_buf buf18 = ac::get_esent_value_buf(v18);
    ac::esent_value_buf buf19 = ac::get_esent_value_buf(v19);

    ac::esent_value_buf buf21 = ac::get_esent_value_buf(v21);
    ac::esent_value_buf buf22 = ac::get_esent_value_buf(v22);
    ac::esent_value_buf buf23 = ac::get_esent_value_buf(v23);
    ac::esent_value_buf buf24 = ac::get_esent_value_buf(v24);
    ac::esent_value_buf buf25 = ac::get_esent_value_buf(v25);
    ac::esent_value_buf buf26 = ac::get_esent_value_buf(v26);
    ac::esent_value_buf buf27 = ac::get_esent_value_buf(v27);
    ac::esent_value_buf buf28 = ac::get_esent_value_buf(v28);
    ac::esent_value_buf buf29 = ac::get_esent_value_buf(v29);

    ac::esent_value_buf buf31 = ac::get_esent_value_buf(v31);
    ac::esent_value_buf buf32 = ac::get_esent_value_buf(v32);
    ac::esent_value_buf buf33 = ac::get_esent_value_buf(v33);
    ac::esent_value_buf buf34 = ac::get_esent_value_buf(v34);
    ac::esent_value_buf buf35 = ac::get_esent_value_buf(v35);
    ac::esent_value_buf buf36 = ac::get_esent_value_buf(v36);
    ac::esent_value_buf buf37 = ac::get_esent_value_buf(v37);
    ac::esent_value_buf buf38 = ac::get_esent_value_buf(v38);
    ac::esent_value_buf buf39 = ac::get_esent_value_buf(v39);

    ac::esent_value_buf buf41 = ac::get_esent_value_buf(v41);
    ac::esent_value_buf buf42 = ac::get_esent_value_buf(v42);
    ac::esent_value_buf buf43 = ac::get_esent_value_buf(v43);
    ac::esent_value_buf buf44 = ac::get_esent_value_buf(v44);
    ac::esent_value_buf buf45 = ac::get_esent_value_buf(v45);
    ac::esent_value_buf buf48 = ac::get_esent_value_buf(v48);
    ac::esent_value_buf buf49 = ac::get_esent_value_buf(v49);

    ac::esent_default_value_buf def_v11{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v11, false) };
    ac::esent_default_value_buf def_v12{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v12, 'b') };
    ac::esent_default_value_buf def_v13{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v13, 2.0 ) };
    ac::esent_default_value_buf def_v14{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v14, (ac::cbuffer{4,5,6})) };
    ac::esent_default_value_buf def_v15{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v15, (std::string{'d','e','f'})) };
    ac::esent_default_value_buf def_v16{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v16, 3UL) };
    ac::esent_default_value_buf def_v17{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v17, nullptr) };
    ac::esent_default_value_buf def_v18{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v18, ac::esent_empty) };
    ac::esent_default_value_buf def_v19{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v19, std::string{}) };

    def_v11();
    def_v12();
    def_v13();
    def_v14();
    def_v15();
    def_v16();
    def_v17();
    def_v18();
    def_v19();

    ac::esent_default_value_buf def_v21{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v21, std::make_optional(false)) };
    ac::esent_default_value_buf def_v22{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v22, std::make_optional('b')) };
    ac::esent_default_value_buf def_v23{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v23, std::make_optional(2.0)) };
    ac::esent_default_value_buf def_v24{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v24, std::make_optional(ac::cbuffer{4,5,6})) };
    ac::esent_default_value_buf def_v25{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v25, std::make_optional(std::string{'d','e','f'})) };
    ac::esent_default_value_buf def_v26{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v26, std::make_optional(3UL)) };
    ac::esent_default_value_buf def_v27{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v27, nullptr) };
    ac::esent_default_value_buf def_v28{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v28, ac::esent_empty) };
    ac::esent_default_value_buf def_v29{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v29, std::optional<std::string>{}) };

    def_v21();
    def_v22();
    def_v23();
    def_v24();
    def_v25();
    def_v26();
    def_v27();
    def_v28();
    def_v29();

    ac::esent_default_value_buf def_v31{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v31, false) };
    ac::esent_default_value_buf def_v32{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v32, 'b') };
    ac::esent_default_value_buf def_v33{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v33, 2.0) };
    ac::esent_default_value_buf def_v34{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v34, (ac::cbuffer{4,5,6})) };
    ac::esent_default_value_buf def_v35{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v35, (std::string{'d','e','f'})) };
    ac::esent_default_value_buf def_v36{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v36, nullptr) };
    ac::esent_default_value_buf def_v37{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v37, ac::esent_empty) };
    ac::esent_default_value_buf def_v38{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v38, ac::cbuffer{}) };
    ac::esent_default_value_buf def_v39{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v39, std::string{}) };

    def_v31();
    def_v32();
    def_v33();
    def_v34();
    def_v35();
    def_v36();
    def_v37();
    def_v38();
    def_v39();

    ac::esent_default_value_buf def_v41{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v41, false) };
    ac::esent_default_value_buf def_v42{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v42, 'b') };
    ac::esent_default_value_buf def_v43{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v43, 2.0) };
    ac::esent_default_value_buf def_v44{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v44, (ac::cbuffer{4,5,6})) };
    ac::esent_default_value_buf def_v45{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v45, (std::string{'d','e','f'})) };
    ac::esent_default_value_buf def_v48{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v48, ac::cbuffer{}) };
    ac::esent_default_value_buf def_v49{ ESENT_INIT_DEFAULT_VALUE_BUFFER(v49, std::string{}) };

    def_v41();
    def_v42();
    def_v43();
    def_v44();
    def_v45();
    def_v48();
    def_v49();
}
