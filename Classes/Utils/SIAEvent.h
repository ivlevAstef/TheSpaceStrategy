//
//File: SIASIAEvent.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 21:21 16/7/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_EVENT_EVENT_H__
#define _SIA_EVENT_EVENT_H__

#include "SIADelegate.h"
#include <set>

namespace SIA
{
  template<class ...Args>
  class Event {
  public:
    Event() {
      m_iterator = m_delegates.end();
    }

    Event<Args...>& operator +=(const Delegate<Args...>& delegate) {
      m_delegates.insert(delegate);
      return *this;
    }
    Event<Args...>& operator -=(const Delegate<Args...>& delegate) {
      m_delegates.erase(delegate);
      return *this;
    }

    Event<Args...>& operator +=(std::set<Delegate<Args...>> delegates) {
      m_delegates.insert(std::begin(delegates), std::end(delegates));
      return *this;
    }

    void clean(void* id) {
      DIterator iter = m_delegates.begin();
      while (iter != m_delegates.end()) {
        if ((*iter).parentId() == (Delegate<Args...>::ParentID)id) {
          if (iter == m_iterator) {
            iter = m_delegates.erase(iter);
            m_iterator = iter;
          } else {
            iter = m_delegates.erase(iter);
          }
        } else {
          ++iter;
        }
      }
    }

  protected:
    typedef typename std::set<Delegate<Args...>>::const_iterator DIterator;
    std::set<Delegate<Args...>> m_delegates;
    DIterator m_iterator;
  };


  template<class ...Args>
  class PublicEvent: public Event<Args...> {
  public:
    void operator()(Args... argc) {
      m_iterator = m_delegates.begin();
      while (m_iterator != m_delegates.end()) {
        if ((*m_iterator)(argc...)) {
          return;
        }
        if (m_iterator != m_delegates.end()) {
          ++m_iterator;
        }
      }
    }
  };

  template<class Friend, class ...Args>
  class FriendEvent: public Event<Args...> {
  private:
    friend Friend;
    void operator()(Args... argc) {
      m_iterator = m_delegates.begin();
      while (m_iterator != m_delegates.end()) {
        if ((*m_iterator)(argc...)) {
          return;
        }
        if (m_iterator != m_delegates.end()) {
          ++m_iterator;
        }
      }
    }
  };
};

#endif // _SIA_EVENT_EVENT_H__
