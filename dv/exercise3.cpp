#include <VExercise3.h>
#include <iostream>
#include <random>

using namespace std;

uint8_t mystery1(uint8_t a, uint8_t b, uint8_t c) {
  switch(a) {
    case 0:
      return (a<<6 | (b&7)<<3 | (c&7));
    case 1:
      return  (a<<6 | ((7 & c)<<3) | (7 & b));
    case 2:
      return b;
    default:
      return c;
  }
}

int reduction_op(uint16_t in){
  int sum=0;
  for (int i=0; i<16; i++){
  sum+= (in>>i)&1;
  }
  return sum%2;
}

struct mystery2{
  int reset;
  int count=0;
  uint16_t state;

  uint16_t step(uint8_t x, uint8_t y, int reset){


    if (reset){
      count=0;
      return state = y<<8 | x;
    }
  else {
    
  switch((count++)%5) {
      case 0:
        return state = (x)<<8 | (state & 0xFF); 
      case 1:
        return state = (((state >>8)& 0xff) << 8) | y; 
      case 2:
        return state = (state << 8) | (state >> 8);
      case 3:
        return state = (state << 12) | ((state>>4)&15)<<8 | ((state>>8)&15)<<4| (state>>12);
      case 4:
    return state=  reduction_op(state);

  }
  

  }}
};


struct Excercise3Sim {
  mystery2 state;

  uint16_t reset(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in ={mystery1(a & 0x3, b & 0xFF, c & 0xFF)};
    uint8_t b_in ={mystery1(a >> 2, b >> 8, c >> 8)};
    return state.step(a_in, b_in, 1);
  
  }

  uint16_t step(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in ={mystery1(a & 0x3, b & 0xFF, c & 0xFF)};
    uint8_t b_in ={mystery1(a >> 2, b >> 8, c >> 8)};
    return state.step(a_in, b_in, 0);
  }
};

int main(){
VExercise3 model;
Excercise3Sim sim;
 std::default_random_engine re {std::random_device {}()};
  std::uniform_int_distribution<uint8_t> rand4 {0, 15};
  std::uniform_int_distribution<uint16_t> rand16;

for (int i=0; i<4; i++){
  model.a = rand4(re);
  model.b = rand16(re);
  model.c = rand16(re);

//test reset:
model.reset=1;
model.clk=1;
model.eval();
model.clk=0;
model.eval();

uint16_t reset=sim.reset(model.a,model.b,model.c);

if(model.out != reset){
  cout<<"reset is not working";
  cout<<"j= "<<i<<endl;
  cout<<"a: " <<bitset<16> (model.a)<<endl;
  cout<<"b: " << bitset<16> (model.b)<<endl;
  cout<<"c: "<< bitset<16> (model.c)<<endl;
  cout<<"model output: "<< bitset<16> (model.out) <<endl;
  cout<<"expected    : "<<bitset<16>(reset)<<endl;
  return 1;
}


for (int j=0;j<20; j++){

model.reset=0;
model.clk=1;
model.eval();
model.clk=0;
model.eval();

uint16_t expected= sim.step(model.a,model.b,model.c);

if(model.out!= expected){
  cout<<"wrong output for:" <<endl;
  cout<<"j= "<<j<<endl;
  cout<<"a: " <<bitset<16> (model.a)<<endl;
  cout<<"b: " << bitset<16> (model.b)<<endl;
  cout<<"c: "<< bitset<16> (model.c)<<endl;
  cout<<"model output: "<< bitset<16> (model.out) <<endl;
  cout<<"expected    : "<<bitset<16>(expected)<<endl;

  return 1;
}
}
}
cout<<"all test passed"<<endl;
return 0;

}
