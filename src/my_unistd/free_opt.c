#include <my_unistd.h>

void free_opt(my_getopt_t* getopt_ptr)
{
    free_str_array(getopt_ptr);
    if (getopt_ptr->nbr_str > 0)
    {
        free(getopt_ptr->str_arr);
    }
    free(getopt_ptr->bool_arr);;
    free(getopt_ptr);
}