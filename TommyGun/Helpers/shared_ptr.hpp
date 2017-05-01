//----------------------------------------------------------------------------------------------------
// shared_ptr.hpp
//
// kalin
// Copyright (c) 2005 Binary Storm
//----------------------------------------------------------------------------------------------------

#ifndef _SHARED_PTR_HPP_INCLUDE_GUARD
#define _SHARED_PTR_HPP_INCLUDE_GUARD

#include "ptr_exceptions.hpp"

#ifdef MSCVER
#pragma warning(push)
#pragma warning(disable:4355) // warning C4355: 'this' : used in base member initializer list
#endif


// Lacking:
//   * No support for Weak pointers.
//   * Need a binder and lambda for convenient CustomDeleter support.

// Notes:
//   Needs a rewrite/redesign to improve error locations when changing things.
//   Need to seperate ReferenceHolder/shared_ptr some more, and keep shared_ptr's
//   interface simple and ReferenceHolder can automatically handle the complex stuff.

// Tradeoffs:
//   Should we access the pointer through the shared_count at the expense of the forwarded call?
//   Will there even be an expense?
//   If there is, should we just store the pointer in the shared_ptr for faster access?
//     -- Pointer removed, it should incur no overhead calling the shared_count.ptr()

/*------------------------------------------------------------------------------------------------
// Synopsis.
//------------------------------------------------------------------------------------------------

template <class T>
class shared_ptr
{
public:
  typedef T*              pointer_type;
  typedef const T*        const_pointer_type;
  typedef T&              reference_type;
  typedef const T&        const_reference_type;
  typedef size_t          count_type;
  typedef shared_ptr<T>   self_type;

  shared_ptr();

  template <class Y> shared_ptr(Y* p);
  template <class Y> shared_ptr(shared_ptr<Y>& rhs);
  template <class Y> shared_ptr<T>& operator=(shared_ptr<Y>& rhs);
  
  count_type           count();
  pointer_type         get();
  const_pointer_type   get() const;

  pointer_type         operator->();
  const_pointer_type   operator->() const;

  reference_type       operator*();
  const_reference_type operator*() const;

  bool empty() const;
  bool operator !() const;
  operator bool() const;

  void reset(T* p = 0);
  void swap(self_type& rhs);
};

//------------------------------------------------------------------------------------------------
// Usage
//------------------------------------------------------------------------------------------------

struct Foo {};
struct CustomDeleter { void operator() (Foo* p) { delete p; } }

shared_ptr<Foo> p(new Foo);
shared_ptr<Foo> p(new Foo, CustomDeleter());

------------------------------------------------------------------------------------------------*/


#include <cassert>

namespace detail
{
  template <class T>
  class shared_count;
}

template <class T>
class shared_ptr
{
public:
  typedef T*              pointer_type;
  typedef const T*        const_pointer_type;
  typedef T&              reference_type;
  typedef const T&        const_reference_type;
  typedef size_t          count_type;
  typedef shared_ptr<T>   self_type;

  shared_ptr();

  template <class Y> explicit shared_ptr(Y* p);
  template <class Y> explicit shared_ptr(const shared_ptr<Y>& rhs);
  template <class Y> shared_ptr<T>& operator=(const shared_ptr<Y>& rhs);

  count_type           use_count() const;
  pointer_type         get();
  const_pointer_type   get() const;

  pointer_type         operator->();
  const_pointer_type   operator->() const;

  reference_type       operator*();
  const_reference_type operator*() const;

  bool expired() const;
  bool operator !() const;
  operator bool() const;

  void reset();
  template <class Y> void reset(Y* p);
  void swap(self_type& rhs);
  
private:
  template <class Y>
  self_type& operator=(Y* p);

  detail::shared_count<T> ref;
};

//----------------------------------------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------------------------------------

namespace detail
{
  template <class T>
  class shared_count
  {
    friend class shared_ptr<T>;

    shared_count()
      : ptr(0)
      , count(new size_t(1))
    { }

    shared_count(T* p)
      : ptr(p)
      , count(new size_t(1))
    { }

    shared_count(const shared_count& rhs)
      : ptr(rhs.ptr)
      , count(rhs.count)
    {
      ++*count;
    }

    ~shared_count()
    {
      if (--*count == 0)
      {
        delete ptr;
        delete count;
      }
    }

    T*      ptr;
    size_t* count;
  };
} 

//----------------------------------------------------------------------------------------------------
template <class T>
shared_ptr<T>::shared_ptr()
{ }

template <class T>
template <class Y>
shared_ptr<T>::shared_ptr(Y* p)
  : ref(p) 
{ }
  
template <class T>
template <class Y>
shared_ptr<T>::shared_ptr(const shared_ptr<Y>& rhs)
  : ref(rhs.ref)
{ }

template <class T>
template <class Y>
shared_ptr<T>& shared_ptr<T>::operator= (const shared_ptr<Y>& rhs)
{
  ref = rhs.ref;
  return *this;
}

template <class T>
typename shared_ptr<T>::count_type shared_ptr<T>::use_count() const
{
  return *ref.count;
}

template <class T>
typename shared_ptr<T>::pointer_type shared_ptr<T>::get()
{
  return ref.ptr;
}            

template <class T>
typename shared_ptr<T>::const_pointer_type shared_ptr<T>::get() const
{
  return ref.ptr;
}

template <class T>
typename shared_ptr<T>::pointer_type shared_ptr<T>::operator-> ()
{
  if (!ref.ptr) throw null_dereference(); return ref.ptr;
}

template <class T>
typename shared_ptr<T>::const_pointer_type shared_ptr<T>::operator-> () const
{
  if (!ref.ptr) throw null_dereference(); return ref.ptr;
}

template <class T>
typename shared_ptr<T>::reference_type shared_ptr<T>::operator* ()
{
  if (!ref.ptr) throw null_dereference(); return *ref.ptr;
}

template <class T>
typename shared_ptr<T>::const_reference_type shared_ptr<T>::operator* () const
{
  if (!ref.ptr) throw null_dereference(); return *ref.ptr;
}

template <class T>
bool shared_ptr<T>::expired() const
{
  return ref.ptr == 0;
}

template <class T>
bool shared_ptr<T>::operator! () const
{
  return expired();
}

template <class T>
shared_ptr<T>::operator bool () const
{
  return expired() == false;
}

template <class T>
void shared_ptr<T>::reset()
{
  shared_ptr<T>().swap(*this);
}

template <class T>
template <class Y>
void shared_ptr<T>::reset(Y* p)
{
  shared_ptr<T>(p).swap(*this);
}

template <class T>
void shared_ptr<T>::swap(shared_ptr<T>& rhs)
{
  shared_ptr<T> tmp(*this);
  *this = rhs;
  rhs = tmp;
}

#ifdef MSCVER
#pragma warning(pop)
#endif

#endif // _SHARED_PTR_HPP_INCLUDE_GUARD