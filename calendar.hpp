#if !defined(ESPADIN_CALENDAR_HPP__)
#define ESPADIN_CALENDAR_HPP__

#include <ctime>

namespace espadin
{

namespace calendar
{

std::time_t get_utc(const std::tm& pieces);

}

}

#endif
