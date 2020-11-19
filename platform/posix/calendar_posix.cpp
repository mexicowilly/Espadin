#include "../../calendar.hpp"

namespace espadin
{

namespace calendar
{

std::tm get_pieces(std::time_t tm)
{
    std::tm result;
    gmtime_r(&tm, &result);
    return result;
}

std::time_t get_utc(const std::tm& pieces)
{
    return timegm(&const_cast<std::tm&>(pieces));
}

}

}