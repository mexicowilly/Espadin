#include <espadin/finalize.hpp>
#include "garbage_cleaner.hpp"

namespace espadin
{

void finalize()
{
    delete &garbage_cleaner::get();
}

}
