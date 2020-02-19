#ifndef ROTOR_H
#define ROTOR_H

#include "errors.h"

using namespace std;

class Rotor {

 private:
  
   /* *** FUNCTIONING OF ROTOR *** */

  //Number of rotations
  int rotation_counter;
  
  //Forward maping of .rot file
  int forward_mapping_rotor[ALPHABET_SIZE];

  //Backward maping: position is input, value is output
  int backward_mapping_rotor[ALPHABET_SIZE];

  //Position mapping: position of outter ring letters rotor
  int position_mapping[ALPHABET_SIZE];
  
  //Notches Mapping - Note (value = '-1' if not notch)
  int notches[ALPHABET_SIZE];

  
 public:

  /* *** ERROR TESTING *** */
  
  /* DECLARATION OF "rotor_test" */
  //Tests errors 3, 4, 7 for .rot file
  int rotor_test(char* arg_rot);
  

  /* *** FUNCTIONING OF ROTOR *** */
 
  /* DECLARATION OF "build_rotor" */
  //Builds the rotor with mappings of .rot file
  int build_rotor(char* arg_rot);

  /* DECLARATION OF "forward_change_letter" */
  //Rotor letter change according to forward mapping
  char forward_change_letter(char in_letter);
  
  /* DECLARATION OF "backward_change_letter" */
  //Rotor letter change according to backward mapping
  char backward_change_letter(char in_letter);

  /* DECLARATION OF "rotate_rotor" */
  //Rotates the rotor (shifting position array accordindgly)
  void rotate_rotor();

  /* DECLARATION OF "is_notch" */
  //returns true if notch at positon 0 on rotor
  bool is_notch();


};


#endif
