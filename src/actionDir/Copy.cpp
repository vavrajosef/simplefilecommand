#include "Create.cpp"

using namespace std;

Copy::Copy(shared_ptr<FileClass> triggeredFile, shared_ptr<Directory> triggeredDirectory,
           shared_ptr<FileClass> destinationFile, shared_ptr<Directory> destinationDirectory) : Action(triggeredFile,
                                                                                                  triggeredDirectory) {
    _destinationDirectory = destinationDirectory;
    _destinationFile = destinationFile;
}

shared_ptr<Directory> Copy::getDestinationDirectory() {
    return _destinationDirectory;
}

shared_ptr<FileClass> Copy::getDestinationFile() {
    return _destinationFile;
}

void Copy::execute() {
    string wholeDestinationPath = _destinationDirectory->getPath() + "/" + _destinationFile->getFileName();
    _triggeredFile->copy(_triggeredDirectory->getPath(), wholeDestinationPath);
}
