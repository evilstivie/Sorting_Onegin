#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

/**
* \brief Calculate the number of lines on original text
*
* \param inp original text
*/

size_t calc_lines(const char *inp) {
	assert(inp);

	size_t cnt = 1; // Empty file has 1 line
	while (*inp) {
		cnt += (*(inp++) == '\n');
	}
	return cnt;
}

/**
* \brief Fill up the array of structures with {string, its length}
*
* Takes a string with lines and divides it on array of str 
*
* \param raw_text text to procces
* \param text text to fill
*/

void procces_raw_text(char *raw_text, str *text) {
	assert(raw_text);

	size_t ind = 0;
	text[0].line = raw_text; // set first element to the start of raw_text
	text[0].len = 0; // initialize the length
	
	while (*raw_text) {
		if (*raw_text == '\n') {
			++ind;
			text[ind].line = raw_text + 1; // skip '\n'
			text[ind].len = 0; // initialize the length

			*raw_text = '\0';
		} else {
			++text[ind].len;
		}

		++raw_text;
	}
}

/**
* \brief Get size of file in bytes
*/

size_t get_file_size(FILE *file) { //:OPT: fstat
	long cur_pos = ftell(file);
	fseek(file, 0, SEEK_END);
	long result = ftell(file);
	fseek(file, cur_pos, SEEK_SET);
	return result;
}

/**
* \brief Reads file's input
*/

void get_file(FILE *file, char *raw_text, size_t text_size) {
	fread(raw_text, sizeof(raw_text[0]), text_size, file);
	if (ferror(file)) {
		fprintf(stderr, "%s\n", "Error while reading the file");
        exit(EXIT_FAILURE);
	}
}

/**
* \brief Prints the result of sorting
*/

void str_output(FILE *outp, str *text, int cnt) {
	for (int i = 0; i < cnt; ++i, ++text) {
		fprintf(outp,"%s\n", (text->line));
	}
}

char* procces_file() {
	FILE *file = fopen("onegin.txt", "r"); // not binary mode for ignoring '\r'
	if (ferror(file)) {
        fprintf(stderr, "%s\n", "Error while opening the file");
        exit(EXIT_FAILURE);
    }

	size_t text_size = get_file_size(file);

	char *raw_text = calloc(text_size + 2, sizeof(raw_text[0])); // +2'/0' on top and end
	if (!raw_text) {
		fprintf(stderr, "%s\n", "Memory allocation failed");
        exit(EXIT_FAILURE);
	}

	raw_text[0] = '\0'; // '\0' on top

	get_file(file, raw_text + 1, text_size);
	fclose(file);

	return raw_text;
}
