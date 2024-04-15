#ifndef __READLINE_HEADERFILE_
#define __READLINE_HEADERFILE_

#include <my_libasm.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int READLINE_READ_SIZE;
extern char* rl_buff;

/*
readline function following specifics specs. 

- one global variable for the size
- one global variable for the buffer;
    read a file line by line. 
    
    logic Readline:
    if '\n' in buffer:
    {
        extract 
        dup from buffer init pos to '\n'
        move init pos
        return new line
    }
    else
    {
        read to size and concat to buffer
    }
*/

#define SPACE_CHAR ' '
//readline.h
char*   my_readline(int fd);                        // main,
char*   init_my_readline();                         // main,
int     my_realloc_rl(int size);                    // readline,
int     seek_newline(int size);                     // readline
bool    is_newline(int size);                       // readline,
void    tmp_buff_reset();                           // readline,

#ifdef __cplusplus
}
#endif

#endif