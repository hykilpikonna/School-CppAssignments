#include <iostream>
#include <utility>
#include <array>

using namespace std;

void print(const string &a);

class Item
{
public:
    int field;

    // Constructor
    Item(int field, int field2)
    {
        this->field = field;
        this->field2 = field2;
    }

    // ctor constructors
    Item(): Item(1, 3) {}

    // Class functions
    void increment() { field++; }

private:
    int field2;
};

int main()
{
    print("Hello, World");

    // These are both int arrays with 25 elements.

    // Structure array type[]
    int a[25];
    cout << "The array a has " << sizeof(a) / sizeof(a[0]) << " elements." << endl;

    // Class array<type, size>
    array<int, 25> b;
    cout << "The array b has " << b.size() << " elements" << endl;

    return 0;
}

void print(const string &a)
{
    cout << a << endl;
}


class Robot {
public:
    string name;

    explicit Robot(string name) { this->name = std::move(name); }

    void makeNoise() const { cout << name << " is not a robot" << endl; }
};

class RobotDog: public Robot {
public:
    // Override constructor
    explicit RobotDog(const string& name): Robot(name + " (Dog)") {};

    // Override function
    void makeNoise() {
        Robot::makeNoise(); // Call super class methods
        cout << name << " is also not a robot dog" << endl;
    }
};