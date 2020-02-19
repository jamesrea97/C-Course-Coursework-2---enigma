#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "errors.h"

using namespace std;

class Plugboard {

 public:

  /* *** ERROR TESTING *** */
  
  /* DECLARATION OF "plugboard_test" */
  //Tests errors 3, 4, 5, 6 for .pb file
  int plugboard_test(char* arg_plug);

  
 /* *** FUNCTIONING OF PLUGBOARD *** */
  
  //Maping of .pb file
  int mapping_plugboard[ALPHABET_SIZE];


  /* DECLARATION OF "build_plug_board" */
  //Builds the plugboard with mapping of .pb file
    int build_plugboard(char*  arg_plug);

  /* DECLARATION OF "letter_change" */
  //Plugboard letter change according to mapping
  char change_letter(char in_letter);

};


#endif
