#include <iostream>
#include "class1.h"
#include "adopt.h"

using namespace std;

void class1::draw(){
  draw_line(100,200,300,400,128,255,255);
}
void class1::text(){
  cout<<"This is class1 object"<<endl;
}