#include <espadin/reply.hpp>
#include "cjson_util.hpp"

namespace espadin
{

reply::reply(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("id", id_);
    ju.set_time("createdTime", created_time_);
    ju.set_time("modifiedTime", modified_time_);
    ju.set_object("author", author_);
    ju.set_string("htmlContent", html_content_);
    ju.set_string("content", content_);
    ju.set_bool("deleted", deleted_);
    ju.set_string("action", action_);
}

}