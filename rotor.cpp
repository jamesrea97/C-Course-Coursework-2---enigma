#include <iostream>
#include <fstream>
#include <string>
#include "rotor.h"
#include "error.h"

using namespace std;

/* DEFINITION OF "rotor_test" */
int Rotor::rotor_test(char* arg_rot) {

  //setting up array for rot_config_test:
  bool test_array[ALPHABET_SIZE];
  for (int count = 0; count < ALPHABET_SIZE; count++) {
    test_array[count] = false;
  }
  //counter for 26 first numbers - rest notches
  int counter = 1;
  
  ifstream fin;
  string num_string;
  int num;
  
  fin.open(arg_rot);

  //test file open correctly
  if (open_file_test(fin) != NO_ERROR) {  
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  fin >> num_string;

  while(!fin.eof()) {

    if (num_test(num_string) != NO_ERROR) {
      cerr << " for mapping in rotor file rotor.rot";
      return NON_NUMERIC_CHARACTER;
    }

    //convert num_string to int
    num = stoi(num_string);

    if (index_test(num) != NO_ERROR) {
      return INVALID_INDEX;
    }

    //convert num_string to int
    num = stoi(num_string);

    if (index_test(num) != NO_ERROR) {
      return INVALID_INDEX;
    }

    if (rot_config_test(num, test_array, counter)) {
      return INVALID_ROTOR_MAPPING;
    }
    
    fin >> num_string;

    counter++;
  }

  //remaining of test for rotor mapping (check not only injective)
  for (int count = 0; count < ALPHABET_SIZE; count++) {
    if (test_array[count] == false) {
      cerr << "Not all letters have been mapped";
      return INVALID_ROTOR_MAPPING;
    }
    
  }

  fin.close();
  return NO_ERROR;
}
 

/* DEFINITION OF "build_rotor" */
int Rotor::build_rotor(char* arg_rot) {
  
  ifstream fin;
  int error_code;
  
  string string_num;
  int num;
  int notch_pos = 0;

  //initialise a notches mapping (Note: '-1' implies end of notches for rotor)
  for (int count = 0; count < ALPHABET_SIZE; count++) {
    notches[count] = -1;
  }

  //initialise a position rotor mapping
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    position_mapping[i] = i;
      
  }


  fin.open(arg_rot);

  //checking open correctly
  error_code = open_file_test(fin);
  if (error_code != NO_ERROR) {
    return error_code;
  }
  
  fin >> string_num;
  
  for (int count = 0; count < ALPHABET_SIZE; count++) {
    num = stoi(string_num);
    forward_mapping_rotor[count] = num;
    fin >> string_num;
  }

  //generating coresponding backward mapping
  for (int count = 0; count < ALPHABET_SIZE; count++) {
    int step = 0;
    while(forward_mapping_rotor[step] != count) {
      step++;
    }
    backward_mapping_rotor[count] = step;
  }

  while (!fin.eof()) {
    num = stoi(string_num);
    notches[notch_pos] = num;
    notch_pos++;
    fin >> string_num;
  }

  fin.close();
  
  return NO_ERROR;
}


/* DEFINTION OF "forward_change_letter" */
char Rotor::forward_change_letter(char in_letter) {
  char output_letter;

  //index of relative rotor mapping
  int index = 0;

  int letter_in = static_cast<int>(in_letter) - 65;

  //fingding relative letter at absolute value of letter_in
  int relative_letter_val = position_mapping[letter_in];

  //mapping of relative letter
  int forward_mapping_val = forward_mapping_rotor[relative_letter_val];

  //finding the index of where the relative mapping letter is
  while (position_mapping[index] != forward_mapping_val) {
    index++;
  }

  output_letter = static_cast<char>(index + 65);

  return output_letter; 
}

/* DEFINITION OF "backward_change_letter" */
char Rotor::backward_change_letter(char in_letter) {
  char output_letter;

  //index of relative rotor mapping
  int index = 0;
  
  int letter_in = static_cast<int>(in_letter) - 65;

  //fingding relative letter at absolute value of letter_in
  int relative_letter_val = position_mapping[letter_in];

  //mapping of relative letter
  int backward_mapping_val = backward_mapping_rotor[relative_letter_val];

  //finding the index of where the relative mapping letter is
  while (position_mapping[index] != backward_mapping_val) {
    index++;
  }
  output_letter = static_cast<char>(index + 65);

  return output_letter; 
}

/* DEFINITION OF "rotate_rotor" */
void Rotor::rotate_rotor() {
  int temp = position_mapping[0];
  for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
    position_mapping[i] = position_mapping[i + 1];    
  }
  position_mapping[ALPHABET_SIZE - 1] = temp;
}

/* DEFINITION OF "is_notch" */
bool Rotor::is_notch() {
  int i = 0;
  while(notches[i] != -1) {
    if (position_mapping[0]  == notches[i]) {
      return true;
    }
    i++;
  }
  return false;
}
