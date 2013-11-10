/*
 *  File : jsonC.c
 *  Description : Wrapper for json-C
 *	Date : 2013/11/11
 *  Author : lester_hu@bandrich
 *  Copyright BandRich .Inc All rights reserved.
 */
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <json/json.h>
#include "jsonC.h"

/*****************************************/
/* Function for init object from file    */
/*****************************************/
struct json_object* br_json_load_from_file (char *filename)
{
	assert(filename);
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
	assert(filename);
	
	// 0 : pass , -1: fail
	return json_object_to_file_ext(filename, obj, JSON_FORMAT);
}

/*****************************************/
/* Function for create value from object */
/*****************************************/
void br_json_add_string (json_object *obj, char *_key, char *_value)
{
	assert(_key);
	assert(_value);
	
	/* Creating a json string */
	json_object *jstring = json_object_new_string(_value);

	/* Form the json object */
	json_object_object_add(obj, _key, jstring);
}

void br_json_add_integer (json_object *obj, char *_key, int _value)
{
	assert(_key);
	
	/* Creating a json integer */
	json_object *jint = json_object_new_int(_value);

	/* Form the json object */
	json_object_object_add(obj, _key, jint);
}

void br_json_add_boolean (json_object *obj, char *_key, bool _value)
{
	assert(_key);

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
	assert(_key);

	/* Creating a json string */
	json_object_object_del(obj, _key);
}

/*****************************************/
/* Function for update value from object */
/* Basically, it calls add method		 */
/*****************************************/
void br_json_update_string (json_object *obj, char *_key, char *_value)
{
	assert(_key);
	assert(_value);
	
	/* Creating a json string */
	br_json_add_string(obj, _key, _value);
}

void br_json_update_integer (json_object *obj, char *_key, int _value)
{
	assert(_key);
	
	/* Creating a json string */
	br_json_add_integer(obj, _key, _value);
}

void br_json_update_boolean (json_object *obj, char *_key, bool _value)
{
	assert(_key);
	
	/* Creating a json string */
	br_json_add_boolean(obj, _key, _value);
}

/*****************************************/
/* 	Function for get value from object 	 */
/*****************************************/
static char* br_json_get_string (json_object *obj, char *_key)
{
	assert(_key);

	bool exist=false;
	char *data;
	json_object_object_foreach(obj, key, val) {
		if (strcmp(key, _key) == 0) {
			if (json_object_get_type(val) == json_type_string) {
				data = (char*) json_object_get_string(val);
				exist=true;
				break;
			}
		}
	}
	return (exist == true) ? data : NULL;
}

static int br_json_get_integer (json_object *obj, char *_key)
{
	assert(_key);

	bool exist=false;
	int data;
	json_object_object_foreach(obj, key, val) {
		if (strcmp(key, _key) == 0) {
			if (json_object_get_type(val) == json_type_int) {
				data = json_object_get_int(val);
				exist=true;
				break;
			}
		}
	}
	return (exist == true) ? data : -1;
}

static bool br_json_get_boolean (json_object *obj, char *_key)
{
	assert(_key);
	
	bool exist=false;
	bool data;
	json_object_object_foreach(obj, key, val) {
		if (strcmp(key, _key) == 0) {
			if (json_object_get_type(val) == json_type_boolean) {
				data = json_object_get_boolean(val);
				exist=true;
				break;
			}
		}
	}
	return (exist == true) ? data : false;
}

/*****************************************************/
/* 	Function for convert between string and object 	 */
/*****************************************************/
struct json_object* br_json_string_to_obj (const char *str)
{
	return json_tokener_parse(str);
}

char* br_json_obj_to_string (json_object *obj)
{
	return (char*)json_object_to_json_string_ext(obj , JSON_FORMAT);
}

/**************************************************/
/* 	Function for insert object to another object  */
/**************************************************/
void br_json_add_obj (struct json_object *dest_obj, const char *_key, struct json_object *src_obj)
{
	json_object_object_add(dest_obj, _key, src_obj);
}

char* br_json_query_string (json_object *obj, char *_key)
{
	char *data = (char*) br_json_get_string(obj, _key);
	
	// search first level
	if (data == NULL) {
		json_object_object_foreach(obj, key, val) {
			if (json_object_get_type(val) == json_type_object) {
				// Get sub object for parsing
				struct json_object *sub_obj = json_object_object_get(obj, key);
				data = br_json_query_string(sub_obj, _key);
				if (data != NULL) {
					return data;
				}
			}
		}
	} else {
		return data;
	}
}

// If no conversion exists then 0 is returned and errno is set to EINVAL.
int br_json_query_integer (json_object *obj, char *_key)
{
	int data = br_json_get_integer(obj, _key);
	
	// search first level
	if (data == -1) {
		json_object_object_foreach(obj, key, val) {
			if (json_object_get_type(val) == json_type_object) {
				// Get sub object for parsing
				struct json_object *sub_obj = json_object_object_get(obj, key);
				data = br_json_query_integer(sub_obj, _key);
				if (data != 0) {
					return data;
				}
			}
		}
	} else {
		return data;
	}
}

int br_json_query_boolean (json_object *obj, char *_key)
{
	bool data = br_json_get_boolean(obj, _key);
	
	// search first level
	if (data != true) {
		json_object_object_foreach(obj, key, val) {
			if (json_object_get_type(val) == json_type_object) {
				// Get sub object for parsing
				struct json_object *sub_obj = json_object_object_get(obj, key);
				data = br_json_query_boolean(sub_obj, _key);
				if (data != false) {
					return data;
				}
			}
		}
	} else {
		return data;
	}
}

void main(void)
{
	struct json_object* obj = br_json_load_from_file ("./test.json");
	//DEBUG("[ORIGINAL] : %s\n", json_object_to_json_string(obj));

	DEBUG("company : %s\n", 	(char*) br_json_query_string(obj, "company"));
	DEBUG("title : %s\n", 		(char*) br_json_query_string(obj, "title"));
	DEBUG("ID : %s\n", 			(char*) br_json_query_string(obj, "ID"));
	DEBUG("SortAs : %s\n", 		(char*) br_json_query_string(obj, "SortAs"));
	DEBUG("GlossTerm : %s\n", 	(char*) br_json_query_string(obj, "GlossTerm"));
	DEBUG("Acronym : %s\n", 	(char*) br_json_query_string(obj, "Acronym"));
	DEBUG("Abbrev : %s\n", 		(char*) br_json_query_string(obj, "Abbrev"));
	DEBUG("para : %s\n", 		(char*) br_json_query_string(obj, "para"));
	DEBUG("GML : %s\n", 		(char*) br_json_query_string(obj, "GML"));
	DEBUG("GlossSee : %s\n", 	(char*) br_json_query_string(obj, "GlossSee"));
	
	// Failure case : Item "123" doesn't appear in test.json, it will return NULL.
	DEBUG("123 : %s\n", 		(char*) br_json_query_string(obj, "123"));

    // add string to object
    br_json_add_string(obj, "key-br_json_add_string", "value-br_json_add_string");

	// add integer to object
	br_json_add_integer(obj, "key-br_json_add_integer", 19);

    // add boolean to object
    br_json_add_boolean(obj, "key-br_json_add_boolean", true);
      
    // delete boolean from object (string, integer, and boolean are applicable)
    br_json_del_object(obj, "company");

    // Get integer value from object by key
    int iResult = br_json_query_integer(obj, "integer2");

    // Get boolean value from object by key
	bool bRet = br_json_query_boolean(obj, "boolean");

    //DEBUG("%s\n", json_object_to_json_string(obj));

    // Write obj to file
    br_json_to_file("./dup.json", obj);
	
	return;
}