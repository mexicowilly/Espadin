#include <espadin/comment.hpp>
#include "cjson_util.hpp"

namespace espadin
{

comment::comment(const cJSON& json)
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
    ju.set_bool("resolved", resolved_);
    ju.set_object("quotedFileContent", quoted_file_content_);
    ju.set_string("anchor", anchor_);
    ju.set_object_vector("replies", replies_);
}

void comment::to_json(cJSON& json) const
{
    cjson::util ju(json);
    ju.add_string("anchor", anchor_);
    ju.add_string("content", content_);
    ju.add_object("quotedFileContent", quoted_file_content_);
}

comment::quoted_file_content::quoted_file_content(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("mimeType", mime_type_);
    ju.set_string("value", value_);
}

void comment::quoted_file_content::to_json(cJSON& json) const
{
    cjson::util ju(json);
    ju.add_string("value", value_);
}

}