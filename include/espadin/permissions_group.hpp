#if !defined(ESPADIN_PERMISSIONS_GROUP_HPP_)
#define ESPADIN_PERMISSIONS_GROUP_HPP_

#include <espadin/permission.hpp>
#include <memory>

namespace espadin
{

class ESPADIN_EXPORT permissions_group
{
public:
    class create_interface
    {
    public:
        virtual ~create_interface() = default;

        virtual create_interface& email_message(const std::string& str) = 0;
        virtual create_interface& fields(const std::string& str) = 0;
        virtual create_interface& move_to_new_owners_root(bool to_set) = 0;
        virtual std::unique_ptr<permission> run() = 0;
        virtual create_interface& send_notification_email(bool to_set) = 0;
        virtual create_interface& supports_all_drives(bool to_set) = 0;
        virtual create_interface& transfer_ownership(bool to_set) = 0;
        virtual create_interface& use_domain_admin_access(bool to_set) = 0;
    };

    class delete_interface
    {
    public:
        virtual ~delete_interface() = default;

        virtual void run() = 0;
        virtual delete_interface& supports_all_drives(bool to_set) = 0;
        virtual delete_interface& use_domain_admin_access(bool to_set) = 0;
    };

    class get_interface
    {
    public:
        virtual ~get_interface() = default;

        virtual get_interface& fields(const std::string& str) = 0;
        virtual std::unique_ptr<permission> run() = 0;
        virtual get_interface& supports_all_drives(bool to_set) = 0;
        virtual get_interface& use_domain_admin_access(bool to_set) = 0;
    };

    class list_interface
    {
    public:
        class reply
        {
        public:
            reply(const cJSON& json);

            const std::optional<std::string>& kind() const;
            const std::optional<std::string>& next_page_token() const;
            const std::optional<std::vector<permission>>& permissions() const;

        private:
            std::optional<std::string> kind_;
            std::optional<std::string> next_page_token_;
            std::optional<std::vector<permission>> permissions_;
        };

        virtual ~list_interface() = default;

        virtual list_interface& fields(const std::string& str) = 0;
        virtual list_interface& include_permissions_for_view(const std::string& str) = 0;
        virtual list_interface& page_size(std::size_t num) = 0;
        virtual list_interface& page_token(const std::string& tok) = 0;
        virtual std::unique_ptr<reply> run() = 0;
        virtual list_interface& supports_all_drives(bool to_set) = 0;
        virtual list_interface& use_domain_admin_access(bool to_set) = 0;
    };

    class update_interface
    {
    public:
        virtual ~update_interface() = default;

        virtual update_interface& fields(const std::string& str) = 0;
        virtual update_interface& remove_expiration(bool to_set) = 0;
        virtual std::unique_ptr<permission> run() = 0;
        virtual update_interface& supports_all_drives(bool to_set) = 0;
        virtual update_interface& transfer_ownership(bool to_set) = 0;
        virtual update_interface& use_domain_admin_access(bool to_set) = 0;
    };

    virtual ~permissions_group() = default;

    virtual std::unique_ptr<create_interface> create(permission&& perm) = 0;
    virtual std::unique_ptr<delete_interface> del(const std::string& permission_id) = 0;
    virtual std::unique_ptr<get_interface> get(const std::string& permission_id) = 0;
    virtual std::unique_ptr<list_interface> list() = 0;
    virtual std::unique_ptr<update_interface> update(const std::string& permission_id, permission&& perm) = 0;
};

inline const std::optional<std::string>& permissions_group::list_interface::reply::kind() const
{
    return kind_;
}

inline const std::optional<std::string>& permissions_group::list_interface::reply::next_page_token() const
{
    return next_page_token_;
}

inline const std::optional<std::vector<permission>>& permissions_group::list_interface::reply::permissions() const
{
    return permissions_;
}

}

#endif
