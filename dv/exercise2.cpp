#include <VExercise2.h>
#include <iostream>
using namespace std;

int main(){
VExercise2 model;
  uint16_t series=0xffff;
  
  

  for(int cycles=0; cycles<100; ++cycles){

    model.init=series;

    model.reset=1;
    model.clk=1;
    model.eval();
    model.clk=0;
    model.eval();
    uint16_t test = ~series;
    
    if(model.out!= test) {cout<<"reset does not work at cycle"<<cycles<<endl;return 1;}


    model.clk=0;
    model.eval();
    model.clk=1;
    model.eval();
    
    if(model.out!= test) {cout<<"model output changed when clk is posedge"<<endl;return 1;}


    model.out=series;
    model.reset=0;
    model.clk=1;
    model.eval();
    model.clk=0;
    model.eval();
    
    uint16_t correct_out=((series <<1) | ((series>>10 &1) ^ (series>>8 &1) ^ (series>>3 &1) ^(series>>1 &1)));
    if(model.out!=correct_out) {cout<<"model wrong ouput"<<
    "  corrected out: "<<(int)correct_out<<"  model out: "<<(int)model.out<<endl; return 1;}

    series=model.out;
   
    model.clk=0;
    model.eval();
    model.clk=1;
    model.eval();
    if(model.out!=correct_out) {cout<<"model change when clk is posedge"<<endl; return 1;}
  }
  cout<<"all tests passed";
  
  return 0;}