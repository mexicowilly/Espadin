#if !defined(ESPADIN_FILES_GROUP_HPP__)
#define ESPADIN_FILES_GROUP_HPP__

#include <espadin/file.hpp>
#include <string>
#include <memory>
#include <functional>
#include <filesystem>

namespace espadin
{

class drive;

class ESPADIN_EXPORT files_group
{
public:
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

    class list_interface
    {
    public:
        class reply
        {
        public:
            reply(const cJSON& json);

            const std::vector<file>& files() const;
            bool incomplete_search() const;
            const std::string& kind() const;
            const std::string& next_page_token() const;

        private:
            std::string kind_;
            std::string next_page_token_;
            std::vector<file> files_;
            bool incomplete_search_;
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

    files_group(drive& drv);
    files_group(const files_group&) = delete;

    files_group& operator= (const files_group&) = delete;

    std::unique_ptr<create_interface> create(const file& metadata);
    std::unique_ptr<create_interface> create(const file& metadata,
                                             const std::vector<std::byte>& data);
    std::unique_ptr<list_interface> list();

private:
    drive& drive_;
};

inline const std::vector<file>& files_group::list_interface::reply::files() const
{
    return files_;
}

inline bool files_group::list_interface::reply::incomplete_search() const
{
    return incomplete_search_;
}

inline const std::string& files_group::list_interface::reply::kind() const
{
    return kind_;
}

inline const std::string& files_group::list_interface::reply::next_page_token() const
{
    return next_page_token_;
}

}

#endif