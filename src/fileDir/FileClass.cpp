#include "files.h"

using namespace std;

FileClass::FileClass(string fileName, bool isActive) {
    _fileName = fileName;
    _isActive = isActive;
}

string FileClass::toString(char type) {
    string result, fileName;
    if(_fileName.size() > 10) {
        fileName = _fileName.substr(0, 7);
        fileName += "...";
    } else {
				fileName = _fileName;
				fileName.insert(_fileName.size(), 10 - _fileName.size(), ' ');
		}
		result = fileName;
    result += "|";
    result += type;
    result += "|";
    if(_isActive) {
    	result += "*";
    }
		return result;
}

string FileClass::getFileName() {
    return _fileName;
}

bool FileClass::isActive() {
    return _isActive;
}

void FileClass::setActive(bool isActive) {
    _isActive = isActive;
}