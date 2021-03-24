#if !defined(ESPADIN_PERMISSIONS_GROUP_IMPL_HPP__)
#define ESPADIN_PERMISSIONS_GROUP_IMPL_HPP__

#include <espadin/permissions_group.hpp>
#include "access_token_accessor.hpp"

namespace espadin
{

class permissions_group_impl : public permissions_group, public access_token_accessor
{
public:
    permissions_group_impl(access_token_function func, const std::string& file_id);

    virtual std::unique_ptr<create_interface> create(permission&& perm) override;
    virtual std::unique_ptr<delete_interface> del(const std::string& permission_id) override;
    virtual std::unique_ptr<get_interface> get(const std::string& permission_id) override;
    virtual std::unique_ptr<list_interface> list() override;
    virtual std::unique_ptr<update_interface> update(const std::string& permission_id, permission&& perm) override;

private:
    std::string file_id_;
};

}

#endif