#include <iostream>
#include <vector>

using namespace std;

class Action {
public:
    virtual void execute() const = 0;
    virtual ~Action() = default;
};

class CreateAction: public Action {
public:
    void execute() const override { cout << "Create file" << "\n"; }
};

class ExitAction: public Action {
public:
    void execute() const override { cout << "Exit application" << "\n"; }
};

class MenuItem {
private:
    string text;
    Action* action;
public:
    MenuItem(const string &text, Action *action) : text(text), action(action) {}
    ~MenuItem() { delete action; }
    virtual void print() const { cout << "MI:" << text << "\n"; }
    void clicked() const {
        print();
        if (action) action->execute();
    }
};

class Menu: public MenuItem {
private:
    vector<MenuItem*> items;
public:
    Menu(const string &text) : MenuItem(text, nullptr) {}
    Menu(const string &text, Action *action) : MenuItem(text, action) {}
    void add(MenuItem* m) { items.push_back(m); }
    ~Menu() { for (const auto &m: items) delete m; }
    void print() const override {
        cout << "Menu:\n";
        MenuItem::print();
        for (const auto &m: items) m->print();
        cout << "\n";
    }
};

class MenuBar {
private:
    vector<Menu*> menus;
public:
    void add(Menu* m) { menus.push_back(m); }
    ~MenuBar() { for (const auto &m: menus) delete m; }
    void print() const { for (const auto &m: menus) m->print(); }
};


int main() {
    auto new_ = new Menu("New");
    new_->add(new Menu("Text", new CreateAction()));
    auto cpp = new Menu("C++", new CreateAction());
    new_->add(cpp);

    auto exit = new Menu("Exit", new ExitAction());

    auto file = new Menu("File");
    file->add(new_);
    file->add(exit);
    auto about = new Menu("About");

    MenuBar menuBar;
    menuBar.add(file);
    menuBar.add(about);

    menuBar.print();
    file->clicked();
    new_->clicked();
    cpp->clicked(); // prints: "Create file"

//    menuBar.print();
//    file->clicked();
    exit->clicked(); // prints: "Exit application"

    return 0;
}
