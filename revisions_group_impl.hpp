#if !defined(ESPADIN_REVISIONS_GROUP_IMPL_HPP_)
#define ESPADIN_REVISIONS_GROUP_IMPL_HPP_

#include <espadin/revisions_group.hpp>
#include "access_token_accessor.hpp"

namespace espadin
{

class revisions_group_impl : public revisions_group, public access_token_accessor
{
public:
    revisions_group_impl(access_token_function func, const std::string& file_id);

    virtual std::unique_ptr<delete_interface> del(const std::string& revision_id) override;
    virtual std::unique_ptr<get_interface> get(const std::string& revision_id) override;
    virtual std::unique_ptr<list_interface> list() override;
    virtual std::unique_ptr<update_interface> update(const std::string& revision_id, revision&& to_update) override;

private:
    std::string file_id_;
};

}

#endif
