#include <espadin/files_group.hpp>
#include <espadin/drive.hpp>
#include "request.hpp"

namespace
{

const std::string FILES_URL_BASE("files");

class create_impl : public espadin::files_group::create_interface, public espadin::post_request
{
public:
    create_impl(const std::string& access_token, const espadin::file& metadata);
    create_impl(const std::string& access_token,
                const espadin::file& metadata,
                const std::vector<std::byte>& data,
                const std::string& mime_type);

    virtual create_interface& ignore_default_visibility(bool state) override;
    virtual bool is_upload() const override;
    virtual create_interface& keep_revision_forever(bool state) override;
    virtual create_interface& ocr_language(const std::string& lang) override;
    virtual std::unique_ptr<espadin::file> run() override;
    virtual create_interface& supports_all_drives(bool state) override;
    virtual std::string url_stem() const override;
    virtual create_interface& use_content_as_indexable_text(bool state) override;

private:
    bool is_upload_;
};

create_impl::create_impl(const std::string& access_token, const espadin::file& metadata)
    : espadin::post_request(access_token),
      is_upload_(false)
{
    parameters_["uploadType"] = std::string("multipart");
    auto doc = cJSON_CreateObject();
    metadata.to_json(*doc);
    auto json = cJSON_PrintUnformatted(doc);
    cJSON_Delete(doc);
    curl_.post_part("application/json; charset=UTF-8", json);
    cJSON_free(json);
}

create_impl::create_impl(const std::string& access_token,
                         const espadin::file& metadata,
                         const std::vector<std::byte>& data,
                         const std::string& mime_type)
    : create_impl(access_token, metadata)
{
    is_upload_ = true;
    curl_.post_part(mime_type, data);
}

espadin::files_group::create_interface& create_impl::ignore_default_visibility(bool state)
{
    parameters_["ignoreDefaultVisibility"] = state;
    return *this;
}

bool create_impl::is_upload() const
{
    return is_upload_;
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

std::unique_ptr<espadin::file> create_impl::run()
{
    auto doc = run_impl();
    return std::make_unique<espadin::file>(*doc->get());
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
    return std::make_unique<reply>(*doc->get());
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

}

namespace espadin
{

files_group::files_group(drive& drv)
    : drive_(drv)
{
}

std::unique_ptr<files_group::create_interface> files_group::create(const file& metadata)
{
    return std::make_unique<create_impl>(drive_.access_token_, metadata);
}

std::unique_ptr<files_group::create_interface> files_group::create(const file& metadata,
                                                                   const std::vector<std::byte>& data,
                                                                   const std::string& mime_type)
{
    return std::make_unique<create_impl>(drive_.access_token_, metadata, data, mime_type);
}

std::unique_ptr<files_group::list_interface> files_group::list()
{
    return std::make_unique<list_impl>(drive_.access_token_);
}

files_group::list_interface::reply::reply(const cJSON& json)
{
    auto obj = cJSON_GetObjectItemCaseSensitive(&json, "kind");
    if (obj != nullptr)
        kind_ = obj->valuestring;
    obj = cJSON_GetObjectItemCaseSensitive(&json, "nextPageToken");
    if (obj != nullptr)
        next_page_token_ = obj->valuestring;
    obj = cJSON_GetObjectItemCaseSensitive(&json, "incompleteSearch");
    if (obj != nullptr)
        incomplete_search_ = obj->type == cJSON_True;
    obj = cJSON_GetObjectItemCaseSensitive(&json, "files");
    if (obj != nullptr && cJSON_IsArray(obj))
    {
        cJSON* item;
        cJSON_ArrayForEach(item, obj)
            files_.emplace_back(*item);
    }
}

}