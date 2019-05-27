#include "panel.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <regex.h>

using namespace std;

Panel::Panel(int positionX, int positionY, int sizeX, int sizeY) {
    _positionX = positionX;
    _positionY = positionY;
    _sizeX = sizeX;
    _sizeY = sizeY;
    Directory newDir(".", false, ".");
    currentDirectory = make_shared<Directory>(newDir);
}

string Panel::changeDirectory(string path) {
    string errorMessage = "";
    vector <shared_ptr<FileClass>> loadedFiles = FileLoader::loadDirectory(path);
    if (loadedFiles.empty()) {
        errorMessage = "Error opening a directory";
    } else {
        Directory newDir(path, false, path);
        currentDirectory = make_shared<Directory>(newDir);
        filesInDir.clear();
        if (activeFile != nullptr) {
            activeFile->setActive(false);
        }
        filesInDir.insert(filesInDir.begin(), loadedFiles.begin(), loadedFiles.end());
        filesInDir[0]->setActive(true);
        activeFile = filesInDir[0];
        paging.currentPage = 0;
        paging.maxPages = filesInDir.size() / 15;
        paging.recordCount = filesInDir.size();
        paging.positionOfFile = 0;
    }
    return errorMessage;
}

shared_ptr <FileClass> Panel::getActiveFile() {
    return activeFile;
}

shared_ptr <Directory> Panel::getDirectory() {
    return currentDirectory;
}

int Panel::getSizeX() {
    return _sizeX;
}

int Panel::getSizeY() {
    return _sizeY;
}

int Panel::getPositionX() {
    return _positionX;
}

int Panel::getPositionY() {
    return _positionY;
}

string Panel::changeDirectory(Directory dir) {
    return changeDirectory(dir.getPath());
}

void Panel::reload() {
    changeDirectory(currentDirectory->getPath());
}

vector <string> Panel::printCurrentDir() {
    vector <string> fileDetails;
    int startPage = paging.currentPage * 15;
    int endPage = (startPage + 15) > paging.recordCount ? paging.recordCount : (startPage + 15);
    for (int i = startPage; i < endPage; i++) {
        fileDetails.push_back(filesInDir[i]->toString());
    }
    return fileDetails;
}

void Panel::switchActiveFileDown() {
    int fileCount = filesInDir.size() - 1;
    if (paging.positionOfFile < fileCount) {
        activeFile->setActive(false);
        paging.positionOfFile++;
        activeFile = filesInDir[paging.positionOfFile];
        activeFile->setActive(true);
        if (paging.positionOfFile >= ((paging.currentPage + 1) * 15)) {
            paging.currentPage++;
        }
    }
}

void Panel::switchActiveFileUp() {
    if (paging.positionOfFile > 0) {
        activeFile->setActive(false);
        paging.positionOfFile--;
        activeFile = filesInDir[paging.positionOfFile];
        activeFile->setActive(true);
        if (paging.positionOfFile < (paging.currentPage * 15)) {
            paging.currentPage--;
        }
    }
}

vector <shared_ptr<FileClass>> Panel::getMatchingFiles(string regExpression, string *errorMessage) {
    vector <shared_ptr<FileClass>> matchingFiles;
    regex_t r;
    if (regcomp(&r, regExpression.c_str(), REG_EXTENDED) == 0) {
        for (auto it = filesInDir.begin(); it != filesInDir.end(); ++it) {
            int status = regexec(&r, (*it)->getFileName().c_str(), 0, NULL, 0);
            if (status == 0) {
                matchingFiles.push_back(*it);
            }
        }
        if (matchingFiles.empty()) {
            *errorMessage = "No file matched regular expression";
        }
    } else {
        *errorMessage = "Regular expression could not be compiled";
    }
    return matchingFiles;
}
