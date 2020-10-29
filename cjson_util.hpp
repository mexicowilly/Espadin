#if !defined(EPSADIN_CJSON_UTIL_HPP__)
#define EPSADIN_CJSON_UTIL_HPP__

#include "cJSON.h"
#include <string>
#include <chrono>
#include <stdexcept>
#include <vector>

namespace espadin
{

namespace cjson
{

void set_bool(const cJSON& json,
              const char* const name,
              bool& to_set);
void set_bytes(const cJSON& json,
               const char* const name,
               std::vector<std::byte>& to_set);
template <typename type>
void set_number(const cJSON& json,
                const char* const name,
                type& to_set);
void set_string(const cJSON& json,
                const char* const name,
                std::string& to_set);
void set_time(const cJSON& json,
              const char* const name,
              std::chrono::system_clock::time_point& to_set);

template <typename type>
void set_number(const cJSON& json,
                const char* const name,
                type& to_set)
{
    to_set = 0;
    auto num_obj = cJSON_GetObjectItem(&json, name);
    if (num_obj != nullptr)
    {
        if (cJSON_IsNumber(num_obj))
            to_set = num_obj->valuedouble;
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a number");
    }
}

}

}

#endif
