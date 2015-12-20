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

namespace pointer
{

    class ReferenceCounter
    {
        public:
            ReferenceCounter();

            int getCount();

            int increment();
            int decrement();

        private:
            int refCount;
    };


    template <typename T>
    class SP
    {
        public:
            SP();
            SP(T* t);
            ~SP();

            SP(const SP& other);
            SP& operator=(const SP& rhs);

            // Implemented for maps (they need this operator to order the keys)
            bool operator<(const T& t) const;

            T& operator*();
            T* operator->();

            explicit operator bool();

            int getRefCount();

        private:
            T* object;

            ReferenceCounter* counter;
    };

}

#endif // SMARTPOINTER_HPP
