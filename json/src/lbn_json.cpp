#include "../include/lbn_json.h"
#include <cstdlib>
#include <cstring>
#include <math.h>   //HUGE NUMBER
#include <errno.h>  //ERROR NUMBER
#include <assert.h> //ASSERT
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

namespace lbn{
#define PARSE_STACK_INIT_SIZE 255
#define ISDIGIT(ch)      ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)  ((ch) >= '1' && (ch) <= '9')
/*TODO: 为什么要设置成 do{...}while(0)形式？*/
#define SET_NULL(v)      free_str(v);
#define PUTC(c, ch)      do{ *(char*)context_push(c, sizeof(char)) = (ch);}while(0)

/* 希望不会出错 */
#define EXPECT(c, ch)\
    do{\
        assert(*c->json == (ch));\
        c->json++;\
    }while(0)

/* for pass the parameters */
typedef struct {
    const char* json;
    char* stack;
    size_t top, size;
}context;

/* white space*/
static void parse_whitespace(context* c){
    const char* p = c->json;
    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

/* push operator */
static void* context_push(context* c, size_t size) {
    void* ret;
    assert(nullptr != c && size > 0);
    if(c->top + size >= c->size) {
        if(c->size == 0) 
            c->size = PARSE_STACK_INIT_SIZE;
        while(c->top + size >= c->size) 
            c->size += c->size >> 1;
        c->stack = (char*)realloc(c->stack, c->size);
    }
    ret = c->stack + c->top;
    c->top += size;
    return ret;
}

/* pop operator */
static void* context_pop(context* c, size_t size) {
    assert(c->top >= size);
    return c->stack + (c->top -= size);
}

/* For String */
void free_str(value* v) {
    if(v->type == TYPE_STRING) {
        delete v->u.s.ptr;
    }
    v->type = TYPE_NULL;
}

/* get a memory */
void set_str(value* v, const char* ch, size_t size) {
    assert(nullptr != v && (nullptr != ch || size == 0));
    v->type = TYPE_STRING;
    ch = new char[size+1];
    memcpy(v->u.s.ptr, ch, size);
    v->u.s.ptr[size] = '\0'; //end flag
    v->type = TYPE_STRING;
}

/********************************************************************************/
/* just one function */
static int parse_literal(context* c, value* v, const char* literal, Type type) {
    assert(nullptr != c && nullptr != v);
    // EXPECT(c, literal[0]);
    v->type =  TYPE_NULL;
    for(int idx = 0; literal[idx] != '\0'; ++idx, c->json++) {
        if(!c->json || *c->json != literal[idx]) return JSON_PARSE_INVALID_VALUE;
    }
    v->type = type;
    return JSON_PARSE_OK;
}
/* parse null */
static int parse_null(context* c, value* v) {
    EXPECT(c, 'n');
    if( c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l' ) // error
        return JSON_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = TYPE_NULL;
    return JSON_PARSE_OK;
}

/* parse true */
static int parse_true(context* c, value* v) {
    //BUG little or big ?
    EXPECT(c, 't'); 
    if( c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return JSON_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = TYPE_TRUE;
    return JSON_PARSE_OK;
}

/* parse true */
static int parse_false(context* c, value* v) {
    //BUG  big or litte?
    EXPECT(c, 'f'); 
    if( c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return JSON_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = TYPE_FALSE;
    return JSON_PARSE_OK;
}
/********************************************************************************/

/* for number*/
static int parse_number(context* c, value* v) {
    const char* p = c->json;
    if (*p == '-') p++;
    if (*p == '0') p++;
    else {
        if (!ISDIGIT1TO9(*p)) return JSON_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++);
    }
    if (*p == '.') {
        p++;
        if (!ISDIGIT(*p)) return JSON_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p) ; p++);
    }
    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '+' || *p == '-') p++;
        if (!ISDIGIT(*p)) return JSON_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++);
    }
    errno = 0;
    v->u.num = strtod(c->json, NULL);
    if (errno == ERANGE && (v->u.num == HUGE_VAL || v->u.num == -HUGE_VAL))
        return JSON_PARSE_NUMBER_TO_BIG;
    v->type = TYPE_NUMBER;
    c->json = p;
    return JSON_PARSE_OK;
}

/* for string */ 
static int parse_string(context* c, value* v) {
    size_t head = c->top, len;
    const char* p;
    EXPECT(c, '\"');
    p = c->json; // "\"\v.."
    for(;;) {
        printf("p = %s\n", p);
        char  ch = *p++;
        printf("ch = %c\n", ch);
        switch (ch) {
            case '\"': 
                len = c->top - head;
                set_str(v, (const char*)context_pop(c, len), len);
                c->json = p;
                return JSON_PARSE_OK;
            case '\0' : 
                c->top = head;
                return JSON_PARSE_MISS_QUOTATION_MARK;
            case '\\' :  // 转义符
                switch(*p++) {
                    case '\\' : PUTC(c, '\\'); break;
                    case '\"' : PUTC(c, '\"'); break;
                    case '/'  : PUTC(c, '/'); break;
                    case 'f'  : PUTC(c, '\f'); break;
                    case 'b'  : PUTC(c, '\b'); break;
                    case 'n'  : PUTC(c, '\n'); break;
                    case 'r'  : PUTC(c, '\r'); break;
                    case 't'  : PUTC(c, '\t'); break;
                    default   : 
                        c->top = head; 
                        return JSON_PARSE_INVALID_STRING_CHAR;
                }
                break;
            default:
                if ((unsigned char)ch < 0x20) { 
                    c->top = head;
                    return JSON_PARSE_INVALID_STRING_CHAR;
                }
                PUTC(c, ch);
        }
    }
}

/* for whitch value is */
static int parse_value(context* c, value* v) {
    switch (*c->json) {
        case 'n' : return parse_literal(c,v, "null", TYPE_NULL); 
        case 'f' : return parse_literal(c, v, "false", TYPE_FALSE);
        case 't' : return parse_literal(c, v, "true", TYPE_TRUE);
        case '"' : return parse_string(c, v);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        default  : return parse_number(c, v);
    }
}

// NOTE: this is the gate
int parse(value* v, const char* json) {
    context c;
    assert(v != nullptr);
    c.json = json;
    c.size = c.top = 0;
    c.stack = nullptr;      /*->*/
    v->type = TYPE_NULL;    /*->*/
    parse_whitespace(&c);
    int ret;
    if( (ret = parse_value(&c, v))  == JSON_PARSE_OK) {
        parse_whitespace(&c);
        if(*c.json != '\0')
        {
            v->type = TYPE_NULL;
            ret = JSON_PARSE_ROOT_NOT_SINGLUAR;
        }
    }
    assert(0 == c.top);    /*<-*/
    delete c.stack;         /*<-*/
    return ret;
}

Type getType(const value *v){
    assert(v != nullptr);
    return v->type;
}

double getNumber(const value* node){
    assert(node != nullptr);
    return node->u.num;
}

void setNumber(value* v, double n){
    assert(v != nullptr);
    v->u.num = n;
}

int getBoolean(const value* v) {
    assert(v != NULL && (v->type == TYPE_FALSE || v->type == TYPE_TRUE));
    return v->type == TYPE_TRUE;
}

void setBoolean(value* v, int b) {
    free_str(v);
    v->type = b ? TYPE_TRUE : TYPE_FALSE;
}

char* getString(value* v) {
    assert(nullptr != v && v->type == TYPE_STRING);
    return v->u.s.ptr;
}

size_t getStringLen(value* v) {
    assert(nullptr != v && v->type == TYPE_STRING);
    return v->u.s.len;
}

void setString(value* v, const char* s, size_t len) {
    assert(v != nullptr && (s != nullptr || len != 0) );
    free_str(v);
    v->u.s.ptr = (char*)malloc(len + 1); 
    memcpy(v->u.s.ptr, s, len);
    v->u.s.ptr[len] = '\0';
    v->u.s.len = len;
    v->type = TYPE_STRING;
}
} // namespace 
