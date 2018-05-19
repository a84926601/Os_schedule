#ifndef PROGRAM_H
#define PROGRAM_H
#endif // PROGRAM_H

using namespace std;

class program{
public:
    program();
    program(string,int,int,int);
    string getName();
    int getTime();
    int getDeadline();
    int getPriority();
    
private:
    string name;
    int time,deadline,priority;
};