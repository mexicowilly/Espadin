#if !defined(ESPADIN_REPLIES_GROUP_IMPL_HPP_)
#define ESPADIN_REPLIES_GROUP_IMPL_HPP_

#include <espadin/replies_group.hpp>
#include "access_token_accessor.hpp"

namespace espadin
{

class replies_group_impl : public replies_group, public access_token_accessor
{
public:
    replies_group_impl(access_token_function func, const std::string& file_id, const std::string& comment_id);

    virtual std::unique_ptr<create_interface> create(reply&& to_create, const std::string& fields) override;
    virtual std::unique_ptr<delete_interface> del(const std::string& reply_id) override;
    virtual std::unique_ptr<get_interface> get(const std::string& reply_id, const std::string& fields) override;
    virtual std::unique_ptr<list_interface> list(const std::string& fields) override;
    virtual std::unique_ptr<update_interface> update(const std::string& reply_id, const std::string& content, const std::string& fields) override;

private:
    std::string file_id_;
    std::string comment_id_;
};

}

#endif
