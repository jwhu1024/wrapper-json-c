#include <json/json.h>
#include <stdio.h>

/*
http://linuxprograms.wordpress.com/2010/08/19/json_object_array_put_idx/

Input:
NONE

Output:
{
  "Categories":[
    null,
    null,
    "c",
    "c++",
    "php"
  ]
}
*/

int main() {
	/*Creating a json object*/
	json_object * jobj = json_object_new_object();

	/*Creating a json array*/
	json_object *jarray = json_object_new_array();

	/*Creating json strings*/
	json_object *jstring[3];
	jstring[0] = json_object_new_string("c");
	jstring[1] = json_object_new_string("c++");
	jstring[2] = json_object_new_string("php");

	/*Adding the above created json strings to the array*/
	int i;
	for (i=0;i<3; i++) { 
		json_object_array_put_idx(jarray,i+2, jstring[i]);
	}

	/*Form the json object*/
	json_object_object_add(jobj,"Categories", jarray);

	/*Now printing the json object*/
	printf ("%s\n", json_object_to_json_string(jobj));
}