// Shared Ownership with shared_ptr

#include <iostream>
#include <memory>
using namespace std;

int main() {

    // Create an object with shared ownership
    auto firstOwner = make_shared<int>(100);

    cout << "Initial value: " << *firstOwner << '\n';

    cout << "Number of owners: "
         << firstOwner.use_count() << '\n';

    {
        // Create another owner
        auto secondOwner = firstOwner;

        cout << "\nInside the scope:\n";

        cout << "Number of owners: "
             << firstOwner.use_count() << '\n';

        // Both pointers refer to the same object
        *secondOwner = 250;

        cout << "Value through firstOwner: "
             << *firstOwner << '\n';

        cout << "Value through secondOwner: "
             << *secondOwner << '\n';
    }

    // secondOwner has been destroyed
    cout << "\nOutside the scope:\n";

    cout << "Number of owners: "
         << firstOwner.use_count() << '\n';

    cout << "Final value: " << *firstOwner << '\n';

    return 0;
}