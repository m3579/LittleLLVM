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

#include "SP.h"

namespace pointer
{
    ReferenceCounter()
    {
        refCount = 0;
    }

    int getCount()
    {
        return refCount;
    }

    int increment()
    {
        return ++refCount;
    }

    int decrement()
    {
        return --refCount;
    }


    SP::SP() :
        object(nullptr)
    {
        counter = new ReferenceCounter();
        counter.increment();
    }

    SP::SP(T* t) :
        object(t)
    {
        counter = new ReferenceCounter();
        counter.increment();
    }

    SP::~SP()
    {
        counter.decrement();
        if (counter.getCount() == 0) {
            delete object;
            delete counter;
        }
    }

    SP::SP(const SP& other)
    {
        object = other.object;
        counter = other.counter;
        counter.increment();
    }

    SP& SP::operator=(const SP& rhs)
    {
        if (this == &rhs) return *this; // handle self assignment

        counter.decrement();
        if (counter.getCount() == 0) {
            delete object;
            delete counter;
        }

        object = rhs.object;
        counter = rhs.counter;

        coutner.increment();

        return *this;
    }

    bool operator<(const T& t) const
    {
        // Order doesn't matter
        return true;
    }

    T& SP::operator*()
    {
        return *object;
    }

    T* SP::operator->()
    {
        return object;
    }

    explicit SP::operator bool()
    {
        return object;
    }

}
