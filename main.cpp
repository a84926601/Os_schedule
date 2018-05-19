#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <fstream>
#include "program.h"
#include "process.h"

using namespace std;

list<program*> programList;
list<program*>::iterator miter;
list<process*> processList;
list<process*>::iterator siter;
bool readFile();
int normalizeInput(string);
void initialProcess();
int processID=0;

int main(){
    if(readFile()){
        initialProcess();
    }else{
        cout<<"File I/O failed."<<endl;
    }
    return 0;
}
int normalizeInput(string temp){
    return stoi(temp.substr(temp.find(":")+1));
}
bool readFile(){
    string filePath,line;
    cout<<"Input your file path:";  //home/payne/Os_process_sim/input.txt
    filePath="input2.txt";
    //cin>>filePath;
    ifstream processData(filePath, ios_base::in);
    //Push program to ram
    while(getline(processData, line)){
        string tmpName,temp;
        int tempTime,tempDeadline,tempPriority;
        istringstream iss(line);
        //取得輸入
        iss>>tmpName;
        iss>>temp;
        tempTime=normalizeInput(temp);
        iss>>temp;
        tempDeadline=normalizeInput(temp);
        iss>>temp;
        tempPriority=normalizeInput(temp);

        programList.push_back(new program(tmpName,tempTime,tempDeadline,tempPriority));
        //cout<<programList.front()->getName()<<endl;
        //cout<<iter->getName()<<" "<<iter->getTime()<<" "<<iter->getDeadline()<<" "<<iter->getPriority()<<endl;
    }
    if(programList.size()>0){return true;}
        else return false;
}
void initialProcess(){
    for(miter=programList.begin();miter!=programList.end();++miter){
        processList.push_back(new process(*miter,processID++,(*miter)->getTime()));
    }
}