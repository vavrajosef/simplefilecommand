#include "Action.cpp"

using namespace std;

Delete::Delete(shared_ptr<FileClass> triggeredFile, shared_ptr<Directory> triggeredDirectory) : Action::Action(
        triggeredFile, triggeredDirectory) {}

void Delete::execute() {
    _triggeredFile->deleteFile(_triggeredDirectory->getPath());
}
