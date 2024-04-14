#include <main_header.hpp>

cmd_ptr_t cmd_ptr_map[] = {
    {_ADD_ENTRY_, addEntry},
    {_LIST_ENTRY_, listEntry},
    {_FIND_ENTRY_, findEntry},
    {_REMOVE_ENTRY_, removeEntry},
    {_QUIT_, quit},
    {NULL, nullptr}
};

void checkArgCount(int nb_args, int expected)
{
    if (nb_args < expected)
    {
        throw ArgError("Missing argument");
    }
}

int addEntry(MyGetOpt& GetOptObj,  Library& library)
{
    char** args = GetOptObj.getArgs();
    const std::string cmd = args[1];
    if (cmd == _BD_ARG_)
    {
        checkArgCount(GetOptObj.getArgCount(), 5);
        createBd(library, args[2], args[3], args[4]);
    }
    else if (cmd == _LIVRE_ARG_)
    {
        checkArgCount(GetOptObj.getArgCount(), 5);
        createLivre(library, args[2], args[3], args[4]);
    }
    else if (cmd == _AUTEUR_ARG_)
    {
        checkArgCount(GetOptObj.getArgCount(), 3);
        library.addAuthor(args[2]);
    }
    return EXIT_SUCCESS;
}

//helper
void createBd(Library& library, const std::string& title, const std::string& author, const std::string& illustrator) // maybe use a struct next time.
{
    std::unique_ptr<BookCreator> creator;
    creator = std::make_unique<BandeDessineCreator>();
    std::unique_ptr<LibraryItem> item = creator->createBook(title, author, illustrator);
    library.addItem(std::move(item));
}

void createLivre(Library& library, const std::string& title, const std::string& author, const std::string& pages)
{
    int pages_int = std::stoi(pages);
    std::unique_ptr<BookCreator> creator;
    creator = std::make_unique<LivreCreator>();
    std::unique_ptr<LibraryItem> item = creator->createBook(title, author, "", pages_int);
    library.addItem(std::move(item));
}

int listEntry(MyGetOpt& GetOptObj,  Library& library)
{
    checkArgCount(GetOptObj.getArgCount(), 2);
    char** args = GetOptObj.getArgs();
    const std::string cmd = args[1];
    if (cmd == _BOOKS_ARG_)
    {
        library.displayItems();
    }
    else if (cmd == _AUTEUR_ARG_)
    {
        library.displayAuthors();
    }
    return EXIT_SUCCESS;
}

int findEntry(MyGetOpt& GetOptObj,  Library& library)
{
    char** args = GetOptObj.getArgs();
    const std::string cmd = args[1];
    if (cmd == _AUTEUR_ARG_)
    {
        library.findAuthorByBookTitle(args[2]);
    }
    else if (cmd == _BOOKS_ARG_)
    {
        library.findBooksByAuthor(args[2]);
    }
    return EXIT_SUCCESS;
}

int removeEntry(MyGetOpt& GetOptObj,  Library& library)
{
    char** args = GetOptObj.getArgs();
    checkArgCount(GetOptObj.getArgCount(), 2);
    const std::string cmd = args[1];
    if (cmd == _BD_ARG_|| cmd == _LIVRE_ARG_)
    {
        checkArgCount(GetOptObj.getArgCount(), 4);
        library.removeItem(args[2], args[3]);
    }
    else if (cmd == _AUTEUR_ARG_)
    {
        checkArgCount(GetOptObj.getArgCount(), 3);
        library.removeAuthor(args[2]);
    }
    return EXIT_SUCCESS;
}

int quit(MyGetOpt& GetOptObj,  Library& library)
{
    (void)library;
    GetOptObj.setExit();
    std::cout << "quit cmd: exiting program" << std::endl;
    return EXIT_SUCCESS;
}

int execute_cmd(MyGetOpt& GetOptObj,  Library& library)
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {    
        if (_my_strcmp(GetOptObj.getKeyword(), cf_ptr->cmd) == 0)
        {
            try
            {
                return cf_ptr->func_ptr(GetOptObj, library);
            }
            catch (const std::exception& error)
            {
                std::cerr << error.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
        cf_ptr++;
    }
    return EXIT_SUCCESS;
}