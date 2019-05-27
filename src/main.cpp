#include <iostream>
#include <ncurses.h>
#include <string>
#include "actionDir/Move.cpp"
#include <regex.h>

using namespace std;

string handleInput(int *, Panel **active, Panel **inactive);

void printDir(Panel *, WINDOW *);

void clearInteractionLine();

void reload(Panel *, Panel *);

void reprint(WINDOW *, Panel *);

shared_ptr <Action> prepareDeleteAction(Panel *);

shared_ptr <Action> prepareCreateAction(shared_ptr <FileClass> fileToCreate, Panel *);

shared_ptr <Action> prepareCopyAction();

shared_ptr <Action> prepareMoveAction();

string receiveInputFromUser();

string handleRegexAction(Panel *active, Panel *inactive);

int main() {

    // Screen initialization
    Panel *leftPanel = new Panel(1, 1, 49, 20);
    Panel *rightPanel = new Panel(50, 1, 49, 20);
    Panel *activeP = leftPanel;
    Panel *inactiveP = rightPanel;
    initscr();
    refresh();
    WINDOW *leftWindow = newwin(leftPanel->getSizeY(), leftPanel->getSizeX(), leftPanel->getPositionY(),
                                leftPanel->getPositionX());

    WINDOW *rightWindow = newwin(rightPanel->getSizeY(), rightPanel->getSizeX(), rightPanel->getPositionY(),
                                 rightPanel->getPositionX());

    // set directories in panels to current directory
    activeP->changeDirectory(".");
    inactiveP->changeDirectory(".");
    noecho();
    int inputChar;
    string errorMessage;

    // main loop
    do {
        reprint(leftWindow, leftPanel);
        reprint(rightWindow, rightPanel);
        refresh();

        errorMessage = handleInput(&inputChar, &activeP, &inactiveP);

        // clear previous error message
        clearInteractionLine();
        wclear(leftWindow);
        wclear(rightWindow);
        if (errorMessage != "") {
            // set new error message
            mvprintw(INTERACTION_LINE, 0, errorMessage.c_str());
        }
    } while (inputChar != QUIT);
    endwin();
    free(leftPanel);
    free(rightPanel);
    return 0;
}

string handleInput(int *inputChar, Panel **active, Panel **inactive) {
    string errorMessage = "";
    *inputChar = getch();

    // dummy object for actions
    shared_ptr <Action> dummy = nullptr;
    switch (*inputChar) {
        case COPY_ACTION: {
            dummy = prepareCopyAction(*active, *inactive);
            break;
        }
        case UP_KEY:
            (*active)->switchActiveFileUp();
            break;
        case DOWN_KEY:
            (*active)->switchActiveFileDown();
            break;
        case REGEX_ACTION: {
            errorMessage = handleRegexAction(*active, *inactive);
            break;
        }
        case TAB_KEY: {
            (*active).swap(*inactive);
            break;
        }
        case ENTER_KEY: {
            shared_ptr <FileClass> cur = (*active)->getActiveFile();
            if (typeid(*cur) == typeid(Directory)) {
                errorMessage = (*active)->changeDirectory(*dynamic_pointer_cast<Directory>(cur));
            } else {
                errorMessage = "Not a directory.";
            }
            break;
        }
        case DELETE_ACTION: {
            dummy = prepareDeleteAction(*active);
            break;
        }
        case CREATE_DIR: {
            string dirName = receiveInputFromUser();
            Directory newDir(dirName, false, (*active)->getDirectory()->getPath());
            dummy = prepareCreateAction(make_shared<FileClass>(newDir), *active);
            break;
        }
        case CREATE_REG_FILE: {
            string newFileName = receiveInputFromUser();
            RegularFile newFile(newFileName, false);
            dummy = prepareCreateAction(make_shared<FileClass>(newFile), *active);
            break;
        }
        case CREATE_LINK: {
            string newLinkName = receiveInputFromUser();
            string target = receiveInputFromUser();
            Link newLink(newLinkName, false, target);
            dummy = prepareCreateAction(make_shared<FileClass>(newLink), *active);
            break;
        }
        case MOVE_ACTION: {
            dummy = prepareMoveAction(*active, *inactive);
            break;
        }
        default:
            break;
    }

    // execute any pending action
    if (dummy != nullptr) {
        errorMessage = dummy->execute();
        reload(*active, *inactive);
    }
    return errorMessage;
}

void printDir(Panel *panel, WINDOW *window) {
    vector <string> files = panel->printCurrentDir();

    // line counter
    int ypos = 1;
    for (auto it = files.begin(); it != files.end(); ++it) {
        mvwprintw(window, ypos, 1, it->c_str());
        ypos++;
    }
}

void clearInteractionLine() {
    move(INTERACTION_LINE, 0);
    clrtoeol();
}

void reload(Panel *active, Panel *inactive) {
    active->reload();
    inactive->reload();
}

void reprint(WINDOW *window, Panel *panel) {
    box(window, 0, 0);
    printDir(panel, window);
    wrefresh(window);
}

shared_ptr <Action> prepareDeleteAction(Panel *active) {
    Delete deleteAction((*active)->getActiveFile(), (*active)->getDirectory());
    return make_shared<Delete>(deleteAction);
}

string receiveInputFromUser() {
    clearInteractionLine();
    char inputChar;
    string result = "";

    // set visible user input
    echo();
    while (true) {
        inputChar = getch();
        if (inputChar == '\n') {
            break;
        }
        result += inputChar;
    }
    clearInteractionLine();

    // set input invisible again
    noecho();
    return result;
}

shared_ptr <Action> prepareCreateAction(shared_ptr <FileClass> file, Panel *activePanel) {
    Create createAction(file, activePanel->getDirectory());
    return make_shared<Create>(createAction);
}

shared_ptr <Action> prepareCopyAction(Panel *active, Panel *inactive) {
    Copy copyAction(active->getActiveFile(), active->getDirectory(), active->getActiveFile(), inactive->getDirectory());
    return make_shared<Copy>(copyAction);
}

shared_ptr <Action> prepareMoveAction(Panel *active, Panel *inactive) {
    Move moveAction(active->getActiveFile(), active->getDirectory(), active->getActiveFile(), inactive->getDirectory());
    return make_shared<Move>(moveAction);
}

string handleRegexAction(Panel *active, Panel *inactive) {
    string errorMessage = "";
    string expression = receiveInputFromUser();

    // get all files in current directory matching regular expression
    vector <shared_ptr<FileClass>> matchingFiles = active->getMatchingFiles(expression, &errorMessage);
    if (errorMessage == "") {
        *inputChar = getch();
        switch (*inputChar) {
            case DELETE_ACTION: {
                for (auto it = matchingFiles.begin(); it != matchingFiles.end(); ++it) {
                    Delete deleteAction((*it), active->getDirectory());
                    errorMessage = deleteAction.execute();
                }
                break;
            }
            case COPY_ACTION: {
                for (auto it = matchingFiles.begin(); it != matchingFiles.end(); ++it) {
                    Copy copyAction((*it), active->getDirectory(),
                                    (*it), inactive->getDirectory());
                    errorMessage = copyAction.execute();
                }
                break;
            }
            case MOVE_ACTION: {
                for (auto it = matchingFiles.begin(); it != matchingFiles.end(); ++it) {
                    Move moveAction((*it), active->getDirectory(),
                                    (*it), inactive->getDirectory());
                    errorMessage = moveAction.execute();
                }
                break;
            }
            default:
                errorMessage = "Command not supported";
                break;
        }
    }
    reload(active, inactive);
    return errorMessage;
}

