#if !defined(ESPADIN_REPLIES_GROUP_HPP_)
#define ESPADIN_REPLIES_GROUP_HPP_

#include <espadin/reply.hpp>
#include <memory>
#include <vector>

namespace espadin
{

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

    class list_interface
    {
    public:
        class reply
        {
        public:
            reply(const cJSON& json);

            const std::optional<std::string>& kind() const;
            const std::optional<std::string>& next_page_token() const;
            const std::optional<std::vector<espadin::reply>>& replies() const;

        private:
            std::optional<std::string> kind_;
            std::optional<std::string> next_page_token_;
            std::optional<std::vector<espadin::reply>> replies_;
        };

        virtual ~list_interface() = default;

        virtual list_interface& include_deleted(bool to_set) = 0;
        virtual list_interface& page_size(std::size_t num) = 0;
        virtual list_interface& page_token(const std::string& tok) = 0;
        virtual std::unique_ptr<reply> run() = 0;
    };

    class update_interface
    {
    public:
        virtual ~update_interface() = default;

        virtual std::unique_ptr<reply> run() = 0;
    };

    virtual ~replies_group() = default;

    virtual std::unique_ptr<create_interface> create(reply&& to_create, const std::string& fields) = 0;
    virtual std::unique_ptr<delete_interface> del(const std::string& reply_id) = 0;
    virtual std::unique_ptr<get_interface> get(const std::string& reply_id, const std::string& fields) = 0;
    virtual std::unique_ptr<list_interface> list(const std::string& fields) = 0;
    virtual std::unique_ptr<update_interface> update(const std::string& reply_id, const std::string& content, const std::string& fields) = 0;
};

inline const std::optional<std::string>& replies_group::list_interface::reply::kind() const
{
    return kind_;
}

inline const std::optional<std::string>& replies_group::list_interface::reply::next_page_token() const
{
    return next_page_token_;
}

inline const std::optional<std::vector<espadin::reply>>& replies_group::list_interface::reply::replies() const
{
    return replies_;
}

}

#endif