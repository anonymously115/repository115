#include <string.h>
#include <stdlib.h>
#include "split.h"
int split(char* dst[], const char* src, const char* delim, const char* quote){
  int n=0;
  const char* s=src;
  for(;;){
    strcpy(dst[n],"");
    char* q=strchr(quote,*s);
    if(q && *q){
      for(;;){//(*2)
        char* c=strchr(s+1,*s);
        strncat(dst[n],s+1,c-s-1);
        s=c+1;
        if(*s==*q){
          strncat(dst[n],s,1);
        }else{
          break;
        }
      }
      if(*s=='\0'){
        break;
      }
      if(strchr(delim,*s)){
        s++;
      }else{
        abort();
      }
    }else{
      char* c=strpbrk(s, delim);
      if(!c){
        strcat(dst[n],s);
        break;
      }
      strncat(dst[n],s,c-s);
      s=c+1;
    }
    n++;
  }
  return ++n;
}
