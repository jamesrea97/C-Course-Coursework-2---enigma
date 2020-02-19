#include <fstream>
#include <iostream>
#include <string>
#include "reflector.h"
#include "errors.h"

using namespace std;

/* DEFINITION OF "reflector_test" */
int Reflector::reflector_test(char* arg_ref){

  //setting up array for ref_config_test:
  bool test_array[ALPHABET_SIZE];
  for (int count = 0; count < ALPHABET_SIZE; count++) {
    test_array[count] = false;
  }

  ifstream fin;
  string num_string;
  int num;

  //setting up counter for ref_param_test
  int counter = 0;
 
  fin.open(arg_ref);
  
  //test file open correctly
  if (open_file_test(fin) != NO_ERROR) {
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  fin >> num_string;
  
  while(!fin.eof()) {
    
    if (num_test(num_string) != NO_ERROR) {
      cerr << " in reflector file reflector.rf";
      return NON_NUMERIC_CHARACTER;
    }

    //convert num_string to int
    num = stoi(num_string);

    if (index_test(num) != NO_ERROR) {
      return INVALID_INDEX;
    }

    if (ref_config_test(num, test_array) != NO_ERROR) {
      return INVALID_REFLECTOR_MAPPING;
    }

    counter++;

    fin >> num_string;
  }
  
  if (ref_param_test(counter) != NO_ERROR) {
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  fin.close();
  return NO_ERROR;
}

/* DEFINITION OF "build_reflector" */
int Reflector::build_reflector(char* arg_ref) {

  ifstream fin;
  int error_code;
  
  string string1, string2;
  int left_pair, right_pair;

  //initialise a mapping
  for (int count = 0; count < ALPHABET_SIZE; count++) {
    mapping_reflector[count] = count;
  }

  fin.open(arg_ref);

  //checking open correctly
  error_code = open_file_test(fin);
  if (error_code != NO_ERROR) {
    return error_code;
  }
 
  fin >> string1;
  fin >> string2;
  
  while (!fin.eof()) {
    left_pair = stoi(string1);
    right_pair = stoi(string2);

    mapping_reflector[left_pair] = right_pair;
    mapping_reflector[right_pair] = left_pair;

    fin >> string1;
    fin >> string2;
  }
  
  fin.close();
  
  return NO_ERROR;
}

/* DEFINITION OF MEMBER FUNCTION "change_letter" */
char Reflector::change_letter(char in_letter) {

  char output_letter;
  int num_letter = static_cast<int>(in_letter) - 65;

  output_letter = static_cast<char>(mapping_reflector[num_letter] + 65);
  
  return output_letter;
}
