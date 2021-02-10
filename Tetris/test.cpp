#include <iostream>
#include <stdlib.h>
#include <time.h>



enum class Type { I, O, T, L, J, Z, S };



int main(){
  // srand(time(NULL));
  // Type test = (Type)(rand() % 7);
  // if (test!=Type::I&&test!=Type::O&&test!=Type::T&&test!=Type::L&&test!=Type::J&&test!=Type::Z&&test!=Type::S){
  //   std::cerr<<"problème"<<std::endl;
  //   return EXIT_FAILURE;
  // }
  // std::cout<<int(test)<<std::endl;
  int test=1;
  if(test==1){
    std::cout<<"youhou1"<<std::endl;
  }
  if(test==1){
    std::cout<<"youhou2"<<std::endl;
  }
  return EXIT_SUCCESS;
}
