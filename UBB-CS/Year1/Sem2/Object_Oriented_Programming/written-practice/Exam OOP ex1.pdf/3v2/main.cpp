#include <iostream>
#include <vector>

class Action {
public:
    virtual void execute() const = 0;
    virtual ~Action() = default;
};

class CreateAction: public Action {
public:
    void execute() const override { std::cout << "Create file"; }
};

class ExitAction: public Action {
public:
    void execute() const override { std::cout << "Exit application"; }
};

class MenuItem {
private:
    std::string text{};
    Action* action;
public:
    MenuItem(const std::string &text, Action *action) : text(text), action(action) {}
    ~MenuItem() {
        fprintf(stderr, "[~MenuItem()] START action %p\n", action);
        delete action;
//        action = nullptr;
        fprintf(stderr, "[~MenuItem()] END action %p\n", action);
    }
    virtual void print() const { std::cout << text; }
    void clicked() const {
        print(); // TODO: is this polymorphic call? I think it is
        if (action)
            action->execute();
    }
};

class Menu: public MenuItem {
private:
    std::vector<MenuItem*> items;
public:
//    Menu(const std::string &text, Action *action) : MenuItem(text, nullptr) {}
    Menu(const std::string &text) : MenuItem(text, nullptr) {}
    virtual ~Menu() { for (const auto &m: items) delete m; }
    void add(MenuItem* m) { items.push_back(m); }
    void print() const override {
        MenuItem::print();
        for (const auto &m: items)
            m->print();
    }
};

class MenuBar {
private:
    std::vector<Menu> menus;
public:
    void add(const Menu& m) { menus.push_back(m); }
    void print() const {
        for (const auto &m: menus)
            m.print();
    }
};


int main() {
    auto new_ = new Menu("New");
//    new_.add(MenuItem("Text", new CreateAction()));
    auto cpp = new MenuItem("C++", new CreateAction());
    new_->add(cpp);

    Menu file("File");
    file.add(new_);
    file.add(new MenuItem("Exit", new ExitAction()));

    MenuBar menuBar;
    menuBar.add(file);
    menuBar.add(Menu("About"));

    menuBar.print();
    file.clicked();
    new_->clicked();
    cpp->clicked();

    return 0;
}
