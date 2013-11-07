#include <stdio.h>
#include <stdbool.h>
#include <json/json.h>
#include "jsonC.h"

/*****************************************/
/* Function for init object from file    */
/*****************************************/
struct json_object* br_json_load_from_file (char *filename)
{
	json_object * jobj = json_object_from_file (filename);

#ifdef _DEBUG
	(json_object_is_type(jobj, json_type_object))
	? DEBUG("Object type correctly\n")
	: DEBUG("Object type abnormal\n");;
#endif

	return (json_object_get_type(jobj) == json_type_object)
			? jobj
			: NULL;
}

/*****************************************/
/* Function for write object to file    */
/*****************************************/
int br_json_to_file (char *filename, json_object *obj)
{
	// 0 : pass
	// -1: fail
	return json_object_to_file(filename, obj);
}

/*****************************************/
/* Function for create value from object */
/*****************************************/
void br_json_add_string (json_object *obj, char *_key, char *_value)
{
	/* Creating a json string */
	json_object *jstring = json_object_new_string(_value);

	/* Form the json object */
	json_object_object_add(obj, _key, jstring);
}

void br_json_add_integer (json_object *obj, char *_key, int _value)
{
	/* Creating a json integer */
	json_object *jint = json_object_new_int(_value);

	/* Form the json object */
	json_object_object_add(obj, _key, jint);
}

void br_json_add_boolean (json_object *obj, char *_key, bool _value)
{
	/* Creating a json boolean */
	json_object *jbool = json_object_new_boolean(_value);

	/* Form the json object */
	json_object_object_add(obj, _key, jbool);
}

/*****************************************/
/* Function for remove value from object */
/*****************************************/
void br_json_del_object (json_object *obj, char *_key)
{
	/* Creating a json string */
	json_object_object_del(obj, _key);
}

/*****************************************/
/* Function for update value from object */
/* Basically, it calls add method		 */
/*****************************************/
void br_json_update_string (json_object *obj, char *_key, char *_value)
{
	/* Creating a json string */
	br_json_add_string(obj, _key, _value);
}

void br_json_update_integer (json_object *obj, char *_key, int _value)
{
	/* Creating a json string */
	br_json_add_integer(obj, _key, _value);
}

void br_json_update_boolean (json_object *obj, char *_key, bool _value)
{
	/* Creating a json string */
	br_json_add_boolean(obj, _key, _value);
}

/*****************************************/
/* 	Function for get value from object 	 */
/*****************************************/
char* br_json_get_string (json_object *obj, char *_key)
{
	char *data;
	json_object_object_foreach(obj, key, val) {
		if (strcmp(key, _key) == 0) {
			if (json_object_get_type(val) == json_type_string) {
				data = (char*) json_object_get_string(val);
			}
		}
	}
	return (data != NULL) ? data : NULL;
}

int br_json_get_integer (json_object *obj, char *_key)
{
	int data=0;
	json_object_object_foreach(obj, key, val) {
		if (strcmp(key, _key) == 0) {
			if (json_object_get_type(val) == json_type_int) {
				data = json_object_get_int(val);
			}
		}
	}
	return data;
}

bool br_json_get_boolean (json_object *obj, char *_key)
{
	bool data;
	json_object_object_foreach(obj, key, val) {
		if (strcmp(key, _key) == 0) {
			if (json_object_get_type(val) == json_type_boolean) {
				data = json_object_get_boolean(val);
			}
		}
	}
	return data;
}

// main function only for test
#ifdef _DEBUG
void main(void)
{
	json_object *obj = br_json_load_from_file ("./test.json");

	// add string to object
	br_json_add_string(obj, "string", "hahahaha");

	// add integer to object
	br_json_add_integer(obj, "integer", 19);

	// add boolean to object
	br_json_add_boolean(obj, "boolean", true);
	
	// delete boolean from object (string, integer, and boolean are applicable)
	br_json_del_object(obj, "purpose");

	// Get string value from object by key
	char *szResult = br_json_get_string(obj, "purpose");

	// Get integer value from object by key
	int iResult = br_json_get_integer(obj, "integer");

	// Get boolean value from object by key
	bool bRet = br_json_get_boolean(obj, "boolean");

	

	DEBUG("%s\n", json_object_to_json_string(obj));

	// Get boolean value from object by key
	br_json_to_file("./dup.json", obj);
	return;
}
#endif