#include <main_header.hpp>
#include <my_tests.hpp>

int test_file(const char* filepath)
{
    int    fd     = open(filepath, O_RDONLY, 0644);
    if (fd == -1)
    {
        return EXIT_FAILURE;
    }
    char*  str    = NULL;
    char** tokens = NULL;
    std::shared_ptr<Library> myLibrary = std::make_shared<Library>();
    init_my_readline();
    std::cout << ">" << std::flush;
    while ((str = my_readline(fd)) != NULL)
    {
        int arg_count = 1;
        tokens = my_strtok(str , &arg_count, __SPACE_CHAR__);
        MyGetOpt* GetOptObj = new MyGetOpt(arg_count, tokens);
        execute_cmd(*GetOptObj, myLibrary);
        if (GetOptObj->getExit() == true)
        {
            close(fd);
            fd = -1;
        }
        delete GetOptObj;
        free(tokens);
        free(str);
        std::cout << ">" << std::flush;
    }
    return EXIT_SUCCESS;
}