#include <string>

#include "program.h"
#include "process.h"

using namespace std;

process::process(){
    p=nullptr;
    id=-1;
    work=-1;
}
process::process(program *_p,int _id,int _work){
    p=_p;
    id=_id;
    work=_work;
}
program* process::getProgram(){
    return p;
}
int process::getID(){
    return id;
}
int process::getWork(){
    return work;
}