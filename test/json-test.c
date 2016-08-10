#include "jsonC.h"

int iter_obj (json_object *obj)
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    it = json_object_iter_begin(obj);
    itEnd = json_object_iter_end(obj);

    while (!json_object_iter_equal(&it, &itEnd)) {
        printf("%s\n", json_object_iter_peek_name(&it));
        json_object_iter_next(&it);
    }
}

int main (void)
{
    json_object *jobj = br_json_load_from_file ("../test.json");
    iter_obj (jobj);
    return 0;
}
