#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "errors.h"

using namespace std;

class Reflector {

 public:
  
  /* *** ERROR TESTING *** */
  
  /* DECLARATION OF "reflector_test" */
  //Tests errors 3, 4, 9, 10 for .rf file
  int reflector_test(char* arg_ref);

   /* *** FUNCTIONING OF REFLECOR *** */

  //Maping of .rf file
  int mapping_reflector[ALPHABET_SIZE];

  /* DECLARATION OF "build_reflector" */
  //Builds the reflector with mapping of .rf file
  int build_reflector(char* arg_ref);
  
  /* DECLARATION OF "change_letter" */
  //Reflector letter change according to mapping
  char change_letter(char in_letter);
  
};

#endif
