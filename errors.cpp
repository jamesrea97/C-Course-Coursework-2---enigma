#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "errors.h"

using namespace std;


/* (1) DEFINITION OF "input_test"*/
int files_test(int num_arg) {
  if (num_arg < 4) {
    cerr << "Usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions";
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }
  return NO_ERROR;
}

/* (2) DEFINITION OF "input_test" */
int input_test(char input_char) {
  if (input_char < 65 || input_char > 90) {
    cerr << input_char << " is not a valid input character ";
    cerr << "(input characters must be upper case letters A-Z)!";
    return INVALID_INPUT_CHARACTER;
  }   
  return NO_ERROR;
}


/* (3) DEFINITINON OF "index_test" */
int index_test(int a_number) {
  if (a_number > 25 || a_number < 0) {
    return INVALID_INDEX;
  }
  return NO_ERROR;
}

/* (4) DEFINTION OF "num_test"*/
int num_test (string string_num) {
  int i = 0;
  while(string_num[i] != '\0') {
    if (string_num[i] < 48 || string_num[i] > 57) {
      cerr << "Non-numeric character ";
      return NON_NUMERIC_CHARACTER;
    }
    i++;
  }
  return NO_ERROR;
}  

/* (5) DEFINTION OF "plug_config_test" */
int plug_config_test(int a_number, bool ar[ALPHABET_SIZE]) {
  if(ar[a_number] == true) {
    cerr << "Impossible plugboard configuration";
    return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  }
  ar[a_number] = true;
  return NO_ERROR;
}

/* (6) DEFINITION OF "plug_param_test" */
int plug_param_test(int a_counter) {
  if (a_counter % 2 != 0 || a_counter > 26) {
    cerr << "Incorrect number of plugboard parameters";
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  return NO_ERROR; 
}

/* (7) DEFINITION OF "rot_config_test" */
int rot_config_test(int a_number, bool ar[ALPHABET_SIZE], int entry) {
  //only need the first 26 numbers in file for mapping
  if (entry > ALPHABET_SIZE) {
    return NO_ERROR;
  }
  if(ar[a_number] == true) {
    cerr << a_number << " has already been mapped";
    return INVALID_ROTOR_MAPPING;
  }
  ar[a_number] = true;
  return NO_ERROR;
}

/* (8) DEFINITION OF "rot_start_test" */
int rot_start_pos(int num_rot, char* arg_pos) {
  int error_code;
  //counting number of rotors in file
  int counter = 0;

  ifstream fin;
  string num_string;
  int num;

  fin.open(arg_pos);

  //testing file correctly open
  error_code = open_file_test(fin);
  if (error_code != NO_ERROR) {
    return error_code;
  }
  fin >> num_string;

  while (!fin.eof()) {

    error_code = num_test(num_string);
    if (error_code != NO_ERROR) {
      cerr << " in rotor position file rotor.pos";
      return error_code;
    }

    //convert num_string to int
    num = stoi(num_string);

    index_test(num);

    counter++;
    fin >> num_string;
  }

  if (counter != num_rot) {
    cerr << "No starting position for rotor " << counter << " in rotor position file: rotor.pos";
    return NO_ROTOR_STARTING_POSITION;
  }
  fin.close();
  return NO_ERROR;
}

/* (9) DEFINITION OF "ref_config_test" */
int ref_config_test(int a_number, bool ar[ALPHABET_SIZE]) {
  if(ar[a_number] == true) {
    cerr << "Invalid reflector mapping";
    return INVALID_REFLECTOR_MAPPING;
  }
  ar[a_number] = true;
  return NO_ERROR;
}

/* (10) DEFINITION OF "reflector_test" */
int ref_param_test(int a_counter) {
  if (a_counter != 26) {
    cerr << "Incorrect number of reflector paramters";
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  return NO_ERROR;
}

/* (11) DEFINITION OF "open_file_test" */
int open_file_test(ifstream& a_fin) {
  if(a_fin.peek() == a_fin.eof()) {
    return NO_ERROR;
  }
  if (!a_fin.is_open()) {
    cerr << "Error opening configuration file";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  return NO_ERROR;
}

  




