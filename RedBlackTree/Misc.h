#ifndef MISC_H
#define MISC_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/unistd.h>
#include<unistd.h>
#include<strings.h>

#define ExitProgramMacro(a) { \
printf("Error: "); printf(a); \
printf("Exiting from line %i in file %s\n",__LINE__,__FILE__); \
printf("\nCausing Segmentation Fault to exit ungracefully\n"); \
       int * junk = NULL; (*junk)++;\
       printf("%i\n",(int)junk);}
	   
#define VERIFY(condition) \
if (!(condition)) { \
fprintf(stderr, "Assumption \"%s\"\nFailed in file %s: at line:%i\n", \
#condition,__FILE__,__LINE__); \
ExitProgramMacro(#condition);}

#ifdef CHECK_ASSUMPTIONS
#define ASSUME(x) VERIFY(x)
#else
#define ASSUME(x) ;
#endif

inline void Assert(int assertion, char* error) {
  if(!assertion) {
    printf("Assertion Failed: %s\n",error);
    ExitProgramMacro("Exiting From Function Assert(...)\n");
  }
}

#endif