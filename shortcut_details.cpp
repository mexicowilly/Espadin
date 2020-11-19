#include <espadin/shortcut_details.hpp>
#include "cjson_util.hpp"

namespace espadin
{

shortcut_details::shortcut_details(const cJSON& json)
{
    cjson::util ju(json);
    ju.set_string("targetId", target_id_);
    ju.set_string("targetMimeType", target_mime_type_);
}

void shortcut_details::to_json(cJSON& json)
{
    if (target_id_)
        cJSON_AddStringToObject(&json, "targetId", target_id_.value().c_str());
}

}