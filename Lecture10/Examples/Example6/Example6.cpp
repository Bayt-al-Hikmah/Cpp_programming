// Observing Objects with weak_ptr

#include <iostream>
#include <memory>
#include <string>
using namespace std;

int main() {

    // Declare a weak observer
    weak_ptr<string> observer;

    {
        // Create a shared object
        auto owner = make_shared<string>("Temperature Sensor");

        // Observe the object without owning it
        observer = owner;

        cout << "Inside the scope:\n";

        cout << "Weak pointer expired: "
             << boolalpha << observer.expired() << '\n';

        // Obtain temporary shared ownership
        if (auto temporaryOwner = observer.lock()) {
            cout << "Object is alive: "
                 << *temporaryOwner << '\n';
        }

        cout << "Strong owners: "
             << owner.use_count() << '\n';
    }

    // The last strong owner has been destroyed
    cout << "\nOutside the scope:\n";

    cout << "Weak pointer expired: "
         << observer.expired() << '\n';

    // Safely attempt to access the object
    if (auto temporaryOwner = observer.lock()) {
        cout << "Object: " << *temporaryOwner << '\n';
    } else {
        cout << "The object no longer exists.\n";
    }

    return 0;
}