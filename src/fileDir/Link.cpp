#include "RegularFile.cpp"

using namespace std;

Link::Link(string fileName, bool isActive, string destination) : FileClass(fileName, isActive) {
    _destination = destination;
}

string Link::toString() {
    return FileClass::toString('L');
}

string Link::moveFile(string path, string destination) {

	return "";
}

string Link::deleteFile(string path) {

	return "";
}

string Link::copy(string source, string destination) {
	return createFile(destination);
}

string Link::createFile(string path) {
	if(symlink(_destination.c_str(), path.c_str()) != 0) {
			return path + " _ " + _destination;
//		return "Could not create symlink";
	}
	return "ok - " +
			path + " _ " + _destination;
}
