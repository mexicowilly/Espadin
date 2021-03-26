#if !defined(ESPADIN_CALENDAR_HPP_)
#define ESPADIN_CALENDAR_HPP_

#include <ctime>

namespace espadin
{

namespace calendar
{

std::tm get_pieces(std::time_t tm);
std::time_t get_utc(const std::tm& pieces);

}

}

#endif
