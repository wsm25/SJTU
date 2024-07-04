#include "row.h"
#include <cctype>

Row::Row(const std::string& line){
    const char* s=line.c_str(), *p=s;
    // name
    while(isprint(*p) && *p!=' ') p++;
    if(*p!=' ') throw "Invalid input";
    name = std::string(s, p);
    while(*p==' ') p++;
    if(*p==0) throw "Unexpected EOL";
    // id
    s=p;
    while(isdigit(*p) && *p!=' ') p++;
    if(*p!=' ') throw "Invalid input";
    id = std::string(s, p);
    while(*p==' ') p++;
    if(*p==0) throw "Unexpected EOL";
    // score
    s=p;
    while(isdigit(*p) && *p!=' ') p++;
    if(*p!=0 && *p!=' ') throw "Invalid input";
    score=atoi(s);
}

std::ostream& operator<<(std::ostream& os, Row& x){
    return os<<x.name<<'\t'<<x.id<<'\t'<<x.score;
}