#include <espadin/content_hints.hpp>
#include "cjson_util.hpp"
#include "cppcodec/base64_url.hpp"

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

void content_hints::to_json(cJSON& json) const
{
    if (indexable_text_)
        cJSON_AddStringToObject(&json, "indexableText", indexable_text_.value().c_str());
    if (thumbnail_image_ || thumbnail_mime_type_)
    {
        auto sub = cJSON_CreateObject();
        if (thumbnail_image_)
        {
            auto encoded = cppcodec::base64_url::encode(*thumbnail_image_);
            cJSON_AddStringToObject(sub, "image", encoded.c_str());
        }
        if (thumbnail_mime_type_)
            cJSON_AddStringToObject(sub, "mimeType", thumbnail_mime_type_.value().c_str());
        cJSON_AddItemToObject(&json, "thumbnail", sub);
    }
}

}