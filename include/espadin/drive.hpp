#if !defined(ESPADIN_DRIVE_HPP__)
#define ESPADIN_DRIVE_HPP__

#include <espadin/files_group.hpp>
#include <espadin/about.hpp>
#include <espadin/comments_group.hpp>

namespace espadin
{

class ESPADIN_EXPORT drive
{
public:
    drive(const std::string& access_token);

    std::unique_ptr<about> about_drive(const std::string& fields);
    std::unique_ptr<comments_group> comments();
    std::unique_ptr<files_group> files();

private:
    friend class comments_group;
    friend class files_group;

    std::string access_token_;
};

}

#endif
