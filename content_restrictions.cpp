#include <espadin/content_restrictions.hpp>
#include "cjson_util.hpp"

namespace espadin
{

content_restrictions::content_restrictions(const cJSON& json)
{
    cjson::set_bool(json, "readOnly", read_only_);
    cjson::set_string(json, "reason", reason_);
    auto user_obj = cJSON_GetObjectItem(&json, "restrictingUser");
    if (user_obj != nullptr)
    {
        if (cJSON_IsObject(user_obj))
            restricting_user_ = user(*user_obj);
        else
            throw std::runtime_error("The JSON 'restrictingUser' is not an object");
    }
    cjson::set_time(json, "restrictionTime", restriction_time_);
    cjson::set_string(json, "type", type_);
}

}