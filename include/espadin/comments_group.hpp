#if !defined(ESPADIN_COMMENTS_GROUP_HPP__)
#define ESPADIN_COMMENTS_GROUP_HPP__

#include <espadin/comment.hpp>
#include <memory>

namespace espadin
{

class ESPADIN_EXPORT comments_group
{
public:
    class create_interface
    {
    public:
        virtual ~create_interface() = default;

        virtual std::unique_ptr<comment> run() = 0;
        virtual create_interface& anchor(const std::string& str) = 0;
        virtual create_interface& quoted_file_content(const std::string& str) = 0;
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

        virtual std::unique_ptr<comment> run() = 0;
    };

    class list_interface
    {
    public:
        class reply
        {
        public:
            reply(const cJSON& json);

            const std::optional<std::vector<comment>>& comments() const;
            const std::optional<std::string>& kind() const;
            const std::optional<std::string>& next_page_token() const;

        private:
            std::optional<std::string> kind_;
            std::optional<std::string> next_page_token_;
            std::optional<std::vector<comment>> comments_;
        };

        virtual ~list_interface() = default;

        virtual list_interface& include_deleted(bool to_set) = 0;
        virtual list_interface& page_size(std::size_t num) = 0;
        virtual list_interface& page_token(const std::string& tok) = 0;
        virtual std::unique_ptr<reply> run() = 0;
        virtual list_interface& start_modified_time(const std::chrono::system_clock::time_point& when) = 0;
    };

    class update_interface
    {
    public:
        virtual ~update_interface() = default;

        virtual std::unique_ptr<comment> run() = 0;
    };

    virtual ~comments_group() = default;

    virtual std::unique_ptr<create_interface> create(const std::string& content,
                                                     const std::string& fields) = 0;
    virtual std::unique_ptr<delete_interface> del(const std::string& comment_id) = 0;
    virtual std::unique_ptr<get_interface> get(const std::string& comment_id,
                                               const std::string& fields) = 0;
    virtual std::unique_ptr<list_interface> list(const std::string& fields) = 0;
    virtual std::unique_ptr<update_interface> update(const std::string& comment_id,
                                                     const std::string& content,
                                                     const std::string& fields) = 0;
};

inline const std::optional<std::vector<comment>>& comments_group::list_interface::reply::comments() const
{
    return comments_;
}

inline const std::optional<std::string>& comments_group::list_interface::reply::kind() const
{
    return kind_;
}

inline const std::optional<std::string>& comments_group::list_interface::reply::next_page_token() const
{
    return next_page_token_;
}

}

#endif