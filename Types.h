//
// Created by chen on 2020/9/10.
//

#ifndef SOMETHINGTEST_TYPES_H
#define SOMETHINGTEST_TYPES_H
#include <inttypes.h>
#include "Macros.h"

typedef uint32_t Index;

#ifdef WIDTH_64
typedef unsigned long UInt;
#define TUPLES_PER_CACHELINE 4
#define STREAM_UNIT 2
#else
typedef unsigned int UInt;
#define TUPLES_PER_CACHELINE 8
#define STREAM_UNIT 4
#endif


struct Tuple{
    UInt value;
    UInt rowId;
};
constexpr UInt shift_distance() {
#ifdef WIDTH_64
    return (64 - log2partitions());
#else
    return (32 - log2partitions());
#endif
}
#endif //SOMETHINGTEST_TYPES_H