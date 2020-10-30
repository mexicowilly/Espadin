#include <espadin/video_media_metadata.hpp>
#include "cjson_util.hpp"

namespace espadin
{

video_media_metadata::video_media_metadata(const cJSON& json)
{
    cjson::util ju(json);
    ju.set_number("width", width_);
    ju.set_number("height", height_);
    ju.set_number("durationMillis", duration_millis_);
}

}