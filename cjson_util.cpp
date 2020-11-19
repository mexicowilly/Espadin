#include "cjson_util.hpp"
#include "calendar.hpp"
#include "cppcodec/base64_rfc4648.hpp"
#include <iomanip>
#include <cstring>
#include <cassert>
#include <algorithm>

namespace espadin
{

namespace cjson
{

util::util(const cJSON& json)
    : json_(json)
{
}

void util::set_bool(const char* const name,
                    std::optional<bool>& to_set)
{
    to_set.reset();
    auto bool_obj = cJSON_GetObjectItemCaseSensitive(&json_, name);
    if (bool_obj != nullptr)
    {
        if (cJSON_IsBool(bool_obj))
            to_set = (bool_obj->type == cJSON_True);
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a bool");
    }
}

void util::set_bytes(const char* const name,
                     std::optional<std::vector<std::byte>>& to_set)
{
    to_set.reset();
    auto str_obj = cJSON_GetObjectItemCaseSensitive(&json_, name);
    if (str_obj != nullptr)
    {
        if (cJSON_IsString(str_obj))
        {
            auto tmp = cppcodec::base64_rfc4648::decode(str_obj->valuestring, std::strlen(str_obj->valuestring));
            to_set.emplace();
            std::transform(tmp.begin(),
                           tmp.end(),
                           std::back_inserter(*to_set),
                           [] (uint8_t c) -> std::byte { return static_cast<std::byte>(c); });
        }
        else
        {
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a string");
        }
    }
}

void util::set_map(const char* const name,
                   std::optional<std::map<std::string, std::string>>& to_set)
{
    to_set.reset();
    auto map_obj = cJSON_GetObjectItemCaseSensitive(&json_, name);
    if (map_obj != nullptr)
    {
        if (cJSON_IsObject(map_obj))
        {
            to_set.emplace();
            cJSON* item;
            cJSON_ArrayForEach(item, map_obj)
            {
                if (cJSON_IsString(item))
                    (*to_set)[item->string] = item->valuestring;
                else
                    throw std::runtime_error(std::string("The child of '") + name + "' item '" + item->string + "' is not a string");
            }
        }
        else
        {
            throw std::runtime_error(std::string("The JSON '") + name + "' is not an object");
        }
    }
}

void util::set_string(const char* const name,
                      std::optional<std::string>& to_set)
{
    to_set.reset();
    auto str_obj = cJSON_GetObjectItemCaseSensitive(&json_, name);
    if (str_obj != nullptr)
    {
        if (cJSON_IsString(str_obj))
            to_set = str_obj->valuestring;
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a string");
    }
}

void util::set_string_vector(const char* const name,
                             std::optional<std::vector<std::string>>& to_set)
{
    to_set.reset();
    auto array_obj = cJSON_GetObjectItemCaseSensitive(&json_, name);
    if (array_obj != nullptr)
    {
        if (cJSON_IsArray(array_obj))
        {
            to_set.emplace();
            cJSON* item;
            cJSON_ArrayForEach(item, array_obj)
            {
                if (cJSON_IsString(item))
                    to_set->emplace_back(item->valuestring);
                else
                    throw std::runtime_error(std::string("The JSON child of parent '") + name + "' is not a string");
            }
        }
        else
        {
            throw std::runtime_error(std::string("The JSON '") + name + "' is not an array");
        }
    }
}

void util::set_time(const char* const name,
                    std::optional<std::chrono::system_clock::time_point>& to_set)
{
    to_set.reset();
    auto str_obj = cJSON_GetObjectItemCaseSensitive(&json_, name);
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