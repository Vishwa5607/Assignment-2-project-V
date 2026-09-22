// source.cpp
// Project V: Advanced Software Development Tools
// Assignment #2 - Debugging vs. Release Coding Practice
//
// STAGE 2 (commit after Step #3): read StudentData.txt into a vector.

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

int main()
{
    std::vector<STUDENT_DATA> students;
    loadStandardData("StudentData.txt", students);

    return 0;
}
