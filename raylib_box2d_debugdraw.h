#pragma once

#include <box2d/box2d.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Return a `b2DebugDraw` that draws using Raylib.
 */
b2DebugDraw b2RaylibDebugDraw();

#ifdef __cplusplus
}
#endif
