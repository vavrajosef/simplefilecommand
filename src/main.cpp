#include <iostream>
#include <ncurses.h>
#include <string>
#include "actionDir/Regex.cpp"
#include <regex.h>

int INTERACTION_LINE = 21;

using namespace std;

string handleInput(int*, Panel** active, Panel** inactive);
void printDir(Panel *, WINDOW *);
int main() {

		Panel * leftPanel = new Panel(1, 1, 49, 20);
		Panel * rightPanel = new Panel(50, 1, 49, 20);
		Panel * activeP = leftPanel;
		Panel * inactiveP = rightPanel;
		initscr();
		refresh();
		WINDOW * leftWindow = newwin(leftPanel->getSizeY(), leftPanel->getSizeX(), leftPanel->getPositionY(), leftPanel->getPositionX())    ;

		WINDOW * rightWindow = newwin(rightPanel->getSizeY(), rightPanel->getSizeX(), rightPanel->getPositionY(), rightPanel->getPositionX());

		activeP->changeDirectory(".");
		inactiveP->changeDirectory(".");
		noecho();
		int inputChar;
		string errorMessage;
		do {
			box(leftWindow, 0, 0);
			box(rightWindow,0,0);
			printDir(leftPanel, leftWindow);
			printDir(rightPanel, rightWindow);
			wrefresh(leftWindow);
			wrefresh(rightWindow);
			refresh();

			errorMessage = handleInput(&inputChar, &activeP, &inactiveP);
			move(INTERACTION_LINE, 0);
			clrtoeol();
			wclear(leftWindow);
			wclear(rightWindow);
			if(errorMessage != "") {
				mvprintw(INTERACTION_LINE, 0, errorMessage.c_str());
			}
		} while(inputChar != 'q');
		endwin();
    return 0;
}

string handleInput(int * inputChar, Panel ** active, Panel ** inactive) {
	string errorMessage = "";
	*inputChar = getch();
	shared_ptr<Action> dummy = nullptr;
	switch(*inputChar) {
		case '5': {
			Copy copyAction((*active)->getActiveFile(), (*active)->getDirectory(),
			(*active)->getActiveFile(), (*inactive)->getDirectory());
			dummy = make_shared<Copy>(copyAction);
			break;
		}
		case 'A':
			(*active)->switchActiveFileUp();
			break;
		case 'B':
			(*active)->switchActiveFileDown();
			break;
		case 'r': {
			move(INTERACTION_LINE, 0);
			clrtoeol();
			echo();
			string expression = "";
			while(true) {
				*inputChar = getch();
				if(*inputChar == '\n') {
					break;
				}
				expression += *inputChar;
			}
			move(INTERACTION_LINE, 0);
			clrtoeol();
			noecho();
			vector<shared_ptr<FileClass>> matchingFiles = (*active)->getMatchingFiles(expression, &errorMessage);
			if(errorMessage == "") {
				*inputChar = getch();
			switch(*inputChar) {
				case 'd': {
					for(auto it = matchingFiles.begin(); it != matchingFiles.end(); ++it) {
						Delete deleteAction ((*it), (*active)->getDirectory());
						errorMessage = deleteAction.execute();
					}	
					break;
				}
				case '5': {
					for(auto it = matchingFiles.begin(); it != matchingFiles.end(); ++it) {
						Copy copyAction((*it), (*active)->getDirectory(),
							(*it), (*inactive)->getDirectory());
						errorMessage = copyAction.execute();
					}	
					break;
				}
				case '6': {
					for(auto it = matchingFiles.begin(); it != matchingFiles.end(); ++it) {
						Move moveAction((*it), (*active)->getDirectory(),
							(*it), (*inactive)->getDirectory());
						errorMessage = moveAction.execute();
					}	
					break;
				}
				default:
					errorMessage = "Command not supported";
					break;
				}
			}
		(*active)->reload();
		(*inactive)->reload();
			}
			break;
		case 9: {
			Panel * temp = *active;
			*active = *inactive;
			*inactive = temp;
			break;
		}
		case 10: {
			shared_ptr<FileClass> cur = (*active)->getActiveFile();
			if(typeid(*cur) == typeid(Directory)) {
				errorMessage = (*active)->changeDirectory(*dynamic_pointer_cast<Directory>(cur));
			} else {
				errorMessage = "Not a directory.";
			}
			break;
		}
		case 'd': {
			Delete deleteAction ((*active)->getActiveFile(), (*active)->getDirectory());
			dummy = make_shared<Delete>(deleteAction);
			break;
		}
		case '7': {
			move(INTERACTION_LINE, 0);
			clrtoeol();
			echo();
			string dirName = "";
			while(true) {
				*inputChar = getch();
				if(*inputChar == '\n') {
					break;
				}
				dirName += *inputChar;
			}
			move(INTERACTION_LINE, 0);
			clrtoeol();
			noecho();
			Directory newDir(dirName, false, (*active)->getDirectory()->getPath());
			Create createAction(make_shared<Directory>(newDir), (*active)->getDirectory());
			dummy = make_shared<Create>(createAction);
			break;
		}
		case '8': {

			move(INTERACTION_LINE, 0);
			clrtoeol();
			echo();
			string newFileName = "";
			while(true) {
				*inputChar = getch();
				if(*inputChar == '\n') {
					break;
				}
				newFileName += *inputChar;
			}
			move(INTERACTION_LINE, 0);
			clrtoeol();
			noecho();
			RegularFile newFile(newFileName, false);
			Create createAction(make_shared<RegularFile>(newFile), (*active)->getDirectory());
			dummy = make_shared<Create>(createAction);
			break;
		}
		case '9': {
			move(INTERACTION_LINE, 0);
			clrtoeol();
			echo();
			string newLinkName = "", target = "";
			while(true) {
				*inputChar = getch();
				if(*inputChar == '\n') {
					break;
				}
				newLinkName += *inputChar;
			}
			move(INTERACTION_LINE, 0);
			clrtoeol();

			while(true) {
				*inputChar = getch();
				if(*inputChar == '\n') {
					break;
				}
				target += *inputChar;
			}
			move(INTERACTION_LINE, 0);
			clrtoeol();
			noecho();
			Link newLink(newLinkName, false, target);
			Create createAction(make_shared<Link>(newLink), (*active)->getDirectory());
			dummy = make_shared<Create>(createAction);
			break;
		}
		case '6': {
			Move moveAction((*active)->getActiveFile(), (*active)->getDirectory(),
			(*active)->getActiveFile(), (*inactive)->getDirectory());
			dummy = make_shared<Move>(moveAction);
		}
		default:
			break;
	}
	if(dummy != nullptr) {
		errorMessage = dummy->execute();
		(*active)->reload();
		(*inactive)->reload();
	}
	return errorMessage;
}

void printDir(Panel * panel, WINDOW * window) {
	vector<string> files = panel->printCurrentDir();
	int ypos = 1;
	for(auto it = files.begin(); it != files.end(); ++it) {
		mvwprintw(window, ypos, 1, it->c_str());
		ypos++;
	}
}

