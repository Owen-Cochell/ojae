#pragma once

#include <fstream>
#include <map>



static bool file_exists(const char* path)
{
    /*
    Checks if a file exists in accordance to the passed path

    :PARAM path: Directory of file

    :RETURN: If the file exists
    */

    FILE *fp = fopen(path, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}


class FileHandler
{
    
}
