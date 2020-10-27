#include <espadin/user.hpp>
#include "cjson_util.hpp"

namespace espadin
{

user::user(const cJSON& json)
{
    cjson::set_string(json, "kind", kind_);
    cjson::set_string(json, "displayName", display_name_);
    cjson::set_string(json, "photoLink", photo_link_);
    cjson::set_bool(json, "me", me_);
    cjson::set_string(json, "permissionId", permission_id_);
    cjson::set_string(json, "emailAddress", email_address_);
}

}