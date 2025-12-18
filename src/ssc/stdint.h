/// @file stdint.h
/// @brief Contains Typedef's For Readability
#pragma once

#ifdef __cplusplus
namespace ssc{
    using f64 =    double; using f32 =              float;
    using i64 = long long; using u64 = unsigned long long; using s64 = signed long long;
    using i32 =       int; using u32 = unsigned       int; using s32 = signed       int;
    using i16 =     short; using u16 = unsigned     short; using s16 = signed     short;
    using i8  =      char; using u8  = unsigned      char; using s8  = signed      char;
} // namespace ssc
#else
    typedef double    f64; typedef float              f32;
    typedef long long i64; typedef unsigned long long u64; typedef signed long long s64;
    typedef int       i32; typedef unsigned int       u32; typedef signed int       s32;
    typedef short     i16; typedef unsigned short     u16; typedef signed short     s16;
    typedef char       i8; typedef unsigned char       u8; typedef signed char       s8;
#endif