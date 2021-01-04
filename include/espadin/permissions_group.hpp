#if !defined(ESPADIN_PERMISSIONS_GROUP_HPP__)
#define ESPADIN_PERMISSIONS_GROUP_HPP__

#include <espadin/permission.hpp>
#include <memory>

namespace espadin
{

class drive;

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

    permissions_group(drive& drv, const std::string& file_id);
    permissions_group(const permissions_group&) = delete;

    permissions_group& operator= (const permissions_group&) = delete;

    std::unique_ptr<create_interface> create(permission&& perm);
    std::unique_ptr<delete_interface> del(const std::string& permission_id);
    std::unique_ptr<get_interface> get(const std::string& permission_id);

private:
    drive& drive_;
    std::string file_id_;
};

}

#endif
