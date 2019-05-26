#include "RegularFile.cpp"

using namespace std;

Link::Link(string fileName, bool isActive, string destination) : FileClass(fileName, isActive) {
    _destination = destination;
}

string Link::toString() {
    return FileClass::toString('L');
}

string Link::moveFile(string path, string destination) {
	string errorMessage = copy(path, destination);
	if(errorMessage != "") {
		return errorMessage;
	}
	errorMessage = deleteFile(path);
	return errorMessage;
}

string Link::deleteFile(string path) {
	int result = unlink(path.c_str());
	if(result != 0) {
		return "Error deleting link: " + path;
	}
	return "";
}

string Link::copy(string source, string destination) {
	return createFile(destination);
}

string Link::createFile(string path) {
	if(symlink(_destination.c_str(), path.c_str()) != 0) {
		return "Could not create symlink";
	}
	return "";
}
