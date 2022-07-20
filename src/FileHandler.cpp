#include <iostream>

#include "FileHandler.h"

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

void FileHandler::dump(nlohmann::json j_loader, const char* path,
    StreamType stream_type)
{
    /*
        Dumps the contents of a passed json object to a file. The behavior of 
        the stream, ie: std::ios::out or std::ios::app is determined by 
        stream_type. If stream_type is DUMP, the fstream will be set to 
        std::ios::out, and if it is ADD, it will be set to std::ios::app

        :PARAM j_loader: Json object that will be dumped to the file
        :PARAM path: Directory of target file
        :PARAM stream_type: Behavior of fstream output
    */
   
    if(!file_exists(path))
    {
        std::cout << "FileHandler.dump_contents: Could not open File -> " << path;
        exit(0);
    }

    switch(stream_type)
    {
        case StreamType::DUMP:
            file_stream.open(path, std::ios::out);
            break;

        case StreamType::ADD:
            file_stream.open(path, std::ios::app);
            break;
        
        default:
            std::cout << "FileHandler.dump_contents: Incorrect specification \
                of stream_type";
            exit(0);
    }

    if(file_stream.is_open())
    {
        file_stream << j_loader;
        file_stream.close();
    }

    file_stream.clear();
}

nlohmann::json FileHandler::get(const char* path)
{
    /*
    Retrieves the data from a json file and stores it in a json object.

    :PARAM path: Directory of target file

    :RETURN: Json object containing data from the json file
    */

    nlohmann::json j_loader;

    if(!file_exists(path))
    {
        std::cout << "FileHandler.get_contents: Could not open File -> " << path;
        exit(0);
    }

    file_stream.open(path, std::ios::in);

    if(file_stream.is_open())
    {
        file_stream >> j_loader;
        file_stream.close();
    }
    file_stream.clear();

    return j_loader;
}
