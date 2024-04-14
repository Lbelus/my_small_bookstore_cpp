#ifndef __PARSER_HEADERFILE_
#define __PARSER_HEADERFILE_

#include <stdbool.h>
#include <stdlib.h>
#include <my_libasm.h>

#define __SPACE_CHAR__   ' '
#define MAX_INPUT_TOKENS 250

#ifdef __cplusplus
extern "C" {
#endif

char**  my_strtok(char* str, int* start_pos, char ch);
int     count_cmd(char* str, bool is_cli);

#ifdef __cplusplus
}
#endif

#endif