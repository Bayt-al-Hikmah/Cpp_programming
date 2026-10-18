#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Node {
public:
    std::string name;
    std::shared_ptr<Node> child;
    std::weak_ptr<Node> parent;

    explicit Node(std::string nodeName)
        : name(std::move(nodeName)) {
        std::cout << "Constructed: " << name << '\n';
    }

    ~Node() {
        std::cout << "Destroyed: " << name << '\n';
    }
};

bool isExpired(const std::weak_ptr<Node>& reference) {
    return reference.expired();
}

int main() {
    std::weak_ptr<Node> weakRoot;
    std::weak_ptr<Node> weakChild;

    {
        auto root = std::make_shared<Node>("Root");
        auto child = std::make_shared<Node>("Child");

        // The root owns the child.
        root->child = child;

        // The child observes the root without owning it.
        child->parent = root;

        weakRoot = root;
        weakChild = child;

        std::cout << "\n=== Initial state ===\n";

        std::cout << "Root use_count: "
                  << root.use_count() << '\n';

        std::cout << "Child use_count: "
                  << child.use_count() << '\n';

        // Access the parent only after locking the weak_ptr.
        if (auto parent = child->parent.lock()) {
            std::cout << "Child's parent: "
                      << parent->name << '\n';
        } else {
            std::cout << "Parent no longer exists.\n";
        }

        std::cout << "\n=== Reset root ===\n";

        root.reset();

        std::cout << "Root weak reference expired: "
                  << std::boolalpha
                  << isExpired(weakRoot) << '\n';

        // The child still exists because the local shared_ptr
        // named child owns it.
        if (auto remainingChild = weakChild.lock()) {
            std::cout << "Child still exists: "
                      << remainingChild->name << '\n';

            if (auto parent = remainingChild->parent.lock()) {
                std::cout << "Parent still exists: "
                          << parent->name << '\n';
            } else {
                std::cout << "Parent has expired.\n";
            }
        }

        std::cout << "Child use_count: "
                  << child.use_count() << '\n';

        // Remove the root's ownership of the child.
        // The child remains alive because child still owns it.
        // The root has already been destroyed.
    }

    std::cout << "\n=== After leaving scope ===\n";

    std::cout << "Root expired: "
              << isExpired(weakRoot) << '\n';

    std::cout << "Child expired: "
              << isExpired(weakChild) << '\n';

    return 0;
}