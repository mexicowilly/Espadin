#include <espadin/permission.hpp>
#include "cjson_util.hpp"

namespace espadin
{

permission::permission(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("id", id_);
    ju.set_string("type", type_);
    ju.set_string("emailAddress", email_address_);
    ju.set_string("domain", domain_);
    ju.set_string("role", role_);
    ju.set_string("view", view_);
    ju.set_bool("allowFileDiscovery", allow_file_discovery_);
    ju.set_string("displayName", display_name_);
    ju.set_string("photoLink", photo_link_);
    ju.set_time("expirationTime", expiration_time_);
    ju.set_object_vector("permissionDetails", permission_details_);
    ju.set_bool("deleted", deleted_);
}

void permission::to_json(cJSON& json) const
{
    cjson::util ju(json);
    ju.add_bool("allowFileDiscovery", allow_file_discovery_);
    ju.add_string("domain", domain_);
    ju.add_string("emailAddress", email_address_);
    ju.add_time("expirationTime", expiration_time_);
    ju.add_string("role", role_);
    ju.add_string("type", type_);
    ju.add_string("view", view_);
}

permission::details::details(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("permissionType", permission_type_);
    ju.set_string("role", role_);
    ju.set_string("inheritedFrom", inherited_from_);
    ju.set_bool("inherited", inherited_);
}

}