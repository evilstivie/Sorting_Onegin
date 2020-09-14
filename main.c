#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "sort.h"

/**
* \brief Free allocated memory
*/

void free_memory(str *file, size_t lines, char *raw_text) {
    free(raw_text);
    free(file);    
}

/**
* \brief Print original text of poem
*
* \param outp file to output the text
* \param tx array of chars 
*/

void print_original_text(FILE *outp, char *tx) {
	while (*tx) {
		fprintf(outp, "%s\n", tx);
		while (*tx != '\0') {
			++tx;
		}
		++tx;
	}
}

int main(const int argC, const char** argV) {
	FILE *file = fopen("onegin.txt", "r");
	if (ferror(file)) {
        assert(!"Error while reading the file");
    }

	size_t text_size = get_file_size(file);

	char *raw_text = calloc(text_size + 2, sizeof(raw_text[0])); // +2'/0' on top and end
	if (!raw_text) {
		assert("Memory allocation failed");
	}

	raw_text[0] = '\0'; // '\0' on top
	++raw_text; // move pointer to the start of the text

	get_file(file, raw_text, text_size); 
	
	fclose(file);

	int cnt_lines = calc_lines(raw_text);
	
	str *text = calloc(cnt_lines, sizeof(str));
	if (!text) {
		assert("Memory allocation failed");
	}
	procces_raw_text(raw_text, text);

	FILE *outp = fopen("output1.txt", "w");
	if (ferror(outp)) {
        assert("Error while reading the file");
    }

	fprintf(outp,"%s", "------Left-Right Sorting------");

	qsort(text, cnt_lines, sizeof(str), cmp_lr);
	str_output(outp, text, cnt_lines);

	fprintf(outp,"%s", "------Right-Left Sorting------");

	qsort(text, cnt_lines, sizeof(text[0]), cmp_rl);
	str_output(outp, text, cnt_lines);

	fprintf(outp,"%s", "------Orgiginal Text------");

	print_original_text(outp, raw_text);

	fclose(outp);
	--raw_text;
	free_memory(text, cnt_lines, raw_text);
}


/*
-> getFileSize -> getFile -> FileToString -> getLines(\n) -> 
-> arrayOfStructs (pointer, str) -> cmp1 -> cmp2 -> qsort(cmp1) ->
-> output -> qsort(cmp2) -> output ->
*/
