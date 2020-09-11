//
// Created by chen on 2020/9/10.
//

#include <stdlib.h>
#include "Types.h"
#include "Macros.h"
#include <sys/time.h>
#include <cstring>
#include <iostream>
#include "RadixPartitioning.h"
using namespace std;
double time_difference(struct timeval& first, struct timeval& second);
void radix_partition_without_buffers(Tuple *input, Tuple *output, Index *histogram) {
    struct timeval init, build, acc, final;

    gettimeofday(&init, NULL);

    constexpr UInt shift = 32 - log2partitions();
    __attribute__((aligned(64))) Index *final_buckets;

    posix_memalign((void**)&final_buckets, 64, N_PARTITIONS * sizeof(Index));
    memset(final_buckets, 0, N_PARTITIONS * sizeof(Index));

    for(Index j = 0; j < ELEMS; ++j){
        ++final_buckets[GET_BUCKET(input[j].value, shift)];
    }

    gettimeofday(&build, NULL);

    for(Index i = 1; i < N_PARTITIONS; ++i){
        final_buckets[i] += final_buckets[i - 1];
    }

    memcpy(histogram, final_buckets, N_PARTITIONS * sizeof(Index));

    gettimeofday(&acc, NULL);

    __attribute__((aligned(64))) Index bucket_num = 0;
    for(Index j = 0; j < ELEMS; ++j){
        bucket_num = GET_BUCKET(input[j].value, shift);
        output[final_buckets[bucket_num] - 1] = input[j];
        --final_buckets[bucket_num];
    }

    free(final_buckets);

    gettimeofday(&final, NULL);

    std::cout << time_difference(init, build) << std::endl << time_difference(build, acc) << std::endl << time_difference(acc, final) << std::endl;
}

