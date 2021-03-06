#include <espadin/drive.hpp>
#include "request.hpp"
#include "files_group_impl.hpp"
#include "comments_group_impl.hpp"
#include "replies_group_impl.hpp"
#include "permissions_group_impl.hpp"
#include "revisions_group_impl.hpp"

namespace
{

class about_impl : public espadin::get_request
{
public:
    about_impl(const std::string& access_token, const std::string& fields);

    std::unique_ptr<espadin::about> run();
    virtual std::string url_stem() const override;
};

about_impl::about_impl(const std::string& access_token, const std::string& fields)
    : espadin::get_request(access_token)
{
    parameters_["fields"] = fields;
}

std::unique_ptr<espadin::about> about_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::about>(*doc->get()) : std::unique_ptr<espadin::about>();
}

std::string about_impl::url_stem() const
{
    return "about";
}

}

namespace espadin
{

drive::drive(const std::string& access_token)
    : access_token_(access_token)
{
}

std::unique_ptr<about> drive::about_drive(const std::string& fields)
{
    about_impl ab(access_token_, fields);
    return ab.run();
}

void drive::access_token(const std::string& token)
{
    std::lock_guard lock(token_guard_);
    access_token_ = token;
}

std::unique_ptr<comments_group> drive::comments(const std::string& file_id)
{
    return std::make_unique<comments_group_impl>(std::bind(&drive::token, this), file_id);
}

std::unique_ptr<files_group> drive::files()
{
    return std::make_unique<files_group_impl>(std::bind(&drive::token, this));
}

std::unique_ptr<permissions_group> drive::permissions(const std::string& file_id)
{
    return std::make_unique<permissions_group_impl>(std::bind(&drive::token, this), file_id);
}

std::unique_ptr<replies_group> drive::replies(const std::string& file_id, const std::string& comment_id)
{
    return std::make_unique<replies_group_impl>(std::bind(&drive::token, this), file_id, comment_id);
}

std::unique_ptr<revisions_group> drive::revisions(const std::string& file_id)
{
    return std::make_unique<revisions_group_impl>(std::bind(&drive::token, this), file_id);
}

const std::string& drive::token()
{
    std::lock_guard lock(token_guard_);
    return access_token_;
}

}