#include <json/json.h>
#include <stdio.h>

/*
http://linuxprograms.wordpress.com/2010/08/19/json_object_new_int/

Input:
NONE

Output:
{
  "Number of posts":10
}
*/

int main() {
	/*Creating a json object*/
	json_object * jobj = json_object_new_object();

	/*Creating a json integer*/
	json_object *jint = json_object_new_int(10);

	/*Form the json object*/
	json_object_object_add(jobj,"Number of posts", jint);

	/*Now printing the json object*/
	printf ("%s\n",json_object_to_json_string(jobj));
}