#if !defined(ESPADIN_VIDEO_MEDIA_METADATA_HPP_)
#define ESPADIN_VIDEO_MEDIA_METADATA_HPP_

#include <espadin/export.hpp>
#include <optional>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT video_media_metadata
{
public:
    video_media_metadata(const cJSON& json);

    const std::optional<long>& duration_millis() const;
    const std::optional<int>& height() const;
    const std::optional<int>& width() const;

private:
    std::optional<int> width_;
    std::optional<int> height_;
    std::optional<long> duration_millis_;
};

inline const std::optional<long>& video_media_metadata::duration_millis() const
{
    return duration_millis_;
}

inline const std::optional<int>& video_media_metadata::height() const
{
    return height_;
}

inline const std::optional<int>& video_media_metadata::width() const
{
    return width_;
}

}

#endif
