all: sfc

sfc: file.o panel.o regularfile.o link.o directory.o action.o create.o delete.o copy.o move.o regex.o
	g++ -lncurses -Wall -pedantic -std=c++14 -g -o main main.cpp

panel.o: panelDir/Panel.cpp 
	g++ -c panelDir/panel.h panelDir/Panel.cpp

file.o: fileDir/FileClass.cpp
	g++ -c fileDir/FileClass.cpp

regularfile.o: fileDir/RegularFile.cpp
	g++ -c fileDir/RegularFile.cpp

link.o: fileDir/Link.cpp
	g++ -c fileDir/Link.cpp

directory.o: fileDir/Directory.cpp
	g++ -c fileDir/Directory.cpp 

action.o: actionDir/Action.cpp
	g++ -c actionDir/Action.cpp

create.o: actionDir/Create.cpp
	g++ -c actionDir/Create.cpp

delete.o: actionDir/Delete.cpp
	g++ -c actionDir/Delete.cpp

copy.o: actionDir/Copy.cpp
	g++ -c actionDir/Copy.cpp

move.o: actionDir/Move.cpp
	g++ -c actionDir/Move.cpp

regex.o: actionDir/Regex.cpp
	g++ -c actionDir/Regex.cpp

clean:
	rm -f main
	rm -f *.o
	rm -f "actionDir/*.o"
	rm -f "fileDir/*.o"
	rm -f "panelDir/*.o"
	rm -f vgcore.*	
	rm -f "actionDir/*.gch"
	rm -f "fileDir/*.gch"
	rm -f "panelDir/*.gch"

run:
    ./main
