#include <iostream>
#include "Transaction.h"
#include "User.h"
#include "Account.h"
#include <time.h>

int main() {
    int n=10;
    std::string repo= "report";
    repo.append("gino");
    repo.append(".txt");
    std::string s="six";
    User *u;
    int count=0;
    u=new User("gino","ciao","st");
    std::ofstream file (repo,std::ios::app);
    file << s <<std::endl;
    file.close();
    char c;
    std::ifstream read(repo);
    while(read.get(c))
        std::cout <<c ;
    read.close();


    return 0;

}
