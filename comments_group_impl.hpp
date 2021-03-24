#if !defined(ESPADIN_COMMENTS_GROUP_IMPL_HPP__)
#define ESPADIN_COMMENTS_GROUP_IMPL_HPP__

#include <espadin/comments_group.hpp>
#include "access_token_accessor.hpp"

namespace espadin
{

class comments_group_impl : public comments_group, public access_token_accessor
{
public:
    comments_group_impl(access_token_function func, const std::string& file_id);

    virtual std::unique_ptr<create_interface> create(const std::string& content,
                                                     const std::string& fields) override;
    virtual std::unique_ptr<delete_interface> del(const std::string& comment_id) override;
    virtual std::unique_ptr<get_interface> get(const std::string& comment_id,
                                               const std::string& fields) override;
    virtual std::unique_ptr<list_interface> list(const std::string& fields) override;
    virtual std::unique_ptr<update_interface> update(const std::string& comment_id,
                                                     const std::string& content,
                                                     const std::string& fields) override;
private:
    std::string file_id_;
};

}

#endif