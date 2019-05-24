#include "panel.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>

using namespace std;

Panel::Panel(int positionX, int positionY, int sizeX, int sizeY) {
    _positionX = positionX;
    _positionY = positionY;
    _sizeX = sizeX;
    _sizeY = sizeY;
		Directory newDir(".", false, ".");
		currentDirectory = make_shared<Directory>(newDir);
		changeDirectory(".");
}

string Panel::changeDirectory(string path) {
	DIR *pDIR;
	struct dirent *entry;
	filesInDir.clear();
	if(activeFile != nullptr) {
		activeFile->setActive(false);
	}
	string errorMessage = "";
	bool isActive = true;
	int fileCount = 0;
	pDIR=opendir(path.c_str());
	if(pDIR != nullptr) {
		entry = readdir(pDIR);
		while(entry != nullptr){
			struct stat s;
			string wholePath = path + "/" + entry->d_name;
			if(stat(wholePath.c_str(), &s) == 0) {
				shared_ptr<FileClass> dummy;
				if(s.st_mode & S_IFDIR) {
					char absolutePath[PATH_MAX + 1];
					realpath(wholePath.c_str(), absolutePath);
					Directory dir(entry->d_name, isActive, string(absolutePath));
					dummy = make_shared<Directory>(dir);
				} else if (s.st_mode & S_IFLNK) {
					Link link(entry->d_name, isActive, "");
					dummy = make_shared<Link>(link);
				} else {
					RegularFile regFile(entry->d_name, isActive);
					dummy = make_shared<RegularFile>(regFile);
				}
				fileCount++;
				filesInDir.push_back(dummy);
				if(isActive) {
					activeFile = dummy;
					isActive = false;
				}
			} else {
				errorMessage = "File reading error";
			}	
		}
		closedir(pDIR);
		paging.currentPage = 0;
		paging.maxPages = fileCount / 15;
		paging.recordCount = fileCount;
		paging.positionOfFile = 0;
	} else {
		errorMessage = "Cannot open dir.";
	}
	
	return errorMessage;
}

shared_ptr<FileClass> Panel::getActiveFile() {
    return activeFile;
}

shared_ptr<Directory> Panel::getDirectory() {
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
    changeDirectory(dir.getPath());
		return dir.getPath();
}

void Panel::reload() {
    changeDirectory(currentDirectory->getPath());
}

vector<string> Panel::printCurrentDir() {
    vector<string> fileDetails;
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
    if(paging.positionOfFile > 0) {
				activeFile->setActive(false);
        paging.positionOfFile--;
        activeFile = filesInDir[paging.positionOfFile];
				activeFile->setActive(true);
        if(paging.positionOfFile < (paging.currentPage * 15)){
            paging.currentPage--;
        }
    }
}
