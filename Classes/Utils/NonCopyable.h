//
//File: NonCopyable.h
//Description: 
//Author: Ivlev Alexander. Stef
//Created: 22:04 31/8/2015
//Copyright (c) SIA 2015. All Right Reserved.
//

#pragma once
#ifndef _SIA_NON_COPYABLE_H__
#define _SIA_NON_COPYABLE_H__

namespace SIA
{
  class NonCopyable {
  public:
    NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
  };
};

#endif //_SIA_NON_COPYABLE_H__