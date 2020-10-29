#if !defined(ESPADIN_CONTENT_HINTS_HPP__)
#define ESPADIN_CONTENT_HINTS_HPP__

#include <espadin/export.hpp>
#include <vector>
#include <string>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT content_hints
{
public:
    content_hints(const cJSON& json);

    const std::string& indexable_text() const;
    const std::vector<std::byte>& thumbnail_image() const;
    const std::string& thumbnail_mime_type() const;

private:
    std::vector<std::byte> thumbnail_image_;
    std::string thumbnail_mime_type_;
    std::string indexable_text_;
};

inline const std::string& content_hints::indexable_text() const
{
    return indexable_text_;
}

inline const std::vector<std::byte>& content_hints::thumbnail_image() const
{
    return thumbnail_image_;
}

inline const std::string& content_hints::thumbnail_mime_type() const
{
    return thumbnail_mime_type_;
}

}

#endif
