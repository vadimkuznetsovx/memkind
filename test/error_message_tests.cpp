/*
 * Copyright (C) 2014 - 2016 Intel Corporation.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice(s),
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice(s),
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
 * EVENT SHALL THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <memkind.h>
#include <errno.h>
#include <gtest/gtest.h>

/* Tests which calls APIS in wrong ways to generate Error Messages thrown by the
 * the memkind library
 */
class ErrorMessage: public :: testing :: Test
{
protected:
    int num_error_code;
    int *all_error_code;

    void SetUp()
    {
        num_error_code = 22;
        all_error_code = new int[num_error_code];
        all_error_code[0] = MEMKIND_ERROR_UNAVAILABLE;
        all_error_code[1] = MEMKIND_ERROR_MBIND;
        all_error_code[2] = MEMKIND_ERROR_MMAP;
        all_error_code[3] = MEMKIND_ERROR_MEMALIGN;
        all_error_code[4] = MEMKIND_ERROR_MALLCTL;
        all_error_code[5] = MEMKIND_ERROR_MALLOC;
        all_error_code[6] = MEMKIND_ERROR_GETCPU;
        all_error_code[7] = MEMKIND_ERROR_RUNTIME;
        all_error_code[8] = MEMKIND_ERROR_TIEDISTANCE;
        all_error_code[9] = MEMKIND_ERROR_ALIGNMENT;
        all_error_code[10] = MEMKIND_ERROR_MALLOCX;
        all_error_code[11] = MEMKIND_ERROR_ENVIRON;
        all_error_code[12] = MEMKIND_ERROR_INVALID;
        all_error_code[13] = MEMKIND_ERROR_REPNAME;
        all_error_code[14] = MEMKIND_ERROR_TOOMANY;
        all_error_code[15] = MEMKIND_ERROR_PTHREAD;
        all_error_code[16] = MEMKIND_ERROR_BADOPS;
        all_error_code[17] = MEMKIND_ERROR_HUGETLB;
        all_error_code[18] = MEMKIND_ERROR_BADPOLICY;
        all_error_code[19] = MEMKIND_ERROR_REPPOLICY;
        all_error_code[20] = EINVAL;
        all_error_code[21] = ENOMEM;
    }
    void TearDown()
    {
        delete[] all_error_code;
    }
};

TEST_F(ErrorMessage, test_TC_MEMKIND_ErrorMsgLength)
{
    int i;
    char error_message[MEMKIND_ERROR_MESSAGE_SIZE];
    for (i = 0; i < num_error_code; ++i) {
        memkind_error_message(all_error_code[i], error_message, MEMKIND_ERROR_MESSAGE_SIZE);
        EXPECT_TRUE(strlen(error_message) < MEMKIND_ERROR_MESSAGE_SIZE - 1);
    }
    memkind_error_message(MEMKIND_ERROR_UNAVAILABLE, NULL, 0);
}

TEST_F(ErrorMessage, test_TC_MEMKIND_ErrorMsgFormat)
{
    int i;
    char error_message[MEMKIND_ERROR_MESSAGE_SIZE];
    for (i = 0; i < num_error_code; ++i) {
        memkind_error_message(all_error_code[i], error_message, MEMKIND_ERROR_MESSAGE_SIZE);
        EXPECT_TRUE(strncmp(error_message, "<memkind>", strlen("<memkind>")) == 0);
    }
}

TEST_F(ErrorMessage, test_TC_MEMKIND_ErrorMsgUndefMesg)
{
    char error_message[MEMKIND_ERROR_MESSAGE_SIZE];
    memkind_error_message(-0xdeadbeef, error_message, MEMKIND_ERROR_MESSAGE_SIZE);
    EXPECT_TRUE(strncmp(error_message, "<memkind> Undefined error number:", strlen("<memkind> Undefined error number:")) == 0);
}

