#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

// -------        ------------------------
// | head |      | tag1                  |
// | NULL | <--- | <ptr to head>         |
// |      |      |                       |
// |      |      | value --> HelloWorld  |
// |      |      |                       |
// | tag1 | ---> | tag2                  | ---->
// --------      -------------------------
class Tag {
    string __name;
    class Tag *__parent;
    map<string, string> attr;
    map<string, class Tag*> tags;

    public:
    Tag() {
    }

    Tag( string name, class Tag *parent ) {
        __name = name;
        __parent = parent;
    }

    void add_attribute( string key, string value) {
        attr[key] = value;
    }
    void add_tag( string key, class Tag *value) {
        tags[key] = value;
    }
    
    class Tag * parseLine( string line) {
        if ( line[1] == '/' ) {
            return __parent;
        }
        int spacePos = line.find(' ');
        string token = line.substr(1, spacePos-1 );
        if ( token == __name ) {
            // Add attribute
            line.erase(0, spacePos+1);
            spacePos = line.find(' ');
            string attribute = line.substr(0, spacePos);
            line.erase(0, spacePos+1);
            spacePos = line.find(' ');
            line.erase(0, spacePos+2);
            spacePos = line.find('"');
            string value = line.substr(0, spacePos);
            // cout << "Adding attribute: " << attribute 
                 // << " --> " << value << " to " << __name << endl;
            add_attribute( attribute, value );
        } else {
            class Tag *newTag = new Tag(token, this);
            add_tag( token, newTag);
            // cout << "Adding tag:" << token << ": in " << __name << endl;
            return newTag->parseLine( line );
        }
        return this;
    }

    void getValue( string line ) {
        // cout << "Processing getValue for " << line << "in " << __name << endl;
        int tildePos = line.find('~');
        if ( tildePos != -1 ) {
            // Do we need to go to a child ?
            int dotPos = line.find('.');
            if ( dotPos != -1 ) {
                string child = line.substr(0, dotPos);
                line = line.substr(dotPos+1);
                // cout << "Going to child:" << child << ":" << endl;
                if ( tags.find( child ) != tags.end() ) {
                    // cout << "Found child " << child << endl;
                    tags[child]->getValue(line);
                    return;
                } else {
                    cout << "Not Found!" << endl;
                }
            } else {
                string child = line.substr(0, tildePos);
                line = line.substr(tildePos+1);
                // cout << "Going to child:" << child << ":" << endl;
                if ( tags.find( child ) != tags.end() ) {
                    // cout << "Found child " << child << endl;
                    tags[child]->getValue(line);
                    return;
                } else {
                    cout << "Not Found!" << endl;
                }
            }
        } else {
            // cout << "Finding " << line << " in " << __name << endl;
            if ( attr.find( line ) != attr.end() ) {
                cout << attr[line] << endl;
            } else {
                cout << "Not Found!" << endl;
            }
        }
    }

};

map<string, class Tag> head;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int c1, c2, i;
    string line;
    class Tag *tag, head("head", NULL);

    cin >> c1 >> c2;
    // For discarding the 1st line
    getline(cin, line);
    tag = &head;
    for (i=0; i<c1; i++) {
        getline(cin, line);
        tag = tag->parseLine(line);
    }
    for (i=0; i<c2; i++) {
        getline(cin, line);
        head.getValue(line);
    }
    return 0;
}


