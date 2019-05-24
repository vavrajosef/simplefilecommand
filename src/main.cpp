#include <iostream>
#include <ncurses.h>
#include <string>
#include "actionDir/Regex.cpp"

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
		WINDOW * leftWindow = newwin(leftPanel->getSizeY(), leftPanel->getSizeX(), leftPanel->getPositionY(), leftPanel->getPositionX())    ;

		WINDOW * rightWindow = newwin(rightPanel->getSizeY(), rightPanel->getSizeX(), rightPanel->getPositionY(), rightPanel->getPositionX());

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
	//shared_ptr<Action> dummy = nullptr;
	switch(*inputChar) {
		case '5': {
			//Copy copyAction((*active)->getActiveFile(), (*active)->getDirectory(),
//(*active)->getActiveFile(), (*inactive)->getDirectory());
			//dummy = make_shared<Copy>(copyAction);
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
			*inputChar = getch();
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
		default:
			break;
	}
	//if(dummy != nullptr) {
	//	dummy->execute();
//	}
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

