//
// Created by chen on 2020/9/10.
//

#ifndef SOMETHINGTEST_MACROS_H
#define SOMETHINGTEST_MACROS_H

#define ELEMS 100000000
#define N_PARTITIONS 16384

#define UNBUFFERED
#define UNBUFFERED_4KB_PAGE
#define UNBUFFERED_3MB_PAGE






constexpr unsigned int log2partitions() {
    return (31 - __builtin_clz(N_PARTITIONS)) * (N_PARTITIONS ? 1 : 0);
}
#define GET_BUCKET(VALUE, BITS) (VALUE >> BITS)
#endif //SOMETHINGTEST_MACROS_H
