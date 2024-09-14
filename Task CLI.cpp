#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

// Data structure to store a task
struct Task {
    int id;
    std::string title;
    std::string description;
    std::string dueDate;  // Due date (YYYY-MM-DD)
    int priority;
    bool isCompleted;
};

// Function to display the menu
void displayMenu() {
    std::cout << "=== Task Manager ===" << std::endl;
    std::cout << "1. Add a new task" << std::endl;
    std::cout << "2. View all tasks" << std::endl;
    std::cout << "3. Mark a task as completed" << std::endl;
    std::cout << "4. Delete a task" << std::endl;
    std::cout << "5. Save and quit" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to add a new task
void addTask(std::vector<Task>& tasks) {
    Task newTask;
    newTask.id = tasks.size() + 1;

    std::cout << "Task title: ";
    std::cin.ignore();
    std::getline(std::cin, newTask.title);

    std::cout << "Task description: ";
    std::getline(std::cin, newTask.description);

    std::cout << "Due date (YYYY-MM-DD): ";
    std::getline(std::cin, newTask.dueDate);

    std::cout << "Priority (1 to 5): ";
    std::cin >> newTask.priority;

    newTask.isCompleted = false;
    tasks.push_back(newTask);

    std::cout << "Task successfully added!" << std::endl;
}

// Function to display all tasks
void displayTasks(const std::vector<Task>& tasks) {
    std::cout << "\n=== Task List ===\n";
    for (const auto& task : tasks) {
        std::cout << "ID: " << task.id << "\n"
                  << "Title: " << task.title << "\n"
                  << "Description: " << task.description << "\n"
                  << "Due Date: " << task.dueDate << "\n"
                  << "Priority: " << task.priority << "\n"
                  << "Status: " << (task.isCompleted ? "Completed" : "Not Completed") << "\n"
                  << "--------------------------" << std::endl;
    }
}

// Function to mark a task as completed
void markAsCompleted(std::vector<Task>& tasks) {
    int id;
    std::cout << "Enter the ID of the task to mark as completed: ";
    std::cin >> id;

    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& t) { return t.id == id; });
    if (it != tasks.end()) {
        it->isCompleted = true;
        std::cout << "Task marked as completed!" << std::endl;
    } else {
        std::cout << "Task not found!" << std::endl;
    }
}

// Function to delete a task
void deleteTask(std::vector<Task>& tasks) {
    int id;
    std::cout << "Enter the ID of the task to delete: ";
    std::cin >> id;

    auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& t) { return t.id == id; });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        std::cout << "Task deleted!" << std::endl;
    } else {
        std::cout << "Task not found!" << std::endl;
    }
}

// Function to save tasks to a file
void saveTasks(const std::vector<Task>& tasks, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task.id << ","
                 << task.title << ","
                 << task.description << ","
                 << task.dueDate << ","
                 << task.priority << ","
                 << task.isCompleted << std::endl;
        }
        file.close();
        std::cout << "Tasks saved to " << filename << "!" << std::endl;
    } else {
        std::cout << "Error opening the file for saving." << std::endl;
    }
}

// Function to load tasks from a file
void loadTasks(std::vector<Task>& tasks, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Task task;
            std::stringstream ss(line);
            std::string temp;

            std::getline(ss, temp, ',');
            task.id = std::stoi(temp);

            std::getline(ss, task.title, ',');
            std::getline(ss, task.description, ',');
            std::getline(ss, task.dueDate, ',');

            std::getline(ss, temp, ',');
            task.priority = std::stoi(temp);

            std::getline(ss, temp, ',');
            task.isCompleted = std::stoi(temp);

            tasks.push_back(task);
        }
        file.close();
    }
}

int main() {
    std::vector<Task> tasks;
    std::string filename = "tasks.txt";

    // Load tasks from the file on startup
    loadTasks(tasks, filename);

    bool quit = false;
    while (!quit) {
        displayMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                displayTasks(tasks);
                break;
            case 3:
                markAsCompleted(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                saveTasks(tasks, filename);
                quit = true;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }

    return 0;
}
