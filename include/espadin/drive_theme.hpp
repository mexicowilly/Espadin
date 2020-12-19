#if !defined(ESPADIN_DRIVE_THEME_HPP__)
#define ESPADIN_DRIVE_THEME_HPP__

#include <espadin/export.hpp>
#include <optional>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT drive_theme
{
public:
    drive_theme(const cJSON& json);

    const std::optional<std::string>& background_image_link() const;
    const std::optional<std::string>& color_rgb() const;
    const std::optional<std::string>& id() const;

private:
    std::optional<std::string> id_;
    std::optional<std::string> background_image_link_;
    std::optional<std::string> color_rgb_;
};

inline const std::optional<std::string>& drive_theme::background_image_link() const
{
    return background_image_link_;
}

inline const std::optional<std::string>& drive_theme::color_rgb() const
{
    return color_rgb_;
}

inline const std::optional<std::string>& drive_theme::id() const
{
    return id_;
}

}

#endif
