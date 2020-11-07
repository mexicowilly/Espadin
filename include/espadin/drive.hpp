#if !defined(ESPADIN_DRIVE_HPP__)
#define ESPADIN_DRIVE_HPP__

#include <espadin/files_group.hpp>

namespace espadin
{

class ESPADIN_EXPORT drive
{
public:
    drive(const std::string& access_token);

    std::unique_ptr<files_group> files();

private:
    friend class files_group;

    std::string access_token_;
};

}

#endif
