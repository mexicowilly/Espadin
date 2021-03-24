#include <espadin/revisions_group.hpp>
#include "cjson_util.hpp"

namespace espadin
{

revisions_group::list_interface::reply::reply(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("nextPageToken", next_page_token_);
    ju.set_object_vector("revisions", revisions_);
}

}