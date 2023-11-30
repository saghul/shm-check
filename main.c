/*
 * Copyright (c) 2023 Saúl Ibarra Corretgé
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdint.h>
#include <stdio.h>
#include <sys/statvfs.h>


int main(int argc, char const *argv[])
{
    static const uint64_t two_gb = 2ULL << 30;

    struct statvfs st;

    int r = statvfs("/dev/shm", &st);
    if (r != 0) {
        perror("failed to open /dev/shm");
        return 1;
    }
    
    uint64_t total_bytes = (st.f_frsize ? st.f_frsize : st.f_bsize) * st.f_blocks;
    //printf("st.f_frsize: %d, st.f_bsize: %d, st.f_blocks: %d, total_bytes: %lld", st.f_frsize, st.f_bsize, st.f_blocks, total_bytes);
    if (total_bytes < two_gb)
        return 1;

    return 0;
}
