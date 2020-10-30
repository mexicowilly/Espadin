#if !defined(EPSADIN_CJSON_UTIL_HPP__)
#define EPSADIN_CJSON_UTIL_HPP__

#include "cJSON.h"
#include <string>
#include <chrono>
#include <stdexcept>
#include <vector>
#include <map>

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
void set_map(const cJSON& json,
             const char* const name,
             std::map<std::string, std::string>& to_set);
template <typename type>
void set_number(const cJSON& json,
                const char* const name,
                type& to_set);
template <typename type>
void set_object(const cJSON& json,
                const char* const name,
                std::optional<type>& to_set);
template <typename type>
void set_object_vector(const cJSON& json,
                       const char* const name,
                       std::vector<type>& to_set);
void set_string(const cJSON& json,
                const char* const name,
                std::string& to_set);
void set_string_vector(const cJSON& json,
                       const char* const name,
                       std::vector<std::string>& to_set);
void set_time(const cJSON& json,
              const char* const name,
              std::chrono::system_clock::time_point& to_set);

template <typename type>
void set_number(const cJSON& json,
                const char* const name,
                type& to_set)
{
    to_set = 0;
    auto num_obj = cJSON_GetObjectItemCaseSensitive(&json, name);
    if (num_obj != nullptr)
    {
        if (cJSON_IsNumber(num_obj))
            to_set = num_obj->valuedouble;
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a number");
    }
}

template <typename type>
void set_object(const cJSON& json,
                 const char* const name,
                 std::optional<type>& to_set)
{
    to_set.reset();
    auto obj_obj = cJSON_GetObjectItemCaseSensitive(&json, name);
    if (obj_obj != nullptr)
    {
        if (cJSON_IsObject(obj_obj))
            to_set.emplace(*obj_obj);
        else
            throw std::runtime_error(std::string("The JSON '") + name + "' is not an object");
    }
}

template <typename type>
void set_object_vector(const cJSON& json,
                       const char* const name,
                       std::vector<type>& to_set)
{
    to_set.clear();
    auto array_obj = cJSON_GetObjectItemCaseSensitive(&json, "owners");
    if (array_obj != nullptr)
    {
        if (cJSON_IsArray(array_obj))
        {
            cJSON* item;
            cJSON_ArrayForEach(item, array_obj)
            {
                if (cJSON_IsObject(item))
                    to_set.emplace_back(*item);
                else
                    throw std::runtime_error(std::string("The child of '") + name + "' is not an object");
            }
        }
        else
        {
            throw std::runtime_error(std::string("The JSON '") + name + "' is not an array");
        }
    }
}

}

}

#endif