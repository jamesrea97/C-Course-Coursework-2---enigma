#ifndef ENIGMA_H
#define ENIGMA_H

#include <vector>
#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"

using namespace std;

class Enigma {

 private:
  
  /* PLUGBOARD */
  Plugboard plug;

  /* ROTORS */
  //Number of rotors in enigma machine
  int number_rotors;

  //Vector of rotors
  vector <Rotor> rotors;

  //Vector of starting configurations for rotors 
  vector <int> starting_positions;

  /* REFLECTOR */
  Reflector ref;


 public:

  /* *** ERROR TESTING *** */
  
  /*DECLARATION OF "enigma_test" */
  //Test errors for number of files and
  //for content of .pb, .rf, .rot, .pos files
  int enigma_test(char** arg, int num_arg);
  
  /* *** FUNCTIONING OF ENIGMA *** */

  /* DECLARATION OF "get_number_rotors" */
  //Gets the number of rotors in the enigma machine
  void get_number_rotors(int num_rot);
  
  /* DECLARATION OF "build_position_rotor" */
  //constructs pos array for intial config of rotors
  int build_position_rotor(char* pos_file);
  
  /* DECLARATION OF "build_enigma" */
  //builds initial enigma
  int build_enigma(char** argv, int num_arg);
  
  /* DECLARATION OF "rotate_rotors" */
  //recursive function rotates the rotors considering notches
  void rotate_rotors(int index_rotor_num);
  
  /* DECLARATION OF "encrypt_letter" */
  //function combines rotation of rotors
  char encrypt_letter(char a_letter);
};



#endif
