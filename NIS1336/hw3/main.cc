#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "row.h"

// case insensitive compare
int icmp(const std::string& lhs, const std::string& rhs){
    size_t len = lhs.size()<rhs.size()?lhs.size():rhs.size();
    for(size_t i=0; i<len; i++){
        char l=tolower(lhs[i]), r=tolower(rhs[i]);
        if(l<r) return -1;
        if(l>r) return 1;
    }
    if(lhs.size()<rhs.size()) return -1;
    if(lhs.size()>rhs.size()) return 1;
    return 0;
}

int main(int argc, char* argv[]){
    if(argc!=2 || std::string("-h")==argv[1]){
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
        printf("Error: file `%s` does not exist!\n", argv[1]);
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
            return -1;
        }
        if(icmp(line,"quit")==0) {
            puts("Quit");
            return 0;
        }
        else if(icmp(line,"showAll")==0){
            std::cout<<"Name"<<'\t'<<"Student ID"<<'\t'<<"Score"<<'\n';
            for(auto &x:table)
                std::cout<<x<<'\n';
        }
        else if(icmp(line,"showMax")==0){
            std::cout<<"Highest score owner: \n";
            std::cout<<"Name"<<'\t'<<"Student ID"<<'\t'<<"Score"<<'\n';
            std::cout<<highest<<'\n';
        }
        else if(icmp(line,"showAve")==0){
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