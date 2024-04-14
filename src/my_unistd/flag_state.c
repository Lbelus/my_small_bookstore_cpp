#include <my_unistd.h>
#include <string.h>

void flag_state(char opt, my_getopt_t *getopt_ptr, char** argv)
{
    switch (opt)
    {
    case 'h':
        getopt_ptr->bool_arr[0] = true;  
    break;
    case ':':
        strcpy(getopt_ptr->str_arr[getopt_ptr->str_pos], argv[getopt_ptr->index]); // _my_strcpy: asm is still causing some issues :/
        getopt_ptr->str_pos += 1;
        getopt_ptr->index += 1;
    break;
    }
    opt = 0;
}
