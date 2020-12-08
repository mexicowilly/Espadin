#include <espadin/user.hpp>
#include "cjson_util.hpp"

namespace espadin
{

user::user(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("displayName", display_name_);
    ju.set_string("photoLink", photo_link_);
    ju.set_bool("me", me_);
    ju.set_string("permissionId", permission_id_);
    ju.set_string("emailAddress", email_address_);
}

}