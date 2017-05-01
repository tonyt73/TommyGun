//----------------------------------------------------------------------------------------------------
// smart_ptr.hpp
//
// kalin
// Copyright (c) 2005 Binary Storm
//----------------------------------------------------------------------------------------------------

#ifndef _SMART_PTR_HPP_INCLUDE_GUARD
#define _SMART_PTR_HPP_INCLUDE_GUARD

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
//   Need to seperate ReferenceHolder/smart_ptr some more, and keep smart_ptr's
//   interface simple and ReferenceHolder can automatically handle the complex stuff.

// Todo:
//   weak_ptr

/*------------------------------------------------------------------------------------------------
// Synopsis.
//------------------------------------------------------------------------------------------------

template <class T>
class smart_ptr
{
public:
  typedef T*              pointer_type;
  typedef const T*        const_pointer_type;
  typedef T&              reference_type;
  typedef const T&        const_reference_type;
  typedef size_t          count_type;
  typedef smart_ptr<T>    self_type;

  smart_ptr();

  template <class Y> smart_ptr(Y* p);
  template <class Y> smart_ptr(smart_ptr<Y>& rhs);
  template <class Y> smart_ptr<T>& operator=(smart_ptr<Y>& rhs);
  
  template <class Y, class D>  smart_ptr(Y* p, D d = detail::default_deleter());

  count_type           use_count();
  pointer_type         get();
  const_pointer_type   get() const;

  pointer_type         operator->();
  const_pointer_type   operator->() const;

  reference_type       operator*();
  const_reference_type operator*() const;

  bool expired() const;
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

smart_ptr<Foo> p(new Foo);
smart_ptr<Foo> p(new Foo, CustomDeleter());

------------------------------------------------------------------------------------------------*/

// TODO: Remove ptr from smart_ptr, and move it into ref, and handle everything there.

#include <cassert>

namespace detail
{
  template <class T>
  class reference_holder;

  struct default_deleter
  {
    template <class T>
    void operator()(T* p) 
    {
      delete p;
    }
  };
}

template <class T>
class smart_ptr
{
public:
  typedef T*              pointer_type;
  typedef const T*        const_pointer_type;
  typedef T&              reference_type;
  typedef const T&        const_reference_type;
  typedef size_t          count_type;
  typedef smart_ptr<T>    self_type;

  smart_ptr();

  template <class Y> smart_ptr(Y* p);
  template <class Y> smart_ptr(smart_ptr<Y>& rhs);
  template <class Y> smart_ptr<T>& operator=(smart_ptr<Y>& rhs);
  
  template <class Y, class D> smart_ptr(Y* p, D d = detail::default_deleter());

  count_type           use_count();
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

  template <class Y>
  void reset(Y* p);
  
  template <class Y, class D>
  void reset(Y* p, D deleter);

  void swap(self_type& rhs);
  
private:
  template <class Y>
  self_type& operator=(Y* p);

  friend class detail::reference_holder;

  // It is important for ref to be before ptr,
  // because we need to perform ref copying prior to ptr copying.
  detail::reference_holder<T> ref;
  T* ptr;
};


namespace detail 
{
  template <class T>
  class reference_base
  {
  public:
    virtual void operator()(T* p) = 0;
  };

  template <class T, class D>
  class reference_concrete
    : public reference_base<T>
  {  
  public:
    explicit reference_concrete(T* p, D d)
      : ptr(p)
      , del(d)
    { }

  public:
    virtual void operator()(T* p)
    {
      del(p);    
    }

    T* ptr;
    D  del;
  };

  template <class T, class D>
  reference_base<T>* make_reference_base(T* p, D d)
  {
    return new reference_concrete<T, D>(p, d);
  }

  template <class T>
  class reference_holder
  {
    typedef smart_ptr<T> smart_pointer_type;
    typedef reference_holder<T> self_type;

    friend class smart_ptr<T>;

    explicit reference_holder(smart_pointer_type& sp)
      : owner(&sp)
      , count(new size_t(1))
      , base(sp.ref.base)
    {
    }

    explicit reference_holder(smart_pointer_type& sp, reference_base<T>* b)
      : owner(&sp)
      , count(new size_t(1))
      , base(b)
    { }

  public:
    ~reference_holder()
    {
      if (--*count == 0)
      {
        delete count;
        base->operator()(owner->ptr);
        delete base;
        //delete owner->ptr;
      }
    }

  private:

    reference_holder(const self_type& rhs)
      : owner(rhs.owner)
      , count(rhs.count)
      , base(rhs.base)
    {
      ++*count;
    }

    self_type& operator=(const self_type& rhs)
    { 
      if (--*count == 0)
      {
        delete count;
        base->operator()(owner->ptr);
        delete base;
      }

      owner = rhs.owner;
      count = rhs.count;
      base  = rhs.base;
      ++*count;
      return *this; 
    }

  private:
    smart_pointer_type* owner;
    size_t* count;
    reference_base<T>* base;
  };

} // namespace detail

//----------------------------------------------------------------------------------------------------
// Implementation.
//----------------------------------------------------------------------------------------------------

template <class T>
smart_ptr<T>::smart_ptr()
  : ref(*this, detail::make_reference_base<T, detail::default_deleter>( reinterpret_cast<T*>(0), detail::default_deleter()))
  , ptr(0)
{
}

template <class T>
template <class Y>
smart_ptr<T>::smart_ptr(Y* p)
  : ref(*this, detail::make_reference_base<T, detail::default_deleter>(p, detail::default_deleter()))
  , ptr(p)
{
}
                                                                                                  
template <class T>
template <class Y, class D>
smart_ptr<T>::smart_ptr(Y* p, D d)
  : ref(*this, detail::make_reference_base<T, D>(p, d))
  , ptr(p)
{
}

template <class T>
template <class Y>
smart_ptr<T>::smart_ptr<T>(smart_ptr<Y>& rhs)
  : ref(rhs.ref)
  , ptr(rhs.ptr)
{
}

template <class T>
template <class Y>
smart_ptr<T>& smart_ptr<T>::operator=(Y* p)
{
  // TODO: This function should not be accessible.
  assert(!"Shouldn't be possible to call this function. (smart_ptr<T>::operator=(Y*))");
}

template <class T>
template <class Y>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr<Y>& rhs)
{
  // Note that we swap the reference first, since it may delete this->ptr.
  ref = rhs.ref;
  ptr = rhs.ptr;
  return *this;
}

template <class T>
typename smart_ptr<T>::count_type smart_ptr<T>::use_count()
{
  return *ref.count;
}

template <class T>
typename smart_ptr<T>::pointer_type smart_ptr<T>::get()
{
  return ptr;
}

template <class T>
typename smart_ptr<T>::const_pointer_type smart_ptr<T>::get() const
{
  return ptr;
}

template <class T>
typename smart_ptr<T>::pointer_type smart_ptr<T>::operator->()
{
  return ptr;
}
  
template <class T>
typename smart_ptr<T>::const_pointer_type smart_ptr<T>::operator->() const
{
  return ptr;
}

template <class T>
typename smart_ptr<T>::reference_type smart_ptr<T>::operator*()
{
  return *ptr;
}
  
template <class T>
typename smart_ptr<T>::const_reference_type smart_ptr<T>::operator*() const
{
  return *ptr;
}

template <class T>
bool smart_ptr<T>::expired() const
{
  return ptr == 0;
}

template <class T>
bool smart_ptr<T>::operator!() const
{
  return expired();
}

template <class T>
smart_ptr<T>::operator bool() const
{
  return expired() == false;
}

template <class T>
void smart_ptr<T>::reset()
{
  ref = detail::reference_holder<T>(*this, detail::make_reference_base<T, detail::default_deleter>(0, detail::default_deleter()));
  ptr = 0;
}


template <class T>
template <class Y>
void smart_ptr<T>::reset(Y* p)
{
  ref = detail::reference_holder<T>(*this, detail::make_reference_base<T, detail::default_deleter>(p, detail::default_deleter()));
  ptr = p;
}

template <class T>
template <class Y, class D>
void smart_ptr<T>::reset(Y* p, D deleter)
{
  ref = detail::reference_holder<T>(*this, detail::make_reference_base<T, D>(p, deleter));
  ptr = p;
}

template <class T>
void smart_ptr<T>::swap(self_type& rhs)
{
  smart_ptr<T> tmp(rhs);
  rhs = *this;
  *this = tmp;
}

#ifdef MSCVER
#pragma warning(pop)
#endif

#endif // _SMART_PTR_HPP_INCLUDE_GUARD