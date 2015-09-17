#ifndef REF_H_INCLUDED
#define REF_H_INCLUDED

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 30, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes: I based this code off of code from CodeProject.com:
 *                  http://www.codeproject.com/Articles/15351/Implementing-a-simple-smart-pointer-in-c
 *
 */

namespace smartPointer
{
	template <typename T>
	class Ref
	{
		public:
			Ref(T* t) :
				ptr(t), rc(0)
			{
				rc++;
			}

			Ref(const Ref<T>& r)
			{
				ptr = r.ptr;
				rc = r.rc;

				rc++;
			}

			virtual ~Ref()
			{
				if (--rc == 0) {
					delete ptr;
				}
			}

			virtual T& operator*()
			{
				return *ptr;
			}

			virtual T* operator->()
			{
				return ptr;
			}

            virtual Ref<T>& operator=(Ref<T>& r)
			{
				if (&r != this) {

					if (--rc == 0) {
						delete ptr;
                    }

					ptr = r.ptr;
					rc = r.rc;

					rc++;
				}

				return *this;
			}

			virtual T* getInnerPointer()
			{
				return ptr;
			}

			virtual T getValue()
			{
				return *ptr;
			}

            virtual int getReferenceCount()
			{
				return rc;
			}

		protected:
			T* ptr;
			int rc;
	};

} /* namespace smartPointers */


#endif // REF_H_INCLUDED
