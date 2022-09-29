// #include <cstdio>

#include <dirent.h>
#include <string>
#include <vector>

struct Directory

{
    static std::vector<std::string> list_directories(const std::string& path) 
    {
        struct dirent *entry;
        DIR *dp;

        std::vector<std::string> dirs;

        dp = ::opendir(path.c_str());
        if (dp == NULL) {
            perror("opendir: Path does not exist or could not be read.");
            return dirs;
        }

        while ((entry = ::readdir(dp))) {
            // std::cout << entry->d_name << std::endl;
            dirs.push_back(std::string{entry->d_name});
        }

        ::closedir(dp);
        return dirs;
    }
};