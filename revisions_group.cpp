#include <espadin/revisions_group.hpp>
#include <espadin/drive.hpp>
#include "request.hpp"
#include "cjson_util.hpp"

namespace
{

std::string make_url_stem(const std::string& file_id)
{
    return "files/" + file_id + "/revisions";
}

class list_impl : public espadin::revisions_group::list_interface, public espadin::get_request
{
public:
    list_impl(const std::string& access_token, const std::string& file_id);

    virtual list_interface& fields(const std::string& str) override;
    virtual list_interface& page_size(std::size_t count) override;
    virtual list_interface& page_token(const std::string& str) override;
    virtual std::unique_ptr<reply> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
};

list_impl::list_impl(const std::string& access_token, const std::string& file_id)
    : espadin::get_request(access_token),
      file_id_(file_id)
{
}

espadin::revisions_group::list_interface& list_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

espadin::revisions_group::list_interface& list_impl::page_size(std::size_t count)
{
    parameters_["pageSize"] = count;
    return *this;
}

espadin::revisions_group::list_interface& list_impl::page_token(const std::string& str)
{
    parameters_["pageToken"] = str;
    return *this;
}

std::unique_ptr<espadin::revisions_group::list_interface::reply> list_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<reply>(*doc->get()) : std::unique_ptr<reply>();
}

std::string list_impl::url_stem() const
{
    return make_url_stem(file_id_);
}

}

namespace espadin
{

revisions_group::revisions_group(drive& drv, const std::string& file_id)
    : drive_(drv),
      file_id_(file_id)
{
}

std::unique_ptr<revisions_group::list_interface> revisions_group::list()
{
    return std::make_unique<list_impl>(drive_.access_token_, file_id_);
}

revisions_group::list_interface::reply::reply(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("nextPageToken", next_page_token_);
    ju.set_object_vector("revisions", revisions_);
}

}