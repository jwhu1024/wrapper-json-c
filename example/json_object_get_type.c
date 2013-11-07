#include <json/json.h>
#include <stdio.h>
// http://linuxprograms.wordpress.com/2010/05/24/json_object_get_type
int main()
{
	//char * string = "{\"name\" : \"programming\"}";	//	-> object
	//char * string = "[\"name\" , \"programming\"]";	//	-> array
	//char * string = "1";		// -> integer
	//char * string = "true";	// -> boolean
	printf("%s\n", string);
	json_object * jobj = json_tokener_parse(string);
	enum json_type type = json_object_get_type(jobj);
	printf("type: ",type);
	switch (type) {
		case json_type_null: printf("json_type_null\n");
		break;
	case json_type_boolean: printf("json_type_boolean\n");
		break;
	case json_type_double: printf("json_type_double\n");
		break;
	case json_type_int: printf("json_type_int\n");
		break;
	case json_type_object: printf("json_type_object\n");
		break;
	case json_type_array: printf("json_type_array\n");
		break;
	case json_type_string: printf("json_type_string\n");
		break;
	}
	return 1;
}
