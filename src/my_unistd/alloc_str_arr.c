#include <my_unistd.h>
#include <string.h>
#include <stdio.h>
void alloc_str_array(char** argv, my_getopt_t *getopt_ptr)
{
    int index = 1;
    int pos = 0;
    while (pos < getopt_ptr->nbr_str)
    {
        if (argv[index][0] != __DASH_CHAR__)
        {
            getopt_ptr->str_arr[pos] = (char*)malloc(sizeof(char) * (_my_strlen(argv[index]) + 1));
            pos += 1;
        }
        index += 1;
    }
}

void free_str_array( my_getopt_t *getopt_ptr)
{
    int index = 0;
    while (index < getopt_ptr->nbr_str)
    {
        free(getopt_ptr->str_arr[index]);
        index += 1;
    }
}