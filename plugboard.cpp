#include <fstream>
#include <iostream>
#include <string>
#include "plugboard.h"
#include "errors.h"

using namespace std;

/* DEFINTION OF "plugboard_test" */
int Plugboard::plugboard_test( char* arg_plug) {
  int error_code;
  //setting up array for plug_config_test:
  bool test_array[ALPHABET_SIZE];
  for (int count = 0; count < ALPHABET_SIZE; count++) {
    test_array[count] = false;
  }

  //setting up counter for plug_param_test
  int counter = 0;

  ifstream fin;
  string num_string;
  int num;
 
  fin.open(arg_plug);

  fin >> num_string;

  //checking file open correctly
  error_code = open_file_test(fin);
  if (error_code !=  NO_ERROR) {
    return error_code;
  }

  while(!fin.eof()) {
    
    if (num_test(num_string) != NO_ERROR) {
      cerr << " in plugboard file plugboard.pb";
      return NON_NUMERIC_CHARACTER;
    }

    //convert num_string to int
    num = stoi(num_string);

    if (index_test(num) != NO_ERROR) {
      return INVALID_INDEX;
    }
    
    if (plug_config_test(num, test_array) != NO_ERROR) {
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }

    counter++;

    fin >> num_string;
  }
  
  if (plug_param_test(counter) != NO_ERROR) {
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  fin.close();
  return NO_ERROR;
}


/* DEFINITION OF "build_plugboard" */ 
int Plugboard::build_plugboard(char* arg_plug) {

  int error_code;
  ifstream fin;
  
  string string1, string2;
  int left_pair, right_pair;

  //initialise a mapping
  for (int count = 0; count < ALPHABET_SIZE; count++) {
    mapping_plugboard[count] = count;
  }

  fin.open(arg_plug);

  if (fin.peek() == fin.eof()) {
    return NO_ERROR;
  }
  //checking open correctly
  error_code = open_file_test(fin);
  if (error_code != NO_ERROR) {
    return error_code;
  }

  fin >> string1;

  //empty plugboard file
  if (string1.empty()) {
    return NO_ERROR;
  }
  
  fin >> string2;
  
  while (!fin.eof()) {
    left_pair = stoi(string1);
    right_pair = stoi(string2);

    mapping_plugboard[left_pair] = right_pair;
    mapping_plugboard[right_pair] = left_pair;

    fin >> string1;
    fin >> string2;
  }

  fin.close();
  
  return NO_ERROR;
}

/* DEFINITION OF "change_letter" */
char Plugboard::change_letter(char in_letter) {

  char output_letter;
  int num_letter = static_cast<int>(in_letter) - 65;

  output_letter = static_cast<char>(mapping_plugboard[num_letter] + 65);

  return output_letter;
}

