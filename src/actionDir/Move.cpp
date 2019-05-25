#include "Copy.cpp"

using namespace std;

Move::Move(shared_ptr<FileClass> triggeredFile, shared_ptr<Directory> triggeredDirectory,
           shared_ptr<FileClass> destinationFile, shared_ptr<Directory> destinationDirectory)
        : Action(triggeredFile, triggeredDirectory),
          Copy(triggeredFile, triggeredDirectory, destinationFile, destinationDirectory) {}

string Move::execute() {
    string errorMessage = Copy::execute();
		if(errorMessage != "") {
			return errorMessage;
		}
    return _triggeredFile->deleteFile(_triggeredDirectory->getPath());
}
