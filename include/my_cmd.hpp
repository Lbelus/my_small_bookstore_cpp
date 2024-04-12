#ifndef _MY_CMD_FN_PTR_
#define _MY_CMD_FN_PTR_

#include <functional> 

#define _ADD_ENTRY_ "ADD"
#define _PRINT_SECOND_ "PRINT_SECOND"
#define _QUIT_ "QUIT"

class MyGetOpt;

#ifndef _CMD_PTR_S_
#define _CMD_PTR_S_
struct cmd_ptr_s
{
    const char* cmd;
    std::function<int(MyGetOpt&, Library&)> func_ptr;
};
typedef struct cmd_ptr_s cmd_ptr_t;
#endif

int addEntry(MyGetOpt& GetOptObj, Library& library);
int print_second(MyGetOpt& GetOptObj, Library& library);
int quit(MyGetOpt& GetOptObj, Library& library);
int execute_cmd(MyGetOpt& GetOptObj, Library& library);

void createBd(Library& library, const std::string& title, const std::string& author, const std::string& illustrator);
void createLivre(Library& library, const std::string& title, const std::string& author, const std::string& pages);


#endif