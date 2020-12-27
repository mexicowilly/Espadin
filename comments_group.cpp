#include <espadin/comments_group.hpp>
#include <espadin/drive.hpp>
#include "request.hpp"
#include "cjson_util.hpp"

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

class delete_impl : public espadin::comments_group::delete_interface, public espadin::delete_request
{
public:
    delete_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& comment_id);

    virtual void run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string comment_id_;
};

delete_impl::delete_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& comment_id)
    : espadin::delete_request(access_token),
      file_id_(file_id),
      comment_id_(comment_id)
{
}

void delete_impl::run()
{
    run_impl();
}

std::string delete_impl::url_stem() const
{
    return make_url_base(file_id_) + "/" + comment_id_;
}

class get_impl : public espadin::comments_group::get_interface, public espadin::get_request
{
public:
    get_impl(const std::string& access_token,
             const std::string& file_id,
             const std::string& comment_id,
             const std::string& fields);

    virtual std::unique_ptr<espadin::comment> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string comment_id_;
};

get_impl::get_impl(const std::string& access_token,
                   const std::string& file_id,
                   const std::string& comment_id,
                   const std::string& fields)
    : espadin::get_request(access_token),
      file_id_(file_id),
      comment_id_(comment_id)
{
    parameters_["fields"] = fields;
}

std::unique_ptr<espadin::comment> get_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::comment>(*doc->get()) : std::unique_ptr<espadin::comment>();
}

std::string get_impl::url_stem() const
{
    return make_url_base(file_id_) + "/" + comment_id_;
}

class list_impl : public espadin::comments_group::list_interface, public espadin::get_request
{
public:
    list_impl(const std::string& access_token,
              const std::string& file_id,
              const std::string& fields);

    virtual list_interface& include_deleted(bool to_set) override;
    virtual list_interface& page_size(std::size_t num) override;
    virtual list_interface& page_token(const std::string& tok) override;
    virtual std::unique_ptr<reply> run() override;
    virtual list_interface& start_modified_time(const std::chrono::system_clock::time_point& when) override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
};

list_impl::list_impl(const std::string& access_token,
                     const std::string& file_id,
                     const std::string& fields)
    : espadin::get_request(access_token),
      file_id_(file_id)
{
    parameters_["fields"] = fields;
}

espadin::comments_group::list_interface& list_impl::include_deleted(bool to_set)
{
    parameters_["includeDeleted"] = to_set;
    return *this;
}

espadin::comments_group::list_interface& list_impl::page_size(std::size_t num)
{
    parameters_["pageSize"] = num;
    return *this;
}

espadin::comments_group::list_interface& list_impl::page_token(const std::string& tok)
{
    parameters_["pageToken"] = tok;
    return *this;
}

std::unique_ptr<espadin::comments_group::list_interface::reply> list_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<reply>(*doc->get()) : std::unique_ptr<reply>();
}

espadin::comments_group::list_interface& list_impl::start_modified_time(const std::chrono::system_clock::time_point& when)
{
    auto obj = cJSON_CreateObject();
    espadin::cjson::util ju(*obj);
    ju.add_time("time", when);
    auto item = cJSON_GetObjectItemCaseSensitive(obj, "time");
    parameters_["startModifiedTime"] = std::string(item->valuestring);
    cJSON_Delete(obj);
    return *this;
}

std::string list_impl::url_stem() const
{
    return make_url_base(file_id_);
}

class update_impl : public espadin::comments_group::update_interface, public espadin::patch_request
{
public:
    update_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& comment_id,
                const std::string& content,
                const std::string& fields);

    virtual std::unique_ptr<espadin::comment> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string comment_id_;
    espadin::comment comment_;
};

update_impl::update_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& comment_id,
                         const std::string& content,
                         const std::string& fields)
    : espadin::patch_request(access_token),
      file_id_(file_id),
      comment_id_(comment_id)
{
    parameters_["fields"] = fields;
    comment_.content(content);
}

std::unique_ptr<espadin::comment> update_impl::run()
{
    auto json = cJSON_CreateObject();
    comment_.to_json(*json);
    to_post(*json);
    cJSON_Delete(json);
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::comment>(*doc->get()) : std::unique_ptr<espadin::comment>();
}

std::string update_impl::url_stem() const
{
    return make_url_base(file_id_) + "/" + comment_id_;
}

}

namespace espadin
{

comments_group::comments_group(drive& drv, const std::string& file_id)
    : drive_(drv),
      file_id_(file_id)
{
}

std::unique_ptr<comments_group::create_interface> comments_group::create(const std::string& content,
                                                                         const std::string& fields)
{
    return std::make_unique<create_impl>(drive_.access_token_, file_id_, content, fields);
}

std::unique_ptr<comments_group::delete_interface> comments_group::del(const std::string& comment_id)
{
    return std::make_unique<delete_impl>(drive_.access_token_, file_id_, comment_id);
}

std::unique_ptr<comments_group::get_interface> comments_group::get(const std::string& comment_id,
                                                                   const std::string& fields)
{
    return std::make_unique<get_impl>(drive_.access_token_, file_id_, comment_id, fields);
}

std::unique_ptr<comments_group::list_interface> comments_group::list(const std::string& fields)
{
    return std::make_unique<list_impl>(drive_.access_token_, file_id_, fields);
}

std::unique_ptr<comments_group::update_interface> comments_group::update(const std::string& comment_id,
                                                                         const std::string& content,
                                                                         const std::string& fields)
{
    return std::make_unique<update_impl>(drive_.access_token_, file_id_, comment_id, content, fields);
}

comments_group::list_interface::reply::reply(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("nextPageToken", next_page_token_);
    ju.set_object_vector("comments", comments_);
}

}