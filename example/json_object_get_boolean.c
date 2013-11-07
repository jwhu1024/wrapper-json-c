#include <json/json.h>
#include <stdio.h>

/*
http://linuxprograms.wordpress.com/2010/05/25/json_object_get_boolean-get-boolean-value-of-a-json-object/

Input:
{
 "admin" : true,
 "reviewer" : false,
 "author" : true
}
Output:
type: json_type_string
type: json_type_array
type: json_type_object
*/

void json_parse(json_object * jobj) {
	enum json_type type;
	json_object_object_foreach(jobj, key, val) {
		type = json_object_get_type(val);
		switch (type) {
		case json_type_boolean:
			printf("%s boolean is %s\n" , key	\
										, json_object_get_boolean(val)? "true, ": "false, ");
			break;
		}
	}
}

int main() {
	char * string = "{\"admin\" : true,		\
					  \"reviewer\" 	: false,	\
					  \"author\" 	: true		\
					}";

	json_object * jobj = json_tokener_parse(string);
	json_parse(jobj);
}