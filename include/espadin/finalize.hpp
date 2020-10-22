#if !defined(ESPADIN_FINALIZE_HPP__)
#define ESPADIN_FINALIZE_HPP__

#include <espadin/export.hpp>

/**
 * @file 
 * Espadin's finalization functionality
 */

/**
 * The Espadin namespace
 */
namespace espadin
{

/**
 * Finalize the Espadin library. This function should be called
 * if you believe your memory leak analysis tools when they tell 
 * you that static objects that live the life of the application 
 * are memory leaks. You should also use this function if you 
 * are using Espadin as a shared object or within an enclosing
 * shared object. 
 *  
 * Included by @p <espadin/finalize.hpp>.
 *  
 * @note No Espadin APIs may be used after calling this function.
 *       The result is extremely undefined.
 * @ingroup miscellaneous
 */
ESPADIN_EXPORT void finalize();

}

#endif
