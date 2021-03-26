#if !defined(ESPADING_REVISION_HPP_)
#define ESPADING_REVISION_HPP_

#include <espadin/user.hpp>
#include <chrono>
#include <map>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT revision
{
public:
    revision(const cJSON& json);

    const std::optional<std::map<std::string, std::string>>& export_links() const;
    const std::optional<std::string>& id() const;
    const std::optional<bool>& keep_forever() const;
    revision& keep_forever(bool to_set);
    const std::optional<std::string>& kind() const;
    const std::optional<user>& last_modifying_user() const;
    const std::optional<std::string>& md5_checksum() const;
    const std::optional<std::string>& mime_type() const;
    const std::optional<std::chrono::system_clock::time_point>& modified_time() const;
    const std::optional<std::string>& original_filename() const;
    const std::optional<bool>& publish_auto() const;
    revision& publish_auto(bool to_set);
    const std::optional<bool>& published() const;
    revision& published(bool to_set);
    const std::optional<std::string>& published_link() const;
    const std::optional<bool>& published_outside_domain() const;
    revision& published_outside_domain(bool to_set);
    const std::optional<std::size_t>& size() const;
    void to_json(cJSON& json) const;

private:
    std::optional<std::string> kind_;
    std::optional<std::string> id_;
    std::optional<std::string> mime_type_;
    std::optional<std::chrono::system_clock::time_point> modified_time_;
    std::optional<bool> keep_forever_;
    std::optional<bool> published_;
    std::optional<std::string> published_link_;
    std::optional<bool> publish_auto_;
    std::optional<bool> published_outside_domain_;
    std::optional<user> last_modifying_user_;
    std::optional<std::string> original_filename_;
    std::optional<std::string> md5_checksum_;
    std::optional<std::size_t> size_;
    std::optional<std::map<std::string, std::string>> export_links_;
};

inline const std::optional<std::map<std::string, std::string>>& revision::export_links() const
{
    return export_links_;
}

inline const std::optional<std::string>& revision::id() const
{
    return id_;
}

inline const std::optional<bool>& revision::keep_forever() const
{
    return keep_forever_;
}

inline revision& revision::keep_forever(bool to_set)
{
    keep_forever_ = to_set;
    return *this;
}

inline const std::optional<std::string>& revision::kind() const
{
    return kind_;
}

inline const std::optional<user>& revision::last_modifying_user() const
{
    return last_modifying_user_;
}

inline const std::optional<std::string>& revision::md5_checksum() const
{
    return md5_checksum_;
}

inline const std::optional<std::string>& revision::mime_type() const
{
    return mime_type_;
}

inline const std::optional<std::chrono::system_clock::time_point>& revision::modified_time() const
{
    return modified_time_;
}

inline const std::optional<std::string>& revision::original_filename() const
{
    return original_filename_;
}

inline const std::optional<bool>& revision::publish_auto() const
{
    return publish_auto_;
}

inline revision& revision::publish_auto(bool to_set)
{
    publish_auto_ = to_set;
    return *this;
}

inline const std::optional<bool>& revision::published() const
{
    return published_;
}

inline revision& revision::published(bool to_set)
{
    published_ = to_set;
    return *this;
}

inline const std::optional<std::string>& revision::published_link() const
{
    return published_link_;
}

inline const std::optional<bool>& revision::published_outside_domain() const
{
    return published_outside_domain_;
}

inline revision& revision::published_outside_domain(bool to_set)
{
    published_outside_domain_ = to_set;
    return *this;
}

inline const std::optional<std::size_t>& revision::size() const
{
    return size_;
}

}

#endif