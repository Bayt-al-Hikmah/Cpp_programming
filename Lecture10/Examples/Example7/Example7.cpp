// Parent-Child Relationships

#include <iostream>
#include <memory>
#include <string>
#include <utility>
using namespace std;

class Node {
public:
    string name;

    // Strong ownership of the child
    shared_ptr<Node> child;

    // Non-owning observation of the parent
    weak_ptr<Node> parent;

    explicit Node(string nodeName)
        : name(move(nodeName)) {}

    ~Node() {
        cout << "Destroying: " << name << '\n';
    }
};

int main() {

    auto root = make_shared<Node>("Root");
    auto child = make_shared<Node>("Child");

    // Root owns the child
    root->child = child;

    // Child observes the root
    child->parent = root;

    cout << "Root owners: "
         << root.use_count() << '\n';

    cout << "Child owners: "
         << child.use_count() << '\n';

    // Access the parent safely
    if (auto parent = child->parent.lock()) {
        cout << child->name
             << " belongs to "
             << parent->name << '\n';
    }

    cout << "\nResetting root and external child pointers...\n";

    // Remove both external strong owners
    root.reset();
    child.reset();

    cout << "External pointers have been reset.\n";

    return 0;
}