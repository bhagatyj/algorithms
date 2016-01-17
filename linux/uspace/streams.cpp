#include <iostream>

using namespace std;
int main (int argc, char **argv) {
    FILE *fp;

    close( fileno( stdout ) );
    fp = fopen( "/tmp/test.log", "w" );
    cout << "Through stdout: Hello World" << endl;

    close( fileno(stderr) );
    dup2( fileno(stdout), fileno(stderr) );
    cerr << "Through stderr: Hello World" << endl;

    fclose( fp );
}
