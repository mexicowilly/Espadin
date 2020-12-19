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

util::util(cJSON& json)
    : json_(json)
{
}

void util::add_bool(const char* const name,
                    const std::optional<bool>& to_add)
{
    if (to_add)
        cJSON_AddBoolToObject(&json_, name, to_add.value() ? cJSON_True : cJSON_False);
}

void util::add_map(const char* const name,
                   const std::optional<std::map<std::string, std::string>>& to_add)
{
    if (to_add && !to_add->empty())
    {
        auto obj = cJSON_CreateObject();
        for (const auto& p : *to_add)
            cJSON_AddStringToObject(obj, p.first.c_str(), p.second.c_str());
        cJSON_AddItemToObject(&json_, name, obj);
    }
}

void util::add_string(const char* const name,
                      const std::optional<std::string>& to_add)
{
    if (to_add)
        cJSON_AddStringToObject(&json_, name, to_add->c_str());
}

void util::add_string_vector(const char* const name,
                             const std::optional<std::vector<std::string>>& to_add)
{
    if (to_add && !to_add->empty())
    {
        auto arr = cJSON_CreateArray();
        for (const auto& s : *to_add)
        {
            auto str = cJSON_CreateString(s.c_str());
            cJSON_AddItemToArray(arr, str);
        }
        cJSON_AddItemToObject(&json_, name, arr);
    }
}

void util::add_time(const char* const name,
                    const std::optional<std::chrono::system_clock::time_point>& to_add)
{
    if (to_add)
    {
        auto pieces = calendar::get_pieces(std::chrono::system_clock::to_time_t(*to_add));
        std::ostringstream stream;
        stream << std::put_time(&pieces, "%FT%T.000Z");
        cJSON_AddStringToObject(&json_, name, stream.str().c_str());
    }
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

void util::set_map_of_string_array(const char* const name,
                                   std::optional<std::map<std::string, std::vector<std::string>>>& to_set)
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
                if (cJSON_IsArray(item))
                {
                    cJSON* sub;
                    std::vector<std::string> vec;
                    cJSON_ArrayForEach(sub, item)
                    {
                        if (cJSON_IsString(sub))
                            vec.emplace_back(sub->valuestring);
                        else
                            throw std::runtime_error(std::string("The child of '") + item->string + "' item '" + item->string + "' is not a string");
                    }
                    to_set->emplace(item->string, vec);
                }
            }
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