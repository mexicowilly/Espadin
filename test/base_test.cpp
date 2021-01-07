#include "base_test.hpp"
#include <espadin/drive.hpp>

extern std::string ACCESS_TOKEN;

namespace espadin::test
{

std::string base::parent_id;

base::base()
    : drive_(ACCESS_TOKEN)
{
    if (parent_id.empty())
    {
        auto lst = drive_.files()->list();
        lst->fields("files/id")
            .query("name='Espadin Test' and mimeType='application/vnd.google-apps.folder' and 'root' in parents");
        auto reply = lst->run();
        if (!reply->files())
            throw std::runtime_error("Error listing folder 'Espadin Test'");
        if (reply->files()->empty())
        {
            file metadata;
            metadata.name("Espadin Test")
                    .parents({"root"})
                    .mime_type("application/vnd.google-apps.folder");
            auto created = drive_.files()->create(std::move(metadata))->run();
            if (!created || !created->id())
                throw std::runtime_error("Could not create folder 'Espadin Test'");
            parent_id = *created->id();
        }
        else
        {
            parent_id = reply->files()->at(0).id().value();
        }
    }
}

std::string base::create_doc(const std::string& name)
{
    espadin::file metadata;
    metadata.parents({parent_id})
            .name(name)
            .mime_type("application/vnd.google-apps.document");
    auto reply = drive_.files()->create(std::move(metadata))->run();
    if (!reply->id())
        throw std::runtime_error("Error creating doc '" + name + "'");
    return *reply->id();
}

void base::trash(const std::string& file_id)
{
    espadin::file f;
    f.trashed(true);
    drive_.files()->update(file_id, std::move(f))->run();
}

}