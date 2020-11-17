#if !defined(ESPADIN_CONTENT_HINTS_HPP__)
#define ESPADIN_CONTENT_HINTS_HPP__

#include <espadin/export.hpp>
#include <vector>
#include <string>
#include <optional>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT content_hints
{
public:
    content_hints(const cJSON& json);

    const std::optional<std::string>& indexable_text() const;
    const std::optional<std::vector<std::byte>>& thumbnail_image() const;
    const std::optional<std::string>& thumbnail_mime_type() const;

private:
    std::optional<std::vector<std::byte>> thumbnail_image_;
    std::optional<std::string> thumbnail_mime_type_;
    std::optional<std::string> indexable_text_;
};

inline const std::optional<std::string>& content_hints::indexable_text() const
{
    return indexable_text_;
}

inline const std::optional<std::vector<std::byte>>& content_hints::thumbnail_image() const
{
    return thumbnail_image_;
}

inline const std::optional<std::string>& content_hints::thumbnail_mime_type() const
{
    return thumbnail_mime_type_;
}

}

#endif
