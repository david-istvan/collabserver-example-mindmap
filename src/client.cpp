#include <iostream>

#include "mindmap/Mindmap.h"

using namespace std;

int main() {
    /**
     *  Command format:
     *  * CREATE [type] [name]
     *  * READ
     *  * UPDATE [name] [property] [value]
     *  * DELETE [name]
     */
    string command;
    string operation;
    string args;
    string type;
    string name;
    string property;
    string value;

    do {
        getline(cin, command);

        std::string::size_type pos;
        pos = command.find(' ', 0);

        operation = command.substr(0, pos);
        args = command.substr(pos + 1);

        if (operation == "create") {
            pos = args.find(' ', 0);
            type = args.substr(0, pos);
            args = args.substr(pos + 1);

            pos = args.find(' ', 0);
            name = args.substr(0, pos);

            cout << "...creation of " << name << " of type " << type << endl;
        } else if (operation == "read") {
            cout << "...reading mindmap" << endl;
        } else if (operation == "update") {
            pos = args.find(' ', 0);
            name = args.substr(0, pos);
            args = args.substr(pos + 1);

            pos = args.find(' ', 0);
            property = args.substr(0, pos);
            args = args.substr(pos + 1);

            pos = args.find(' ', 0);
            value = args.substr(0, pos);

            cout << "...updating property " << property << " in " << name << " to value " << value << endl;
        } else if (operation == "delete") {
            pos = args.find(' ', 0);
            name = args.substr(0, pos);

            cout << "...deleting " << name << endl;
        } else {
            cout << "unknown command\n";
        }
    } while (true);

    return 0;
}