#include "Link.cpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <memory>

using namespace std;

Directory::Directory(string fileName, bool isActive, string creationTime, string path) : FileClass(fileName, isActive,
                                                                                                   creationTime) {
    _path = path;
}

string Directory::toString() {
    return FileClass::toString('D');
}

string Directory::getPath() {
    return _path;
}

string Directory::deleteFile(string path) {
    string errorMessage = "";
    vector <shared_ptr<FileClass>> filesToDelete = FileLoader::loadDirectory(path);
    if (filesToDelete.empty()) {
        errorMessage = "Error deleting directory";
    } else {
        for (auto it = filesToDelete.begin(); it != filesToDelete.end(); ++it) {
            string fileName = (*it)->getFileName();
            if (fileName == "." || fileName == "..") {
                continue;
            }
            errorMessage = (*it)->deleteFile(path + "/" + fileName);
        }
        int result = rmdir(path.c_str());
        if (result != 0) {
            errorMessage = "Error deleting directory";
        }
    }
    return errorMessage;
}

string Directory::copy(string path, string destination) {
    string errorMessage = "";
    int result = mkdir(destination.c_str(), 0777);
    if (result != 0) {
        errorMessage = "Could not create directory";
    } else {
        vector <shared_ptr<FileClass>> filesToCopy = FileLoader::loadDirectory(path);
        if (filesToCopy.empty()) {
            errorMessage = "Error copying directory";
        } else {
            for (auto it = filesToDelete.begin(); it != filesToCopy.end(); ++it) {
                string fileName = (*it)->getFileName();
                if (fileName == "." || fileName == "..") {
                    continue;
                }
                errorMessage = (*it)->copy(_copy, path + "/" + fileName);
            }
        }
    }
    return errorMessage;
}

string Directory::moveFile(string path, string destination) {
    string errorMessage = copy(path, destination);
    if (errorMessage != "") {
        return errorMessage;
    }
    errorMessage = deleteFile(path);
    return errorMessage;
}

string Directory::createFile(string path) {
    int result = mkdir(path.c_str(), 0777);
    if (result != 0) {
        return "Could not create directory";
    }
    return "";
}

