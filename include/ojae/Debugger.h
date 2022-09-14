#pragma once

#include <fstream>

class Debugger
{

private:

    std::fstream file_stream; // Instance of the fstream

    

    /**
     * @brief Dumps the passed string to a file
     * @param content Content to dump 
     * @param output_time Add the current time before the content
     * @param new_line Add a new line to the end of the content*/
    void dump(std::string content, bool output_time, bool new_line);

public:

    const char* path; // Path to logging file

    Debugger();
    Debugger(const char* _path);
    ~Debugger();

    /**
     * @brief Adds content to the logging file 
     * @param contents Content to add
     * @param output_time Add the current time before the content 
     * @param new_line Add a new line to the end of the 
     *  content (default = true) */
    void log(const char* content, bool output_time = true, 
        bool new_line = true);
    void log(char content, bool output_time = true, bool new_line = true);
    void log(std::string content, bool output_time = true, 
        bool new_line = true);
    void log(int content, bool output_time = true, bool new_line = true);
    void log(size_t content, bool output_time = true, bool new_line = true);

    /**
     * @brief Clears the logging file of all its contents */
    void clear();

    /**
     * @brief Checks if a file exists
     * 
     * @param path Directory of file
     * @return True if the file exists
     */
    bool file_exists(const char* path);

};