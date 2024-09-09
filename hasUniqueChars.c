/*
 * hasUniqueChars.c
 * 
 * Determines if a string consists entirely of unique printable ascii characters
 * 
 * Author: rachel schecter 
 */

#include <stdio.h>  // fprintf, printf
#include <stdlib.h> // exit() defined here
#include <string.h> // useful string operations
#include <ctype.h>  //useful character operations
#include <stdbool.h>  // to define a boolean type and true, false
                      // see https://en.wikibooks.org/wiki/C_Programming/stdbool.h

#include "binary_convert.h"


/*
 * This function is for debugging by printing out the value
 * of an input insigned long as a binary string.
 */
void seeBits(unsigned long value, char *debug_text) {
  
  // string to represent binary value of variable value
  char *bin_str;

  bin_str = ulong_to_bin_str(value);
  printf("%s%s\n", debug_text, bin_str);
  free(bin_str);
  
}


/*
 * Given an input string of chars, check for any non-printing
 * characters and prints an error and exits if the string has any.
 */
void checkInvalid(char * inputStr) {
  char nextChar;
  int i;
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    // if nextChar is invalid (31 or less or 127 as an ascii char code), then bail out
    if ((nextChar <= 31 ) || (nextChar == 127)) {
      fprintf(stderr, "invalid character in string\n");
      exit(EXIT_FAILURE);
    }
  }
}
/*
 * Adds the character to the bit vector, and returns false unless the vector didn't change,
 * which means we've already added that character to the bit vector
 */
bool compareCharToVector(char curChar, unsigned long* vectorToCheck) {
  unsigned long vector = *vectorToCheck;      // saves the initial value of the vector
  unsigned long mask = 1UL << curChar;        // this creates an unsigned long with only the curChar-th bit nonzero
  *vectorToCheck = *vectorToCheck | mask;     // adds the character to the vector
  return (vector == *vectorToCheck);
}

/*
 * Determines if an input string consists entirely of unique characters.
 * Returns true if it does.
 * Returns false if it doesn't.
 * Exits with failure if the string contains any invalid characters.
 */
bool hasUniqueChars(char * inputStr) {
  // bail out quickly if any invalid characters
  checkInvalid(inputStr);
  
  int i;   // loop counter
  
  // unsigned long can handle 64 different chars in a string
  // if a bit at a position is 1, then we have seen that character
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp =0;  // for checking ! though @ 

  char nextChar;         // next character in string to check

  unsigned long* vectorToCheck;
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];
    if (nextChar < 65) {                    // determines which vector to add the number to
      nextChar = nextChar - 32;             // not necessary but nice for debugging
      vectorToCheck = &checkBitsexcl_amp;
    }
    else {
      nextChar = nextChar - 65;
      vectorToCheck = &checkBitsA_z;
    }
    bool containsDuplicate = compareCharToVector(nextChar, vectorToCheck);
    if (containsDuplicate) {
      return false;
    }
  }

  // if through all the characters, then no duplicates found
  return true;
  
}
