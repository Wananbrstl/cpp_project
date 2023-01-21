#include "../include/lbn_json.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

/* TODO: 有必要设置精度嘛？*/
#define EPS 1e-5

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

using namespace lbn;

/*************************************************************/
/* NOTE: 基础的一个等式 */
#define EXPECT_EQ_BASE(equality, expect, actual, format)\
    do {\
        test_count ++;\
        if(equality) {\
            test_pass++;\
        } else {\
            fprintf(stderr, "%s:%d expect : " format " actual :  " format "\n", __FILE__, __LINE__,expect, actual);\
            main_ret = 1;\
        }\
    }while(0)

#define EXPECT_EQ_INT(expect, actual)\
    EXPECT_EQ_BASE(((expect) == (actual)), expect, actual, "%d")

/* FIX: 为什么可以使用等号？*/
#define EXPECT_EQ_DOUBLE(expect, actual)\
    EXPECT_EQ_BASE((expect) == (actual), expect, actual, ".17g")

#define TEST_NUMBER(expect, json)\
    do{\
        value v;\
        EXPECT_EQ_INT(JSON_PARSE_OK, parse(&v, json));\
        EXPECT_EQ_INT(TYPE_NUMBER, getType(&v));\
        EXPECT_EQ_DOUBLE(expect, getNumber(&v));\
    }while(0)

#define TEST_STRING(expect, json)\
    do{\
        value v;\
        INIT(&v);\
        EXPECT_EQ_INT(JSON_PARSE_OK, parse(&v, json));\
        EXPECT_EQ_INT(TYPE_STRING, getType(&v));\
        EXPECT_EQ_STRING(expect, getString(&v), getStringLen(&v));\
        free_str(&v);\
    }while(0)

#define TEST_ERROR(error, json)\
    do{\
        value v;\
        v.type = TYPE_FALSE;\
        EXPECT_EQ_INT(error, parse(&v, json));\
        EXPECT_EQ_INT(TYPE_NULL, getType(&v));\
    }while(0)

#define EXPECT_EQ_STRING(expect, actual, alength)\
    EXPECT_EQ_BASE((sizeof(expect) == alength + 1) && (memcmp(expect, actual, alength) == 0), expect, actual, "%s");

 
/*************************************************************/
/* expect null */
static void test_parse_null() {
    value v;
    v.type = lbn::TYPE_NULL;
    EXPECT_EQ_INT(JSON_PARSE_OK, parse(&v, "null"));
    EXPECT_EQ_INT(TYPE_NULL, getType(&v));
}

/* expect true */
static void test_parse_true() {
    value v;
    v.type = lbn::TYPE_NULL;
    EXPECT_EQ_INT(JSON_PARSE_OK, parse(&v, "true"));
    EXPECT_EQ_INT(TYPE_TRUE, getType(&v));
}

/* expect false */
static void test_parse_false() {
    value v;
    v.type = lbn::TYPE_NULL;
    EXPECT_EQ_INT(JSON_PARSE_OK, parse(&v, "false"));
    EXPECT_EQ_INT(TYPE_FALSE, getType(&v));
}

// static void test_parse_iterator(const char* except, const char* json){
//
// }

static void test_parse_number() {
    TEST_NUMBER(0.0, "0");
    TEST_NUMBER(0.0, "-0");
    TEST_NUMBER(0.0, "-0.0");
    TEST_NUMBER(1.0, "1");
    TEST_NUMBER(-1.0, "-1");
    TEST_NUMBER(1.5, "1.5");
    TEST_NUMBER(-1.5, "-1.5");
    TEST_NUMBER(3.1416, "3.1416");
    TEST_NUMBER(1E10, "1E10");
    TEST_NUMBER(1e10, "1e10");
    TEST_NUMBER(1E+10, "1E+10");
    TEST_NUMBER(1E-10, "1E-10");
    TEST_NUMBER(-1E10, "-1E10");
    TEST_NUMBER(-1e10, "-1e10");
    TEST_NUMBER(-1E+10, "-1E+10");
    TEST_NUMBER(-1E-10, "-1E-10");
    TEST_NUMBER(1.234E+10, "1.234E+10");
    TEST_NUMBER(1.234E-10, "1.234E-10");
    TEST_NUMBER(0.0, "1e-10000"); /* must underflow */

    TEST_NUMBER(1.0000000000000002, "1.0000000000000002"); /* the smallest number > 1 */
    TEST_NUMBER( 4.9406564584124654e-324, "4.9406564584124654e-324"); /* minimum denormal */
    TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
    TEST_NUMBER( 2.2250738585072009e-308, "2.2250738585072009e-308");  /* Max subnormal double */
    TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
    TEST_NUMBER( 2.2250738585072014e-308, "2.2250738585072014e-308");  /* Min normal positive double */
    TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
    TEST_NUMBER( 1.7976931348623157e+308, "1.7976931348623157e+308");  /* Max double */
    TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
}

static void test_parse_invalid_value() {
    value v;
    v.type = lbn::TYPE_FALSE;
    EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, parse(&v, "nul"));
    EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, parse(&v, "?"));
    EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, parse(&v, "Null"));
    EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, parse(&v, "Tre"));
    EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, parse(&v, "flase"));


    /* number test */
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "1.");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "+1");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, ".1");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "INF");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "inf");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "nan");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "NAN");
}

static void test_parse_string() {
    TEST_STRING("", "\"\"");
    TEST_STRING("Hello", "\"Hello\"");
    TEST_STRING("Hello\nWorld", "\"Hello\\nWorld\"");
    TEST_STRING("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
}

static void test_parse_expect_value() {
    TEST_ERROR(JSON_PARSE_EXPECT_VALUE, "");
    TEST_ERROR(JSON_PARSE_EXPECT_VALUE, "  ");
}

static void test_parse_root_not_singluar() {
    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGLUAR, "null x");

    /* invalid number */
    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGLUAR, "0123"); /* after zero should be '.' or nothing */
    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGLUAR, "0x0");
    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGLUAR, "0x123");

}

static void test_parse_number_too_big() {
#if 1
    // TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "1e309");
    // TEST_ERROR(LEPT_PARSE_NUMBER_TOO_BIG, "-1e309");
#endif
}

static void test_parse_missing_quotation_mar() {
    TEST_ERROR(JSON_PARSE_MISS_QUOTATION_MARK, "\"");
    TEST_ERROR(JSON_PARSE_MISS_QUOTATION_MARK, "\"abc\0");
}
static void test_parse_invalid_string_char() {
    TEST_ERROR(JSON_PARSE_INVALID_STRING_CHAR, "\"\x01\"");
    TEST_ERROR(JSON_PARSE_INVALID_STRING_CHAR, "\"\x1F\"");
}

static void test_parse_invalid_string_escape() {
    TEST_ERROR(JSON_PARSE_INVALID_STRING_ESCAPE, "\"\\v\"");
    TEST_ERROR(JSON_PARSE_INVALID_STRING_ESCAPE, "\"\\'\"");
    TEST_ERROR(JSON_PARSE_INVALID_STRING_ESCAPE, "\"\\0\"");
    TEST_ERROR(JSON_PARSE_INVALID_STRING_ESCAPE, "\"\\x12\"");
}

static void test_access_null() {
    value v;
    INIT(&v);
    setString(&v, "a", 1);
    free_str(&v);
    EXPECT_EQ_INT(TYPE_NULL, getType(&v));
    free_str(&v);
}

static void test_access_boolean() {
    value v;
    INIT(&v);
    setString(&v, "a", 1);
    setBoolean(&v, 1);
    /* TODO: 第三章进一步的学习... */
}

static void test_parse() {
    test_parse_null();
    test_parse_true();
    test_parse_false();
    test_parse_number();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singluar();
    test_parse_number_too_big();

    test_parse_missing_quotation_mar();
    test_parse_invalid_string_char();
    test_parse_invalid_string_escape();
    test_parse_string();

}

int main()
{
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return 0;
}
