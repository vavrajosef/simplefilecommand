#include "Copy.cpp"

using namespace std;

Move::Move(shared_ptr<FileClass> triggeredFile, shared_ptr<Directory> triggeredDirectory,
           shared_ptr<FileClass> destinationFile, shared_ptr<Directory> destinationDirectory)
        : Action(triggeredFile, triggeredDirectory),
          Copy(triggeredFile, triggeredDirectory, destinationFile, destinationDirectory) {}

string Move::execute() {
	string wholeDestinationPath = _destinationDirectory->getPath() + "/" + _destinationFile->getFileName();
	string wholeSourcePath = _triggeredDirectory->getPath() + "/" + _triggeredFile->getFileName();
	return _triggeredFile->moveFile(wholeSourcePath, wholeDestinationPath);
}
