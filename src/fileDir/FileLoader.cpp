#include "files.h"
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <memory>

using namespace std;

vector <shared_ptr<FileClass>> FileLoader::loadDirectory(string path) {

    DIR *pDIR;
    struct dirent *entry;
    vector <shared_ptr<FileClass>> files;
    pDIR = opendir(path.c_str());
    if (pDIR != nullptr) {
        while ((entry = readdir(pDIR))) {
            struct stat s;
            string fileName = string(entry->d_name);
            string currentFilePath = path + "/" + fileName;
            if (lstat(currentFilePath.c_str(), &s) == 0) {
                shared_ptr <FileClass> dummy;
                string untrimmedTime = ctime(&s.st_ctime);
								size_t last = untrimmedTime.find_last_not_of("\t\n\v\f\r ");
    						string timeDetail = untrimmedTime.substr(0, (last + 1));
                switch (s.st_mode & S_IFMT) {

                    // directory
                    case S_IFDIR: {
                        char absolutePath[PATH_MAX + 1];
                        realpath(currentFilePath.c_str(), absolutePath);
                        Directory dir(fileName, false, timeDetail, string(absolutePath));
                        dummy = make_shared<Directory>(dir);
                        break;
                    }
                        // link
                    case S_IFLNK: {
                        char absolutePath[PATH_MAX + 1];
                        readlink(currentFilePath.c_str(), absolutePath, sizeof(absolutePath));
                        Link link(fileName, false, timeDetail, string(absolutePath));
                        dummy = make_shared<Link>(link);
                        break;
                    }
                        // everything else is treated as regular file
                    default: {
                        RegularFile regFile(fileName, false, timeDetail);
                        dummy = make_shared<RegularFile>(regFile);
                        break;
                    }
                }
                files.push_back(dummy);
            }
        }
        closedir(pDIR);
    }
    return files;
}
