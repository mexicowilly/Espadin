#include <espadin/replies_group.hpp>
#include <espadin/drive.hpp>
#include "request.hpp"

namespace
{

std::string make_url_stem(const std::string& file_id, const std::string& comment_id)
{
    return "files/" + file_id + "/comments/" + comment_id + "/replies";
}

class create_impl : public espadin::replies_group::create_interface, public espadin::post_request
{
public:
    create_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& comment_id,
                espadin::reply&& to_create,
                const std::string& fields);

    virtual std::unique_ptr<espadin::reply> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string comment_id_;
    espadin::reply to_create_;
};

create_impl::create_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& comment_id,
                         espadin::reply&& to_create,
                         const std::string& fields)
    : espadin::post_request(access_token),
      file_id_(file_id),
      comment_id_(comment_id),
      to_create_(std::move(to_create))
{
    parameters_["fields"] = fields;
}

std::unique_ptr<espadin::reply> create_impl::run()
{
    auto json = cJSON_CreateObject();
    to_create_.to_json(*json);
    to_post(*json);
    cJSON_Delete(json);
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::reply>(*doc->get()) : std::unique_ptr<espadin::reply>();
}

std::string create_impl::url_stem() const
{
    return make_url_stem(file_id_, comment_id_);
}

}

namespace espadin
{

replies_group::replies_group(drive& drv, const std::string& file_id, const std::string& comment_id)
    : drive_(drv),
      file_id_(file_id),
      comment_id_(comment_id)
{
}

std::unique_ptr<replies_group::create_interface> replies_group::create(reply&& to_create, const std::string& fields)
{
    return std::make_unique<create_impl>(drive_.access_token_, file_id_, comment_id_, std::move(to_create), fields);
}

}