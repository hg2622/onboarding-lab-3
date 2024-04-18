#include <VExercise4.h>
#include <iostream>
#include <random>

using namespace std;


uint8_t select(uint8_t a, uint8_t b,uint8_t c, int cs, int sel){
  if(!cs){
    return 0;
  }
  else {
    switch(sel){
      case 0: return a;
      case 1: return b;
      case 2: return c;
      default: return a & (b|c);
    }
  }
}
int main() {
  VExercise4 model;
 std::default_random_engine re {std::random_device {}()};
 std::uniform_int_distribution<uint8_t> rand8;
  uint8_t a = 5;
uint8_t b = 6;
uint8_t c= 7;
  model.gamma = c;
  model.alpha = a;
  model.beta = b;




for (int i=0; i<20; i++){

  model.cs=1;
   model.sel=i;
  model.eval();
 
  if(model.out!= select(a,b,c,1,i)){
    cout<<i<<endl;
    cout<<"wrong output for cs=1"<<endl;
    cout<<"model output: "<<(int)model.out<<endl;
    cout<<" expected: "<< (int) select(a,b,c,1,i);
    return 1;
  }

  model.cs=0;
  model.eval();
  if(model.out!= select(a,b,c,0,i)){
    cout<<"wrong output for cs=0"<<endl;
     cout<<"model output: "<<(int)model.out<<endl;
    cout<<" expected"<<(int) select(a,b,c,0,i);
    return 1;
  }

}
  cout<<"all test passed"<<endl;
  return 0;


}
