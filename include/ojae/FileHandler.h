#pragma once

#include <fstream>
#include <map>
#include <string>

#include "json.hpp"

static bool file_exists(const char* path)
{
    /*
    Checks if a file exists

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

    /*
    Offers functionality to dump json objects to files, and retrieve json objects from them
    */
    
private:

    std::fstream file_stream;

public:

    enum StreamType
    {
        DUMP,
        ADD,
    };

    FileHandler();
    ~FileHandler();

    void dump(nlohmann::json j_loader, const char* path, 
        StreamType stream_type);
    nlohmann::json get(const char* path);

};
