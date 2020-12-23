#include <espadin/comments_group.hpp>
#include <espadin/drive.hpp>
#include "request.hpp"

namespace
{

std::string make_url_base(const std::string& file_id)
{
    return "files/" + file_id + "/comments";
}

class create_impl : public espadin::comments_group::create_interface, public espadin::post_request
{
public:
    create_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& content,
                const std::string& fields);

    virtual create_interface& anchor(const std::string& str) override;
    virtual create_interface& quoted_file_content(const std::string& str) override;
    virtual std::unique_ptr<espadin::comment> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    espadin::comment comment_;
};

create_impl::create_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& content,
                         const std::string& fields)
    : espadin::post_request(access_token),
      file_id_(file_id)
{
    parameters_["fields"] = fields;
    comment_.content(content);
}

espadin::comments_group::create_interface& create_impl::anchor(const std::string& str)
{
    comment_.anchor(str);
    return *this;
}

espadin::comments_group::create_interface& create_impl::quoted_file_content(const std::string& str)
{
    espadin::comment::quoted_file_content qfc;
    qfc.value(str);
    comment_.set_quoted_file_content(std::move(qfc));
    return *this;
}

std::unique_ptr<espadin::comment> create_impl::run()
{
    auto json = cJSON_CreateObject();
    comment_.to_json(*json);
    to_post(*json);
    cJSON_Delete(json);
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::comment>(*doc->get()) : std::unique_ptr<espadin::comment>();
}

std::string create_impl::url_stem() const
{
    return make_url_base(file_id_);
}

}

namespace espadin
{

comments_group::comments_group(drive& drv)
    : drive_(drv)
{
}

std::unique_ptr<comments_group::create_interface> comments_group::create(const std::string& file_id,
                                                                         const std::string& content,
                                                                         const std::string& fields)
{
    return std::make_unique<create_impl>(drive_.access_token_, file_id, content, fields);
}

}