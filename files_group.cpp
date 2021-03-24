#include <espadin/files_group.hpp>
#include "cjson_util.hpp"

namespace espadin
{

files_group::generate_ids_interface::reply::reply(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("space", space_);
    ju.set_string_vector("ids", ids_);
}

files_group::list_interface::reply::reply(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("nextPageToken", next_page_token_);
    ju.set_bool("incompleteSearch", incomplete_search_);
    ju.set_object_vector("files", files_);
}

}