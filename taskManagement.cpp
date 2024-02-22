//Task management app

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <conio.h>
#include <fstream>

class Task
{
    private:
        std::string title;
        std::string description;
        std::string dueDate;
        std::string priority;
        std::string status;

    public:
        Task(){}
        Task(std::string title, std::string description, std::string dueDate, std::string priority)
        {
            this->title = title;
            this->description = description;
            this->dueDate = dueDate;
            this->priority = priority;
            this->status = "Not Completed";
        }

        friend class App;
};

class App
{
    private:
        std::vector<Task> tasks;
    public:
        App()
        {
            std::cout << "\033[2J;\033[0;0H";
            std::cout << "--------------------" << std::endl;
            std::cout << "| TASK MANAGER APP |" << std::endl;
            std::cout << "--------------------" << std::endl;
        }

        void getTasks()
        {
            std::ifstream file("tasks.txt");
            
            if (file.peek() == std::ifstream::traits_type::eof())
            {
                return;
            }

            while(!file.eof())
            {
                Task temp;
                std::getline(file, temp.title);
                if(temp.title.empty())
                {
                    return;
                }
                std::getline(file, temp.description);
                std::getline(file, temp.dueDate);
                std::getline(file, temp.priority);
                std::getline(file, temp.status);
                tasks.push_back(temp);
            }
            file.close();
        }

       
        void displayMenu()
        {
            std::cout << "\033[4;0H\033[J";
            std::cout << "------" << std::endl;
            std::cout << "|MENU|" << std::endl;
            std::cout << "------" << std::endl;
            std::cout << "1. Add task" << std::endl;
            std::cout << "2. List tasks" << std::endl;
            std::cout << "3. Mark task as completed" << std::endl;
            std::cout << "4. Delete task" << std::endl;
            std::cout << "5. Exit" << std::endl;
        }

        void addTask()
        {
            std::cout << "\033[4;0H\033[J";
            std::cout << "----------" << std::endl;
            std::cout << "|ADD TASK|" << std::endl;
            std::cout << "----------" << std::endl;
            std::string title;
            std::string description;
            std::string dueDate;
            char priorityMark;
            std::string priority;

            std::cout << "Enter the title of the task: " << std::endl;
            std::getline(std::cin, title);
            std::cout << "Enter the description of the task: " << std::endl;
            std::getline(std::cin, description);
            std::cout << "Enter the due date of task: " << std::endl; 
            std::getline(std::cin, dueDate);
            std::cout << "Enter the priority of the task[high[h]/ medium[m]/ low[l]]: " << std::endl; 
            std::cin >> priorityMark;
            getchar();
            if (priorityMark == 'h' || priorityMark == 'H') priority = "High Priority";
            else if (priorityMark == 'm' || priorityMark == 'M') priority = "Medium Priority";
            else if (priorityMark == 'l' || priorityMark == 'L') priority = "Low Priority";
            else 
            {
                std::cout << "Please enter a valid option[high[h]/ medium[m]/ low[l]]" << std::endl;
            }
            Task newTask = Task(title, description, dueDate, priority);
            tasks.push_back(newTask);
            std::cout << "Task has been added successfully!" << std::endl;
            std::cout << "Press any key to continue.." << std::endl;
            getch();
        }

        void listTasks()
        {
            int i = 1;
            std::cout << "\033[4;0H\033[J";
            std::cout << "-----------" << std::endl;
            std::cout << "|TASK LIST|" << std::endl;
            std::cout << "-----------" << std::endl;
            if (tasks.empty())
            {
                std::cout << "No tasks found, please add some tasks.";
            }
            for(const auto& task: tasks)
            {
                std::cout << i << ". " << task.title << " (" << task.priority << ")" << std::endl;
                std::cout << "   Description: " << task.description << std::endl;
                std::cout << "   Due Date: " << task.dueDate << std::endl;
                std::cout << "   Status: " << task.status << std::endl;
                std::cout << "\n";
                i++;
            }
            std::cout << "Press any key to continue...";
            getch();
        }

        void markTaskAsCompleted()
        {
            std::cout << "\033[4;0H\033[J";
            std::cout << "------------------------" << std::endl;
            std::cout << "|MARK TASK AS COMPLETED|" << std::endl;
            std::cout << "------------------------" << std::endl;
            int taskNumber;
            std::cout << "Enter the task number: ";
            std::cin >> taskNumber;
            tasks[taskNumber - 1].status = "Completed";
            std::cout << "Task status updated!" << std::endl;
            std::cout << "Press any key to continue...";
            getch();
        }
        
        void deleteTask()
        {
            std::cout << "\033[4;0H\033[J";
            std::cout << "-------------" << std::endl;
            std::cout << "|DELETE TASK|" << std::endl;
            std::cout << "-------------" << std::endl;
            int taskNumber;
            std::cout << "Enter the task number: ";
            std::cin >> taskNumber;
            tasks.erase(tasks.begin() + taskNumber - 1);
            std::cout << "Task deleted successfully!" << std::endl;
            std::cout << "Press any key to continue...";
            getch();
        }

        void updateFile()
        {
            std::ofstream file("tasks.txt");
            for(auto& task: tasks)
            {
                file << task.title << std::endl;
                file << task.description << std::endl;
                file << task.dueDate << std::endl;
                file << task.priority << std::endl;
                file << task.status << std::endl;
            }
            file.close();
        }
};

int main()
{
    App taskApp;
    taskApp.getTasks();
    int choice;
    while (true)
    {
        taskApp.displayMenu();
        std::cout << "Enter your choice: "; 
        std::cin >> choice; 
        getchar();
        if (choice == 1)
        {
            taskApp.addTask();
        }
        else if (choice == 2)
        {
            taskApp.listTasks();
        }
        else if (choice == 3)
        {
            taskApp.markTaskAsCompleted();
        }
        else if (choice == 4)
        {
            taskApp.deleteTask();
        }
        else if (choice == 5)
        {
            char choice;
            std::cout << "Are you sure you want to exit? [Yes[Y]/No[any key]]: "; 
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y')
                break;
            getchar(); // consume newline character
        }
        else 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Please enter a valid choice [1 - 5]: ";
        }
    }
    taskApp.updateFile();

    return 0;
}