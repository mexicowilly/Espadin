#if !defined(ESPADIN_DRIVE_HPP__)
#define ESPADIN_DRIVE_HPP__

#include <espadin/files_group.hpp>
#include <espadin/about.hpp>
#include <espadin/comments_group.hpp>
#include <espadin/replies_group.hpp>
#include <espadin/permissions_group.hpp>

namespace espadin
{

class ESPADIN_EXPORT drive
{
public:
    drive(const std::string& access_token);

    std::unique_ptr<about> about_drive(const std::string& fields);
    std::unique_ptr<comments_group> comments(const std::string& file_id);
    std::unique_ptr<files_group> files();
    std::unique_ptr<permissions_group> permissions(const std::string& file_id);
    std::unique_ptr<replies_group> replies(const std::string& file_id, const std::string& comment_id);

private:
    friend class comments_group;
    friend class files_group;
    friend class replies_group;
    friend class permissions_group;

    std::string access_token_;
};

}

#endif
