#include <iostream>
#include <string>
#include <stack>

using namespace std;

// The procedure is very simple once you start using a stack.
// It is important to identify and check for all the error
// conditions.
bool 
isValid(string input) {
    stack<char> paraStack;
    char d;
    
    for( char &c : input ) {

        switch( c ) {
            case '(' :
            case '[' :
            case '{' :
                paraStack.push(c);
                break;
            case ')' :
            case ']' :
            case '}' :
                if( not paraStack.empty() ) {
                    d = paraStack.top();
                    paraStack.pop();
                    if( (( d == '{' ) && ( c == '}' )) ||
                        (( d == '[' ) && ( c == ']' )) ||
                        (( d == '(' ) && ( c == ')' )) ) {
                        continue;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
                break;
            default:
                break;
        }

    }

    if( paraStack.empty() ) {
        return true; 
    } else {
        return false;
    }
}

int 
main() {

	cout <<  isValid(string ("((((())))){{{{}}}}" ) ) << endl ;
	cout <<  isValid(string ("((((())))){{{}}}}" ) ) << endl ;
	cout <<  isValid(string ("(((((" ) ) << endl ;
	cout <<  isValid(string (")" ) ) << endl ;
}
