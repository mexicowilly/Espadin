#include <espadin/permissions_group.hpp>
#include <espadin/drive.hpp>
#include "request.hpp"
#include "cjson_util.hpp"

namespace
{

std::string make_url_stem(const std::string& file_id)
{
    return "files/" + file_id + "/permissions";
}

class create_impl : public espadin::permissions_group::create_interface, public espadin::post_request
{
public:
    create_impl(const std::string& access_token, const std::string& file_id, espadin::permission&& perm);

    virtual create_interface& email_message(const std::string& str) override;
    virtual create_interface& fields(const std::string& str) override;
    virtual create_interface& move_to_new_owners_root(bool to_set) override;
    virtual std::unique_ptr<espadin::permission> run() override;
    virtual create_interface& send_notification_email(bool to_set) override;
    virtual create_interface& supports_all_drives(bool to_set) override;
    virtual create_interface& transfer_ownership(bool to_set) override;
    virtual std::string url_stem() const override;
    virtual create_interface& use_domain_admin_access(bool to_set) override;

private:
    std::string file_id_;
};

create_impl::create_impl(const std::string& access_token, const std::string& file_id, espadin::permission&& perm)
    : espadin::post_request(access_token),
      file_id_(file_id)
{
    auto doc = cJSON_CreateObject();
    perm.to_json(*doc);
    to_post(*doc);
    cJSON_Delete(doc);
}

espadin::permissions_group::create_interface& create_impl::email_message(const std::string& str)
{
    parameters_["emailMessage"] = str;
    return *this;
}

espadin::permissions_group::create_interface& create_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

espadin::permissions_group::create_interface& create_impl::move_to_new_owners_root(bool to_set)
{
    parameters_["moveToNewOwnersRoot"] = to_set;
    return *this;
}

std::unique_ptr<espadin::permission> create_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::permission>(*doc->get()) : std::unique_ptr<espadin::permission>();
}

espadin::permissions_group::create_interface& create_impl::send_notification_email(bool to_set)
{
    parameters_["sendNotificationEmail"] = to_set;
    return *this;
}

espadin::permissions_group::create_interface& create_impl::supports_all_drives(bool to_set)
{
    parameters_["supportsAllDrives"] = to_set;
    return *this;
}

espadin::permissions_group::create_interface& create_impl::transfer_ownership(bool to_set)
{
    parameters_["transferOwnership"] = to_set;
    return *this;
}

std::string create_impl::url_stem() const
{
    return make_url_stem(file_id_);
}

espadin::permissions_group::create_interface& create_impl::use_domain_admin_access(bool to_set)
{
    parameters_["useDomainAdminAccess"] = to_set;
    return *this;
}

class delete_impl : public espadin::permissions_group::delete_interface, public espadin::delete_request
{
public:
    delete_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& permission_id);

    virtual void run() override;
    virtual delete_interface& supports_all_drives(bool to_set) override;
    virtual std::string url_stem() const override;
    virtual delete_interface& use_domain_admin_access(bool to_set) override;

private:
    std::string file_id_;
    std::string permission_id_;
};

delete_impl::delete_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& permission_id)
    : espadin::delete_request(access_token),
      file_id_(file_id),
      permission_id_(permission_id)
{
}

void delete_impl::run()
{
    run_impl();
}

espadin::permissions_group::delete_interface& delete_impl::supports_all_drives(bool to_set)
{
    parameters_["supportsAllDrives"] = to_set;
    return *this;
}

std::string delete_impl::url_stem() const
{
    return make_url_stem(file_id_) + "/" + permission_id_;
}

espadin::permissions_group::delete_interface& delete_impl::use_domain_admin_access(bool to_set)
{
    parameters_["useDomainAdminAccess"] = to_set;
    return *this;
}

class get_impl : public espadin::permissions_group::get_interface, public espadin::get_request
{
public:
    get_impl(const std::string& access_token,
             const std::string& file_id,
             const std::string& permission_id);

    virtual get_interface& fields(const std::string& str) override;
    virtual std::unique_ptr<espadin::permission> run() override;
    virtual get_interface& supports_all_drives(bool to_set) override;
    virtual std::string url_stem() const override;
    virtual get_interface& use_domain_admin_access(bool to_set) override;

private:
    std::string file_id_;
    std::string permission_id_;
};

get_impl::get_impl(const std::string& access_token,
                   const std::string& file_id,
                   const std::string& permission_id)
    : espadin::get_request(access_token),
      file_id_(file_id),
      permission_id_(permission_id)
{
}

espadin::permissions_group::get_interface& get_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

std::unique_ptr<espadin::permission> get_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::permission>(*doc->get()) : std::unique_ptr<espadin::permission>();
}

espadin::permissions_group::get_interface& get_impl::supports_all_drives(bool to_set)
{
    parameters_["supportsAllDrives"] = to_set;
    return *this;
}

std::string get_impl::url_stem() const
{
    return make_url_stem(file_id_) + "/" + permission_id_;
}

espadin::permissions_group::get_interface& get_impl::use_domain_admin_access(bool to_set)
{
    parameters_["useDomainAdminAccess"] = to_set;
    return *this;
}

class list_impl : public espadin::permissions_group::list_interface, public espadin::get_request
{
public:
    list_impl(const std::string& access_token, const std::string& file_id);

    virtual list_interface& fields(const std::string& str) override;
    virtual list_interface& include_permissions_for_view(const std::string& str) override;
    virtual list_interface& page_size(std::size_t num) override;
    virtual list_interface& page_token(const std::string& tok) override;
    virtual std::unique_ptr<reply> run() override;
    virtual list_interface& supports_all_drives(bool to_set) override;
    virtual std::string url_stem() const override;
    virtual list_interface& use_domain_admin_access(bool to_set) override;

private:
    std::string file_id_;
};

list_impl::list_impl(const std::string& access_token, const std::string& file_id)
    : espadin::get_request(access_token),
      file_id_(file_id)
{
}

espadin::permissions_group::list_interface& list_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

espadin::permissions_group::list_interface& list_impl::include_permissions_for_view(const std::string& str)
{
    parameters_["includePermissionsForView"] = str;
    return *this;
}

espadin::permissions_group::list_interface& list_impl::page_size(std::size_t num)
{
    parameters_["pageSize"] = num;
    return *this;
}

espadin::permissions_group::list_interface& list_impl::page_token(const std::string& tok)
{
    parameters_["pageToken"] = tok;
    return *this;
}

std::unique_ptr<espadin::permissions_group::list_interface::reply> list_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<reply>(*doc->get()) : std::unique_ptr<reply>();
}

espadin::permissions_group::list_interface& list_impl::supports_all_drives(bool to_set)
{
    parameters_["supportsAllDrives"] = to_set;
    return *this;
}

std::string list_impl::url_stem() const
{
    return make_url_stem(file_id_);
}

espadin::permissions_group::list_interface& list_impl::use_domain_admin_access(bool to_set)
{
    parameters_["useDomainAdminAccess"] = to_set;
    return *this;
}

class update_impl : public espadin::permissions_group::update_interface, public espadin::patch_request
{
public:
    update_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& permission_id,
                espadin::permission&& perm);

    virtual update_interface& fields(const std::string& str) override;
    virtual update_interface& remove_expiration(bool to_set) override;
    virtual std::unique_ptr<espadin::permission> run() override;
    virtual update_interface& supports_all_drives(bool to_set) override;
    virtual update_interface& transfer_ownership(bool to_set) override;
    virtual std::string url_stem() const override;
    virtual update_interface& use_domain_admin_access(bool to_set) override;

private:
    std::string file_id_;
    std::string permission_id_;
};

update_impl::update_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& permission_id,
                         espadin::permission&& perm)
    : espadin::patch_request(access_token),
      file_id_(file_id),
      permission_id_(permission_id)
{
    auto doc = cJSON_CreateObject();
    perm.to_json(*doc);
    to_post(*doc);
    cJSON_Delete(doc);
}

espadin::permissions_group::update_interface& update_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

espadin::permissions_group::update_interface& update_impl::remove_expiration(bool to_set)
{
    parameters_["removeExpiration"] = to_set;
    return *this;
}

std::unique_ptr<espadin::permission> update_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::permission>(*doc->get()) : std::unique_ptr<espadin::permission>();
}

espadin::permissions_group::update_interface& update_impl::supports_all_drives(bool to_set)
{
    parameters_["supportsAllDrives"] = to_set;
    return *this;
}

espadin::permissions_group::update_interface& update_impl::transfer_ownership(bool to_set)
{
    parameters_["transferOwnership"] = to_set;
    return *this;
}

std::string update_impl::url_stem() const
{
    return make_url_stem(file_id_) + "/" + permission_id_;
}

espadin::permissions_group::update_interface& update_impl::use_domain_admin_access(bool to_set)
{
    parameters_["useDomainAdminAccess"] = to_set;
    return *this;
}

}

namespace espadin
{

permissions_group::permissions_group(drive& drv, const std::string& file_id)
    : drive_(drv),
      file_id_(file_id)
{
}

std::unique_ptr<permissions_group::create_interface> permissions_group::create(permission&& perm)
{
    return std::make_unique<create_impl>(drive_.access_token_, file_id_, std::move(perm));
}

std::unique_ptr<permissions_group::delete_interface> permissions_group::del(const std::string& permission_id)
{
    return std::make_unique<delete_impl>(drive_.access_token_, file_id_, permission_id);
}

std::unique_ptr<permissions_group::get_interface> permissions_group::get(const std::string& permission_id)
{
    return std::make_unique<get_impl>(drive_.access_token_, file_id_, permission_id);
}

std::unique_ptr<permissions_group::list_interface> permissions_group::list()
{
    return std::make_unique<list_impl>(drive_.access_token_, file_id_);
}

std::unique_ptr<permissions_group::update_interface> permissions_group::update(const std::string& permission_id,
                                                                               permission&& perm)
{
    return std::make_unique<update_impl>(drive_.access_token_, file_id_, permission_id, std::move(perm));
}

permissions_group::list_interface::reply::reply(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("nextPageToken", next_page_token_);
    ju.set_object_vector("permissions", permissions_);
}

}