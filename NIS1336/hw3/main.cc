#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

struct Row{
    std::string name;
    std::string id;
    int score;
public:
    Row(const std::string& line){
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
    friend std::ostream& operator<<(std::ostream& os, Row& x){
        return os<<x.name<<'\t'<<x.id<<'\t'<<x.score;
    }
};

int main(int argc, char* argv[]){
    if(argc!=2 || strcmp(argv[1], "-h")==0){
        printf(
            "Usage: %s [file] | [-h]\n"
            "Arguments:\n"
            "    file:   load scores from `file`\n"
            "    -h:     show manual\n",
            argv[0]
        );
        return 0;
    }
    std::ifstream file(argv[1]);
    if(file.fail()){
        printf("Error: file `%s` does not exist!", argv[1]);
        return -1;
    }
    std::string line;
    std::vector<Row> table;
    int rows=0;
    while(std::getline(file, line)){
        try {table.push_back(Row(line));}
        catch(...) {
            puts("Error: invalid file input! exiting...");
            return -1;
        }
        rows++;
    }
    printf("Load %d rows from file `%s`\n", rows, argv[1]);
    // sort by name
    std::sort(table.begin(), table.end(), 
        [](const Row& lhs, const Row& rhs)->bool{
            return lhs.id<rhs.id;
        }
    );
    // highest guy
    Row& highest=*std::max_element(table.begin(), table.end(), 
        [](const Row& lhs, const Row& rhs)->bool{return lhs.score<rhs.score;}
    );
    // average
    double avg=0;
    for(auto& x:table) avg+=x.score;
    avg/=table.size();
    // shell loop
    for(;;){
        printf("ScoreManager> ");
        if(!std::getline(std::cin, line)) {
            puts("EOF");
            return 0;
        }
        if(line=="quit") {
            puts("Quit");
            return 0;
        }
        else if(line=="showAll"){
            std::cout<<"Name"<<'\t'<<"Student ID"<<'\t'<<"Score"<<'\n';
            for(auto &x:table)
                std::cout<<x<<'\n';
        }
        else if(line=="showMax"){
            std::cout<<"Highest score owner: \n";
            std::cout<<"Name"<<'\t'<<"Student ID"<<'\t'<<"Score"<<'\n';
            std::cout<<highest<<'\n';
        }
        else if(line=="showAve"){
            std::cout<<"Average score: "<<avg<<"\n";
        }
        else {
            std::cout<<"Invalid command. Supported command: \n"
                       "    showAll     show all information in order of student id\n"
                       "    showAve     show average score\n"
                       "    showMax     show information of the highest score owner\n"
                       "    quit        exit the shell\n";
        }
    }
}