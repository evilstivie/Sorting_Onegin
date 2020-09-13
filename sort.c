#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "file.h"
#include "sort.h"

int cmp_lr(const void *a, const void *b) {
	const char *x = ((const str*)a)->line;
    const char *y = ((const str*)b)->line;

    const size_t nx = ((const str*)a)->len;
    const size_t ny = ((const str*)b)->len;
    
    int i, j;
    for (i = 0, j = 0; i < nx && j < ny;) {
    	if (ispunct(x[i])) {
    		++i;
    		continue;		
    	}
    	if (ispunct(y[j])) {
    		++j;
    		continue;
    	}

    	if (x[i] == y[j]) {
    		++i; ++j;
    		continue;
    	}

    	return x[i] < y[j] ? -1 : 1; 
    }

    if (i == nx && j == ny) {
        return 0;
    }
    return i == nx ? -1 : 1;
}

int cmp_rl(const void *a, const void *b) {
	const char *x = ((const str*)a)->line;
    const char *y = ((const str*)b)->line;

    const size_t nx = ((const str*)a)->len;
    const size_t ny = ((const str*)b)->len;

    int i, j;
    for (i = nx - 1, j = ny - 1; i >= 0 && j >= 0;) {
    	if (ispunct(x[i]) || isspace(x[i])) {
    		--i;
    		continue;		
    	}
    	if (ispunct(y[j]) || isspace(y[j])) {
    	    --j;
    		continue;
    	}
    	if (x[i] < 0 && y[j] < 0) {

    		unsigned short ts1 = 
    		(((unsigned short)x[i - 1]) << 8u) | (unsigned char)x[i];
    		unsigned short ts2 = 
    		(((unsigned short)y[j - 1]) << 8u) | (unsigned char)y[j];
    		if (ts1 == ts2) {
    			i -= 2; j -= 2;
    			continue;
    		}
    		return (int)ts1 - ts2;
    	}
		
    	if (x[i] == y[j]) {
    		--i; --j;
    		continue;
    	}

    	return x[i] < y[j] ? -1 : 1; 
    }

    return i == -1 ? -1 : 1;
}