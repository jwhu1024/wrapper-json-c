#ifndef JSON_C_H
#define JSON_C_H
#define _DEBUG

#ifdef _PRETTY_PRINT_
#define JSON_FORMAT JSON_C_TO_STRING_PRETTY
#else
#define JSON_FORMAT JSON_C_TO_STRING_SPACED
#endif

#ifdef _DEBUG
#define DEBUG(format, args...) printf("[%s:%d] "format, __func__, __LINE__, ##args)
#else
#define DEBUG(args...)
#endif

/* Function for init object from file */
struct json_object* br_json_load_from_file (char *filename);

/* Function for write object to file */
int br_json_to_file (char *filename, json_object *obj);

/* Function for create value from object */
void br_json_add_string  (json_object *obj, char *_key, char *_value);
void br_json_add_integer (json_object *obj, char *_key, int _value);
void br_json_add_boolean (json_object *obj, char *_key, bool _value);

/* Function for remove value from object */
void br_json_del_object (json_object *obj, char *_key);

/* Function for update the value in object */
void br_json_update_string  (json_object *obj, char *_key, char *_value);
void br_json_update_integer (json_object *obj, char *_key, int _value);
void br_json_update_boolean (json_object *obj, char *_key, bool _value);

/* Function for get value from object */
char* br_json_query_string  (json_object *obj, char *_key);
int   br_json_query_integer (json_object *obj, char *_key);
int   br_json_query_boolean (json_object *obj, char *_key);

/* Function for convert between obj and string */
struct json_object* br_json_string_to_obj (const char *str);
char* br_json_obj_to_string (json_object *obj);

/* Function for insert object to object */
void br_json_add_obj (struct json_object *dest_obj, const char *_key, struct json_object *src_obj);

/* Function for query string in object (recursively) */
char* br_json_query_nested_string (struct json_object *obj, char *_key);

#endif /* JSON_C_H */