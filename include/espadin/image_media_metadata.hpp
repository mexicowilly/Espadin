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

        double altitude() const;
        double latitude() const;
        double longitude() const;

    private:
        double latitude_;
        double longitude_;
        double altitude_;
    };

    image_media_metadata(const cJSON& json);

    double aperture() const;
    const std::string& camera_make() const;
    const std::string& camera_model() const;
    const std::string& color_space() const;
    double exposure_bias() const;
    const std::string& exposure_mode() const;
    double exposure_time() const;
    bool flash_used() const;
    double focal_length() const;
    const std::optional<location>& get_location() const;
    int height() const;
    int iso_speed() const;
    const std::string& lens() const;
    double max_aperture_value() const;
    const std::string& metering_mode() const;
    int rotation() const;
    const std::string& sensor() const;
    int subject_distance() const;
    const std::string& time() const;
    const std::string& white_balance() const;
    int width() const;
    
private:
    int width_;
    int height_;
    int rotation_;
    std::optional<location> loc_;
    std::string time_;
    std::string camera_make_;
    std::string camera_model_;
    double exposure_time_;
    double aperture_;
    bool flash_used_;
    double focal_length_;
    int iso_speed_;
    std::string metering_mode_;
    std::string sensor_;
    std::string exposure_mode_;
    std::string color_space_;
    std::string white_balance_;
    double exposure_bias_;
    double max_aperture_value_;
    int subject_distance_;
    std::string lens_;
};

inline double image_media_metadata::aperture() const
{
    return aperture_;
}

inline const std::string& image_media_metadata::camera_make() const
{
    return camera_make_;
}

inline const std::string& image_media_metadata::camera_model() const
{
    return camera_model_;
}

inline const std::string& image_media_metadata::color_space() const
{
    return color_space_;
}

inline double image_media_metadata::exposure_bias() const
{
    return exposure_bias_;
}

inline const std::string& image_media_metadata::exposure_mode() const
{
    return exposure_mode_;
}

inline double image_media_metadata::exposure_time() const
{
    return exposure_time_;
}

inline bool image_media_metadata::flash_used() const
{
    return flash_used_;
}

inline double image_media_metadata::focal_length() const
{
    return focal_length_;
}

inline const std::optional<image_media_metadata::location>& image_media_metadata::get_location() const
{
    return loc_;
}

inline int image_media_metadata::height() const
{
    return height_;
}

inline int image_media_metadata::iso_speed() const
{
    return iso_speed_;
}

inline const std::string& image_media_metadata::lens() const
{
    return lens_;
}

inline double image_media_metadata::max_aperture_value() const
{
    return max_aperture_value_;
}

inline const std::string& image_media_metadata::metering_mode() const
{
    return metering_mode_;
}

inline int image_media_metadata::rotation() const
{
    return rotation_;
}

inline const std::string& image_media_metadata::sensor() const
{
    return sensor_;
}

inline int image_media_metadata::subject_distance() const
{
    return subject_distance_;
}

inline const std::string& image_media_metadata::time() const
{
    return time_;
}

inline const std::string& image_media_metadata::white_balance() const
{
    return white_balance_;
}

inline int image_media_metadata::width() const
{
    return width_;
}

inline double image_media_metadata::location::altitude() const
{
    return altitude_;
}

inline double image_media_metadata::location::latitude() const
{
    return latitude_;
}

inline double image_media_metadata::location::longitude() const
{
    return longitude_;
}

}

#endif
