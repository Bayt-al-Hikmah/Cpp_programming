#include <iostream>
#include <queue>
#include <stack>
#include <string>

int main(){
    std::queue<std::string> tasks;
    std::stack<std::string> completed;
    int choice;
    std::string task;

    do{
        std::cout << "\n--- Task Manager ---\n";
        std::cout << "1. Add a task\n";
        std::cout << "2. Process a task\n";
        std::cout << "3. Show the most recently completed task\n";
        std::cout << "4. Show pending tasks count\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        std::cin >> choice;

        switch (choice){
            case 1:
                std::cout << "Enter task name: ";
                std::cin >> task;

                tasks.push(task);
                std::cout << "Task added.\n";
                break;

            case 2:
                if (!tasks.empty()){
                    task = tasks.front();
                    tasks.pop();

                    completed.push(task);

                    std::cout << "Processed task: " << task << '\n';
                } else {
                    std::cout << "No pending tasks.\n";
                }
                break;

            case 3:
                if (!completed.empty()){
                    std::cout << "Last completed task: " << completed.top() << '\n';
                } else {
                    std::cout << "No completed tasks.\n";
                }
                break;

            case 4:
                std::cout << "Pending tasks: " << tasks.size() << '\n';
                break;

            case 0:
                std::cout << "Exiting task manager.\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}