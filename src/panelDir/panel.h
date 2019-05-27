#include<vector>
#include <memory>
#include "../fileDir/Directory.cpp"

struct Paging {
    int maxPages;
    int currentPage;
    int recordCount;
    int positionOfFile;
};

class Panel {
private:
    int _sizeX;
    int _sizeY;
    int _positionX;
    int _positionY;
    std::shared_ptr <FileClass> activeFile;
    std::shared_ptr <Directory> currentDirectory;
    std::vector <std::shared_ptr<FileClass>> filesInDir;
    Paging paging;
public:
    Panel(int positionX, int positionY, int sizeX, int sizeY);

    int getPositionX();

    int getPositionY();

    int getSizeX();

    int getSizeY();

    std::shared_ptr <Directory> getDirectory();

    std::shared_ptr <FileClass> getActiveFile();

    void reload();

    std::string changeDirectory(std::string path);

    std::string changeDirectory(Directory dir);

    std::vector <std::string> printCurrentDir();

    void switchActiveFileDown();

    void switchActiveFileUp();

    std::vector <std::shared_ptr<FileClass>> getMatchingFiles(std::string regExpression, std::string *errorMessage);
};
