#if !defined(ESPADIN_CJSON_DOC_HPP__)
#define ESPADIN_CJSON_DOC_HPP__

#include "cJSON.h"
#include <string>

namespace espadin
{

namespace cjson
{

class doc
{
public:
    doc(const std::string& text);
    doc(const doc&) = delete;

    ~doc();

    doc& operator=(const doc&) = delete;

    cJSON* operator*();

    cJSON* get();

private:
    cJSON* json_;
};

inline cJSON* doc::operator*()
{
    return json_;
}

cJSON* doc::get()
{
    return json_;
}

}

}

#endif