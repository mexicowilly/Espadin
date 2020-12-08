#include "resumable_file_upload.hpp"
#include <espadin/exception.hpp>

namespace
{

struct read_data
{
    read_data(std::ifstream& s) : stream(s), current_count(0), current_chunk_size(0) { }
    std::ifstream& stream;
    std::size_t current_count;
    std::size_t current_chunk_size;
};

std::uintmax_t current_pos_from_range_response(const std::optional<std::string>& rr)
{
    if (!rr)
        throw std::runtime_error("The Range header is not present in the response");
    auto start_pos = rr->find('-');
    if (start_pos == std::string::npos)
        throw std::runtime_error("The Range header does not contain '-'");
    auto sub = rr->substr(++start_pos);
    return std::stoull(sub) + 1;
}

std::size_t read_callback(char* buf, std::size_t sz, std::size_t nitems, void* udata)
{
    auto rd = reinterpret_cast<read_data*>(udata);
    std::size_t result = 0;
    if (rd->current_count < rd->current_chunk_size)
    {
        auto to_read = std::min(sz * nitems, rd->current_chunk_size - rd->current_count);
        rd->stream.read(buf, to_read);
        result = rd->stream.gcount();
        rd->current_count += result;
    }
    return result;
}

}

namespace espadin
{

resumable_file_upload::resumable_file_upload(const std::string& auth_header,
                                             const std::string& url,
                                             const std::filesystem::path& file,
                                             const std::function<void(double)>& progress_callback)
    : progress_callback_(progress_callback),
      file_(file),
      stream_(file)
{
    curl_.header("Authorization", auth_header);
    curl_.set_option(CURLOPT_UPLOAD, 1, "upload");
    curl_.set_option(CURLOPT_READFUNCTION, read_callback, "read function");
    curl_.set_option(CURLOPT_URL, url.c_str(), "URL");
}

std::unique_ptr<cjson::doc> resumable_file_upload::run()
{
    std::unique_ptr<cjson::doc> result;
    auto total_size = std::filesystem::file_size(file_);
    read_data rd(stream_);
    curl_.set_option(CURLOPT_READDATA, &rd, "read data");
    std::uintmax_t current_pos = 0;
    while (current_pos < total_size)
    {
        rd.current_count = 0;
        rd.current_chunk_size = std::min(total_size - current_pos, 256UL * 1024UL);
        std::ostringstream range;
        range << "bytes " << current_pos << '-' << current_pos + rd.current_chunk_size - 1 << '/' << total_size;
        curl_.header("Content-Length", std::to_string(rd.current_chunk_size));
        curl_.header("Content-Range", range.str());
        result = curl_.perform();
        if (curl_.response_code() >= 400)
            throw http_exception(curl_.response_code());
        if (curl_.response_code() > 201)
        {
            auto actual_current_pos = current_pos_from_range_response(curl_.response_header("Range"));
            if (stream_.tellg() != actual_current_pos)
                stream_.seekg(actual_current_pos);
            current_pos = actual_current_pos;
        }
        else
        {
            current_pos = total_size;
        }
        if (progress_callback_)
            progress_callback_(static_cast<double>(current_pos) / static_cast<double>(total_size) * 100.0);
    }
    return result;
}

}