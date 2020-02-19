#include <iostream>
#include <string>
#include <fstream>
#include "errors.h"
#include "enigma.h"
#include <vector>

using namespace std;

/* DEFINITION OF "enigma_test" */
int Enigma::enigma_test(char** arg, int num_arg) {
  int error_code;
  
 //TESTING: Number of files
  error_code = files_test(num_arg);
  if (error_code != NO_ERROR) {
    return error_code;
  }

  //TESTING: Plugboard file:
  error_code = plug.plugboard_test(arg[1]);
  if (error_code != NO_ERROR) {
    return error_code;
  }

  //TESTING: Reflector file:
  error_code = ref.reflector_test(arg[2]);
  if (error_code != NO_ERROR) {
    return error_code;
  }

  
  if (number_rotors > 0) {
    //TESTING: Rotor file(s):
    for (int i = 0; i < number_rotors; i++) {
      error_code = rotors[i].rotor_test(arg[i + 3]);
      if (error_code != NO_ERROR) {
	return error_code;
      }
    }

    //TESTING: Position rotor file
    error_code = rot_start_pos(number_rotors, arg[num_arg - 1]);
    if (error_code != NO_ERROR) {
      return error_code;
    }
  }
          

  return NO_ERROR;
}

/* DEFINITION OF "get_number_rotors" */
void Enigma::get_number_rotors(int num_rot) {
  number_rotors = num_rot;
}

/* DEFINTION OF "build_position_rotor" */
int Enigma::build_position_rotor(char* arg_pos_file) {
  int error_code;
   
  ifstream fin;
  string initial_pos_string;
  int initial_pos;
  
  fin.open(arg_pos_file);
  
  //checking open correctly
  error_code = open_file_test(fin);
  if (error_code != NO_ERROR) {
    return error_code;
  }
  
  fin >> initial_pos_string;

  while (!fin.eof()) {
    
    initial_pos = stoi(initial_pos_string);
    starting_positions.push_back(initial_pos);
    fin >> initial_pos_string;

  }
  fin.close();
  
  return NO_ERROR;
}

int Enigma::build_enigma(char** argv, int argc) {
  int error_code;
  
  //setting up the plugboard 
  error_code = plug.build_plugboard(argv[1]);
  if (error_code != NO_ERROR) {
    return error_code;
  }

  //setting up the rotors/rotor position mapping
  if (number_rotors > 0) {
    error_code = build_position_rotor(argv[argc - 1]);
    if (error_code != NO_ERROR) {
      return error_code;
    }
    for (int i = 0; i < number_rotors; i++ ) {
      Rotor rot;
      rotors.push_back(rot);
      error_code = rotors[i].build_rotor(argv[i + 3]);
      if (error_code != NO_ERROR) {
	return error_code;
      }
      
      for (int j = 0; j < starting_positions[i]; j++) {
	rotors[i].rotate_rotor();
      }
    }
  }
  
  //setting up reflector
  error_code = ref.build_reflector(argv[2]);
  if (error_code != NO_ERROR) {
    return error_code;
  }
  
  return NO_ERROR;
}

/* DEFINITION OF "rotate_rotors" */
void Enigma::rotate_rotors(int index_rotor_num) {

  //stopping condition
  if (number_rotors == 0) {
    rotors[index_rotor_num].rotate_rotor();
    return;
  }
  
  rotors[index_rotor_num].rotate_rotor();
  
  if (rotors[index_rotor_num].is_notch()) {
    if (index_rotor_num != 0) {
      rotate_rotors(index_rotor_num - 1);
    }
  }
}

/* DEFINITION OF "encrypt_letter" */
char Enigma::encrypt_letter(char a_letter) {  
  char output_letter;

  //shifting (potentially) next rotors
  if (number_rotors > 0) {
  rotate_rotors(number_rotors - 1);
  }

  //plugboard
  output_letter = plug.change_letter(a_letter);

 
  //rotors - right to left forward
  if (number_rotors > 0) {
    for (int i = number_rotors - 1; i > -1; i--) {
      output_letter = rotors[i].forward_change_letter(output_letter);
    }
  }

  //reflector
  output_letter = ref.change_letter(output_letter);
 

  //rotors - left to right backward
  if (number_rotors > 0) { 
    for (int i = 0; i < number_rotors; i++) {
      output_letter = rotors[i].backward_change_letter(output_letter);
    }
  }

  //plugboard
  output_letter = plug.change_letter(output_letter);

  return output_letter;
  
}
