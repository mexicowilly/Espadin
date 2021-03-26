#if !defined(ESPADIN_GARBAGE_CLEANER_HPP_)
#define ESPADIN_GARBAGE_CLEANER_HPP_

#include <functional>
#include <stack>
#include <mutex>

namespace espadin
{

class garbage_cleaner
{
public:
    using cleaner_type = std::function<void()>;

    static garbage_cleaner& get();

    virtual ~garbage_cleaner();

    void add(cleaner_type cln);

private:
    std::stack<cleaner_type> cleaners_;
    std::mutex guard_;
};

}

#endif
