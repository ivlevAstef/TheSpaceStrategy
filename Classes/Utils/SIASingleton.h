//
//File: SIASingleton.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:21 16/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_SINGLETON_H__
#define _SIA_SINGLETON_H__

#include <assert.h>

namespace SIA
{
  template<typename Parent>
  class Singleton
  {
  public:
    Singleton() {
      assert(nullptr == ref());
      ref(static_cast<Parent*>(this), true);
    }

    static Parent& instance() {
      assert(nullptr != ref());
      return *ref();
    }

  protected:
    ~Singleton() {
      if (static_cast<Parent*>(this) == ref())
        ref(nullptr, true);
    }
  private:
    Singleton(const Singleton<Parent>&) {
      assert(true);
    }
    Singleton<Parent>& operator=(const Singleton<Parent>&) {
      assert(true);
      return *this;
    }

  private:
    static Parent* ref(Parent* pThis = nullptr, bool create = false) {
      static Parent* sSingleton = nullptr;
      if (create) {
        sSingleton = pThis;
      }
      return sSingleton;
    }
  };
};

#endif // _SIA_SINGLETON_H__
