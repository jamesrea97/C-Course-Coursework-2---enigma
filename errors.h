/* error codes  */
#define INSUFFICIENT_NUMBER_OF_PARAMETERS         1
#define INVALID_INPUT_CHARACTER                   2
#define INVALID_INDEX                             3
#define NON_NUMERIC_CHARACTER                     4
#define IMPOSSIBLE_PLUGBOARD_CONFIGURATION        5
#define INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS  6
#define INVALID_ROTOR_MAPPING                     7
#define NO_ROTOR_STARTING_POSITION                8
#define INVALID_REFLECTOR_MAPPING                 9
#define INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS  10
#define ERROR_OPENING_CONFIGURATION_FILE          11
#define NO_ERROR                                  0

#ifndef ERRORS_H
#define ERRORS_H

#include <string>

using namespace std;

int const ALPHABET_SIZE = 26;

/* ****** FUNCTIONS FOR INPUT ERROR CHECK ****** */

/* DECLARATION OF "files_test" - ERROR 1 */
//Tests whehter at least 4 files are provided.
int files_test(int num_arg);

/* DECLARATION OF "input_test" - ERROR 2 */
//Test whether input file characters in range A-Z
int input_test(char input_char);


/* ****** ERROR FOR FORMAT OF INPUT FILES ****** */

/* DECLARATION OF "index_test" - ERROR 3 */
//Test whether numbers in range 1 - 26
int index_test(int a_number) ;

/* DECLARATION OF "index_test" ERROR 4 */
//Tests whether the string is made up of numbers
int  num_test (string string_num);


/* ****** PLUGBOARD SPECIFIC FUNCTIONS ****** */

/* DECLARATION OF "plug_config_test" - ERROR 5 */
//Test whether mapping is non-self mapping/surjective
int plug_config_test(int a_number, bool ar[ALPHABET_SIZE]);

/* DECLARATION OF "plug_param_test" - ERROR 6*/
//Test mapping has only pairings (up to 13 pairs)
int plug_param_test(int a_counter);


/* ****** ROTOR SPECIFIC FUNCTIONS ****** */

/* DECLARATION OF "rot_config_test" - ERROR 7 */
//Exactly one mapping per lettetr
int rot_config_test(int a_number, bool ar[ALPHABET_SIZE], int number);

/* DECLARATION OF "rot_start_test" - ERROR 8 */
//Checks number of rotors is equivalent to number of start positions in .pos file
int rot_start_pos(int num_rot,char* arg_pos);


/* ****** REFLECTOR SPECIFIC FUNCTION ****** */

/* DECLARATION OF "ref_config_test" - ERROR 9 */
//Tests whether mapping ois non-self mapping/surjective
int ref_config_test(int a_number, bool ar[ALPHABET_SIZE]);

/* DECLARATION OF "ref_param_test" - ERROR 10 */
//Tests maping has exactly 13 pairs
int ref_param_test(int a_counter);


/* ****** ERROR FILE OPENING ****** */

/* DECLARATION OF "open_file_test" - ERROR 11*/
//Tests file stream is not corupted
int open_file_test(ifstream& a_fin);


#endif
