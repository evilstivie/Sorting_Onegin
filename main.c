#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

typedef struct {
	char *line;
	size_t len;
} str;

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

    return i == nx;
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

int calc_lines(const char *inp) {
	size_t cnt = 1;
	while (*inp) {
		cnt += (*(inp++) == '\n');
	}
	return cnt;
}

void procces_raw_text(char *raw_text, str *text) {
	int ind = 0;
	text[0].line = raw_text;
	text[0].len = 0;
	
	while (*raw_text) {
		if (*raw_text == '\n') {
			++ind;
			text[ind].line = raw_text + 1;
			text[ind].len = 0;

			*raw_text = '\0';
		} else {
			++text[ind].len;
		}

		++raw_text;
	}
}

int64_t get_file_size(FILE *file) {
	long cur_pos = ftell(file);
	fseek(file, 0, SEEK_END);
	long result = ftell(file);
	fseek(file, cur_pos, SEEK_SET);
	return result;
}

void get_file(FILE *file, char *raw_text, size_t text_size) {
	fread(raw_text, sizeof(raw_text[0]), text_size, file);
}

void str_output(FILE *outp, str *text, int cnt) {
	
	for (int i = 0; i < cnt; ++i, ++text) {
		fprintf(outp,"%s", (text->line));
	}
}

int main(const int argC, const char** argV) {
	FILE *file = fopen("onegin.txt", "r");

	size_t text_size = get_file_size(file);

	printf("%ld \n", text_size);

	char *raw_text = malloc(text_size + 1);
	raw_text[0] = '\0';
	++raw_text;

	// get_file(file, raw_text, text_size); 
	fread(raw_text, sizeof(raw_text[0]), text_size, file);
/*
	for (int i = 0; i < text_size; ++i) {
		if ('A' <= raw_text[i] && raw_text[i] <= 'z') {
			printf("%c", raw_text[i]);
		} else {
			printf("%d", (int)raw_text[i]);
		}
	}
	*/
	fclose(file);

//

	int cnt_lines = calc_lines(raw_text);
	
	str *text = calloc(cnt_lines, sizeof(str));
	procces_raw_text(raw_text, text);


// 	
	FILE *outp;
	outp = fopen("output1.txt", "w");

	// qsort(text, cnt_lines, sizeof(str), cmp_lr);

	// str_output(outp, text, cnt_lines);

	// str_output(outp, text, cnt_lines);

	qsort(text, cnt_lines, sizeof(text[0]), cmp_rl);
	/*fprintf(stderr, "%d\n", cnt_lines);*/

	str_output(outp, text, cnt_lines);
	// free_memory();


}


/*
-> getFileSize -> getFile -> FileToString -> getLines(\n) -> 
-> arrayOfStructs (pointer, str) -> cmp1 -> cmp2 -> qsort(cmp1) ->
-> output -> qsort(cmp2) -> output ->




ispunct 
ftell fseek -- File_Size
*/