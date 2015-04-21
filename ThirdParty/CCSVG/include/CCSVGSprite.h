#pragma once
#ifndef __COCOS_2D_CCSVG_SPRITE_H__
#define __COCOS_2D_CCSVG_SPRITE_H__

#include "cocos2d.h"


@class CCSVGSource;


@interface CCSVGSprite : CCNode <CCBlendProtocol>


#pragma mark

@property (readwrite, retain) CCSVGSource *source;


#pragma mark

+ (id)spriteWithFile:(NSString *)file;

+ (id)spriteWithSource:(CCSVGSource *)source;

- (id)initWithFile:(NSString *)file;

- (id)initWithSource:(CCSVGSource *)source;


@end

#endif