#if !defined(ESPADIN_REPLIES_GROUP_HPP__)
#define ESPADIN_REPLIES_GROUP_HPP__

#include <espadin/reply.hpp>
#include <memory>

namespace espadin
{

class drive;

class ESPADIN_EXPORT replies_group
{
public:
    class create_interface
    {
    public:
        virtual ~create_interface() = default;

        virtual std::unique_ptr<reply> run() = 0;
    };

    class delete_interface
    {
    public:
        virtual ~delete_interface() = default;

        virtual void run() = 0;
    };

    class get_interface
    {
    public:
        virtual ~get_interface() = default;

        virtual get_interface& include_deleted(bool to_set) = 0;
        virtual std::unique_ptr<reply> run() = 0;
    };

    replies_group(drive& drv, const std::string& file_id, const std::string& comment_id);
    replies_group(const replies_group&) = delete;

    replies_group& operator= (const replies_group&) = delete;

    std::unique_ptr<create_interface> create(reply&& to_create, const std::string& fields);
    std::unique_ptr<delete_interface> del(const std::string& reply_id);
    std::unique_ptr<get_interface> get(const std::string& reply_id, const std::string& fields);

private:
    drive& drive_;
    std::string file_id_;
    std::string comment_id_;
};

}

#endif