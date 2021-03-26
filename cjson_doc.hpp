#if !defined(ESPADIN_CJSON_DOC_HPP_)
#define ESPADIN_CJSON_DOC_HPP_

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

inline cJSON* doc::get()
{
    return json_;
}

}

}

#endif