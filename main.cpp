#include <string>
#include <iostream>
#include <fstream>
#include "errors.h"
#include "enigma.h"

using namespace std;

/* *** MAIN FUNCTION *** */

int main(int argc, char** argv) {

  int error_code;
  char input_letter;
  int num_rotors;
  
  //number of rotors
  num_rotors = argc - 4;

  Enigma E;

  //Setting numbe rof rotors
  E.get_number_rotors(num_rotors);

  //checking files
  error_code = E.enigma_test(argv, argc);
  if (error_code != NO_ERROR) {
    return error_code;
  }

  //building enigma
  E.build_enigma(argv, argc);

  //letter from standard input
  cin >> input_letter;
  
  while(!cin.eof()) {
    while(isspace(input_letter)) {
      cin >> input_letter;
    }
    error_code = input_test(input_letter);
    if (error_code != NO_ERROR) {
      return error_code;
    }
    //outputed to the standard output
    cout << E.encrypt_letter(input_letter);
    cin >> input_letter;
  }
    
  return 0;
  
}
