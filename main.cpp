#include <algorithm>
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
list<process*> processList,watingList,stopList;
list<process*>::iterator siter;
int Worldtime=0,processID=0,MAX_DEADLINE=0;
int normalizeInput(string temp){
    return stoi(temp.substr(temp.find(":")+1));
}
bool maxDeadline(program* s1, program* s2) {
    return s1->getDeadline() < s2->getDeadline();
}
bool readFile(){
    string filePath,line;
    cout<<"Input your file path:\n";  //home/payne/Os_process_sim/input.txt
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
    if(programList.size()>0){
        //定義最大的DEADLINE,作為程式結束信號
        list<program*>::iterator tmp=max_element(programList.begin(),programList.end(),maxDeadline);
        MAX_DEADLINE=(*tmp)->getDeadline();
        return true;
    }
    else return false;
}
void initialProcess(){
    Worldtime=0;
    processID=0;
    processList.clear();
    for(miter=programList.begin();miter!=programList.end();++miter){
        processList.push_back(new process(*miter,processID++,(*miter)->getTime(),(*miter)->getDeadline()));
    }
}
bool PriorityDesc(process* First, process* Next)
{
    //First Argument Stays First (Return true)
    if (First->getProgram()->getPriority() > 
        Next->getProgram()->getPriority()) 
        return true;
 
    //First Argument goes Next 
    //(Swap) (Return false)
    if (First->getProgram()->getPriority() < 
        Next->getProgram()->getPriority()) 
        return false;
 
    //a==b. First Argument Stays 
    //first (No need to Swap)
    return true;
}
void PriorityScheduling(){
    //程式結束點是週期最長的程式
    int PLlastsize=0;
    bool FLAG_MODIFIED=true,FLAG_IDLEED=false,FLAG_START=true,FLAG_MISSEDDEADLINE=false;
    string currentProcess="";
    cout<<"Start-(Priority-based Scheduling)"<<endl;
    while(Worldtime<MAX_DEADLINE){
        //檢查是否要喚醒程式
        for(siter=watingList.begin();siter!=watingList.end();){
            if((*siter)->getDeadline()<=Worldtime){
                (*siter)->resume();
                processList.push_back(*siter);
                siter=watingList.erase(siter);
                FLAG_MODIFIED=true;
            }else siter++;
        }
        //檢查Miss Deadline
            for(siter=processList.begin();siter!=processList.end();){
                if((*siter)->getDeadline()<=Worldtime){
                    cout<<Worldtime<<endl<<(*siter)->getProgram()->getName()<<" Miss Deadline\n";
                    stopList.push_back(*siter);
                    siter=processList.erase(siter);
                    FLAG_MODIFIED=true;
                    FLAG_MISSEDDEADLINE=true;
                }else siter++;
            }
        //如有可執行程式
        if(processList.size()>0){
            FLAG_IDLEED=false;
            //假如processList變動,代表有人結束或有人執行
            if(FLAG_MODIFIED){
                processList.sort(PriorityDesc);
                PLlastsize=processList.size();
                FLAG_MODIFIED=false;
            }
            //格式化輸出
            if(currentProcess!=processList.front()->getProgram()->getName()){
                if(!FLAG_START&&!FLAG_MISSEDDEADLINE){cout<<Worldtime<<endl;}
                else if(FLAG_MISSEDDEADLINE){FLAG_MISSEDDEADLINE=false;}
                else{FLAG_START=false;}
                cout<<processList.front()->getProgram()->getName()<<" "<<Worldtime<<"-";
                currentProcess=processList.front()->getProgram()->getName();
            }
            switch(processList.front()->execute(Worldtime)){
                case true: //normal execute
                    break;
                case false: //work end
                    watingList.push_back(processList.front());
                    processList.pop_front();
                    FLAG_MODIFIED=true;
                    break;
            }
        }
        else if(!FLAG_IDLEED){
            cout<<Worldtime<<endl<<"idle "<<Worldtime<<"-";
            FLAG_IDLEED=true;
        } 
        Worldtime++;
    }
    cout<<"\rEND                    "<<endl<<"Miss deadline:";
    string missDeadline="NONE";
    if(stopList.size()>0){
        missDeadline="";
        for(siter=stopList.begin();siter!=stopList.end();siter++){
            missDeadline+=(*siter)->getProgram()->getName()+" ";
        }
    }
    cout<<missDeadline<<endl;
}
bool RateAsc(process* First, process* Next)
{
    //First Argument Stays First (Return true)
    if (First->getProgram()->getDeadline() > 
        Next->getProgram()->getDeadline()) 
        return false;
 
    //First Argument goes Next 
    //(Swap) (Return false)
    if (First->getProgram()->getDeadline() < 
        Next->getProgram()->getDeadline()) 
        return true;
 
    //a==b. First Argument Stays 
    //first (No need to Swap)
    return true;
}
int main(){
    if(readFile()){
        initialProcess();
        PriorityScheduling();
    }else{
        cout<<"File I/O failed."<<endl;
    }
    return 0;
}