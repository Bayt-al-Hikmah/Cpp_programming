// Working with Container Adaptors

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main() {
    // Stack: Last In, First Out
    stack<int> history;

    history.push(10);
    history.push(20);
    history.push(30);

    cout << "Stack:\n";

    while (!history.empty()) {
        cout << history.top() << ' ';
        history.pop();
    }

    cout << "\n\n";

    // Queue: First In, First Out
    queue<string> customers;

    customers.push("Ali");
    customers.push("Sara");
    customers.push("Yacine");

    cout << "Queue:\n";

    while (!customers.empty()) {
        cout << customers.front() << ' ';
        customers.pop();
    }

    cout << "\n\n";

    // Priority queue: Largest value first by default
    priority_queue<int> priorities;

    priorities.push(20);
    priorities.push(50);
    priorities.push(10);
    priorities.push(40);

    cout << "Priority queue:\n";

    while (!priorities.empty()) {
        cout << priorities.top() << ' ';
        priorities.pop();
    }

    cout << '\n';

    return 0;
}