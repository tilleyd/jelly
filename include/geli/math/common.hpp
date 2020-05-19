#ifndef _GELI_MATH_COMMON_HPP_
#define _GELI_MATH_COMMON_HPP_

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

#define MIN(x, y) (x < y ? x : y)

#define MAX(x, y) (x > y ? x : y)

#define CLAMP(x, min, max) (MIN(max, MAX(min, x)))

#define DEG_TO_RAD(deg) (deg * M_PI / 180.0)

#define RAD_TO_DEG(rad) (rad * 180.0 / M_PI)

#endif
