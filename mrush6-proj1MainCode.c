/*  projMainCode

	Written 5/16/2022 by Mustafa Rsuhdi for CS 211, Summer 2022
	
	This program 1
	
	TODO:  Update this comment, including file name adjustment as needed
  
*/

#include <stdio.h>

#include <stdlib.h>

//function used to copy elements form old array to the newley allocated array
void copyArray(int * pOriginal, int * pChanged, int size) {
  //loops through the known size of original array
  for (int i = 0; i < size; i++) {
    //each index the newley alloacted array will hold the dame value ast the old original one
    *(pChanged + i) = * (pOriginal + i);
  }
}
// this function uses the concept of bubble sorting to sort values from least to greatest
void BubbleSort(int * pChanged, int size) {
  //loop through newley alloacted array
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      //if the value at index i is less then the value at index j we swap using a temperory variable  
      if ( * (pChanged + i) >= * (pChanged + j)) {
        int Temp;
        Temp = * (pChanged + i);
        *(pChanged + i) = * (pChanged + j);
        *(pChanged + j) = Temp;
      }
    }
  }
}
//This function returns the values in both original and modified arrays
int countMatches(int * pOriginal, int * pChanged, int size) {
  double sameValues = 0;
  for (int i = 0; i < size; i++) {
    //if both derfranced pointers have the same value at the same index  we increment out counter by one
    if ( * (pOriginal + i) == * (pChanged + i)) {
      sameValues++;
    }
  }
  return sameValues;
}
int findInList(int * pOriginal, int * pChanged, int size, int target, int * nfound, int * index) {
  int returnValues = 0;
  int notSameIndex = 0;
  int notInList = 0;
  //I loop through the original pointer to get the elements that match the target value i do this in seperate loop because of the break statment used below
  for (int i = 0; i < size; i++) {
    if (target == * (pChanged + i)) {
      * nfound += 1;
    }
  } // I then loop through the array again to see if the atreget is within the modified pointer and if the elemets in the original array and the modified one have the same value
  for (int i = 0; i < size; i++) {
    if (target == * (pChanged + i) && * (pChanged + i) == * (pOriginal + i)) {
      // if the stament is true index then holds the value of that position plus 1 beacsue position starts at 1 but index starts at 0
      * index = i + 1;
      returnValues = 1;
      //break beacsue we can get the the return valuie as well as getting the first index of matching numbers
      break;
      // else if statment used to find if the target is within but the values in the index are not the same 
    } else if (target == * (pChanged + i) && * (pChanged + i) != * (pOriginal + i)) {
      //counter used to get if there is an insatnce where the number is within
      ++notSameIndex;
    } else if (target != * (pChanged + i)) {
      //counter used to seee if there are any instances where the number is not in the list at all
      ++notInList;
    }
    //if the loop doesnt break it runs down here to see if the counter is equall or greater then 1 then we return the value 0
    if (notSameIndex >= 1) {
      returnValues = 0;
      //if the loop doesnt break it runs down here to see if the counter is equall or greater then 1 then we return the value -1
    } else if (notInList >= 1) {
      returnValues = -1;
    }
  }
  return returnValues;
}

int main(void) {
  int val;
  //created to the hold the ammount of inputs the user enters
  int counter = 0;
  /* Create a dynamically allocated array of ints, with initial size 100 */
  int * pOriginal = NULL;
  int allocated = 100;
  pOriginal = (int * ) malloc(allocated * (sizeof(int)));

  /* Prompt the user for input */
  printf("Enter in a list of numbers to be stored in a dynamic array.\n");
  printf("End the list with the terminal value of -999\n");

  /* loop until the user enters -999 */
  scanf("%d", & val);
  while (val != -999) {
    /* Store the value into an array, growing array if needed. */
    /* Double the array size whenever more space is needed. */
    if (allocated <= counter) {
      int * temp;
      temp = pOriginal;
      pOriginal = (int * ) malloc(2 * allocated * sizeof(int));
      for (int i = 0; i < allocated; i++) {
        pOriginal[i] = temp[i];
      }
      free(temp);
      temp = NULL;
      allocated = allocated * 2;
    }
    for (int i = counter; i < counter + 1; i++) {
      *(pOriginal + i) = val;
    }
    /* get next value */
    scanf("%d", & val);
    // counter to hold the amount of elemts inserted
    counter++;
  }
  //newley allocated array to copy and sort it or just modyfing it
  int * pChanged = NULL;
  pChanged = (int * ) malloc(allocated * sizeof(int));
  /* Call function to make a copy of the array of values. */
  copyArray(pOriginal, pChanged, counter);
  /* Call function to sort one of the arrays. */
  BubbleSort(pChanged, counter);
  /* Call function to count matches, and report results. */
  // variable created to hold the return value of countMatches
  int sameValues = countMatches(pOriginal, pChanged, counter);
  //Variable used to get the average matched numbers and total numbers inserted
  double averageSameValues = (1.0 * sameValues / counter) * 100;
  //reporting results
  printf("Numbers already in sorted order = %d / %d = %.2f percent.\n", sameValues, counter, averageSameValues);

  /* Now check target numbers to see if they are in the list and where. */
  //from line 
  int foundElements = 0;
  int * pFound = NULL;
  pFound = & foundElements;
  int numberAtIndex = 0;
  int * index = NULL;
  index = & numberAtIndex;

  /* loop until the user enters -999 */
  printf("Enter in a list of numbers to search for.  \n");
  printf("End the list with a terminal value of -999\n");

  scanf("%d", & val);
  while (val != -999) {
    /* call function to perform target search operation */
    int resultsValue = 0;
    resultsValue = findInList(pOriginal, pChanged, counter, val, & foundElements, & numberAtIndex);
    /* print out info about the target search results  */
    if (resultsValue == 1) {
      printf("Target: %d = Present %d times(s) and in order. First match at position %d.\n", val, * pFound, * index);
    } else if (resultsValue == 0) {
      printf("Target: %d = Present %d times(s) but not in order.\n", val, * pFound);
    } else {
      printf("Target: %d = Not even in the list!\n", val);
    }
    //here we retart the pointer values for found and index because we are looping through it again when a user eneters a different number
    * pFound = 0;
    * index = 0;
    /* get next value */
    scanf("%d", & val);
  }
  // freeing 
  free(pChanged);
  pChanged = NULL;
  free(pOriginal);
  pOriginal = NULL;
  /* Final results could be printed here, such as the total # found, etc. */
  printf("Good bye\n");

  return 0;
}