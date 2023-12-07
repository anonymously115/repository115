#include <string.h>
#include "replace.h"
char* replace(char* dst, const char* src, const char* old, const char* new){
  if(!strcmp(old,"")){
    strcpy(dst,src);
    return dst;
  }
  strcpy(dst, "");
  int a=(int)strlen(old);
  const char* c=src;
  char* s=strstr(c,old);
  while(s){
    strncat(dst,c,s-c);
    strcat(dst,new);
    c=s+a;
    s=strstr(c,old);
  }
  strcat(dst,c);
  return dst;
}
