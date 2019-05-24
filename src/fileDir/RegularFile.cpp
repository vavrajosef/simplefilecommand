#include "FileClass.cpp"
#include <sys/sendfile.h>  // sendfile
#include <fcntl.h>         // open
#include <unistd.h>        // close
#include <sys/stat.h>      // fstat


using namespace std;

RegularFile::RegularFile(string fileName, bool isActive)  : FileClass(fileName, isActive){}

string RegularFile::toString() {
    return FileClass::toString('F');
}

string RegularFile::deleteFile(string path) {
	return "";
}

string RegularFile::moveFile(string path, string destination) {
	return "";
}

string RegularFile::copy(string source, string destination) {
	int srcDesc = open(source.c_str(), O_RDONLY, 0);
	int destDesc = open(destination.c_str(), O_WRONLY | O_CREAT, 0644);
	struct stat stat_source;
	fstat(srcDesc, &stat_source);

	sendfile(destDesc, srcDesc, 0, stat_source.st_size);

	close(srcDesc);
	close(destDesc);
	return "";
}
