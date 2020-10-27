#include "../../calendar.hpp"

namespace espadin
{

namespace calendar
{

std::time_t get_utc(const std::tm& pieces)
{
    return timegm(&const_cast<std::tm&>(pieces));
}

}

}