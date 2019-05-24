#include "../panelDir/Panel.cpp"
#include <memory>
#include <vector>

class Regexable {
};

class Action {
protected:
    std::shared_ptr<FileClass> _triggeredFile;
    std::shared_ptr<Directory> _triggeredDirectory;
public:
    Action(std::shared_ptr<FileClass> triggeredFile, std::shared_ptr<Directory> triggeredDirectory);

    std::shared_ptr<FileClass> getTriggeredFile();

    std::shared_ptr<Directory> getTriggeredDirectory();

    virtual void execute() = 0;

   // virtual ~Action() = 0;
};

class Copy : virtual public Action,  virtual public Regexable {
private:
    std::shared_ptr<FileClass> _destinationFile;
    std::shared_ptr<Directory> _destinationDirectory;
public:
    Copy(std::shared_ptr<FileClass> triggeredFile, std::shared_ptr<Directory> triggeredDirectory,
         std::shared_ptr<FileClass> destinationFile, std::shared_ptr<Directory> destinationDirectory);

    std::shared_ptr<FileClass> getDestinationFile();

    std::shared_ptr<Directory> getDestinationDirectory();

    void execute() override;

   // ~Copy() override = 0;
};

class Create : virtual public Action {
private:
    std::string _newFileName;
public:
    Create(std::string newFileName, std::shared_ptr<Directory> triggeredDirectory);

    void execute() override;
};

class Delete : virtual public Action, virtual public Regexable {
public:
    Delete(std::shared_ptr<FileClass> triggeredFile, std::shared_ptr<Directory> triggeredDirectory);

    void execute() override;

    //~Delete() override = 0;
};

class Move : virtual public Copy, virtual public Regexable {
public:
    Move(std::shared_ptr<FileClass> triggeredFile, std::shared_ptr<Directory> triggeredDirectory,
         std::shared_ptr<FileClass> destinationFile, std::shared_ptr<Directory> destinationDirectory);

    void execute() override;

    //~Move() override = 0 ;
};

class Regex : virtual public Action {
private:
    std::shared_ptr<Regexable> _action;
    std::shared_ptr<Directory> _destinationDirectory;
    std::string _regex;
    std::vector<std::string> affectedFiles;
public:
    Regex(std::shared_ptr<Regexable> action, std::shared_ptr<Directory> destination);
    void execute() override;
   // ~Regex() override = 0;
};
