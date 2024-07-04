#ifndef ROW_H
#define ROW_H
#include <string>
#include <iostream>

struct Row{
    std::string name;
    std::string id;
    int score;
public:
    Row(const std::string& line);
};

std::ostream& operator<<(std::ostream& os, Row& x);
#endif // ROW_H