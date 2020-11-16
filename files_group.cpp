#include <espadin/files_group.hpp>
#include <espadin/drive.hpp>
#include "request.hpp"

namespace
{

const std::string FILES_URL_BASE("files");

class list_impl : public espadin::files_group::list_interface, public espadin::request
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
    : espadin::request(access_token)
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

std::unique_ptr<files_group::list_interface> files_group::list()
{
    return std::make_unique<list_impl>(drive_.access_token_);
}

files_group::list_interface::~list_interface()
{
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