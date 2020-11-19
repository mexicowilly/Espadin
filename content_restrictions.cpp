#include <espadin/content_restrictions.hpp>
#include "cjson_util.hpp"

namespace espadin
{

content_restrictions::content_restrictions(const cJSON& json)
{
    cjson::util ju(json);
    ju.set_bool("readOnly", read_only_);
    ju.set_string("reason", reason_);
    ju.set_object("restrictingUser", restricting_user_);
    ju.set_time("restrictionTime", restriction_time_);
    ju.set_string("type", type_);
}

void content_restrictions::to_json(cJSON& json)
{
    if (read_only_)
        cJSON_AddBoolToObject(&json, "readOnly", *read_only_);
    if (reason_)
        cJSON_AddStringToObject(&json, "reason", reason_.value().c_str());
}

}