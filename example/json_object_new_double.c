#include <json/json.h>
#include <stdio.h>

/*
http://linuxprograms.wordpress.com/2010/08/19/json_object_new_double/

Input:
NONE

Output:
{
  "PI":3.1400000000000001
}
*/

int main() {
	/*Creating a json object*/
	json_object * jobj = json_object_new_object();

	/*Creating a json double*/
	json_object *jdouble = json_object_new_double(3.14);

	/*Form the json object*/
	json_object_object_add(jobj,"PI", jdouble);

	/*Now printing the json object*/
	printf ("%s\n", json_object_to_json_string(jobj));
}