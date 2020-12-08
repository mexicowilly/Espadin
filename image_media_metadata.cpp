#include <espadin/image_media_metadata.hpp>
#include "cjson_util.hpp"

namespace espadin
{

image_media_metadata::image_media_metadata(const cJSON& json)
{
    cjson::util ju (const_cast<cJSON&>(json));
    ju.set_number("width", width_);
    ju.set_number("height", height_);
    ju.set_number("rotation", rotation_);
    ju.set_object("location", loc_);
    ju.set_string("time", time_);
    ju.set_string("cameraMake", camera_make_);
    ju.set_string("cameraModel", camera_model_);
    ju.set_number("exposureTime", exposure_time_);
    ju.set_number("aperture", aperture_);
    ju.set_bool("flashUsed", flash_used_);
    ju.set_number("focalLength", focal_length_);
    ju.set_number("isoSpeed", iso_speed_);
    ju.set_string("meteringMode", metering_mode_);
    ju.set_string("sensor", sensor_);
    ju.set_string("exposureMode", exposure_mode_);
    ju.set_string("colorSpace", color_space_);
    ju.set_string("whiteBalance", white_balance_);
    ju.set_number("exposureBias", exposure_bias_);
    ju.set_number("maxApertureValue", max_aperture_value_);
    ju.set_number("subjectDistance", subject_distance_);
    ju.set_string("lens", lens_);
}

image_media_metadata::location::location(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_number("latitude", latitude_);
    ju.set_number("longitude", longitude_);
    ju.set_number("altitude", altitude_);
}

}