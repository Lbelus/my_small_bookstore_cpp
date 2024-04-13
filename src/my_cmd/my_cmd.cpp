#include <main_header.hpp>

cmd_ptr_t cmd_ptr_map[] = {
    {_ADD_ENTRY_, addEntry},
    {_LIST_ENTRY_, listEntry},
    {_FIND_ENTRY_, findEntry},
    {_REMOVE_ENTRY_, removeEntry},
    {_QUIT_, quit},
    {NULL, nullptr}
};

int addEntry(MyGetOpt& GetOptObj,  Library& library)
{
    if (_my_strcmp(GetOptObj.getArgs()[1], "bd") == 0)
    {
        createBd(library, GetOptObj.getArgs()[2], GetOptObj.getArgs()[3], GetOptObj.getArgs()[4]);
    }
    else if (_my_strcmp(GetOptObj.getArgs()[1], "livre") == 0)
    {
        createLivre(library, GetOptObj.getArgs()[2], GetOptObj.getArgs()[3], GetOptObj.getArgs()[4]);
    }
    else if (_my_strcmp(GetOptObj.getArgs()[1], "auteur") == 0)
    {
        library.addAuthor(GetOptObj.getArgs()[2]);
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
    if (_my_strcmp(GetOptObj.getArgs()[1], "books") == 0)
    {
        library.displayItems();
    }
    else if (_my_strcmp(GetOptObj.getArgs()[1], "auteur") == 0)
    {
        library.displayAuthors();
    }
    return EXIT_SUCCESS;
}


int findEntry(MyGetOpt& GetOptObj,  Library& library)
{
    if (_my_strcmp(GetOptObj.getArgs()[1], "auteur") == 0)
    {
        library.findAuthorByBookTitle(GetOptObj.getArgs()[2]);
    }
    else if (_my_strcmp(GetOptObj.getArgs()[1], "books") == 0)
    {
        library.findBooksByAuthor(GetOptObj.getArgs()[2]);
    }
    return EXIT_SUCCESS;
}

int removeEntry(MyGetOpt& GetOptObj,  Library& library)
{
    if (_my_strcmp(GetOptObj.getArgs()[1], "bd") == 0 || _my_strcmp(GetOptObj.getArgs()[1], "livre") == 0)
    {
        library.removeItem(GetOptObj.getArgs()[2], GetOptObj.getArgs()[3]);
    }
    else if (_my_strcmp(GetOptObj.getArgs()[1], "auteur") == 0)
    {
        library.removeAuthor(GetOptObj.getArgs()[2]);
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