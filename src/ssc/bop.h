/// @file bop.h
/// @brief Contains Utilities For Bitwise Operations
#pragma once
#include "stdint.h"
#include <immintrin.h>

#ifdef __cplusplus
namespace ssc{
#endif
    #ifdef __AVX512F__
        #define MAX_MEMXOR_SIZE 64ull
    #elif defined(__AVX2__)
        #define MAX_MEMXOR_SIZE 32ull
    #elif defined(__SSE2__)
        #define MAX_MEMXOR_SIZE 16ull
    #else
        #define MAX_MEMXOR_SIZE 8ull
    #endif
    /// @brief          Returns A Right Rotated 32-Bit Integer
    /// @param Base     Number To Rotate
    /// @param Rotation Amount To Rotate By
    /// @return         Rotated Number
    u32 ror32(u32 Base, u32 Rotation){
        return (Base >> Rotation) | (Base << (32u - Rotation));
    }
    /// @brief          Returns A Left Rotated 32-Bit Integer
    /// @param Base     Number To Rotate
    /// @param Rotation Amount To Rotate By
    /// @return         Rotated Number
    u32 rol32(u32 Base, u32 Rotation){
        return (Base << Rotation) | (Base >> (32u - Rotation));
    }
    /// @brief      Xor's Src To Dst For Size Bytes
    /// @param Dst  Pointer Of Data To Xor
    /// @param Src  Pointer Of Data Xoring
    /// @param Size Total Bytes To Xor
    void memxor(u8* const __restrict Dst, const u8* const __restrict Src, const u64 Size){
        for(u64 Index = 0ull; Index < Size;){
            u64 ChunkSize = Size - Index;    // Dont Let Overflow
            if(ChunkSize  > MAX_MEMXOR_SIZE) // Limit To SIMD Size
                ChunkSize = MAX_MEMXOR_SIZE;
        #ifdef __AVX512F__
            if(ChunkSize & MAX_MEMXOR_SIZE){
                *(__m512i*)(&Dst[Index]) = *(const __m512i*)(&Src[Index]);
                Index += ChunkSize;
                continue; // Can Skip Other If Statements
            }
        #endif
        #ifdef __AVX2__
            #ifdef __AVX512F__
                if(ChunkSize & 32ull){
                    *(__m256i*)(&Dst[Index]) = *(const __m256i*)(&Src[Index]);
                    Index += 32ull;
                    ChunkSize -= 32ull;
                }
            #else
                if(ChunkSize & MAX_MEMXOR_SIZE){
                    *(__m256i*)(&Dst[Index]) = *(const __m256i*)(&Src[Index]);
                    Index += ChunkSize;
                    continue; // Can Skip Other If Statements
                }
            #endif
        #endif
        #ifdef __SSE2__
            #if defined(__AVX512F__) || defined(__AVX2__)
                if(ChunkSize & 16ull){
                    *(__m128i*)(&Dst[Index]) = *(const __m128i*)(&Src[Index]);
                    Index += 16ull;
                    ChunkSize -= 16ull;
                }
            #else
                if(ChunkSize & MAX_MEMXOR_SIZE){
                    *(__m128i*)(&Dst[Index]) = *(const __m128i*)(&Src[Index]);
                    Index += ChunkSize;
                    continue; // Can Skip Other If Statements
                }
            #endif
        #endif
        #if MAX_MEMXOR_SIZE == 8ull
            if(ChunkSize & MAX_MEMXOR_SIZE){
                *(u64*)(&Dst[Index]) = *(const u64*)(&Src[Index]);
                Index += ChunkSize;
                continue; // Can Skip Other If Statements
            }
        #else
            if(ChunkSize & 8ull){
                *(u64*)(&Dst[Index]) = *(const u64*)(&Src[Index]);
                Index += 8ull;
                ChunkSize -= 8ull;
            }
        #endif
            if(ChunkSize & 4ull){
                *(u32*)(&Dst[Index]) = *(const u32*)(&Src[Index]);
                Index += 4ull;
                ChunkSize -= 4ull;
            }
            if(ChunkSize & 2ull){
                *(u16*)(&Dst[Index]) = *(const u16*)(&Src[Index]);
                Index += 2ull;
                ChunkSize -= 2ull;
            }
            if(ChunkSize){
                Dst[Index] = Src[Index];
                ++Index;
            }
        }
    }
#ifdef __cplusplus
} // namespace ssc
#endif