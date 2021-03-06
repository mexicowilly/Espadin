#include "files_group_impl.hpp"
#include <espadin/drive.hpp>
#include "resumable_file_upload.hpp"
#include "request.hpp"
#include "cjson_util.hpp"
#include <fstream>
#include <cassert>
#include <cstring>

namespace
{

const std::string FILES_URL_BASE("files");

class copy_impl : public espadin::files_group::copy_interface, public espadin::post_request
{
public:
    copy_impl(const std::string& access_token, const std::string& file_id, espadin::file&& metadata);

    virtual copy_interface& fields(const std::string& str) override;
    virtual copy_interface& ignore_default_visibility(bool state) override;
    virtual copy_interface& include_permissions_for_view(const std::string& str) override;
    virtual copy_interface& keep_revision_forever(bool state) override;
    virtual copy_interface& ocr_language(const std::string& lang) override;
    virtual std::unique_ptr<espadin::file> run() override;
    virtual copy_interface& supports_all_drives(bool state) override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
};

copy_impl::copy_impl(const std::string& access_token, const std::string& file_id, espadin::file&& metadata)
    : espadin::post_request(access_token),
      file_id_(file_id)
{
    auto doc = cJSON_CreateObject();
    metadata.to_json(*doc);
    to_post(*doc);
    cJSON_Delete(doc);
}

espadin::files_group::copy_interface& copy_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

espadin::files_group::copy_interface& copy_impl::ignore_default_visibility(bool state)
{
    parameters_["ignoreDefaultVisibility"] = state;
    return *this;
}

espadin::files_group::copy_interface& copy_impl::include_permissions_for_view(const std::string& str)
{
    parameters_["includePermissionsForView"] = str;
    return *this;
}

espadin::files_group::copy_interface& copy_impl::keep_revision_forever(bool state)
{
    parameters_["keepRevisionForever"] = state;
    return *this;
}

espadin::files_group::copy_interface& copy_impl::ocr_language(const std::string& lang)
{
    parameters_["ocrLanguage"] = lang;
    return *this;
}

std::unique_ptr<espadin::file> copy_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::file>(*doc->get()) : std::unique_ptr<espadin::file>();
}

espadin::files_group::copy_interface& copy_impl::supports_all_drives(bool state)
{
    parameters_["supportsAllDrives"] = state;
    return *this;
}

std::string copy_impl::url_stem() const
{
    return FILES_URL_BASE + "/" + file_id_ + "/copy";
}

class create_impl : public espadin::files_group::create_interface, public espadin::uploadable_file_request
{
public:
    create_impl(const std::string& access_token, espadin::file&& metadata);
    create_impl(const std::string& access_token,
                espadin::file&& metadata,
                const std::filesystem::path& to_upload);

    virtual create_interface& ignore_default_visibility(bool state) override;
    virtual create_interface& keep_revision_forever(bool state) override;
    virtual create_interface& ocr_language(const std::string& lang) override;
    virtual create_interface& progress_callback(const std::function<void (double)>& cb) override;
    virtual std::unique_ptr<espadin::file> run() override;
    virtual create_interface& supports_all_drives(bool state) override;
    virtual std::string url_stem() const override;
    virtual create_interface& use_content_as_indexable_text(bool state) override;
};

create_impl::create_impl(const std::string& access_token, espadin::file&& metadata)
    : espadin::uploadable_file_request(access_token, std::move(metadata))
{
}

create_impl::create_impl(const std::string& access_token,
                         espadin::file&& metadata,
                         const std::filesystem::path& to_upload)
    : espadin::uploadable_file_request(access_token, std::move(metadata), to_upload)
{
}

espadin::files_group::create_interface& create_impl::ignore_default_visibility(bool state)
{
    parameters_["ignoreDefaultVisibility"] = state;
    return *this;
}

espadin::files_group::create_interface& create_impl::keep_revision_forever(bool state)
{
    parameters_["keepRevisionForever"] = state;
    return *this;
}

espadin::files_group::create_interface& create_impl::ocr_language(const std::string& lang)
{
    parameters_["ocrLanguage"] = lang;
    return *this;
}

espadin::files_group::create_interface& create_impl::progress_callback(const std::function<void (double)>& cb)
{
    progress_callback_ = cb;
    return *this;
}

std::unique_ptr<espadin::file> create_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::file>(*doc->get()) : std::unique_ptr<espadin::file>();
}

espadin::files_group::create_interface& create_impl::supports_all_drives(bool state)
{
    parameters_["supportsAllDrives"] = state;
    return *this;
}

std::string create_impl::url_stem() const
{
    return FILES_URL_BASE;
}

espadin::files_group::create_interface& create_impl::use_content_as_indexable_text(bool state)
{
    parameters_["useContentAsIndexableText"] = state;
    return *this;
}

class delete_impl : public espadin::files_group::delete_interface, public espadin::delete_request
{
public:
    delete_impl(const std::string& access_token, const std::string& file_id);

    virtual void run() override;
    virtual delete_interface& supports_all_drives(bool sup) override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
};

delete_impl::delete_impl(const std::string& access_token, const std::string& file_id)
    : espadin::delete_request(access_token),
      file_id_(file_id)
{
}

void delete_impl::run()
{
    run_impl();
}

espadin::files_group::delete_interface& delete_impl::supports_all_drives(bool state)
{
    parameters_["supportsAllDrives"] = state;
    return *this;
}

std::string delete_impl::url_stem() const
{
    return FILES_URL_BASE + "/" + file_id_;
}

class empty_trash_impl : public espadin::delete_request
{
public:
    empty_trash_impl(const std::string& access_token);
    void run();
    virtual std::string url_stem() const override;
};

empty_trash_impl::empty_trash_impl(const std::string& access_token)
    : espadin::delete_request(access_token)
{
}

void empty_trash_impl::run()
{
    run_impl();
}

std::string empty_trash_impl::url_stem() const
{
    return FILES_URL_BASE + "/trash";
}

class export_impl : public espadin::files_group::export_interface, public espadin::get_request
{
public:
    export_impl(const std::string& access_token,
                const std::string& file_id,
                const std::string& mime_type,
                std::ostream& content_destination);

    virtual void run() override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
};

export_impl::export_impl(const std::string& access_token,
                         const std::string& file_id,
                         const std::string& mime_type,
                         std::ostream& content_destination)
    : espadin::get_request(access_token),
      file_id_(file_id)
{
    parameters_["mimeType"] = mime_type;
    curl_.output(content_destination);
}

void export_impl::run()
{
    run_impl();
}

std::string export_impl::url_stem() const
{
    return FILES_URL_BASE + "/" + file_id_ + "/export";
}

class generate_ids_impl : public espadin::files_group::generate_ids_interface, public espadin::get_request
{
public:
    generate_ids_impl(const std::string& access_token);

    virtual generate_ids_interface& count(std::size_t number) override;
    virtual generate_ids_interface& fields(const std::string& str) override;
    virtual std::unique_ptr<reply> run() override;
    virtual generate_ids_interface& space(const std::string& str) override;
    virtual std::string url_stem() const override;
};

generate_ids_impl::generate_ids_impl(const std::string& access_token)
    : espadin::get_request(access_token)
{
}

espadin::files_group::generate_ids_interface& generate_ids_impl::count(std::size_t number)
{
    parameters_["count"] = number;
    return *this;
}

espadin::files_group::generate_ids_interface& generate_ids_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

std::unique_ptr<espadin::files_group::generate_ids_interface::reply> generate_ids_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<reply>(*doc->get()) : std::unique_ptr<reply>();
}

espadin::files_group::generate_ids_interface& generate_ids_impl::space(const std::string& str)
{
    parameters_["space"] = str;
    return *this;
}

std::string generate_ids_impl::url_stem() const
{
    return FILES_URL_BASE + "/generateIds";
}

class get_impl : public espadin::files_group::get_interface, public espadin::get_request
{
public:
    get_impl(const std::string& access_token, const std::string& file_id);
    get_impl(const std::string& access_token, const std::string& file_id, std::ostream& content_destination);

    virtual get_interface& acknowledge_abuse(bool ack) override;
    virtual get_interface& fields(const std::string& str) override;
    virtual get_interface& include_permissions_for_view(const std::string& str) override;
    virtual std::unique_ptr<espadin::file> run() override;
    virtual get_interface& supports_all_drives(bool sup) override;
    virtual std::string url_stem() const override;

private:
    std::string file_id_;
};

get_impl::get_impl(const std::string& access_token, const std::string& file_id)
    : espadin::get_request(access_token),
      file_id_(file_id)
{
}

get_impl::get_impl(const std::string& access_token, const std::string& file_id, std::ostream& content_destination)
    : get_impl(access_token, file_id)
{
    parameters_["alt"] = std::string("media");
    curl_.output(content_destination);
}

espadin::files_group::get_interface& get_impl::acknowledge_abuse(bool ack)
{
    parameters_["acknowledgeAbuse"] = ack;
    return *this;
}

espadin::files_group::get_interface& get_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

espadin::files_group::get_interface& get_impl::include_permissions_for_view(const std::string& str)
{
    parameters_["includePermissionsForView"] = str;
    return *this;
}

std::unique_ptr<espadin::file> get_impl::run()
{
    auto doc = run_impl();
    std::unique_ptr<espadin::file> result;
    if (doc)
        result = std::make_unique<espadin::file>(*doc->get());
    return result;
}

espadin::files_group::get_interface& get_impl::supports_all_drives(bool sup)
{
    parameters_["supportsAllDrives"] = sup;
    return *this;
}

std::string get_impl::url_stem() const
{
    return FILES_URL_BASE + "/" + file_id_;
}

class list_impl : public espadin::files_group::list_interface, public espadin::get_request
{
public:
    list_impl(const std::string& access_token);

    virtual list_interface& corpora(const std::string& str) override;
    virtual list_interface& drive_id(const std::string& str) override;
    virtual list_interface& fields(const std::string& str) override;
    virtual list_interface& include_items_from_all_drives(bool flg) override;
    virtual list_interface& include_permissions_for_view(const std::string& str) override;
    virtual list_interface& order_by(const std::string& str) override;
    virtual list_interface& page_size(std::size_t count) override;
    virtual list_interface& page_token(const std::string& str) override;
    virtual list_interface& query(const std::string& str) override;
    virtual std::unique_ptr<reply> run() override;
    virtual list_interface& spaces(const std::string& str) override;
    virtual list_interface& supports_all_drives(bool flg) override;
    virtual std::string url_stem() const override;
};

list_impl::list_impl(const std::string& access_token)
    : espadin::get_request(access_token)
{
}

espadin::files_group::list_interface& list_impl::corpora(const std::string& str)
{
    parameters_["corpora"] = str;
    return *this;
}

espadin::files_group::list_interface& list_impl::drive_id(const std::string& str)
{
    parameters_["driveId"] = str;
    return *this;
}

espadin::files_group::list_interface& list_impl::fields(const std::string& str)
{
    parameters_["fields"] = str;
    return *this;
}

espadin::files_group::list_interface& list_impl::include_items_from_all_drives(bool flg)
{
    parameters_["includeItemsFromAllDrives"] = flg;
    return *this;
}

espadin::files_group::list_interface& list_impl::include_permissions_for_view(const std::string& str)
{
    parameters_["includePermissionsForView"] = str;
    return *this;
}

espadin::files_group::list_interface& list_impl::order_by(const std::string& str)
{
    parameters_["orderBy"] = str;
    return *this;
}

espadin::files_group::list_interface& list_impl::page_size(std::size_t count)
{
    parameters_["pageSize"] = count;
    return *this;
}

espadin::files_group::list_interface& list_impl::page_token(const std::string& str)
{
    parameters_["pageToken"] = str;
    return *this;
}

espadin::files_group::list_interface& list_impl::query(const std::string& str)
{
    parameters_["q"] = str;
    return *this;
}

std::unique_ptr<list_impl::reply> list_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<reply>(*doc->get()) : std::unique_ptr<reply>();
}

espadin::files_group::list_interface& list_impl::spaces(const std::string& str)
{
    parameters_["spaces"] = str;
    return *this;
}

espadin::files_group::list_interface& list_impl::supports_all_drives(bool flg)
{
    parameters_["supportsAllDrives"] = flg;
    return *this;
}

std::string list_impl::url_stem() const
{
    return FILES_URL_BASE;
}

class update_impl : public espadin::files_group::update_interface, public espadin::uploadable_file_request
{
public:
    update_impl(const std::string& access_token,
                const std::string& file_id,
                espadin::file&& metadata);
    update_impl(const std::string& access_token,
                const std::string& file_id,
                espadin::file&& metadata,
                const std::filesystem::path& to_upload);

    virtual update_interface& add_parents(const std::string& parents) override;
    virtual update_interface& include_permissions_for_view(const std::string& str) override;
    virtual update_interface& keep_revision_forever(bool flg) override;
    virtual update_interface& ocr_language(const std::string& lang) override;
    virtual update_interface& progress_callback(const std::function<void (double)>& cb) override;
    virtual update_interface& remove_parents(const std::string& parents) override;
    virtual std::unique_ptr<espadin::file> run() override;
    virtual update_interface& supports_all_drives(bool flg) override;
    virtual std::string url_stem() const override;
    virtual update_interface& use_content_as_indexable_text(bool flg) override;

private:
    std::string file_id_;
};

update_impl::update_impl(const std::string& access_token,
                         const std::string& file_id,
                         espadin::file&& metadata)
    : espadin::uploadable_file_request(access_token, std::move(metadata)),
      file_id_(file_id)
{
    curl_.set_option(CURLOPT_CUSTOMREQUEST, "PATCH", "set HTTP patch");
}

update_impl::update_impl(const std::string& access_token,
                         const std::string& file_id,
                         espadin::file&& metadata,
                         const std::filesystem::path& to_upload)
    : espadin::uploadable_file_request(access_token, std::move(metadata), to_upload),
      file_id_(file_id)
{
    curl_.set_option(CURLOPT_CUSTOMREQUEST, "PATCH", "set HTTP patch");
}

espadin::files_group::update_interface& update_impl::add_parents(const std::string& parents)
{
    parameters_["addParents"] = parents;
    return *this;
}

espadin::files_group::update_interface& update_impl::include_permissions_for_view(const std::string& str)
{
    parameters_["includePermissionsForView"] = str;
    return *this;
}

espadin::files_group::update_interface& update_impl::keep_revision_forever(bool flg)
{
    parameters_["keepRevisionForever"] = flg;
    return *this;
}

espadin::files_group::update_interface& update_impl::ocr_language(const std::string& lang)
{
    parameters_["ocrLanguage"] = lang;
    return *this;
}

espadin::files_group::update_interface& update_impl::progress_callback(const std::function<void (double)>& cb)
{
    progress_callback_ = cb;
    return *this;
}

espadin::files_group::update_interface& update_impl::remove_parents(const std::string& parents)
{
    parameters_["removeParents"] = parents;
    return *this;
}

std::unique_ptr<espadin::file> update_impl::run()
{
    auto doc = run_impl();
    return doc ? std::make_unique<espadin::file>(*doc->get()) : std::unique_ptr<espadin::file>();
}

espadin::files_group::update_interface& update_impl::supports_all_drives(bool flg)
{
    parameters_["supportsAllDrives"] = flg;
    return *this;
}

std::string update_impl::url_stem() const
{
    return FILES_URL_BASE + "/" + file_id_;
}

espadin::files_group::update_interface& update_impl::use_content_as_indexable_text(bool flg)
{
    parameters_["useContentAsIndexableText"] = flg;
    return *this;
}

}

namespace espadin
{

files_group_impl::files_group_impl(access_token_function func)
    : access_token_accessor(func)
{
}

std::unique_ptr<files_group_impl::copy_interface> files_group_impl::copy(const std::string& file_id, file&& metadata)
{
    return std::make_unique<copy_impl>(access_token_(), file_id, std::move(metadata));
}

std::unique_ptr<files_group_impl::create_interface> files_group_impl::create(file&& metadata)
{
    return std::make_unique<create_impl>(access_token_(), std::move(metadata));
}

std::unique_ptr<files_group_impl::create_interface> files_group_impl::create(file&& metadata,
                                                                   const std::filesystem::path& to_upload)
{
    return std::make_unique<create_impl>(access_token_(), std::move(metadata), to_upload);
}

std::unique_ptr<files_group_impl::delete_interface> files_group_impl::del(const std::string& file_id)
{
    return std::make_unique<delete_impl>(access_token_(), file_id);
}

void files_group_impl::empty_trash()
{
    empty_trash_impl et(access_token_());
    et.run();
}

std::unique_ptr<files_group_impl::export_interface> files_group_impl::exp(const std::string& file_id,
                                                                const std::string& mime_type,
                                                                std::ostream& content_destination)
{
    return std::make_unique<export_impl>(access_token_(), file_id, mime_type, content_destination);
}

std::unique_ptr<files_group_impl::generate_ids_interface> files_group_impl::generate_ids()
{
    return std::make_unique<generate_ids_impl>(access_token_());
}

std::unique_ptr<files_group_impl::get_interface> files_group_impl::get(const std::string& file_id)
{
    return std::make_unique<get_impl>(access_token_(), file_id);
}

std::unique_ptr<files_group_impl::get_interface> files_group_impl::get(const std::string& file_id, std::ostream& content_destination)
{
    return std::make_unique<get_impl>(access_token_(), file_id, content_destination);
}

std::unique_ptr<files_group_impl::list_interface> files_group_impl::list()
{
    return std::make_unique<list_impl>(access_token_());
}

std::unique_ptr<files_group_impl::update_interface> files_group_impl::update(const std::string& file_id,
                                                                   file&& metadata)
{
    return std::make_unique<update_impl>(access_token_(), file_id, std::move(metadata));
}

std::unique_ptr<files_group_impl::update_interface> files_group_impl::update(const std::string& file_id,
                                                                   file&& metadata,
                                                                   const std::filesystem::path& to_upload)
{
    return std::make_unique<update_impl>(access_token_(), file_id, std::move(metadata), to_upload);
}

}