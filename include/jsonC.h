#define _DEBUG

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
char* br_json_get_string  (json_object *obj, char *_key);
int   br_json_get_integer (json_object *obj, char *_key);
bool  br_json_get_boolean (json_object *obj, char *_key);