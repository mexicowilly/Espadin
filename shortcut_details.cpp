#include <espadin/shortcut_details.hpp>
#include "cjson_util.hpp"

namespace espadin
{

shortcut_details::shortcut_details(const cJSON& json)
{
    cjson::set_string(json, "targetId", target_id_);
    cjson::set_string(json, "targetMimeType", target_mime_type_);
}

}