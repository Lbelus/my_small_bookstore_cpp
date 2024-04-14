#include <my_parser.h>

int find_ch(char* str, char ch)
{
    int index = 0;
    while (str[index] != ch && str[index] != '\0')
    {
        index += 1;
    }
    return index;
}

char change_delimiter(char first_ch, char ch)
{
    if (first_ch == '"' && ch != '"')
    {
        ch = '"';
        return ch;
    }
    return ch;
}

char** my_strtok(char* str, int* start_pos, char ch)
{
    char** tokens = (char**)malloc(sizeof(char*) * MAX_INPUT_TOKENS);
    char* start = str;
    char* end;
    int index = *start_pos;
    int pos = 0;
    while ((end = _my_strchr(start, ch)) != NULL)
    {
        pos = find_ch(start, ch);
        start[pos] = '\0';
        if (start[0] != '\0' && start[0] != __SPACE_CHAR__)
        {
            tokens[index] = start;
            index += 1;
            start = end + 1;
        }
        else
        {
            start = end + 1;
        }
        ch = change_delimiter(start[0], ch);
    }
    if (ch != '"')
    {
        tokens[index] = start;
        index += 1;
    }
    *start_pos = index;
    return tokens;
}