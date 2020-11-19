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
    content_hints() = default;
    content_hints(const cJSON& json);

    const std::optional<std::string>& indexable_text() const;
    content_hints& indexable_text(const std::string& txt);
    const std::optional<std::vector<std::byte>>& thumbnail_image() const;
    content_hints& thumbnail_image(const std::vector<std::byte>& bytes);
    const std::optional<std::string>& thumbnail_mime_type() const;
    content_hints& thumbnail_mime_type(const std::string& txt);
    void to_json(cJSON& json) const;

private:
    std::optional<std::vector<std::byte>> thumbnail_image_;
    std::optional<std::string> thumbnail_mime_type_;
    std::optional<std::string> indexable_text_;
};

inline const std::optional<std::string>& content_hints::indexable_text() const
{
    return indexable_text_;
}

inline content_hints& content_hints::indexable_text(const std::string& txt)
{
    indexable_text_ = txt;
    return *this;
}

inline const std::optional<std::vector<std::byte>>& content_hints::thumbnail_image() const
{
    return thumbnail_image_;
}

inline content_hints& content_hints::thumbnail_image(const std::vector<std::byte>& bytes)
{
    thumbnail_image_ = bytes;
    return *this;
}

inline const std::optional<std::string>& content_hints::thumbnail_mime_type() const
{
    return thumbnail_mime_type_;
}

inline content_hints& content_hints::thumbnail_mime_type(const std::string& txt)
{
    thumbnail_mime_type_ = txt;
    return *this;
}

}

#endif
