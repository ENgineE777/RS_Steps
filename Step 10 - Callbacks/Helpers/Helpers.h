
#pragma once

#define RADIAN  0.01745329f
#define PI      3.14159265f
#define TWO_PI  6.28318530f
#define HALF_PI 1.57079632f

#define rnd() ((float)rand()/RAND_MAX)
#define rnd_range(a, b) (a + (b - a) * (float)rand()/RAND_MAX)

#define RELEASE(p) if (p) { p->Release(); p = NULL; }

#include "Color.h"
#include "Vector2.h"
#include "Vector.h"
#include "Vector4.h"
#include "Matrix.h"
#include "Buffer.h"
#include "Delegate.h"
