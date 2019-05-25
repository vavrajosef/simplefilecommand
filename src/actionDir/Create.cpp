#include "Delete.cpp"

using namespace std;

Create::Create(string newFileName, shared_ptr<Directory> triggeredDirectory) : Action::Action(
        nullptr, triggeredDirectory) {
    _newFileName = newFileName;
}

string Create::execute() {
	return "";
}



