#include <json/json.h>
#include <stdio.h>

/*
http://linuxprograms.wordpress.com/2010/08/19/json_object_is_type/

Input:
{
    "sitename" : "joys of programming",
    "tags" : [
        "c" ,
        "c++",
        "java",
        "PHP"
    ],
    "author-details": {
        "name" : "Joys of Programming",
        "Number of Posts" : 10
    }
}
Output:
type: json_type_string
type: json_type_array
type: json_type_object
*/

int main()
{
	char * string = "{\"sitename\" : \"joys of programming\", \"tags\" : [ \"c\" , \"c++\", \"java\", \"PHP\" ], \"author-details\": { \"name\" : \"Joys of Programming\", \"Number of Posts\" : 10 }}";
    json_object * jobj = json_tokener_parse(string);
	enum json_type type;
	json_object_object_foreach(jobj, key, val) {
		printf("type: ",type);
		if (json_object_is_type(val, json_type_null)) {
			printf("json_type_null\n");
		}
		if (json_object_is_type(val, json_type_boolean)) {
			printf("json_type_boolean\n");
		}
		if (json_object_is_type(val, json_type_double)) {
			printf("json_type_double\n");
		}
		if (json_object_is_type(val, json_type_int)) {
			printf("json_type_int\n");
		}
		if (json_object_is_type(val, json_type_object)) {
			printf("json_type_object\n");
		}
		if (json_object_is_type(val, json_type_array)) {
			printf("json_type_array\n");
		}
		if (json_object_is_type(val, json_type_string)) {
			printf("json_type_string\n");
		}
	}
	return 1;
}
