#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "sort.h"

/**
* \brief Print original text of poem
*
* \param outp file to output the text
* \param tx array of chars
*/

void print_original_text(FILE *outp, char *tx) {
	while (*tx) {
		fprintf(outp, "%c", *tx); // :NOTE: toooo slow
        ++tx;
		if (*tx == '\0') {
		    fprintf(outp, "\n");
			++tx;
		}
	}
}

int main(const int argC, const char** argV) {
	setlocale(LC_ALL, "ru_RU.CP1251");

	char *raw_text = procces_file();
	size_t cnt_lines = calc_lines(raw_text + 1);

	str *text = calloc(cnt_lines, sizeof(str));
	if (!text) {
		fprintf(stderr, "%s\n", "Memory allocation failed");
        exit(EXIT_FAILURE);
    }

	procces_raw_text(raw_text + 1, text);

	FILE *outp = fopen("output1.txt", "w");
	if (ferror(outp)) {
        fprintf(stderr, "%s\n", "Error while opening the file");
        exit(EXIT_FAILURE);
    }

	fprintf(outp,"%s \n", "------Left-Right Sorting------");

	qsort(text, cnt_lines, sizeof(str), cmp_lr);
	str_output(outp, text, cnt_lines);

	fprintf(outp,"%s\n", "------Right-Left Sorting------");

	qsort(text, cnt_lines, sizeof(text[0]), cmp_rl);
	str_output(outp, text, cnt_lines);

	fprintf(outp,"%s\n", "------Original Text------");

	print_original_text(outp, raw_text + 1);

	fclose(outp);

	free(raw_text);
    free(text);
}


/*
-> getFileSize -> getFile -> FileToString -> getLines(\n) ->
-> arrayOfStructs (pointer, str) -> cmp1 -> cmp2 -> qsort(cmp1) ->
-> output -> qsort(cmp2) -> output ->
*/
