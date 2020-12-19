#include <espadin/storage_quota.hpp>
#include "cjson_util.hpp"

namespace espadin
{

storage_quota::storage_quota(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_number("limit", limit_);
    ju.set_number("usage", usage_);
    ju.set_number("usageInDrive", usage_in_drive_);
    ju.set_number("usageInDriveTrash", usage_in_drive_trash_);
}

}