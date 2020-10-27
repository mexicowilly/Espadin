#if !defined(EPSADIN_CJSON_UTIL_HPP__)
#define EPSADIN_CJSON_UTIL_HPP__

#include "cJSON.h"
#include <string>

namespace espadin
{

namespace cjson
{

void set_bool(const cJSON& json,
              const char* const name,
              bool& to_set);
void set_string(const cJSON& json,
                const char* const name,
                std::string& to_set);

}

}

#endif
