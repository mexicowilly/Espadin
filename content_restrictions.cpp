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

}