#if !defined(ESPADIN_COMMENTS_GROUP_HPP__)
#define ESPADIN_COMMENTS_GROUP_HPP__

#include <espadin/comment.hpp>
#include <memory>

namespace espadin
{

class drive;

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

    comments_group(drive& drv);
    comments_group(const comments_group&) = delete;

    comments_group& operator= (const comments_group&) = delete;

    std::unique_ptr<create_interface> create(const std::string& file_id,
                                             const std::string& content,
                                             const std::string& fields);
    std::unique_ptr<delete_interface> del(const std::string& file_id, const std::string& comment_id);
    std::unique_ptr<get_interface> get(const std::string& file_id,
                                       const std::string& comment_id,
                                       const std::string& fields);

private:
    drive& drive_;
};

}

#endif