#pragma once
#ifndef __COCOS_2D_SVG_DEFINES_H__
#define __COCOS_2D_SVG_DEFINES_H__

#if !defined(_USRSVGDLL)
#   pragma comment(lib, "CCSVG.lib")
#endif

#if defined(_USRSVGDLL)
  #define CC_SVG_DLL     __declspec(dllexport)
#else         /* use a DLL library */
  #define CC_SVG_DLL     __declspec(dllimport)
#endif

#endif