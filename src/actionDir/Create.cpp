#include "Delete.cpp"

using namespace std;

Create::Create(shared_ptr <FileClass> newFile, shared_ptr <Directory> triggeredDirectory) : Action::Action(
        newFile, triggeredDirectory) {
}

string Create::execute() {
    string filePath = _triggeredDirectory->getPath() + "/" + _triggeredFile->getFileName();
    return _triggeredFile->createFile(filePath);
}

