#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <fstream>
#include "program.h"
#include "process.h"

using namespace std;

string readFile();
int normalizeInput(string);
list<program*> programList;
list<program*>::iterator iter;

int main(){
    readFile();
    return 0;
}

string readFile(){
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
        //cout<<iter->getName()<<" "<<iter->getTime()<<" "<<iter->getDeadline()<<" "<<iter->getPriority()<<endl;
        /*programList.push(process(tmpname,tempwork));
        programCount++;*/
    }
}
int normalizeInput(string temp){
    return stoi(temp.substr(temp.find(":")+1));
}