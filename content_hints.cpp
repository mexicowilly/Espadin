#include <espadin/content_hints.hpp>
#include "cjson_util.hpp"

namespace espadin
{

content_hints::content_hints(const cJSON& json)
{
    auto thumb_obj = cJSON_GetObjectItemCaseSensitive(&json, "thumbnail");
    if (thumb_obj != nullptr)
    {
        if (cJSON_IsObject(thumb_obj))
        {
            cjson::util ju(*thumb_obj);
            ju.set_bytes("image", thumbnail_image_);
            ju.set_string("mimeType", thumbnail_mime_type_);
        }
        else
        {
            throw std::runtime_error("The JSON 'thumbnail' is not an object");
        }
    }
    cjson::util ju(json);
    ju.set_string("indexableText", indexable_text_);
}

}