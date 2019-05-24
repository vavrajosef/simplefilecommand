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

string Link::copy(string path, string destination) {

	return "";
}
