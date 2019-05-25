#include "Move.cpp"

using namespace std;

Regex::Regex(shared_ptr<Regexable> action, shared_ptr<Directory> destination) : Action(nullptr, nullptr) {
    _action = action;
    _destinationDirectory = destination;
}

string Regex::execute() {
    // todo find affected files first
		return "";
}
