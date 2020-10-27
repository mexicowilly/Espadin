#include "cjson_doc.hpp"
#include <stdexcept>

namespace espadin
{

namespace cjson
{

doc::doc(const std::string& text)
: json_(cJSON_Parse(text.c_str()))
{
    if (json_ == nullptr)
        throw std::runtime_error(std::string("Unable to parse '") + text + "'");
}

doc::~doc()
{
    cJSON_Delete(json_);
}

}

}