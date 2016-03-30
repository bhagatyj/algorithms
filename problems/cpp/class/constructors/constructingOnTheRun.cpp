#include <iostream>

using namespace std;

class MyClass {
    protected:
        int value;

    public:
        MyClass(void);
        MyClass(int x);
        friend std::ostream& operator<< ( std::ostream& stream, const MyClass& m) {
            stream << m.value;
            return stream;
        }
};

MyClass::MyClass( void ) {
    value = 0;
}

MyClass::MyClass( int x ) {
    value = x;
}

int main (int argc, char **argv) {

    // The MyClass constructor is used to automatically construct
    // a MyClass object. This is possible because the constructor
    // has not been declared as "explicit". Hence implicit construction
    // is allowed.
    MyClass x = 2;
    cout << x;

}
