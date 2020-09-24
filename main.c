#include <assert.h>
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

void print_original_text(FILE *outp, char *tx);

int main(const int argC, const char** argV) {
    setlocale(LC_ALL, "ru_RU.CP1251");

    char *raw_text = procces_file();
    size_t cnt_lines = calc_lines(raw_text + 1);

    str *text = procces_raw_text(raw_text + 1, cnt_lines);

    FILE *outp = fopen("output1.txt", "w");
    if (ferror(outp)) {
        assert(!"Error while reading the file");
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


void print_original_text(FILE *outp, char *tx) {
    while (*tx) {
        fputc(*tx, outp);
        ++tx;
        if (*tx == '\0') {
            fputc('\n', outp);
            ++tx;
        }
    }
}

/*
-> getFileSize -> getFile -> FileToString -> getLines(\n) ->
-> arrayOfStructs (pointer, str) -> cmp1 -> cmp2 -> qsort(cmp1) ->
-> output -> qsort(cmp2) -> output ->
*/
