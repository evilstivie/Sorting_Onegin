#ifndef FILE_H
#define FILE_H

/**
* \breif Struct to keep len and its string
*
* \param line Pointer on a string
* \param 
*/

typedef struct {
	char *line;
	size_t len;
} str;

size_t get_file_size(FILE *file);

void get_file(FILE *file, char *raw_text, size_t text_size);

void str_output(FILE *outp, str *text, int cnt);

size_t calc_lines(const char *inp);

void procces_raw_text(char *raw_text, str *text);

char* procces_file();

#endif // FILE_H
