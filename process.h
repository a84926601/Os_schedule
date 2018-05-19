#ifndef PROCESS_H
#define PROCESS_H
#endif // PROCESS_H

using namespace std;

class process{
public:
    process();
    process(program);
private:
    program *p;
    int id,work,deadline;
};