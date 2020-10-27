#include "cjson_util.hpp"
#include "calendar.hpp"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <cassert>

namespace espadin
{

namespace cjson
{

void set_bool(const cJSON& json,
              const char* const name,
              bool& to_set)
{
    auto bool_obj = cJSON_GetObjectItem(&json, name);
    if (bool_obj != nullptr)
    {
        if (cJSON_IsBool(bool_obj))
            to_set = (bool_obj->type == cJSON_True);
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a bool");
    }
}

void set_string(const cJSON& json,
                const char* const name,
                std::string& to_set)
{
    auto str_obj = cJSON_GetObjectItem(&json, name);
    if (str_obj != nullptr)
    {
        if (cJSON_IsString(str_obj))
            to_set = str_obj->valuestring;
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a string");
    }
}

void set_time(const cJSON& json,
              const char* const name,
              std::chrono::system_clock::time_point& to_set)
{
    auto str_obj = cJSON_GetObjectItem(&json, name);
    if (str_obj != nullptr)
    {
        if (cJSON_IsString(str_obj))
        {
            std::istringstream stream(str_obj->valuestring);
            std::tm pieces;
            std::memset(&pieces, 0, sizeof(pieces));
            stream >> std::get_time(&pieces, "%Y-%m-%dT%T.");
            auto seconds = calendar::get_utc(pieces);
            unsigned milliseconds;
            stream >> milliseconds;
            std::string tz;
            stream >> tz;
            assert(tz == "Z");
            to_set = std::chrono::system_clock::from_time_t(seconds) + std::chrono::milliseconds(milliseconds);
        }
        else
        {
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a string");
        }
    }
}

}

}