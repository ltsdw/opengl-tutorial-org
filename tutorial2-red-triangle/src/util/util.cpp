#include "util.hpp"

void removeExeFromAbsPath(char* path, char* buf)
{
    char* token = strtok(path, "/");
    char* tmp[200];
    size_t bnd = sizeof(tmp) - 1;
    int c = 0;

    while (token != NULL)
    {
        tmp[c] = token;
        token = strtok(NULL, "/");
        c++;
    }

    strncat(buf, "/", bnd);

    for (int i = 0; i <= c-2; i++)
    {
        strncat(buf, tmp[i], bnd);
        strncat(buf, "/", bnd);
    }
}

void absBinPath(char* buf_, const char* argv0)
{
    char buf[200];
    char tmp[200];
    size_t bnd = sizeof(tmp) - 1;

    if (argv0[0] == '/')
        strncpy(buf, argv0, bnd);
    else
    {
        if (!getcwd(tmp, bnd))
            return;

        strncat(tmp, "/", bnd);
        strncat(tmp, argv0, bnd);
    }

    if (!realpath(tmp, buf))
        return;

    removeExeFromAbsPath(tmp, buf_);
}
