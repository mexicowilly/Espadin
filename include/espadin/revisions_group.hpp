#if !defined(ESPADIN_REVISIONS_GROUP_HPP_)
#define ESPADIN_REVISIONS_GROUP_HPP_

#include <espadin/revision.hpp>
#include <vector>
#include <memory>

namespace espadin
{

class ESPADIN_EXPORT revisions_group
{
public:
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

        virtual get_interface& acknowledge_abuse(bool to_set) = 0;
        virtual get_interface& fields(const std::string& str) = 0;
        virtual std::unique_ptr<revision> run() = 0;
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
            const std::optional<std::vector<revision>>& revisions() const;

        private:
            std::optional<std::string> kind_;
            std::optional<std::string> next_page_token_;
            std::optional<std::vector<revision>> revisions_;
        };

        virtual ~list_interface() = default;

        virtual list_interface& fields(const std::string& str) = 0;
        virtual list_interface& page_size(std::size_t count) = 0;
        virtual list_interface& page_token(const std::string& str) = 0;
        virtual std::unique_ptr<reply> run() = 0;
    };

    class update_interface
    {
    public:
        virtual ~update_interface() = default;

        virtual update_interface& fields(const std::string& str) = 0;
        virtual std::unique_ptr<revision> run() = 0;
    };

    virtual ~revisions_group() = default;

    virtual std::unique_ptr<delete_interface> del(const std::string& revision_id) = 0;
    virtual std::unique_ptr<get_interface> get(const std::string& revision_id) = 0;
    virtual std::unique_ptr<list_interface> list() = 0;
    virtual std::unique_ptr<update_interface> update(const std::string& revision_id, revision&& to_update) = 0;
};

inline const std::optional<std::string>& revisions_group::list_interface::reply::kind() const
{
    return kind_;
}

inline const std::optional<std::string>& revisions_group::list_interface::reply::next_page_token() const
{
    return next_page_token_;
}

inline const std::optional<std::vector<revision>>& revisions_group::list_interface::reply::revisions() const
{
    return revisions_;
}

}

#endif