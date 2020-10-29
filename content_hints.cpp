#include <espadin/content_hints.hpp>
#include "cjson_util.hpp"

namespace espadin
{

content_hints::content_hints(const cJSON& json)
{
    auto thumb_obj = cJSON_GetObjectItem(&json, "thumbnail");
    if (thumb_obj != nullptr)
    {
        if (cJSON_IsObject(thumb_obj))
        {
            cjson::set_bytes(*thumb_obj, "image", thumbnail_image_);
            cjson::set_string(*thumb_obj, "mimeType", thumbnail_mime_type_);
        }
        else
        {
            throw std::runtime_error("The JSON 'thumbnail' is not an object");
        }
    }
    cjson::set_string(json, "indexableText", indexable_text_);
}

}