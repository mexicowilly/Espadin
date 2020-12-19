#include <espadin/drive_theme.hpp>
#include "cjson_util.hpp"

namespace espadin
{

drive_theme::drive_theme(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("backgroundImageLink", background_image_link_);
    ju.set_string("colorRgb", color_rgb_);
    ju.set_string("id", id_);
}

}