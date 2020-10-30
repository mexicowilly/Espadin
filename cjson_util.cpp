#include "cjson_util.hpp"
#include "calendar.hpp"
#include <iomanip>
#include <cstring>
#include <cassert>

namespace
{

void base64_decode(const char* const in, std::vector<std::byte>& out)
{
    static const unsigned indexes[256] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 63, 62, 62, 63, 52, 53, 54, 55,
        56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0,
        0, 0, 0, 63, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
    };

    auto p = reinterpret_cast<const std::byte*>(in);
    auto len = std::strlen(in);
    auto pad = len > 0 && (len % 4 || p[len - 1] == static_cast<std::byte>('='));
    auto max_l = ((len + 3) / 4 - pad) * 4;
    out.assign(max_l / 4 * 3 + pad, static_cast<std::byte>(0));
    for (std::size_t i = 0, j = 0; i < max_l; i += 4)
    {
        auto n = indexes[static_cast<unsigned>(p[i])] << 18 |
                 indexes[static_cast<unsigned>(p[i + 1])] << 12 |
                 indexes[static_cast<unsigned>(p[i + 2])] << 6 |
                 indexes[static_cast<unsigned>(p[i + 3])];
        out[j++] = static_cast<std::byte>(n >> 16);
        out[j++] = static_cast<std::byte>(n >> 8 & 0xFF);
        out[j++] = static_cast<std::byte>(n & 0xFF);
    }
    if (pad)
    {
        auto n = indexes[static_cast<unsigned>(p[max_l])] << 18 | indexes[static_cast<unsigned>(p[max_l + 1])] << 12;
        out[out.size() - 1] = static_cast<std::byte>(n >> 16);
        if (len > max_l + 2 && p[max_l + 2] != static_cast<std::byte>('='))
        {
            n |= indexes[static_cast<unsigned>(p[max_l + 2])] << 6;
            out.push_back(static_cast<std::byte>(n >> 8 & 0xFF));
        }
    }
}

}

namespace espadin
{

namespace cjson
{

void set_bool(const cJSON& json,
              const char* const name,
              bool& to_set)
{
    to_set = false;
    auto bool_obj = cJSON_GetObjectItemCaseSensitive(&json, name);
    if (bool_obj != nullptr)
    {
        if (cJSON_IsBool(bool_obj))
            to_set = (bool_obj->type == cJSON_True);
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a bool");
    }
}

void set_bytes(const cJSON& json,
               const char* const name,
               std::vector<std::byte>& to_set)
{
    auto str_obj = cJSON_GetObjectItemCaseSensitive(&json, name);
    if (str_obj != nullptr)
    {
        if (cJSON_IsString(str_obj))
            base64_decode(str_obj->valuestring, to_set);
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a string");
    }
}

void set_map(const cJSON& json,
             const char* const name,
             std::map<std::string, std::string>& to_set)
{
    to_set.clear();
    auto map_obj = cJSON_GetObjectItemCaseSensitive(&json, name);
    if (map_obj != nullptr)
    {
        if (cJSON_IsObject(map_obj))
        {
            cJSON* item;
            cJSON_ArrayForEach(item, map_obj)
            {
                if (cJSON_IsString(item))
                    to_set[item->string] = item->valuestring;
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

void set_string(const cJSON& json,
                const char* const name,
                std::string& to_set)
{
    to_set.clear();
    auto str_obj = cJSON_GetObjectItemCaseSensitive(&json, name);
    if (str_obj != nullptr)
    {
        if (cJSON_IsString(str_obj))
            to_set = str_obj->valuestring;
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a string");
    }
}

void set_string_vector(const cJSON& json,
                       const char* const name,
                       std::vector<std::string>& to_set)
{
    to_set.clear();
    auto array_obj = cJSON_GetObjectItemCaseSensitive(&json, name);
    if (array_obj != nullptr)
    {
        if (cJSON_IsArray(array_obj))
        {
            cJSON* item;
            cJSON_ArrayForEach(item, array_obj)
            {
                if (cJSON_IsString(item))
                    to_set.emplace_back(item->valuestring);
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

void set_time(const cJSON& json,
              const char* const name,
              std::chrono::system_clock::time_point& to_set)
{
    to_set = std::chrono::system_clock::time_point();
    auto str_obj = cJSON_GetObjectItemCaseSensitive(&json, name);
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