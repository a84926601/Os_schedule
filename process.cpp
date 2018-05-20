#include <iostream>

#include "program.h"
#include "process.h"

using namespace std;

process::process(){
    p=nullptr;
    id=-1;
    work=-1;
    deadline=-1;
}
process::process(program *_p,int _id,int _work,int _deadline){
    p=_p;
    id=_id;
    work=_work;
    deadline=_deadline;

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
int process::getDeadline(){
    return deadline;
}
void process::resume(){
    deadline+=p->getDeadline();
    work=p->getTime();
    return;
}
void process::show(){
    cout<<p->getName()<<" left:"<<work<<" deadline:"<<deadline<<endl;
}
bool process::execute(int currentTime){
    if(--work<=0){
        //cout<<currentTime<<" clock "<<p->getName()<<" finish"<<endl;
        return false;   //Work end
    }
    //cout<<currentTime<<" clock "<<p->getName()<<endl;
    return true;   //normal execute
}