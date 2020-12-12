#include <espadin/files_group.hpp>
#include <espadin/drive.hpp>
#include "resumable_file_upload.hpp"
#include "request.hpp"
#include <fstream>
#include <cassert>

namespace
{

const std::string FILES_URL_BASE("files");

class create_impl : public espadin::files_group::create_interface, public espadin::post_request
{
public:
    create_impl(const std::string& access_token, const espadin::file& metadata);
    create_impl(const std::string& access_token,
                const espadin::file& metadata,
                const std::filesystem::path& to_upload);

    virtual create_interface& ignore_default_visibility(bool state) override;
    virtual bool is_upload() const override;
    virtual create_interface& keep_revision_forever(bool state) override;
    virtual create_interface& ocr_language(const std::string& lang) override;
    virtual create_interface& progress_callback(const std::function<void (double)>& cb) override;
    virtual std::unique_ptr<espadin::file> run() override;
    virtual create_interface& supports_all_drives(bool state) override;
    virtual std::string url_stem() const override;
    virtual create_interface& use_content_as_indexable_text(bool state) override;

private:
    std::string metadata_to_json(const espadin::file& metadata);

    bool is_upload_;
    std::filesystem::path to_upload_;
    std::function<void (double)> progress_callback_;
    espadin::file metadata_;
};

create_impl::create_impl(const std::string& access_token, const espadin::file& metadata)
    : espadin::post_request(access_token),
      metadata_(metadata)
{
}

create_impl::create_impl(const std::string& access_token,
                         const espadin::file& metadata,
                         const std::filesystem::path& to_upload)
    : espadin::post_request(access_token),
      to_upload_(to_upload),
      metadata_(metadata)
{
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

std::string create_impl::metadata_to_json(const espadin::file& metadata)
{
    auto doc = cJSON_CreateObject();
    metadata.to_json(*doc);
    auto json = cJSON_PrintUnformatted(doc);
    cJSON_Delete(doc);
    std::string result(json);
    cJSON_free(json);
    return result;
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
    bool is_resumable = false;
    if (to_upload_.empty())
    {
        is_upload_ = false;
        parameters_["uploadType"] = std::string("multipart");
        curl_.post_part("application/json; charset=UTF-8", metadata_to_json(metadata_));
    }
    else
    {
        is_upload_ = true;
        auto file_size = std::filesystem::file_size(to_upload_);
        // This magic number is 4.5 MB. Google says only do a single
        // upload for files less than 5 MB.
        if (progress_callback_ || file_size > 9 * 1024 * 512)
        {
            is_resumable = true;
            parameters_["uploadType"] = std::string("resumable");
            auto json = metadata_to_json(metadata_);
            curl_.set_option(CURLOPT_POSTFIELDSIZE, json.length(), "POST field size");
            curl_.set_option(CURLOPT_COPYPOSTFIELDS, json.c_str(), "POST fields");
            if (metadata_.mime_type())
                curl_.header("X-Upload-Content-Type", *metadata_.mime_type());
            curl_.header("X-Upload-Content-Length", std::to_string(file_size));
            curl_.header("Content-Type", "application/json; charset=UTF-8");
            curl_.header("Content-Length", std::to_string(json.length()));
        }
        else
        {
            parameters_["uploadType"] = std::string("multipart");
            curl_.post_part("application/json; charset=UTF-8", metadata_to_json(metadata_));
            if (file_size > 0)
            {
                std::string mime_type = metadata_.mime_type() ? *metadata_.mime_type() : "application/octet-stream";
                std::ifstream stream(to_upload_, std::ios::in | std::ios::binary);
                std::vector<std::byte> data(file_size);
                stream.read(reinterpret_cast<char*>(data.data()), file_size);
                if (!stream)
                    throw std::runtime_error("Error reading file '" + to_upload_.string() + "'");
                curl_.post_part(mime_type, data);
            }
            else
            {
                is_upload_ = false;
            }
        }
    }
    auto doc = run_impl();
    if (is_resumable)
    {
        auto auth = curl_.header("Authorization");
        assert(auth);
        auto loc = curl_.response_header("Location");
        if (!loc)
            throw std::runtime_error("Could not find required header 'Location' in HTTP response");
        espadin::resumable_file_upload up(*auth, *loc, to_upload_, progress_callback_);
        doc = up.run();
    }
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
                                                                   const std::filesystem::path& to_upload)
{
    return std::make_unique<create_impl>(drive_.access_token_, metadata, to_upload);
}

std::unique_ptr<files_group::get_interface> files_group::get(const std::string& file_id)
{
    return std::make_unique<get_impl>(drive_.access_token_, file_id);
}

std::unique_ptr<files_group::get_interface> files_group::get(const std::string& file_id, std::ostream& content_destination)
{
    return std::make_unique<get_impl>(drive_.access_token_, file_id, content_destination);
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