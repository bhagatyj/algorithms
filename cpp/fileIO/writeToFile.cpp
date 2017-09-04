#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {

    ofstream outFile("/tmp/shoppingList.txt");
    string colDelimiter(" : ");
    string rowDelimiter("\n");
    
    if (!outFile) {
        cout << "Could not open input file" << endl;
        exit(-1);
    }

    outFile << "Water" << colDelimiter << 10 << rowDelimiter;
    outFile << "Gasoline" << colDelimiter << 20 << rowDelimiter;
    outFile << "Ethanol" << colDelimiter << 30 << rowDelimiter;
    outFile << "Juice" << colDelimiter << 40 << rowDelimiter;

}
