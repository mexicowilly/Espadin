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

class util
{
public:
    util(cJSON& json);

    void add_bool(const char* const name,
                  const std::optional<bool>& to_add);
    void add_map(const char* const name,
                 const std::optional<std::map<std::string, std::string>>& to_add);
    template <typename type>
    void add_object(const char* const name,
                    const std::optional<type>& to_add);
    template <typename type>
    void add_object_vector(const char* const name,
                           const std::optional<std::vector<type>>& to_add);
    void add_string(const char* const name,
                    const std::optional<std::string>& to_add);
    void add_string_vector(const char* const name,
                           const std::optional<std::vector<std::string>>& to_add);
    void add_time(const char* const name,
                  const std::optional<std::chrono::system_clock::time_point>& to_add);
    void set_bool(const char* const name,
                  std::optional<bool>& to_set);
    void set_bytes(const char* const name,
                   std::optional<std::vector<std::byte>>& to_set);
    void set_map(const char* const name,
                 std::optional<std::map<std::string, std::string>>& to_set);
    void set_map_of_string_array(const char* const name,
                                 std::optional<std::map<std::string, std::vector<std::string>>>& to_set);
    template <typename type>
    void set_number(const char* const name,
                    type& to_set);
    template <typename type>
    void set_number_from_string(const char* const name,
                                type& to_set);
    template <typename type>
    void set_object(const char* const name,
                    std::optional<type>& to_set);
    template <typename type>
    void set_object_vector(const char* const name,
                           std::optional<std::vector<type>>& to_set);
    void set_string(const char* const name,
                    std::optional<std::string>& to_set);
    void set_string_vector(const char* const name,
                           std::optional<std::vector<std::string>>& to_set);
    void set_time(const char* const name,
                  std::optional<std::chrono::system_clock::time_point>& to_set);
private:
    cJSON& json_;
};


template <typename type>
void util::add_object(const char* const name,
                      const std::optional<type>& to_add)
{
    if (to_add)
    {
        auto obj = cJSON_CreateObject();
        to_add->to_json(*obj);
        if (cJSON_GetArraySize(obj) > 0)
            cJSON_AddItemToObject(&json_, name, obj);
        else
            cJSON_Delete(obj);
    }
}

template <typename type>
void util::add_object_vector(const char* const name,
                             const std::optional<std::vector<type>>& to_add)
{
    if (to_add && !to_add->empty())
    {
        auto obj = cJSON_CreateArray();
        for (const auto& item : *to_add)
        {
            auto sub = cJSON_CreateObject();
            item.to_json(*sub);
            if (cJSON_GetArraySize(sub) > 0)
                cJSON_AddItemToArray(obj, sub);
        }
        if (cJSON_GetArraySize(obj) > 0)
            cJSON_AddItemToObject(&json_, name, obj);
        else
            cJSON_Delete(obj);
    }
}

template <typename type>
void util::set_number(const char* const name,
                      type& to_set)
{
    to_set.reset();
    auto num_obj = cJSON_GetObjectItemCaseSensitive(&json_, name);
    if (num_obj != nullptr)
    {
        if (cJSON_IsNumber(num_obj))
            to_set = num_obj->valuedouble;
        else if (cJSON_IsString(num_obj))
            to_set = std::stoul(num_obj->valuestring);
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a number");
    }
}

template <typename type>
void util::set_number_from_string(const char* const name,
                                  type& to_set)
{
    to_set.reset();
    auto num_obj = cJSON_GetObjectItemCaseSensitive(&json_, name);
    if (num_obj != nullptr)
    {
        if (cJSON_IsString(num_obj))
            to_set = std::stol(num_obj->valuestring);
        else
            throw std::runtime_error(std::string("JSON field '") + name + "' is not a string");
    }
}

template <typename type>
void util::set_object(const char* const name,
                      std::optional<type>& to_set)
{
    to_set.reset();
    auto obj_obj = cJSON_GetObjectItemCaseSensitive(&json_, name);
    if (obj_obj != nullptr)
    {
        if (cJSON_IsObject(obj_obj))
            to_set.emplace(*obj_obj);
        else
            throw std::runtime_error(std::string("The JSON '") + name + "' is not an object");
    }
}

template <typename type>
void util::set_object_vector(const char* const name,
                             std::optional<std::vector<type>>& to_set)
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
                if (cJSON_IsObject(item))
                    to_set->emplace_back(*item);
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