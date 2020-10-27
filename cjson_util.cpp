#include "cjson_util.hpp"
#include <stdexcept>

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

}

}