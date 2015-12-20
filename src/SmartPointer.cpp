/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
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

#include "SmartPointer.hpp"

namespace pointer
{
    ReferenceCounter::ReferenceCounter()
    {
        refCount = 0;
    }

    int ReferenceCounter::getCount()
    {
        return refCount;
    }

    int ReferenceCounter::increment()
    {
        return ++refCount;
    }

    int ReferenceCounter::decrement()
    {
        return --refCount;
    }


    template <typename T>
    SP<T>::SP() :
        object(nullptr)
    {
        counter = new ReferenceCounter();
        counter->increment();
    }

    template <typename T>
    SP<T>::SP(T* t) :
        object(t)
    {
        counter = new ReferenceCounter();
        counter->increment();
    }

    template <typename T>
    SP<T>::~SP()
    {
        counter->decrement();
        if (counter->getCount() == 0) {
            delete object;
            delete counter;
        }
    }

    template <typename T>
    SP<T>::SP(SP<T> const& other)
    {
        object = other.object;
        counter = other.counter;
        counter->increment();
    }

    template <typename T>
    SP<T>& SP<T>::operator=(const SP<T>& rhs)
    {
        if (this == &rhs) return *this; // handle self assignment

        counter->decrement();
        if (counter->getCount() == 0) {
            delete object;
            delete counter;
        }

        object = rhs.object;
        counter = rhs.counter;

        counter->increment();

        return *this;
    }

    template <typename T>
    bool SP<T>::operator<(const SP<T>& other) const
    {
        // Order doesn't matter
        return true;
    }

    template <typename T>
    T& SP<T>::operator*()
    {
        return *object;
    }

    template <typename T>
    T* SP<T>::operator->()
    {
        return object;
    }

    template <typename T>
    SP<T>::operator bool() const
    {
        return object;
    }

}
