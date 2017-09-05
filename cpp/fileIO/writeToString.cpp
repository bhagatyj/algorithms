#include <sstream>
#include <iostream>
#include <string>

using namespace std;

int main() {

    stringstream outStream;
    string colDelimiter(" : ");
    string rowDelimiter("\n");
    
    if (!outStream) {
        cout << "Could not open input file" << endl;
        exit(-1);
    }

    outStream << "Water" << colDelimiter << 10 << rowDelimiter;
    outStream << "Gasoline" << colDelimiter << 20 << rowDelimiter;
    outStream << "Ethanol" << colDelimiter << 30 << rowDelimiter;
    outStream << "Juice" << colDelimiter << 40 << rowDelimiter;

    cout << outStream.str() << endl;

}
