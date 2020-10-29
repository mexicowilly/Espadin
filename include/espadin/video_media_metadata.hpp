#if !defined(ESPADIN_VIDEO_MEDIA_METADATA_HPP__)
#define ESPADIN_VIDEO_MEDIA_METADATA_HPP__

#include <espadin/export.hpp>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT video_media_metadata
{
public:
    video_media_metadata(const cJSON& json);

    long duration_millis() const;
    int height() const;
    int width() const;

private:
    int width_;
    int height_;
    long duration_millis_;
};

inline long video_media_metadata::duration_millis() const
{
    return duration_millis_;
}

inline int video_media_metadata::height() const
{
    return height_;
}

inline int video_media_metadata::width() const
{
    return width_;
}

}

#endif
