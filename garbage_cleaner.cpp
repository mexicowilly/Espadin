#include "garbage_cleaner.hpp"

namespace espadin
{

garbage_cleaner::~garbage_cleaner()
{
    std::lock_guard<std::mutex> lg(guard_);
    while (!cleaners_.empty())
    {
        cleaners_.top()();
        cleaners_.pop();
    }
}

void garbage_cleaner::add(cleaner_type cln)
{
    std::lock_guard<std::mutex> lg(guard_);
    cleaners_.push(cln);
}

garbage_cleaner& garbage_cleaner::get()
{
    static std::once_flag once;
    // This gets cleaned by finalize
    static garbage_cleaner* gc;

    std::call_once(once, [&] () { gc = new garbage_cleaner(); });
    return *gc;
}

}
