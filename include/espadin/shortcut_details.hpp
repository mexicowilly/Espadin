#if !defined(ESPADIN_SHORTCUT_DETAILS_HPP_)
#define ESPADIN_SHORTCUT_DETAILS_HPP_

#include <espadin/export.hpp>
#include <string>
#include <optional>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT shortcut_details
{
public:
    shortcut_details() = default;
    shortcut_details(const cJSON& json);

    const std::optional<std::string>& target_id() const;
    shortcut_details& target_id(const std::string& tid);
    const std::optional<std::string>& target_mime_type() const;
    void to_json(cJSON& json) const;

private:
    std::optional<std::string> target_id_;
    std::optional<std::string> target_mime_type_;
};

inline const std::optional<std::string>& shortcut_details::target_id() const
{
    return target_id_;
}

inline shortcut_details& shortcut_details::target_id(const std::string& tid)
{
    target_id_ = tid;
    return *this;
}

inline const std::optional<std::string>& shortcut_details::target_mime_type() const
{
    return target_mime_type_;
}

}

#endif
