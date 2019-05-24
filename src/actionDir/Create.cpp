#include "Delete.cpp"

using namespace std;

Create::Create(string newFileName, std::shared_ptr<Directory> triggeredDirectory) : Action::Action(
        nullptr, triggeredDirectory) {
    _newFileName = newFileName;
}

void Create::execute() {

}



