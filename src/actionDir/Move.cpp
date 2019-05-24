#include "Copy.cpp"

using namespace std;

Move::Move(shared_ptr<FileClass> triggeredFile, shared_ptr<Directory> triggeredDirectory,
           shared_ptr<FileClass> destinationFile, shared_ptr<Directory> destinationDirectory)
        : Action(triggeredFile, triggeredDirectory),
          Copy(triggeredFile, triggeredDirectory, destinationFile, destinationDirectory) {}

void Move::execute() {
    Copy::execute();
    _triggeredFile->deleteFile(_triggeredDirectory->getPath());
}
