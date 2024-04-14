#include <main_header.hpp>

int main(int argc, char** argv)
{
    int    fd     = STDIN_FILENO;
    char*  str    = NULL;
    char** tokens = NULL;
    Library myLibrary;
    init_my_readline();
    std::cout << ">" << std::flush;
    while ((str = my_readline(fd)) != NULL)
    {
        int arg_count = 1;
        tokens = my_strtok(str , &arg_count, __SPACE_CHAR__);
        std::cout << "arg count is:" << arg_count << std::endl; 
        MyGetOpt* GetOptObj = new MyGetOpt(arg_count, tokens);
        execute_cmd(*GetOptObj, myLibrary);
        if (GetOptObj->getExit() == true)
        {
            fd = -1;
        }
        delete GetOptObj;
        free(tokens);
        free(str);
        std::cout << ">" << std::flush;
    }
    return EXIT_SUCCESS;
}