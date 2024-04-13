#include <main_header.hpp>

cmd_ptr_t cmd_ptr_map[] = {
    {_ADD_ENTRY_, addEntry},
    {_LIST_ENTRY_, listEntry},
    {_FIND_ENTRY_, findEntry},
    {_REMOVE_ENTRY_, removeEntry},
    {_QUIT_, quit},
    {NULL, nullptr}
};

#define _BD_ARG_ "bd"
#define _LIVRE_ARG_ "livre"
#define _AUTEUR_ARG_ "auteur"
#define _BOOKS_ARG_ "books"

int addEntry(MyGetOpt& GetOptObj,  Library& library)
{
    char** args = GetOptObj.getArgs();
    const std::string cmd = args[1];
    if (cmd == _BD_ARG_)
    {
        createBd(library, args[2], args[3], args[4]);
    }
    else if (cmd == _LIVRE_ARG_)
    {
        createLivre(library, args[2], args[3], args[4]);
    }
    else if (cmd == _AUTEUR_ARG_)
    {
        library.addAuthor(args[2]);
    }
    return EXIT_SUCCESS;
}

//helper
void createBd(Library& library, const std::string& title, const std::string& author, const std::string& illustrator)
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
    const std::string cmd = args[1];
    if (cmd == _BD_ARG_|| cmd == _LIVRE_ARG_)
    {
        library.removeItem(args[2], args[3]);
    }
    else if (cmd == _AUTEUR_ARG_)
    {
        library.removeAuthor(args[2]);
    }
    return EXIT_SUCCESS;
}

int quit(MyGetOpt& GetOptObj,  Library& library)
{
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
            return cf_ptr->func_ptr(GetOptObj, library);
        }
        cf_ptr++;
    }
    return EXIT_SUCCESS;
}