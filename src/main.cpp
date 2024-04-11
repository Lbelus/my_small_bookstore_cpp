#include <main_header.hpp>

int main(int argc, char** argv)
{
    int             fd          = STDIN_FILENO;
    char*           str         = NULL;
    char**          tokens      = NULL;
    init_my_readline();
    while ((str = my_readline(fd)) != NULL)
    {
        MyGetOpt* GetOptObj = new MyGetOpt;
        tokens = my_strtok(str , 1, __SPACE_CHAR__);
        std::vector<std::string> vec = GetOptObj->convertToVector(tokens);
        GetOptObj->FlagParser(vec);
        execute_cmd(*GetOptObj);
        if (GetOptObj->getExit() == true)
        {
            fd = -1;
        }
        delete GetOptObj;
        free(tokens);
        free(str);
    }
    return EXIT_SUCCESS;
}