#include <espadin/video_media_metadata.hpp>
#include "cjson_util.hpp"

namespace espadin
{

video_media_metadata::video_media_metadata(const cJSON& json)
{
    cjson::set_number(json, "width", width_);
    cjson::set_number(json, "height", height_);
    cjson::set_number(json, "durationMillis", duration_millis_);
}

}