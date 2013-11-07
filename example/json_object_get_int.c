#include <json/json.h>
#include <stdio.h>

/*
http://linuxprograms.wordpress.com/2010/05/25/json_object_get_int/

Input:
{
 "colors" 		: 7,
 "continents" 	: 1,
 "oceans" 		: 3
}

Output:
type: json_type_int, colors integer is 7
type: json_type_int, continents integer is 1
type: json_type_int, oceans integer is 3
*/

void json_parse(json_object * jobj) {
	enum json_type type;
	json_object_object_foreach(jobj, key, val) {
		type = json_object_get_type(val);
		switch (type) {
		case json_type_int: printf("type: json_type_int, ");
			printf("%s integer is %d\n" , key	\
										, json_object_get_int(val));
			break;
		}
	}
}

int main() {
	char * string = "{\"colors\" 	: 7,	\
					  \"continents\": 1,	\
					  \"oceans\" 	: 3		\
					}";
	json_object * jobj = json_tokener_parse(string);
	json_parse(jobj);
}