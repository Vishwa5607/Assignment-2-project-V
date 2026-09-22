// source.cpp
// Project V: Advanced Software Development Tools
// Assignment #2 - Debugging vs. Release Coding Practice

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
};

static std::vector<std::string> splitLine(const std::string& line)
{
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;

    while (std::getline(ss, field, ','))
    {
        fields.push_back(field);
    }
    return fields;
}

static bool loadStandardData(const std::string& path, std::vector<STUDENT_DATA>& students)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> fields = splitLine(line);
        if (fields.size() >= 2)
        {
            STUDENT_DATA student;
            student.firstName = fields[0];
            student.lastName = fields[1];
            students.push_back(student);
        }
    }

    file.close();
    return true;
}

static void printStudents(const std::vector<STUDENT_DATA>& students)
{
    std::cout << "---- Student Data Dump (" << students.size() << " students) ----" << std::endl;
    for (const auto& student : students)
    {
        std::cout << student.firstName << " " << student.lastName << std::endl;
    }
    std::cout << "-----------------------------------------------" << std::endl;
}

int main()
{
    std::vector<STUDENT_DATA> students;

#ifdef PRE_RELEASE
    std::cout << "Running PRE-RELEASE source code." << std::endl;
#else
    std::cout << "Running STANDARD source code." << std::endl;
#endif

    loadStandardData("StudentData.txt", students);

#ifdef _DEBUG
    printStudents(students);
#endif

    std::cin.get();
    return 0;
}
