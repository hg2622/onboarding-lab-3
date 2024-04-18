
#include <iostream>
#include "VExercise1.h" 

using namespace std;

int main()
{
   VExercise1 model;
   
   for (int op=0; op<4; op++){
        for(uint16_t a=0; (int)a<255; a++){
            for (uint16_t b=0; (int)b<255; b++){
                model.op = op;
                model.a = a;
                model.b = b;
                model.eval();
             

                uint8_t expected_result;
                switch (op) {
                    case 0: expected_result = a ^ b; break;
                    case 1: expected_result = b<8? a<<b :0; break;
                    case 2: expected_result = (b==0) ? 0 : (a%b); break;
                    case 3: expected_result = ~(a & b); break;
                }

                
            

                if (model.out != expected_result) {
                    cout << "Wrong result for op=" << (int)op << ", a=" << (int)a << ", b=" << (int)b <<" "<<int(model.out)<<endl;
                    return 1; // return instead of exit
                }
            
        }
        }
    }
    
    cout << "All tests passed." << endl;
    return 0;
}