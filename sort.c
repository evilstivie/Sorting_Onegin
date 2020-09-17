#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "sort.h"

/**
* \brief Comparator for sorting in +1 and -1 mode
*
* \param a first string
* \param b second string
* \param mode The way of sorting str
*/

int cmp(const void *a, const void *b, int mode) {
    const unsigned char *x = ((const str*)a)->line;
    const unsigned char *y = ((const str*)b)->line;

    const size_t nx = ((const str*)a)->len;
    const size_t ny = ((const str*)b)->len;

    int i = (mode == 1 ? 0 : nx - 1), j = (mode == 1 ? 0 : ny - 1);
    while (x[i] != '\0' && y[j] != '\0') {
        if (ispunct(x[i]) || isspace(x[i])) { // :NOTE: isspace()
            i += mode;
            continue;
        }
        if (ispunct(y[j] )|| isspace(y[j])) {
            j += mode;
            continue;
        }

        if (x[i] == y[j]) {
            i += mode;
            j += mode;
            continue;
        }

        return x[i] < y[j] ? -1 : 1;
    }

    if (i == nx && j == ny) {
        return 0;
    }
    return i == nx ? -1 : 1;
}

/**
* \brief Comparator for left to right sorting
*
* \param a first string
* \param b second string
*/

int cmp_lr(const void *a, const void *b) { // :NOTE: copypaste
    return cmp(a, b, 1);
}

/**
* \brief Comparator for right to left sorting
*
* \param a first string
* \param b second string
*/

int cmp_rl(const void *a, const void *b) {
    return cmp(a, b, -1);
}
