#include <espadin/exception.hpp>
#include "cJSON.h"
#include <ostream>

namespace espadin
{

drive_exception::drive_exception(const cJSON& json)
    : code_(std::numeric_limits<int>::min())
{
    auto err = cJSON_GetObjectItemCaseSensitive(&json, "error");
    if (err != nullptr)
    {
        auto sub = cJSON_GetObjectItemCaseSensitive(err, "code");
        if (sub != nullptr && cJSON_IsNumber(sub))
            code_ = sub->valuedouble;
        sub = cJSON_GetObjectItemCaseSensitive(err, "message");
        if (sub != nullptr && cJSON_IsString(sub))
            message_ = sub->valuestring;
        sub = cJSON_GetObjectItemCaseSensitive(err, "errors");
        if (sub != nullptr && cJSON_IsArray(sub))
        {
            cJSON* item;
            cJSON_ArrayForEach(item, sub)
            {
                if (cJSON_IsObject(item))
                {
                    cJSON* item2;
                    cJSON_ArrayForEach(item2, item)
                    {
                        if (cJSON_IsString(item2))
                            errors_[item2->string] = item2->valuestring;
                    }
                }
            }
        }
    }
}

const char* drive_exception::what() const noexcept
{
    return message_.c_str();
}

std::ostream& operator<< (std::ostream& stream, const drive_exception& excp)
{
    auto doc = cJSON_CreateObject();
    if (excp.what()[0] != 0)
        cJSON_AddStringToObject(doc, "message", excp.what());
    if (excp.code() != std::numeric_limits<int>::min())
        cJSON_AddNumberToObject(doc, "code", excp.code());
    if (!excp.errors().empty())
    {
        auto errs = cJSON_CreateObject();
        for (const auto& p : excp.errors())
            cJSON_AddStringToObject(errs, p.first.c_str(), p.second.c_str());
        cJSON_AddItemToObject(doc, "errors", errs);
    }
    auto json = cJSON_PrintUnformatted(doc);
    stream << json;
    cJSON_free(json);
    return stream;
}

http_exception::http_exception(long code)
    : std::runtime_error("HTTP error " + std::to_string(code)),
      code_(code)
{
}

}