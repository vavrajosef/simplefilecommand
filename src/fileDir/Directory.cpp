#include "Link.cpp"

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

	return "";
}

std::string Directory::moveFile(std::string path, std::string destination) {

	return "";
}



