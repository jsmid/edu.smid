/*
    Composite Design Pattern Example in C++

    Purpose:
    The Composite pattern allows you to compose objects into tree structures to represent part-whole hierarchies.
    It lets clients treat individual objects and compositions of objects uniformly.
    This is useful when you want to work with tree-like structures, such as file systems, GUI components, or organizational charts,
    where both individual elements (leaves) and groups of elements (composites) should be treated the same way.

    In this example, we model a simple file system where both files and folders can be treated as FileSystemComponent objects.
*/

#include <iostream>
#include <vector>
#include <string>

// Component interface
class FileSystemComponent {
public:
    virtual void show(int indent = 0) const = 0;
    virtual ~FileSystemComponent() {}
};

// Leaf
class File : public FileSystemComponent {
    std::string name;
public:
    File(const std::string& name) : name(name) {}
    void show(int indent = 0) const {
        std::cout << std::string(indent, ' ') << "- File: " << name << std::endl;
    }
};

// Composite
class Folder : public FileSystemComponent {
    std::string name;
    std::vector<FileSystemComponent*> children;
public:
    Folder(const std::string& name) : name(name) {}
    ~Folder() {
        for (size_t i = 0; i < children.size(); ++i)
            delete children[i];
    }
    void add(FileSystemComponent* component) {
        children.push_back(component);
    }
    void show(int indent = 0) const {
        std::cout << std::string(indent, ' ') << "+ Folder: " << name << std::endl;
        for (size_t i = 0; i < children.size(); ++i)
            children[i]->show(indent + 2);
    }
};

int main() {
    Folder* root = new Folder("root");
    root->add(new File("file1.txt"));
    root->add(new File("file2.txt"));

    Folder* subFolder = new Folder("subfolder");
    subFolder->add(new File("file3.txt"));
    subFolder->add(new File("file4.txt"));

    root->add(subFolder);

    root->show();

    delete root;
    return 0;
}