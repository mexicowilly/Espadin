#include <espadin/revision.hpp>
#include "cjson_util.hpp"

namespace espadin
{

revision::revision(const cJSON& json)
{
    cjson::util ju(const_cast<cJSON&>(json));
    ju.set_string("kind", kind_);
    ju.set_string("id", id_);
    ju.set_string("mimeType", mime_type_);
    ju.set_time("modifiedTime", modified_time_);
    ju.set_bool("keepForever", keep_forever_);
    ju.set_bool("published", published_);
    ju.set_string("publishedLink", published_link_);
    ju.set_bool("publishAuto", publish_auto_);
    ju.set_bool("publishedOutsideDomain", published_outside_domain_);
    ju.set_object("lastModifyingUser", last_modifying_user_);
    ju.set_string("originalFilename", original_filename_);
    ju.set_string("md5Checksum", md5_checksum_);
    ju.set_number("size", size_);
    ju.set_map("exportLinks", export_links_);
}

void revision::to_json(cJSON& json) const
{
    cjson::util ju(json);
    ju.add_bool("keepForever", keep_forever_);
    ju.add_bool("publishAuto", publish_auto_);
    ju.add_bool("published", published_);
    ju.add_bool("publishedOutsideDomain", published_outside_domain_);
}

}