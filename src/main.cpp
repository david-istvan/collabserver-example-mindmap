#include <iostream>
#include <string>

#include "mindmap/Mindmap.h"
#include "modeling/Document.h"

using namespace std;

int main() {
    unsigned int userLocalID = 42;  // A random ID for test (given by the server in real situation)
    Document document(userLocalID);

    Node& node1 = document.addNode("type", "Marker");
    node1.setAttribute("name", "m1");
    node1.setAttribute("isComposite", "true");

    Node& node2 = document.addNode("type", "Model");
    node2.setAttribute("name", "m2");
    node2.setAttribute("isComposite", "false");
    node2.removeAttribute("isComposite");

    string node1_type = node1.getAttribute("type");
    string node2_type = node2.getAttribute("type");

#if 0
    // TODO Temporary commented
    // For now, the mindmap implementation is on hold (work on the modeling document instead)

    /**
     *  Command format:
     *  * CREATE [logicalTypeName] [domainTypeName] [name]
     *  * READ
     *  * UPDATE [name] [property] [value]
     *  * DELETE [name]
     */
    string command;
    string operation;
    string args;
    string what;
    string logicalTypeName;
    string domainTypeName;
    string name;
    string name2;
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
            what = args.substr(0, pos);
            args = args.substr(pos + 1);

            if (what == "association") {
                pos = args.find(' ', 0);
                domainTypeName = args.substr(0, pos);
                args = args.substr(pos + 1);

                pos = args.find(' ', 0);
                name = args.substr(0, pos);
                args = args.substr(pos + 1);

                pos = args.find(' ', 0);
                name2 = args.substr(0, pos);

                cout << "...creation of association  of type " << domainTypeName << " between " << name << " and "
                     << name2 << endl;
            } else {
                domainTypeName = what;

                pos = args.find(' ', 0);
                name = args.substr(0, pos);
                args = args.substr(pos + 1);

                cout << "...creation of entity of type " << domainTypeName << " named " << name << endl;
            }
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

#endif

    return 0;
}