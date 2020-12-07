## Basic Stuff:

```c++
// Includes
// Input and Output
#include<iostream>
// Manipulate input and output
#include<iomanip>
// Math
#include<cmath>

// Remove std:: before using standard library stuff
using namespace std;

/* Block comment */
```

## Input and Output

```c++
cout << "Hello World" << endl;
cin >> var; // Read a thing up to a space or a \n
getline(cin, var) // Read a line up to a \n

// Main function
int main() {
    return 0;
}
```

## Variable & Data Type

```c++
// Types:
bool: 0 to 1
char: -128; 0 to 127; 255 (if /J option used)
int: ±2147483647
unsigned int: 0 to 4294967295
long long: ±9,223,372,036,854,775,807
unsigned long long: 0 to 18,446,744,073,709,551,615
double
string: unlimited length
void: nothing

// Declare variables:
type name = value;
```

## Functions

```c++
// Functions
// string&: The & means pass in pointer like Java
//          If & doesn't exist, it would copy object
void print(const string& a) {
    cout << a << endl;
}

// Function signature
void print(const string& a);

// Pass by value (Modifying parameter values within 
// the function will not change the original variable)
void passByValue(int a) { a = 0; }

// Pass by reference (Modifying parameter values within
// the function will change the original variable)
void passByReference(int& a) { a = 0; }

int main()
{
    int a = 1;
    passByValue(a);
    // Now a is still 1
    passByReference(a);
    // Now a is 0
}
```

## Conditions

```c++
// Operators:
true && false == false // And
true || false == true // Or
!true == false // Not
1 > 1 == false // Greater than
1 >= 1 == true // Greater equal

// If
if (condition) {
    // Executed when true
}
else if (condition2) {
    // Executed when condition2 is true
}
else {
    // Executed when everthing is false
}

// Switch case
switch (var) {
  case value:
    break;
  default:
    break;
}
```

## Collections

```c++
// Array
int array[] = {1, 2};
int array[length]; // Predefined length

// Nested Array
int array[][] = {{1, 2}, {3, 4}};
int array[r][c]; // Predefined rows cols

// Vectors (aka. array lists)
vector<int> list;
list.emplace_back(1) // .add()
```

## Loops

```c++
// While loop
int i = 0;
while (i < 5) {
    i++; // Check condition first, then execute.
}

// Do while loop
int j = 0;
do { // Execute code first, then check condition.
    j++;
} while(j < 5)

// For loop
for (int k = 0; k < 5; k++) {}

// Nested loop
for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++) {
        // Executes total of 25 times
    }
}
```

## Pointers

```c++
int num = 10; // A memory address (pointer) is stored in this variable
cout << &num; // Access the pointer (0x......)

// Pointer variables
int *pNum = &num; // Stores the pointer (must use the matching data type)
cout << pNum; // Access the pointer (0x......)
cout << *pNum; // Dereference pointer, access stored value.
```

## Class

```c++
// Create class
class Item {
public: // Public fields / functions
    int field;
private: // Private fields / functions
    int field2;
};

// Instantiate (doesn't need new)
Item item;
item.field = 10;
// item.field2 = 10; wouldn't work because private

// Class with constructors
class Item {
private:
    int field2;

public:
    int field;

    // Constructor
    Item(int field, int field2) {
        this->field = field;
        this->field2 = field2;
    }

    // ctor constructor overload
    Item(): Item(1, 3) {}

    // Class functions
    void increment() { field++; }

    // Getter and setters
    int getField2() { return field2; }
    void setField2(int val) { field2 = val; }
};

// Instantiate with constructors
Item2 item2(); // (Same as Item2 item2;)
Item2 item3(0, 10);
```

### Inheritance

```c++
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
```

### Struct

```c++
truct product {
  int weight;
  double price;
}
```