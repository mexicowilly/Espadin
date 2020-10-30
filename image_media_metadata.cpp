#include <espadin/image_media_metadata.hpp>
#include "cjson_util.hpp"

namespace espadin
{

image_media_metadata::image_media_metadata(const cJSON& json)
{
    cjson::set_number(json, "width", width_);
    cjson::set_number(json, "height", height_);
    cjson::set_number(json, "rotation", rotation_);
    auto loc_obj = cJSON_GetObjectItemCaseSensitive(&json, "location");
    if (loc_obj != nullptr)
    {
        if (cJSON_IsObject(loc_obj))
            loc_ = location(*loc_obj);
        else
            throw std::runtime_error("JSON field 'location' is not an object");
    }
    cjson::set_string(json, "time", time_);
    cjson::set_string(json, "cameraMake", camera_make_);
    cjson::set_string(json, "cameraModel", camera_model_);
    cjson::set_number(json, "exposureTime", exposure_time_);
    cjson::set_number(json, "aperture", aperture_);
    cjson::set_bool(json, "flashUsed", flash_used_);
    cjson::set_number(json, "focalLength", focal_length_);
    cjson::set_number(json, "isoSpeed", iso_speed_);
    cjson::set_string(json, "meteringMode", metering_mode_);
    cjson::set_string(json, "sensor", sensor_);
    cjson::set_string(json, "exposureMode", exposure_mode_);
    cjson::set_string(json, "colorSpace", color_space_);
    cjson::set_string(json, "whiteBalance", white_balance_);
    cjson::set_number(json, "exposureBias", exposure_bias_);
    cjson::set_number(json, "maxApertureValue", max_aperture_value_);
    cjson::set_number(json, "subjectDistance", subject_distance_);
    cjson::set_string(json, "lens", lens_);
}

image_media_metadata::location::location(const cJSON& json)
{
    cjson::set_number(json, "latitude", latitude_);
    cjson::set_number(json, "longitude", longitude_);
    cjson::set_number(json, "altitude", altitude_);
}

}