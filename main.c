#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "sort.h"

#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

int main(const int argC, const char** argV) {
	FILE *file = fopen("onegin.txt", "r");

	size_t text_size = get_file_size(file);

	char *raw_text = calloc(text_size + 1, sizeof(char));
	raw_text[0] = '\0';
	++raw_text;

	get_file(file, raw_text, text_size); 
	// fread(raw_text, sizeof(raw_text[0]), text_size, file);

	fclose(file);

//

	int cnt_lines = calc_lines(raw_text);
	
	str *text = calloc(cnt_lines, sizeof(str));
	procces_raw_text(raw_text, text);

// 	
	FILE *outp;
	outp = fopen("output1.txt", "w");

	qsort(text, cnt_lines, sizeof(str), cmp_lr);
	str_output(outp, text, cnt_lines);

	qsort(text, cnt_lines, sizeof(text[0]), cmp_rl);
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
