#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

vector<string> tasks;

void showNotification(const string& message) {
    MessageBox(NULL, message.c_str(), "CodeLog Notification", MB_OK | MB_ICONINFORMATION);
}

void loadTasks() {
    ifstream file("tasks.txt");
    tasks.clear();
    string line;
    while (getline(file, line)) {
        if (!line.empty())
            tasks.push_back(line);
    }
    file.close();
}

void saveTasks() {
    ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << task << endl;
    }
    file.close();
}

void addTask() {
    cout << "Enter new task: ";
    string task;
    getline(cin, task);
    if (task.empty()) {
        cout << "Task cannot be empty.\n";
        return;
    }
    tasks.push_back(task);
    saveTasks();
    showNotification("Task added: " + task);
    cout << "Task added successfully.\n";
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }
    cout << "\nYour Tasks:\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i] << endl;
    }
    cout << endl;
}

void deleteTask() {
    if (tasks.empty()) {
        cout << "No tasks to delete.\n";
        return;
    }
    viewTasks();
    cout << "Enter task number to delete: ";
    int num;
    cin >> num;
    cin.ignore();
    if (num < 1 || num > (int)tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }
    string removedTask = tasks[num - 1];
    tasks.erase(tasks.begin() + num - 1);
    saveTasks();
    cout << "Deleted task: " << removedTask << endl;
}

void showMenu() {
    cout << "==== CodeLog To-Do List ====\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Delete Task\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    loadTasks();
    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                cout << "Exiting CodeLog. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
