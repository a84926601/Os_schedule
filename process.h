#ifndef PROCESS_H
#define PROCESS_H
#endif // PROCESS_H

using namespace std;

class process{
public:
    process();
    process(program*,int,int);
    program* getProgram();
    int getID();
    int getWork();
private:
    program *p;
    int id,work;
};