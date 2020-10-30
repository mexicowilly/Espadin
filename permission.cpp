#include <espadin/permission.hpp>
#include "cjson_util.hpp"
#include <stdexcept>

namespace espadin
{

permission::permission(const cJSON& json)
{
    cjson::set_string(json, "kind", kind_);
    cjson::set_string(json, "id", id_);
    cjson::set_string(json, "type", type_);
    cjson::set_string(json, "emailAddress", email_address_);
    cjson::set_string(json, "domain", domain_);
    cjson::set_string(json, "role", role_);
    cjson::set_string(json, "view", view_);
    cjson::set_bool(json, "allowFileDiscovery", allow_file_discovery_);
    cjson::set_string(json, "displayName", display_name_);
    cjson::set_string(json, "photoLink", photo_link_);
    cjson::set_time(json, "expirationTime", expiration_time_);
    auto details_obj = cJSON_GetObjectItemCaseSensitive(&json, "permissionDetails");
    if (details_obj != nullptr)
    {
        if (cJSON_IsArray(details_obj))
        {
            cJSON* item;
            cJSON_ArrayForEach(item, details_obj)
                permission_details_.emplace_back(*item);
        }
        else
        {
            throw std::runtime_error("The JSON 'permissionDetails' is not an array");
        }
    }
}

permission::details::details(const cJSON& json)
{
    cjson::set_string(json, "permissionType", permission_type_);
    cjson::set_string(json, "role", role_);
    cjson::set_string(json, "inheritedFrom", inherited_from_);
    cjson::set_bool(json, "inherited", inherited_);
}

}