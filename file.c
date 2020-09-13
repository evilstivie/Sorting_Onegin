#include <stdio.h>
#include <stdlib.h>

#include "file.h"


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
