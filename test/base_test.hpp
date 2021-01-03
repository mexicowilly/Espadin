#if !defined(ESPADIN_BASE_TEST_HPP__)
#define ESPADIN_BASE_TEST_HPP__

#include <espadin/drive.hpp>

namespace espadin::test
{

class base
{
protected:
    static std::string parent_id;

    base();

    std::string create_doc(const std::string& name);
    void trash(const std::string& file_id);

    drive drive_;
};

}

#endif
