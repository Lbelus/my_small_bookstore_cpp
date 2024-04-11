#ifndef __N_STD_HEADER_
#define __N_STD_HEADER_

#include <stddef.h>
#include <stdbool.h>

#define __SPACE_CHAR__          ' '

#ifdef __cplusplus
extern "C" {
#endif
int     my_ctoi(char *string, size_t n);
#ifdef __cplusplus
}
#endif
#endif