#include "Action.cpp"

using namespace std;

Delete::Delete(shared_ptr <FileClass> triggeredFile, shared_ptr <Directory> triggeredDirectory) : Action::Action(
        triggeredFile, triggeredDirectory) {}

string Delete::execute() {
    return _triggeredFile->deleteFile(_triggeredDirectory->getPath() + "/" + _triggeredFile->getFileName());
}
