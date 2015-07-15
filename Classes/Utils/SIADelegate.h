//
//File: SIADelegate.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:21 16/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_EVENT_DELEGATE_H__
#define _SIA_EVENT_DELEGATE_H__

#include <set>
#include <functional>

namespace SIA
{
  template<class ...Args>
  class Delegate {
  public:
    typedef unsigned long long ParentID;
  private:
    std::function<bool(Args...)> m_execute;

  public:
    Delegate(void* id, std::function<void(Args...)> function, bool fResult = false) {
      m_parentId = (ParentID)id;
      m_execute = [function, fResult] (Args... argc) { function(argc...); return fResult; };
    }

    Delegate(void* id, std::function<bool(Args...)> function, void*) {
      m_parentId = (ParentID)id;
      m_execute = function;
    }

    bool operator <(const Delegate<Args...>& delegate) const {
      return this < &delegate;
    }

    bool operator()(Args... argc) const {
      return m_execute(argc...);
    }

    std::set<Delegate<Args...>> operator +(Delegate<Args...>& delegate) const {
      std::set<Delegate<Args...>> delegates;
      delegates.push_back(delegate);
      delegates.push_back(this);
      return delegates;
    }
    std::set<Delegate<Args...>> operator +(std::set<Delegate<Args...>>& delegates) const {
      delegates.push_back(this);
      return delegates;
    }

    inline const ParentID& parentId() const { return m_parentId; }

  private:
    ParentID m_parentId;
  };
};

#endif // _SIA_EVENT_DELEGATE_H__
