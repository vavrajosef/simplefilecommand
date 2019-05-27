#include <string>
#include "../constants.h"
#include <vector>
#include <memory>

class FileClass {
protected:
    std::string _fileName;
    bool _isActive;
    std::string _creationTime;

    std::string toString(char type);

public:
    FileClass(std::string fileName, bool isActive, std::string creationTime);

    std::string getFileName();

    virtual std::string toString() = 0;

    bool isActive();

    std::string getCreationTime();

    void setActive(bool isActive);

    virtual std::string copy(std::string path, std::string destination) = 0;

    virtual std::string deleteFile(std::string path) = 0;

    virtual std::string moveFile(std::string path, std::string destination) = 0;

    virtual std::string createFile(std::string path) = 0;
};

class Regexable;

struct DateType;

class Directory : public FileClass {
private:
    std::string _path;
public:
    Directory(std::string fileName, bool isActive, std::string creationTime, std::string path);

    std::string getPath();

    std::string toString() override;

    std::string copy(std::string path, std::string destination) override;

    std::string deleteFile(std::string path) override;

    std::string moveFile(std::string path, std::string destination) override;

    std::string createFile(std::string path) override;
};

class Link : public FileClass {
private:
    std::string _destination;
public:
    Link(std::string fileName, bool isActive, std::string creationTime, std::string destination);

    std::string toString() override;

    std::string copy(std::string path, std::string destination) override;

    std::string deleteFile(std::string path) override;

    std::string moveFile(std::string path, std::string destination) override;

    std::string createFile(std::string path) override;
};

class RegularFile : public FileClass {
public:
    RegularFile(std::string fileName, bool isActive, std::string creationTime);

    std::string toString() override;

    std::string copy(std::string path, std::string destination) override;

    std::string deleteFile(std::string path) override;

    std::string moveFile(std::string path, std::string destination) override;

    std::string createFile(std::string path) override;
};

class FileLoader {
private:
    FileLoader() {}

public:
    static std::vector <std::shared_ptr<FileClass>> loadDirectory(std::string path);
};
