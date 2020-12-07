#if !defined(ESPADIN_RESUMABLE_FILE_UPLOAD__)
#define ESPADIN_RESUMABLE_FILE_UPLOAD__

#include "curl.hpp"
#include <filesystem>
#include <functional>
#include <fstream>

namespace espadin
{

class resumable_file_upload
{
public:
    resumable_file_upload(const std::string& auth_header,
                          const std::string& url,
                          const std::filesystem::path& file,
                          const std::function<void(double)>& progress_callback);

    std::unique_ptr<cjson::doc> run();

private:
    curl curl_;
    std::function<void(double)> progress_callback_;
    std::filesystem::path file_;
    std::ifstream stream_;
};

}

#endif
