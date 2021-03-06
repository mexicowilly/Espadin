#include "revisions_group_impl.hpp"
#include "request.hpp"
#include "cjson_util.hpp"

namespace
{

std::string make_url_stem(const std::string& file_id)
{
    return "files/" + file_id + "/revisions";
}

class delete_impl : public espadin::revisions_group::delete_interface, public espadin::delete_request
{
public:
    delete_impl(const std::string& access_token, const std::string& file_id, const std::string& revision_id);

    virtual void run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string revision_id_;
};

delete_impl::delete_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& revision_id)
    : espadin::delete_request(access_token),
      file_id_(file_id),
      revision_id_(revision_id)
{
}

void delete_impl::run()
{
    run_impl();
}

std::string delete_impl::url_stem() const
{
    return make_url_stem(file_id_) + "/" + revision_id_;
}

class get_impl : public espadin::revisions_group::get_interface, public espadin::get_request
{
public:
    get_impl(const std::string& access_token, const std::string& file_id, const std::string& revision_id);

    virtual get_interface& acknowledge_abuse(bool to_set) override;
    virtual get_interface& fields(const std::string& str) override;
    virtual std::unique_ptr<espadin::revision> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string revision_id_;
};

get_impl::get_impl(const std::string& access_token, const std::string& file_id, const std::string& revision_id)
    : espadin::get_request(access_token),
      file_id_(file_id),
      revision_id_(revision_id)
{
}

espadin::revisions_group::get_interface& get_impl::acknowledge_abuse(bool to_set)
{
    parameters_["acknowledgeAbuse"] = to_set;
    return *this;
}

espadin::revisions_group::get_interface& get_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

std::unique_ptr<espadin::revision> get_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::revision>(*doc->get()) : std::unique_ptr<espadin::revision>();
}

std::string get_impl::url_stem() const
{
    return make_url_stem(file_id_) + "/" + revision_id_;
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

class update_impl : public espadin::revisions_group::update_interface, public espadin::patch_request
{
public:
    update_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& revision_id,
                espadin::revision&& to_update);

    virtual update_interface& fields(const std::string& str) override;
    virtual std::unique_ptr<espadin::revision> run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
    std::string revision_id_;
};

update_impl::update_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& revision_id,
                         espadin::revision&& to_update)
    : espadin::patch_request(access_token),
      file_id_(file_id),
      revision_id_(revision_id)
{
    auto doc = cJSON_CreateObject();
    to_update.to_json(*doc);
    to_post(*doc);
    cJSON_Delete(doc);
}

espadin::revisions_group::update_interface& update_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

std::unique_ptr<espadin::revision> update_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::revision>(*doc->get()) : std::unique_ptr<espadin::revision>();
}

std::string update_impl::url_stem() const
{
    return make_url_stem(file_id_) + "/" + revision_id_;
}

}

namespace espadin
{

revisions_group_impl::revisions_group_impl(access_token_function func, const std::string& file_id)
    : access_token_accessor(func),
      file_id_(file_id)
{
}

std::unique_ptr<revisions_group::delete_interface> revisions_group_impl::del(const std::string& revision_id)
{
    return std::make_unique<delete_impl>(access_token_(), file_id_, revision_id);
}

std::unique_ptr<revisions_group::get_interface> revisions_group_impl::get(const std::string& revision_id)
{
    return std::make_unique<get_impl>(access_token_(), file_id_, revision_id);
}

std::unique_ptr<revisions_group::list_interface> revisions_group_impl::list()
{
    return std::make_unique<list_impl>(access_token_(), file_id_);
}

std::unique_ptr<revisions_group::update_interface> revisions_group_impl::update(const std::string& revision_id,
                                                                           revision&& to_update)
{
    return std::make_unique<update_impl>(access_token_(), file_id_, revision_id, std::move(to_update));
}

}