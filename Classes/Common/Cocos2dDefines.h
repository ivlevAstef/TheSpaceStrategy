/*Author: Ivlev Alexander (stef).*/
#pragma once
#ifndef _SIA_THE_SPACE_STRATEGY_COCOS2D_DEFINES_H__
#define _SIA_THE_SPACE_STRATEGY_COCOS2D_DEFINES_H__

#define CSIA_FUNC_ALLOC(TYPE) TYPE *pRet = new(std::nothrow) TYPE()
#define CSIA_FUNC_INIT if (pRet && pRet->init
#define CSIA_FUNC_END ) { \
  pRet->autorelease(); \
  return pRet; \
  } else { \
    delete pRet; \
    return NULL; \
  }

#define COCOS2D_FUNC(TYPE) \
static TYPE* create() { \
  CSIA_FUNC_ALLOC(TYPE); \
  CSIA_FUNC_INIT() CSIA_FUNC_END \
}

#define COCOS2D_FUNC1(TYPE, P1) \
static TYPE* create(P1 param1) { \
  CSIA_FUNC_ALLOC(TYPE); \
  CSIA_FUNC_INIT(param1) CSIA_FUNC_END \
}

#define COCOS2D_FUNC2(TYPE, P1, P2) \
static TYPE* create(P1 param1, P2 param2) { \
  CSIA_FUNC_ALLOC(TYPE); \
  CSIA_FUNC_INIT(param1, param2) CSIA_FUNC_END \
}

#define COCOS2D_FUNC3(TYPE, P1, P2, P3) \
static TYPE* create(P1 param1, P2 param2, P3 param3) { \
  CSIA_FUNC_ALLOC(TYPE); \
  CSIA_FUNC_INIT(param1, param2, param3) CSIA_FUNC_END \
}

#endif _SIA_THE_SPACE_STRATEGY_COCOS2D_DEFINES_H__