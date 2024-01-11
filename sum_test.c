#include <stdio.h>
#include <stdarg.h>
#include <math.h>

double sum(size_t size,...){
    va_list ap;
    va_start(ap,size);
    double total=0.0;
    for(size_t i=0;i<size;i++){
        total+=va_arg(ap,double);
    }
    va_end(ap);
    return total;
}

int tests_run = 0;
void test(size_t size,...){
  va_list ap;
  va_start(ap,size);
  double A[10];
  for(size_t i=0;i<size;i++){
      A[i]=va_arg(ap,double);
      putchar(i?'+':'$');
      printf("%.1lf",A[i]);
  }
  va_end(ap);
  double result=sum(size,A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],A[8],A[9]);
  int exponent;
  double mantissa=frexp(result-1,&exponent);
  printf("=1");
  if(mantissa)printf("%+lf\\times2^{%d}",mantissa*2,exponent-1);
  printf("$\n");
  tests_run++;  
}

void test1(){test(4,.1,.2,.3,.4);}
void test2(){test(4,.1,.2,.4,.3);}
void test3(){test(4,.1,.3,.2,.4);}
void test4(){test(4,.1,.3,.4,.2);}
void test5(){test(4,.1,.4,.2,.3);}
void test6(){test(4,.1,.4,.3,.2);}
void test7(){test(4,.2,.1,.3,.4);}
void test8(){test(4,.2,.1,.4,.3);}
void test9(){test(4,.2,.3,.1,.4);}
void test10(){test(4,.2,.3,.4,.1);}
void test11(){test(4,.2,.4,.1,.3);}
void test12(){test(4,.2,.4,.3,.1);}
void test13(){test(4,.3,.1,.2,.4);}
void test14(){test(4,.3,.1,.4,.2);}
void test15(){test(4,.3,.2,.1,.4);}
void test16(){test(4,.3,.2,.4,.1);}
void test17(){test(4,.3,.4,.1,.2);}
void test18(){test(4,.3,.4,.2,.1);}
void test19(){test(4,.4,.1,.2,.3);}
void test20(){test(4,.4,.1,.3,.2);}
void test21(){test(4,.4,.2,.1,.3);}
void test22(){test(4,.4,.2,.3,.1);}
void test23(){test(4,.4,.3,.1,.2);}
void test24(){test(4,.4,.3,.2,.1);}
void test25(){test(1,1.);}
void test26(){test(2,.1,.9);}
void test27(){test(2,.2,.8);}
void test28(){test(3,.1,.1,.8);}
void test29(){test(2,.3,.7);}
void test30(){test(3,.1,.2,.7);}
void test31(){test(4,.1,.1,.1,.7);}
void test32(){test(2,.4,.6);}
void test33(){test(3,.1,.3,.6);}
void test34(){test(3,.2,.2,.6);}
void test35(){test(4,.1,.1,.2,.6);}
void test36(){test(5,.1,.1,.1,.1,.6);}
void test37(){test(2,.5,.5);}
void test38(){test(3,.1,.4,.5);}
void test39(){test(3,.2,.3,.5);}
void test40(){test(4,.1,.1,.3,.5);}
void test41(){test(4,.1,.2,.2,.5);}
void test42(){test(5,.1,.1,.1,.2,.5);}
void test43(){test(6,.1,.1,.1,.1,.1,.5);}
void test44(){test(3,.2,.4,.4);}
void test45(){test(4,.1,.1,.4,.4);}
void test46(){test(3,.3,.3,.4);}
void test47(){test(4,.1,.2,.3,.4);}
void test48(){test(5,.1,.1,.1,.3,.4);}
void test49(){test(4,.2,.2,.2,.4);}
void test50(){test(5,.1,.1,.2,.2,.4);}
void test51(){test(6,.1,.1,.1,.1,.2,.4);}
void test52(){test(7,.1,.1,.1,.1,.1,.1,.4);}
void test53(){test(4,.1,.3,.3,.3);}
void test54(){test(4,.2,.2,.3,.3);}
void test55(){test(5,.1,.1,.2,.3,.3);}
void test56(){test(6,.1,.1,.1,.1,.3,.3);}
void test57(){test(5,.1,.2,.2,.2,.3);}
void test58(){test(6,.1,.1,.1,.2,.2,.3);}
void test59(){test(7,.1,.1,.1,.1,.1,.2,.3);}
void test60(){test(8,.1,.1,.1,.1,.1,.1,.1,.3);}
void test61(){test(5,.2,.2,.2,.2,.2);}
void test62(){test(6,.1,.1,.2,.2,.2,.2);}
void test63(){test(7,.1,.1,.1,.1,.2,.2,.2);}
void test64(){test(8,.1,.1,.1,.1,.1,.1,.2,.2);}
void test65(){test(9,.1,.1,.1,.1,.1,.1,.1,.1,.2);}
void test66(){test(10,.1,.1,.1,.1,.1,.1,.1,.1,.1,.1);}

int main(int argc, char* argv[]){
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();
	test13();
	test14();
	test15();
	test16();
	test17();
	test18();
	test19();
	test20();
	test21();
	test22();
	test23();
	test24();
	test25();
	test26();
	test27();
	test28();
	test29();
	test30();
	test31();
	test32();
	test33();
	test34();
	test35();
	test36();
	test37();
	test38();
	test39();
	test40();
	test41();
	test42();
	test43();
	test44();
	test45();
	test46();
	test47();
	test48();
	test49();
	test50();
	test51();
	test52();
	test53();
	test54();
	test55();
	test56();
	test57();
	test58();
	test59();
	test60();
	test61();
	test62();
	test63();
	test64();
	test65();
	test66();
  return 0;
}
