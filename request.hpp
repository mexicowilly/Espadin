#if !defined (ESPADIN_REQUEST_HPP__)
#define ESPADIN_REQUEST_HPP__

#include "curl.hpp"
#include <espadin/file.hpp>
#include <chucho/loggable.hpp>
#include <variant>
#include <map>
#include <filesystem>
#include <functional>

namespace espadin
{

class request : public chucho::loggable<request>
{
public:
    virtual ~request() = default;

protected:
    using variant_type = std::variant<std::string, int, bool, std::size_t>;

    request(const std::string& access_token);

    virtual std::unique_ptr<cjson::doc> run_impl();
    virtual std::string url_stem() const = 0;
    virtual bool is_upload() const;

    std::map<std::string, variant_type> parameters_;
    curl curl_;

private:
    std::string parameters_as_url() const;
};

class delete_request : public request
{
protected:
    delete_request(const std::string& access_token);
};

class get_request : public request
{
protected:
    get_request(const std::string& access_token);
};

class patch_request : public request
{
protected:
    patch_request(const std::string& access_token);
};

class post_request : public request
{
protected:
    post_request(const std::string& access_token);
};

class uploadable_file_request : public request
{
public:
    uploadable_file_request(const std::string& access_token,
                            file&& metadata);
    uploadable_file_request(const std::string& access_token,
                            file&& metadata,
                            const std::filesystem::path& to_upload);

protected:
    virtual bool is_upload() const override;
    virtual std::unique_ptr<cjson::doc> run_impl() override;

    std::function<void (double)> progress_callback_;

private:
    std::string metadata_to_json();

    bool is_upload_;
    std::filesystem::path to_upload_;
    file metadata_;
};

}

#endif