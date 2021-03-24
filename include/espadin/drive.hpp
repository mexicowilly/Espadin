#if !defined(ESPADIN_DRIVE_HPP__)
#define ESPADIN_DRIVE_HPP__

#include <espadin/files_group.hpp>
#include <espadin/about.hpp>
#include <espadin/comments_group.hpp>
#include <espadin/replies_group.hpp>
#include <espadin/permissions_group.hpp>
#include <espadin/revisions_group.hpp>
#include <mutex>

namespace espadin
{

class ESPADIN_EXPORT drive
{
public:
    drive(const std::string& access_token);

    std::unique_ptr<about> about_drive(const std::string& fields);
    void access_token(const std::string& token);
    std::unique_ptr<comments_group> comments(const std::string& file_id);
    std::unique_ptr<files_group> files();
    std::unique_ptr<permissions_group> permissions(const std::string& file_id);
    std::unique_ptr<replies_group> replies(const std::string& file_id, const std::string& comment_id);
    std::unique_ptr<revisions_group> revisions(const std::string& file_id);

private:
    const std::string& token();

    std::string access_token_;
    std::mutex token_guard_;
};

}

#endif
