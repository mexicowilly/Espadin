#if !defined(ESPADIN_SHORTCUT_DETAILS_HPP__)
#define ESPADIN_SHORTCUT_DETAILS_HPP__

#include <espadin/export.hpp>
#include <string>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT shortcut_details
{
public:
    shortcut_details(const cJSON& json);

    const std::string& target_id() const;
    const std::string& target_mime_type() const;

private:
    std::string target_id_;
    std::string target_mime_type_;
};

inline const std::string& shortcut_details::target_id() const
{
    return target_id_;
}

inline const std::string& shortcut_details::target_mime_type() const
{
    return target_mime_type_;
}

}

#endif
