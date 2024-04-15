#ifndef _MY_CMD_FN_PTR_
#define _MY_CMD_FN_PTR_

#include <functional> 
#include <my_custom_error.hpp>

#define _ADD_ENTRY_     "ADD"
#define _REMOVE_ENTRY_  "RM"
#define _LIST_ENTRY_    "LIST"
#define _FIND_ENTRY_    "FIND"
#define _QUIT_          "QUIT"

#define _BD_ARG_        "bd"
#define _LIVRE_ARG_     "livre"
#define _AUTEUR_ARG_    "auteur"
#define _BOOKS_ARG_     "books"

class MyGetOpt;

#ifndef _CMD_PTR_S_
#define _CMD_PTR_S_
struct cmd_ptr_s
{
    const char* cmd;
    std::function<int(MyGetOpt&, std::shared_ptr<Library>)> func_ptr;
};
typedef struct cmd_ptr_s cmd_ptr_t;
#endif

int addEntry(MyGetOpt& GetOptObj, std::shared_ptr<Library> library);
int listEntry(MyGetOpt& GetOptObj,  std::shared_ptr<Library> library);
int findEntry(MyGetOpt& GetOptObj,  std::shared_ptr<Library> library);
int removeEntry(MyGetOpt& GetOptObj, std::shared_ptr<Library> library);

int quit(MyGetOpt& GetOptObj, std::shared_ptr<Library> library);
int execute_cmd(MyGetOpt& GetOptObj, std::shared_ptr<Library> library);

void createBd(std::shared_ptr<Library> library, const std::string& title, const std::string& author, const std::string& illustrator);
void createLivre(std::shared_ptr<Library> library, const std::string& title, const std::string& author, const std::string& pages);


#endif