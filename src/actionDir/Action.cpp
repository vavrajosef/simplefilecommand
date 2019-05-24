#include "actions.h"

using namespace std;

Action::Action(shared_ptr<FileClass> triggeredFile, shared_ptr<Directory> triggeredDirectory) {
    _triggeredFile = triggeredFile;
    _triggeredDirectory = triggeredDirectory;
}

shared_ptr<Directory> Action::getTriggeredDirectory() {
    return _triggeredDirectory;
}

shared_ptr<FileClass> Action::getTriggeredFile() {
    return _triggeredFile;
}
