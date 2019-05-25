#include "Link.cpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <memory>

using namespace std;

Directory::Directory(string fileName, bool isActive, string path)  : FileClass(fileName, isActive) {
    _path = path;
}
string Directory::toString() {
    return FileClass::toString('D');
}

string Directory::getPath() {
    return _path;
}

string Directory::deleteFile(string path) {

	return "";
}

string Directory::copy(string path, string destination) {
	int result = mkdir(destination.c_str(), 0777);
	if(result != 0) {
		return "Could not create directory";
	}
	DIR *pDIR;
	struct dirent *entry;
	pDIR = opendir(_path.c_str());
	if(pDIR != nullptr) {
		while((entry = readdir(pDIR))) {
			struct stat s;
			string currentFilePath = _path + "/" + entry->d_name;
			if(lstat(currentFilePath.c_str(), &s) == 0) {
				shared_ptr<FileClass> dummy;
				if(string(entry->d_name) == "." || string(entry->d_name) == "..") {
					continue;
				}
				switch(s.st_mode & S_IFMT) {
					case S_IFDIR: {
						char absolutePath[PATH_MAX + 1];
						realpath(currentFilePath.c_str(), absolutePath);
						Directory dir(entry->d_name, false, string(absolutePath));
						dummy = make_shared<Directory>(dir);
						break;
					}
					case S_IFLNK: {
						char absolutePath[PATH_MAX + 1];
						readlink(currentFilePath.c_str(), absolutePath, sizeof(absolutePath));
						Link link(entry->d_name, false, string(absolutePath));
						dummy = make_shared<Link>(link);
						break;
					}
					default: {
						RegularFile regFile(entry->d_name, false);
						dummy = make_shared<RegularFile>(regFile);
						break;
					}
				}
				dummy->copy(_path, destination + "/" + dummy->getFileName());
			} else {
				return "File reading error";
			}
		}
	} else {
		return "Error opening directory";
	}
	return "";
}

string Directory::moveFile(string path, string destination) {

	return "";
}

string Directory::createFile(string path) {
	string directoryPath = path + "/" + _fileName;
	int result = mkdir(directoryPath.c_str(), 0777);
	if(result != 0) {
		return "Could not create directory";
	}
	return "";
}

