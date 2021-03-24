#include "replies_group_impl.hpp"
#include "request.hpp"
#include "cjson_util.hpp"

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

class delete_impl : public espadin::replies_group::delete_interface, public espadin::delete_request
{
public:
    delete_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& comment_id,
                const std::string& reply_id);

    virtual void run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string comment_id_;
    std::string reply_id_;
};

delete_impl::delete_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& comment_id,
                         const std::string& reply_id)
: espadin::delete_request(access_token),
  file_id_(file_id),
  comment_id_(comment_id),
  reply_id_(reply_id)
{
}

void delete_impl::run()
{
    run_impl();
}

std::string delete_impl::url_stem() const
{
    return make_url_stem(file_id_, comment_id_) +  "/" + reply_id_;
}

class get_impl : public espadin::replies_group::get_interface, public espadin::get_request
{
public:
    get_impl(const std::string& access_token,
             const std::string& file_id,
             const std::string& comment_id,
             const std::string& reply_id,
             const std::string& fields);

    virtual get_interface& include_deleted(bool to_set) override;
    virtual std::unique_ptr<espadin::reply> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string comment_id_;
    std::string reply_id_;
};

get_impl::get_impl(const std::string& access_token,
                   const std::string& file_id,
                   const std::string& comment_id,
                   const std::string& reply_id,
                   const std::string& fields)
: espadin::get_request(access_token),
  file_id_(file_id),
  comment_id_(comment_id),
  reply_id_(reply_id)
{
    parameters_["fields"] = fields;
}

espadin::replies_group::get_interface& get_impl::include_deleted(bool to_set)
{
    parameters_["includeDeleted"] = to_set;
    return *this;
}

std::unique_ptr<espadin::reply> get_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::reply>(*doc->get()) : std::unique_ptr<espadin::reply>();
}

std::string get_impl::url_stem() const
{
    return make_url_stem(file_id_, comment_id_) +  "/" + reply_id_;
}

class list_impl : public espadin::replies_group::list_interface, public espadin::get_request
{
public:
    list_impl(const std::string& access_token,
              const std::string& file_id,
              const std::string& comment_id,
              const std::string& fields);

    virtual list_interface& include_deleted(bool to_set) override;
    virtual list_interface& page_size(std::size_t num) override;
    virtual list_interface& page_token(const std::string& tok) override;
    virtual std::unique_ptr<reply> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string comment_id_;
};

list_impl::list_impl(const std::string& access_token,
                     const std::string& file_id,
                     const std::string& comment_id,
                     const std::string& fields)
: espadin::get_request(access_token),
  file_id_(file_id),
  comment_id_(comment_id)
{
    parameters_["fields"] = fields;
}


espadin::replies_group::list_interface& list_impl::include_deleted(bool to_set)
{
    parameters_["includeDeleted"] = to_set;
    return *this;
}

espadin::replies_group::list_interface& list_impl::page_size(std::size_t num)
{
    parameters_["pageSize"] = num;
    return *this;
}

espadin::replies_group::list_interface& list_impl::page_token(const std::string& tok)
{
    parameters_["pageToken"] = tok;
    return *this;
}

std::unique_ptr<espadin::replies_group::list_interface::reply> list_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<reply>(*doc->get()) : std::unique_ptr<reply>();
}

std::string list_impl::url_stem() const
{
    return make_url_stem(file_id_, comment_id_);
}

class update_impl : public espadin::replies_group::update_interface, public espadin::patch_request
{
public:
    update_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& comment_id,
                const std::string& reply_id,
                const std::string& content,
                const std::string& fields);

    virtual std::unique_ptr<espadin::reply> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string comment_id_;
    std::string reply_id_;
    std::string content_;
};

update_impl::update_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& comment_id,
                         const std::string& reply_id,
                         const std::string& content,
                         const std::string& fields)
: espadin::patch_request(access_token),
  file_id_(file_id),
  comment_id_(comment_id),
  reply_id_(reply_id),
  content_(content)
{
    parameters_["fields"] = fields;
}

std::unique_ptr<espadin::reply> update_impl::run()
{
    espadin::reply r;
    r.content(content_);
    auto json = cJSON_CreateObject();
    r.to_json(*json);
    to_post(*json);
    cJSON_Delete(json);
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::reply>(*doc->get()) : std::unique_ptr<espadin::reply>();
}

std::string update_impl::url_stem() const
{
    return make_url_stem(file_id_, comment_id_) + "/" + reply_id_;
}

}


namespace espadin
{

replies_group_impl::replies_group_impl(access_token_function func, const std::string& file_id, const std::string& comment_id)
    : espadin::access_token_accessor(func),
      file_id_(file_id),
      comment_id_(comment_id)
{
}

std::unique_ptr<replies_group::create_interface> replies_group_impl::create(reply&& to_create, const std::string& fields)
{
    return std::make_unique<create_impl>(access_token_(), file_id_, comment_id_, std::move(to_create), fields);
}

std::unique_ptr<replies_group::delete_interface> replies_group_impl::del(const std::string& reply_id)
{
    return std::make_unique<delete_impl>(access_token_(), file_id_, comment_id_, reply_id);
}

std::unique_ptr<replies_group::get_interface> replies_group_impl::get(const std::string& reply_id, const std::string& fields)
{
    return std::make_unique<get_impl>(access_token_(), file_id_, comment_id_, reply_id, fields);
}

std::unique_ptr<replies_group::list_interface> replies_group_impl::list(const std::string& fields)
{
    return std::make_unique<list_impl>(access_token_(), file_id_, comment_id_, fields);
}

std::unique_ptr<replies_group::update_interface> replies_group_impl::update(const std::string& reply_id,
                                                                            const std::string& content,
                                                                            const std::string& fields)
{
    return std::make_unique<update_impl>(access_token_(),
                                         file_id_,
                                         comment_id_,
                                         reply_id,
                                         content,
                                         fields);
}

}