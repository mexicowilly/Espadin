#if !defined(ESPADIN_FILES_GROUP_HPP__)
#define ESPADIN_FILES_GROUP_HPP__

#include <espadin/file.hpp>
#include <string>
#include <memory>
#include <functional>
#include <filesystem>

namespace espadin
{

class ESPADIN_EXPORT files_group
{
public:
    class copy_interface
    {
    public:
        virtual ~copy_interface() = default;

        virtual copy_interface& fields(const std::string& str) = 0;
        virtual copy_interface& ignore_default_visibility(bool state) = 0;
        virtual copy_interface& include_permissions_for_view(const std::string& str) = 0;
        virtual copy_interface& keep_revision_forever(bool state) = 0;
        virtual copy_interface& ocr_language(const std::string& lang) = 0;
        virtual std::unique_ptr<file> run() = 0;
        virtual copy_interface& supports_all_drives(bool state) = 0;
    };

    class create_interface
    {
    public:
        virtual ~create_interface() = default;

        virtual create_interface& ignore_default_visibility(bool state) = 0;
        virtual create_interface& keep_revision_forever(bool state) = 0;
        virtual create_interface& ocr_language(const std::string& lang) = 0;
        virtual create_interface& progress_callback(const std::function<void (double)>& cb) = 0;
        virtual std::unique_ptr<file> run() = 0;
        virtual create_interface& supports_all_drives(bool state) = 0;
        virtual create_interface& use_content_as_indexable_text(bool state) = 0;
    };

    class delete_interface
    {
    public:
        virtual ~delete_interface() = default;

        virtual delete_interface& supports_all_drives(bool state) = 0;
        virtual void run() = 0;
    };

    class export_interface
    {
    public:
        virtual ~export_interface() = default;

        virtual void run() = 0;
    };

    class generate_ids_interface
    {
    public:
        class reply
        {
        public:
            reply(const cJSON& json);

            const std::optional<std::vector<std::string>>& ids() const;
            const std::optional<std::string>& kind() const;
            const std::optional<std::string>& space() const;

        private:
            std::optional<std::string> kind_;
            std::optional<std::string> space_;
            std::optional<std::vector<std::string>> ids_;
        };

        virtual ~generate_ids_interface() = default;

        virtual generate_ids_interface& count(std::size_t number) = 0;
        virtual generate_ids_interface& fields(const std::string& str) = 0;
        virtual std::unique_ptr<reply> run() = 0;
        virtual generate_ids_interface& space(const std::string& str) = 0;
    };

    class get_interface
    {
    public:
        virtual ~get_interface() = default;

        virtual get_interface& acknowledge_abuse(bool ack) = 0;
        virtual get_interface& fields(const std::string& str) = 0;
        virtual get_interface& include_permissions_for_view(const std::string& str) = 0;
        virtual std::unique_ptr<file> run() = 0;
        virtual get_interface& supports_all_drives(bool sup) = 0;
    };

    class list_interface
    {
    public:
        class reply
        {
        public:
            reply(const cJSON& json);

            const std::optional<std::vector<file>>& files() const;
            const std::optional<bool>& incomplete_search() const;
            const std::optional<std::string>& kind() const;
            const std::optional<std::string>& next_page_token() const;

        private:
            std::optional<std::string> kind_;
            std::optional<std::string> next_page_token_;
            std::optional<std::vector<file>> files_;
            std::optional<bool> incomplete_search_;
        };

        virtual ~list_interface() = default;

        virtual list_interface& corpora(const std::string& str) = 0;
        virtual list_interface& drive_id(const std::string& str) = 0;
        virtual list_interface& fields(const std::string& str) = 0;
        virtual list_interface& include_items_from_all_drives(bool flg) = 0;
        virtual list_interface& include_permissions_for_view(const std::string& str) = 0;
        virtual list_interface& order_by(const std::string& str) = 0;
        virtual list_interface& page_size(std::size_t count) = 0;
        virtual list_interface& page_token(const std::string& str) = 0;
        virtual list_interface& query(const std::string& str) = 0;
        virtual std::unique_ptr<reply> run() = 0;
        virtual list_interface& spaces(const std::string& str) = 0;
        virtual list_interface& supports_all_drives(bool flg) = 0;
    };

    class update_interface
    {
    public:
        virtual ~update_interface() = default;

        virtual update_interface& add_parents(const std::string& parents) = 0;
        virtual update_interface& include_permissions_for_view(const std::string& str) = 0;
        virtual update_interface& keep_revision_forever(bool flg) = 0;
        virtual update_interface& ocr_language(const std::string& lang) = 0;
        virtual update_interface& progress_callback(const std::function<void (double)>& cb) = 0;
        virtual update_interface& remove_parents(const std::string& parents) = 0;
        virtual std::unique_ptr<file> run() = 0;
        virtual update_interface& supports_all_drives(bool flg) = 0;
        virtual update_interface& use_content_as_indexable_text(bool flg) = 0;
    };

    virtual ~files_group() = default;

    virtual std::unique_ptr<copy_interface> copy(const std::string& file_id, file&& metadata) = 0;
    virtual std::unique_ptr<create_interface> create(file&& metadata) = 0;
    virtual std::unique_ptr<create_interface> create(file&& metadata,
                                                     const std::filesystem::path& to_upload) = 0;
    virtual std::unique_ptr<delete_interface> del(const std::string& file_id) = 0;
    virtual void empty_trash() = 0;
    virtual std::unique_ptr<export_interface> exp(const std::string& file_id,
                                                  const std::string& mime_type,
                                                  std::ostream& content_destination) = 0;
    virtual std::unique_ptr<generate_ids_interface> generate_ids() = 0;
    virtual std::unique_ptr<get_interface> get(const std::string& file_id) = 0;
    virtual std::unique_ptr<get_interface> get(const std::string& file_id,
                                               std::ostream& content_destination) = 0;
    virtual std::unique_ptr<list_interface> list() = 0;
    virtual std::unique_ptr<update_interface> update(const std::string& file_id,
                                                     file&& metadata) = 0;
    virtual std::unique_ptr<update_interface> update(const std::string& file_id,
                                                     file&& metadata,
                                                     const std::filesystem::path& to_upload) = 0;
};

inline const std::optional<std::vector<std::string>>& files_group::generate_ids_interface::reply::ids() const
{
    return ids_;
}

inline const std::optional<std::string>& files_group::generate_ids_interface::reply::kind() const
{
    return kind_;
}

inline const std::optional<std::string>& files_group::generate_ids_interface::reply::space() const
{
    return space_;
}

inline const std::optional<std::vector<file>>& files_group::list_interface::reply::files() const
{
    return files_;
}

inline const std::optional<bool>& files_group::list_interface::reply::incomplete_search() const
{
    return incomplete_search_;
}

inline const std::optional<std::string>& files_group::list_interface::reply::kind() const
{
    return kind_;
}

inline const std::optional<std::string>& files_group::list_interface::reply::next_page_token() const
{
    return next_page_token_;
}

}

#endif