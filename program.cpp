#include <string>

#include "program.h"

using namespace std;

program::program(){
    name="null";
    time=0;
    deadline=0;
    priority=0;
}
program::program(string _name,int _time,int _deadline,int _priority){
    name=_name;
    time=_time;
    deadline=_deadline;
    priority=_priority;
}
string program::getName(){
    return name;
}
int program::getTime(){
    return time;
}
int program::getDeadline(){
    return deadline;
}
int program::getPriority(){
    return priority;
}