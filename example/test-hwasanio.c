//===-- test-hwasanio.c ---------------------------------------------===//
//
// Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is a part of HWASanIO.
//
// HWASanio Example Violation Detection.
//===----------------------------------------------------------------------===//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct double_buffer_t {
    char buf1[16];
    char buf2[16];
} double_buffer;

void test_intra_object_overflow() {
    double_buffer db = {
        .buf1 = { 0 },
        .buf2 = { 0 }
    };
    for (int i = 0; i < 20; i++) {
        db.buf1[i] = 'a';
    };
}

void test_in_bounds_load()
{
    int *ptr = malloc(20 * sizeof(int));
    ptr[10] = 42;
}

void test_out_of_bounds_load_fail()
{
    int *ptr = malloc(20 * sizeof(int));
    ptr[21] = 42;
}

void test_in_bounds_store()
{
    uint8_t *ptr = malloc(20 * sizeof(uint8_t));
    ptr[10] = 42;
}

void test_out_of_bounds_store_fail()
{
    uint8_t *ptr = malloc(20 * sizeof(uint8_t));
    ptr[21] = 42;
}

void test_use_after_free()
{
    uint8_t *ptr = malloc(12);
    free(ptr);
    ptr[0] = 5;
}

int main(int argc, char *argv[])
{
    int testcase;
    if (argc > 1)
    {
        testcase = argv[1][0] - '0';
    }
    else
    {
        printf("Specify testcase 0-5 \n");
        return 0;
    }
    switch (testcase)
    {
    case 0:
        printf("test_intra_object_overflow\n");
        test_intra_object_overflow();
        break;
    case 1:
        printf("test_in_bounds_load legal\n");
        test_in_bounds_load();
        break;
    case 2:
        printf("test_out_of_bounds_load illegal\n");
        test_out_of_bounds_load_fail();
        break;
    case 3:
        printf("test_in_bounds_store legal\n");
        test_in_bounds_store();
        break;
    case 4:
        printf("test_out_of_bounds_store illegal\n");
        test_out_of_bounds_store_fail();
        break;
    case 5:
        printf("test_use_after_free illegal\n");
        test_use_after_free();
        break;
    }
    return 0;
}
