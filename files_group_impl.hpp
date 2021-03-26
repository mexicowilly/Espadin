#if !defined(ESPADIN_FILES_GROUP_IMPL_HPP_)
#define ESPADIN_FILES_GROUP_IMPL_HPP_

#include <espadin/files_group.hpp>
#include "access_token_accessor.hpp"

namespace espadin
{

class files_group_impl : public files_group, public access_token_accessor
{
public:
    files_group_impl(access_token_function func);

    virtual std::unique_ptr<copy_interface> copy(const std::string& file_id, file&& metadata) override;
    virtual std::unique_ptr<create_interface> create(file&& metadata) override;
    virtual std::unique_ptr<create_interface> create(file&& metadata,
                                                     const std::filesystem::path& to_upload) override;
    virtual std::unique_ptr<delete_interface> del(const std::string& file_id) override;
    virtual void empty_trash() override;
    virtual std::unique_ptr<export_interface> exp(const std::string& file_id,
                                                  const std::string& mime_type,
                                                  std::ostream& content_destination) override;
    virtual std::unique_ptr<generate_ids_interface> generate_ids() override;
    virtual std::unique_ptr<get_interface> get(const std::string& file_id) override;
    virtual std::unique_ptr<get_interface> get(const std::string& file_id,
                                               std::ostream& content_destination) override;
    virtual std::unique_ptr<list_interface> list() override;
    virtual std::unique_ptr<update_interface> update(const std::string& file_id,
                                                     file&& metadata) override;
    virtual std::unique_ptr<update_interface> update(const std::string& file_id,
                                                     file&& metadata,
                                                     const std::filesystem::path& to_upload) override;
};

}

#endif
