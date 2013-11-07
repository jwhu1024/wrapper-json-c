#include <json/json.h>
#include <stdio.h>

/*
http://linuxprograms.wordpress.com/2010/05/25/json_object_get_string/

Input:
{
 "sitename" : "Joys of Programming",
 "purpose" : "programming tips",
 "platform" : "wordpress"
}

Output:
sitename string is Joys of Programming
purpose string is programming tips
platform string is wordpress
*/

void json_parse(json_object * jobj) {
	enum json_type type;
	json_object_object_foreach(jobj, key, val) {
		type = json_object_get_type(val);
		switch (type) {
		case json_type_string:
			printf("%s string is %s\n"  , key	\
										, json_object_get_string(val));
			break;
		}
	}
}

int main() {
	char * string = "{\"sitename\" 	: \"Joys of Programming\",	\
					  \"purpose\"	: \"programming tips\",		\
					  \"platform\" 	: \"wordpress\"				\
					}";
	json_object * jobj = json_tokener_parse(string);
	json_parse(jobj);
}