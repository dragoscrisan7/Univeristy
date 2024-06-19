#include <iostream>
#include <vector>

class Activity {
private:
    std::string name;
    std::string time;
public:
    Activity(const std::string &name, const std::string &time) : name(name), time(time) {}

    friend std::ostream &operator<<(std::ostream &os, const Activity &a) {
        os << "Activity " << a.name << " will take place at " << a.time << ".";
        return os;
    }
};


template<typename T>
class ToDo {
private:
    std::vector<T> v;
public:
    ToDo& operator+=(const Activity& a) {
        v.push_back(a);
        return *this;
    }

    auto begin() {
        return v.begin();
    }

    auto end() {
        return v.end();
    }

//    Activity* begin() {
//        return v.data();
//    }
//
//    Activity* end() {
//        return v.data() + v.size();
//    }

    void reversePrint(std::ostream& os) {
        for (int i = v.size() - 1; i >= 0; --i) {
            os << v[i] << '\n';
        }
    }
};


void todolist() {
    ToDo<Activity> todo{};
    Activity tiff{"go to TIFF movie", "20:00"};
    todo += tiff;
    Activity project{"present project assignment", "09:20"};
    todo += project;

    for (auto a: todo) {
        std::cout << a << '\n';
    }

    todo.reversePrint(std::cout);
}

int main() {
    todolist();
    return 0;
}
