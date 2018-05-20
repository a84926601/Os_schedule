#ifndef PROCESS_H
#define PROCESS_H
#endif // PROCESS_H

using namespace std;

class process{
public:
    process();
    process(program*,int,int,int);
    program* getProgram();
    int getID();
    int getWork();
    int getDeadline();
    void resume();
    bool execute(int);
private:
    program *p;
    int id,work,deadline;
};