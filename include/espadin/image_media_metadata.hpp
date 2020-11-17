#if !defined(ESPADIN_IMAGE_MEDIA_METADATA_HPP__)
#define ESPADIN_IMAGE_MEDIA_METADATA_HPP__

#include <espadin/export.hpp>
#include <string>
#include <optional>

struct cJSON;

namespace espadin
{

class image_media_metadata
{
public:
    class location
    {
    public:
        location(const cJSON& json);

        const std::optional<double>& altitude() const;
        const std::optional<double>& latitude() const;
        const std::optional<double>& longitude() const;

    private:
        std::optional<double> latitude_;
        std::optional<double> longitude_;
        std::optional<double> altitude_;
    };

    image_media_metadata(const cJSON& json);

    const std::optional<double>& aperture() const;
    const std::optional<std::string>& camera_make() const;
    const std::optional<std::string>& camera_model() const;
    const std::optional<std::string>& color_space() const;
    const std::optional<double>& exposure_bias() const;
    const std::optional<std::string>& exposure_mode() const;
    const std::optional<double>& exposure_time() const;
    const std::optional<bool>& flash_used() const;
    const std::optional<double>& focal_length() const;
    const std::optional<location>& get_location() const;
    const std::optional<int>& height() const;
    const std::optional<int>& iso_speed() const;
    const std::optional<std::string>& lens() const;
    const std::optional<double>& max_aperture_value() const;
    const std::optional<std::string>& metering_mode() const;
    const std::optional<int>& rotation() const;
    const std::optional<std::string>& sensor() const;
    const std::optional<int>& subject_distance() const;
    const std::optional<std::string>& time() const;
    const std::optional<std::string>& white_balance() const;
    const std::optional<int>& width() const;
    
private:
    std::optional<int> width_;
    std::optional<int> height_;
    std::optional<int> rotation_;
    std::optional<location> loc_;
    std::optional<std::string> time_;
    std::optional<std::string> camera_make_;
    std::optional<std::string> camera_model_;
    std::optional<double> exposure_time_;
    std::optional<double> aperture_;
    std::optional<bool> flash_used_;
    std::optional<double> focal_length_;
    std::optional<int> iso_speed_;
    std::optional<std::string> metering_mode_;
    std::optional<std::string> sensor_;
    std::optional<std::string> exposure_mode_;
    std::optional<std::string> color_space_;
    std::optional<std::string> white_balance_;
    std::optional<double> exposure_bias_;
    std::optional<double> max_aperture_value_;
    std::optional<int> subject_distance_;
    std::optional<std::string> lens_;
};

inline const std::optional<double>& image_media_metadata::aperture() const
{
    return aperture_;
}

inline const std::optional<std::string>& image_media_metadata::camera_make() const
{
    return camera_make_;
}

inline const std::optional<std::string>& image_media_metadata::camera_model() const
{
    return camera_model_;
}

inline const std::optional<std::string>& image_media_metadata::color_space() const
{
    return color_space_;
}

inline const std::optional<double>& image_media_metadata::exposure_bias() const
{
    return exposure_bias_;
}

inline const std::optional<std::string>& image_media_metadata::exposure_mode() const
{
    return exposure_mode_;
}

inline const std::optional<double>& image_media_metadata::exposure_time() const
{
    return exposure_time_;
}

inline const std::optional<bool>& image_media_metadata::flash_used() const
{
    return flash_used_;
}

inline const std::optional<double>& image_media_metadata::focal_length() const
{
    return focal_length_;
}

inline const std::optional<image_media_metadata::location>& image_media_metadata::get_location() const
{
    return loc_;
}

inline const std::optional<int>& image_media_metadata::height() const
{
    return height_;
}

inline const std::optional<int>& image_media_metadata::iso_speed() const
{
    return iso_speed_;
}

inline const std::optional<std::string>& image_media_metadata::lens() const
{
    return lens_;
}

inline const std::optional<double>& image_media_metadata::max_aperture_value() const
{
    return max_aperture_value_;
}

inline const std::optional<std::string>& image_media_metadata::metering_mode() const
{
    return metering_mode_;
}

inline const std::optional<int>& image_media_metadata::rotation() const
{
    return rotation_;
}

inline const std::optional<std::string>& image_media_metadata::sensor() const
{
    return sensor_;
}

inline const std::optional<int>& image_media_metadata::subject_distance() const
{
    return subject_distance_;
}

inline const std::optional<std::string>& image_media_metadata::time() const
{
    return time_;
}

inline const std::optional<std::string>& image_media_metadata::white_balance() const
{
    return white_balance_;
}

inline const std::optional<int>& image_media_metadata::width() const
{
    return width_;
}

inline const std::optional<double>& image_media_metadata::location::altitude() const
{
    return altitude_;
}

inline const std::optional<double>& image_media_metadata::location::latitude() const
{
    return latitude_;
}

inline const std::optional<double>& image_media_metadata::location::longitude() const
{
    return longitude_;
}

}

#endif
