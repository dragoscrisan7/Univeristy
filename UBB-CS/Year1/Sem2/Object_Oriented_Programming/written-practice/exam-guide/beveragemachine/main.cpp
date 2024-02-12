#include <iostream>

class Beverage {
private:
    std::string description;
public:
    Beverage(const std::string &description) : description(description) {}

    virtual ~Beverage() = default;

    const std::string &getDescription() const {
        return description;
    }

    virtual double price() const = 0;

    virtual void print() const {
        std::cout << description << " " << price();
    }
};

class Coffee: public Beverage {
public:
    Coffee() : Beverage("Coffee") {}

    double price() const override {
        return 4.5;
    }
};

class Tea: public Beverage {
public:
    Tea() : Beverage("Tea") {}

    double price() const override {
        return 3.5;
    }
};

class BeverageWithMilk: public Beverage {
private:
    Beverage* bev;
    int milkCount;
public:
    BeverageWithMilk(Beverage* bev, int milkCount) : Beverage(bev->getDescription() + " with milk"), bev(bev), milkCount(milkCount) {}
    ~BeverageWithMilk() { delete bev; }

    double price() const override {
        return bev->price() + 0.5 * milkCount;
    }

    void print() const override {
        Beverage::print();
//        std::cout << " " << milkCount;
        std::cout << (milkCount ? 2 + " " : "");
    }
};

class BeverageMachine {
public:
    void prepare(const std::string& beverageType, int milkCount) const {
        Beverage* b;

        if (beverageType == "Tea") {
            b = new Tea;
        }
        else if (beverageType == "Coffee") {
            b = new Coffee;
        }
        else {
            return;
        }

        if (milkCount > 0) {
            b = new BeverageWithMilk(b, milkCount);
        }

        b->print();
        std::cout << "\n";
        delete b;
    }
};

int main() {
    BeverageMachine bm;
    bm.prepare("Tea", 0);
    bm.prepare("Coffee", 1);
    bm.prepare("Coffee", 2);

    return 0;
}
