/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Dec 19, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

#include <memory>

namespace pointer
{
    template <typename T>
    using SP = std::shared_ptr<T>;

    template <typename T>
    using WP = std::weak_ptr<T>;
}

#endif // SMARTPOINTER_HPP
