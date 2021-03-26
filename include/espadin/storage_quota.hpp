#if !defined(ESPADIN_STORAGE_QUOTA_HPP_)
#define ESPADIN_STORAGE_QUOTA_HPP_

#include <espadin/export.hpp>
#include <optional>

struct cJSON;

namespace espadin
{

class ESPADIN_EXPORT storage_quota
{
public:
    storage_quota(const cJSON& json);

    const std::optional<std::size_t>& limit() const;
    const std::optional<std::size_t>& usage() const;
    const std::optional<std::size_t>& usage_in_drive() const;
    const std::optional<std::size_t>& usage_in_drive_trash() const;

private:
    std::optional<std::size_t> limit_;
    std::optional<std::size_t> usage_;
    std::optional<std::size_t> usage_in_drive_;
    std::optional<std::size_t> usage_in_drive_trash_;
};

inline const std::optional<std::size_t>& storage_quota::limit() const
{
    return limit_;
}

inline const std::optional<std::size_t>& storage_quota::usage() const
{
    return usage_;
}

inline const std::optional<std::size_t>& storage_quota::usage_in_drive() const
{
    return usage_in_drive_;
}

inline const std::optional<std::size_t>& storage_quota::usage_in_drive_trash() const
{
    return usage_in_drive_trash_;
}

}

#endif
