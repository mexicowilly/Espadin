#if !defined(ESPADIN_COMMENT_HPP__)
#define ESPADIN_COMMENT_HPP__

#include <espadin/reply.hpp>
#include <vector>

namespace espadin
{

class ESPADIN_EXPORT comment
{
public:
    class quoted_file_content
    {
    public:
        quoted_file_content() = default;
        quoted_file_content(const cJSON& json);

        const std::optional<std::string>& mime_type() const;
        void to_json(cJSON& json) const;
        const std::optional<std::string>& value() const;
        quoted_file_content& value(const std::string& str);

    private:
        std::optional<std::string> mime_type_;
        std::optional<std::string> value_;
    };

    comment() = default;
    comment(const cJSON& json);

    const std::optional<std::string>& anchor() const;
    comment& anchor(const std::string& str);
    const std::optional<user>& author() const;
    const std::optional<std::string>& content() const;
    comment& content(const std::string& str);
    const std::optional<std::chrono::system_clock::time_point>& created_time() const;
    const std::optional<bool>& deleted() const;
    const std::optional<quoted_file_content>& get_quoted_file_content() const;
    const std::optional<std::string>& html_content() const;
    const std::optional<std::string>& id() const;
    const std::optional<std::string>& kind() const;
    const std::optional<std::chrono::system_clock::time_point>& modified_time() const;
    const std::optional<std::vector<reply>>& replies() const;
    const std::optional<bool>& resolved() const;
    comment& set_quoted_file_content(quoted_file_content&& qfc);
    void to_json(cJSON& json) const;

private:
    std::optional<std::string> kind_;
    std::optional<std::string> id_;
    std::optional<std::chrono::system_clock::time_point> created_time_;
    std::optional<std::chrono::system_clock::time_point> modified_time_;
    std::optional<user> author_;
    std::optional<std::string> html_content_;
    std::optional<std::string> content_;
    std::optional<bool> deleted_;
    std::optional<bool> resolved_;
    std::optional<quoted_file_content> quoted_file_content_;
    std::optional<std::string> anchor_;
    std::optional<std::vector<reply>> replies_;
};

inline const std::optional<std::string>& comment::anchor() const
{
    return anchor_;
}

inline comment& comment::anchor(const std::string& str)
{
    anchor_ = str;
    return *this;
}

inline const std::optional<user>& comment::author() const
{
    return author_;
}

inline const std::optional<std::string>& comment::content() const
{
    return content_;
}

inline comment& comment::content(const std::string& str)
{
    content_ = str;
    return *this;
}

inline const std::optional<std::chrono::system_clock::time_point>& comment::created_time() const
{
    return created_time_;
}

inline const std::optional<bool>& comment::deleted() const
{
    return deleted_;
}

inline const std::optional<comment::quoted_file_content>& comment::get_quoted_file_content() const
{
    return quoted_file_content_;
}

inline const std::optional<std::string>& comment::html_content() const
{
    return html_content_;
}

inline const std::optional<std::string>& comment::id() const
{
    return id_;
}

inline const std::optional<std::string>& comment::kind() const
{
    return kind_;
}

inline const std::optional<std::chrono::system_clock::time_point>& comment::modified_time() const
{
    return modified_time_;
}

inline const std::optional<std::vector<reply>>& comment::replies() const
{
    return replies_;
}

inline const std::optional<bool>& comment::resolved() const
{
    return resolved_;
}

inline comment& comment::set_quoted_file_content(quoted_file_content&& qfc)
{
    quoted_file_content_ = std::move(qfc);
    return *this;
}

inline const std::optional<std::string>& comment::quoted_file_content::mime_type() const
{
    return mime_type_;
}

inline const std::optional<std::string>& comment::quoted_file_content::value() const
{
    return value_;
}

inline comment::quoted_file_content& comment::quoted_file_content::value(const std::string& str)
{
    value_ = str;
    return *this;
}

}

#endif