#include <espadin/drive.hpp>

namespace espadin
{

drive::drive(const std::string& access_token)
    : access_token_(access_token)
{
}

std::unique_ptr<files_group> drive::files()
{
    return std::make_unique<files_group>(*this);
}

}