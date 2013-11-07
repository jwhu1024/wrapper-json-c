#include <json/json.h>
#include <stdio.h>

/*
http://linuxprograms.wordpress.com/2010/08/19/json_object_new_string/

Input:
NONE

Output:
{
  "Site Name":"Joys of Programming"
}
*/

int main() {
	/*Creating a json object*/
	json_object * jobj = json_object_new_object();

	/*Creating a json string*/
	json_object *jstring = json_object_new_string("Joys of Programming");

	/*Form the json object*/
	json_object_object_add(jobj, "Site Name", jstring);

	/*Now printing the json object*/
	printf("%s\n", json_object_to_json_string(jobj));
}