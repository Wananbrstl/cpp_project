#ifndef LBN_JSON_
#define LBN_JSON_

#include <stdio.h>

// JSON data structure
//  - number    1,2,3.4,...
//  - string    "hello world"
//  - array     [...]
//  - obj       {...}
//  - boolen    false, true
//  - null
namespace lbn{ // it's important for a project 

#define INIT(v)          do{ (v)->type = TYPE_NULL; }while(0)

// Type
typedef enum {
    TYPE_FALSE,
    TYPE_TRUE,
    TYPE_STRING,
    TYPE_OBJ,
    TYPE_NUMBER,
    TYPE_NULL,
    TYPE_ARRARY,
    TYPE_NUMBER_TO_BIG,
} Type;

// state of return 
enum {
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,
    JSON_PARSE_INVALID_VALUE,
    JSON_PARSE_ROOT_NOT_SINGLUAR,
    JSON_PARSE_NUMBER_TO_BIG,
    JSON_PARSE_MISS_QUOTATION_MARK,
    JSON_PARSE_INVALID_STRING_CHAR,
    JSON_PARSE_INVALID_STRING_ESCAPE,
};

/* node */
typedef struct {
    union {
        struct {char* ptr; size_t len;}s;
        double num;
    }u;
    Type type;
}value;

/* parse the false and true
 *  Useage:
 *  node* root;
 *  char* json = "...";
 *  int ret = parse(root, json);
 */
int parse(value* root, const char* json);

/* get the json node type*/
Type getType(const value* node);

void setNumber(value* v, double n);

double getNumber(const value* node);

int getBoolean(const value* v);

void setBoolean(value* v, int b);

void setString(value* v, const char* s, size_t len);

char* getString(value* v);

size_t getStringLen(value* v);

void free_str(value* v);

} // namespace 
#endif // LBN_JSON_
