#ifndef MY_CUSTOM_ERROR_HEADER_
#define MY_CUSTOM_ERROR_HEADER_

#include <exception>

class ArgError : public std::exception
{
    private:
        std::string message;

    public:
        ArgError(const char* msg) : message("Arg error: " + std::string(msg)) {}

        const char* what() const noexcept override
        {
            return message.c_str();
        }
};

#endif