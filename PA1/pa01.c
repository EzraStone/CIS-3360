/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Ezra Stone
| Language: c
|
| To Compile: gcc -o pa01 pa01.c
|
| To Execute: c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Spring 2024
| Instructor: McAlpin
| Due Date: 2/25/2024
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 10000 // Max length of a message

/*
This fuction does the matrix multiplication needed for the hill cipher
By passing the key, plain text, and size of the matrix from the main
*/
int* matrixMultiply(int** key, int* plainText, int size) {

    // Allocating memory using calloc so the values are assigned to 0 at initialization
    int* newVal = (int*)calloc(size, sizeof(int));

    // Iterates through the rows
    for (int i=0; i<size; i++) {
        // iterates through the columns
        for (int j=0; j<size; j++){
            // Multiplies the key value by the plain chars value then adds the new value then mods 26 for alphabet
            // Ex. key: 2 4  plain: n,o = 13, 14  |(2 * 13) + (4 * 14)| = |26 + 56| = |82 | % 26 = 4
            //          3 5                       |(3 * 13) + (5 * 14)|   |39 + 70| = |109| % 26 = 5
            // a=0,b=1,c=2,d=3,e=4,f=5 so our new values would be e and f
            newVal[i] = (newVal[i] + key[i][j] * plainText[j]) % 26;
        }
    }

    return newVal;
}

/*
Uses the cipher texts integers and converts them back to chars for us to view the cipher text
*/
char* cipherToChar(int* cipherText, int size) {

    char* cipherChar = (char*)malloc((size+1) * sizeof(char));// 1 is added to account for the NULL terminator in a string

    for (int i=0; i<size; i++){
        // Takes the cipherText integer and adds the ascii value of a to get the character number for the cipher
        // Uses char to typecast integer value to a char
        cipherChar[i] = (char)(cipherText[i] + 'a');
    }

    // NULL character terminator
    cipherChar[size] = '\0';

    return cipherChar;
}

/*
Changes characters from the plaintext into integers for our hill cipher
*/
int* charToInt(char* plainText, int n, int iter) {

    int* numArr = (int*)malloc(n * sizeof(int));

    for (int j=iter; j<iter+n; j++){
        // Stores the plain text character value in numArr by subtracting the ascii value
        // Ex. plainText[0] = n or 110 in ascii and a = 97
        // So we do 110 - 97 and get 13 which is what would be used in the matrixMultiply function
        numArr[j-iter] = plainText[j] - 'a';
    }

    return numArr;
}

int main(int argc, char **argv) {

    char ctext[MAX_LEN];

    char* kx = argv[1];
    char* px = argv[2];
    // File IO
    FILE *key_file = fopen(kx, "r");
    FILE *plain_file = fopen(px, "r");

    if (key_file == NULL || plain_file == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    //Key matrix size
    int size;
    // Scans the first line of the file and saves it in size
    fscanf(key_file, "%d", &size);

    // Key row declaration
    int** key = (int**)malloc(size * sizeof(int*));

    for (int i=0; i<size; i++){
        // Declaration of the keys columns
        key[i] = malloc(size * sizeof(int));
    }

    printf("\nKey matrix:\n");
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            // Reads the key from the file and saves it in the key
            fscanf(key_file, "%d", &key[i][j]);
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    printf("\nPlaintext:\n");
    char plainText[MAX_LEN];
    char c;
    int index = 0;

    // Checks if it is at the end of the file 
    while(fscanf(plain_file, "%c", &c) != EOF){
        // Checks if the current char is in the alphabet or not if it is a-z/A-Z it will be ignored
        if(isalpha(c)){
            // Converts the letter found to lowercase and adds 1 to index so we can keep track of current plainText place
            plainText[index] = tolower(c);
            index++;
        }
        // plainText[index+1] = '\0';
    }
  plainText[index+1] = '\0';

    // If statement checks whether the length of plain text mod size is not equal to 0
    // If it is not equal to 0 then this means we will need to pad with an x
    if (strlen(plainText) % size != 0) {
        // Does the math needed to know how much we need to pad
        // It does this by subtracing the size by the remainder of the length of plain text
        int pad_len = size - (strlen(plainText) % size);

        for (int i = 0; i < pad_len; i++) {
            //Goes to end of plaintext and adds the padding
            plainText[strlen(plainText)] = 'x';
        }

        // NULL character terminator
        // plainText[strlen(plainText)] = '\0';
    }
  plainText[strlen(plainText)+1] = '\0';

    // Keeps track of plains character amount
    int plainChar = 0;

    for(int i=0; i<strlen(plainText); i++){
        // Checks if we are at the 80 char mark so that we can print the new line if needed
        if(plainChar >= 80){
            printf("\n");
            // Resets the count so we can run it again if need be
            plainChar = 0;
        }
        // Prints the plain text
        printf("%c", plainText[i]);
        plainChar++;
    }
    printf("\n");

    printf("\nCiphertext:\n");
    int cipherChar = 0;

    // For loop does all the steps needed to print out the cipher
    for (int j=0; j<strlen(plainText); j+=size) {
        // Changes the characters in plain to the ascii value and is stored in plainValue
        int* plainValue = charToInt(plainText, size, j);
        // Uses matrix multiplication to get the cipher text and stores in cipherValue
        int* cipherValue = matrixMultiply(key, plainValue, size);
        // Takes the ciphers int values and changes them back to a character 
        char *cipherText = cipherToChar(cipherValue, size);

        // Print out to screen.
        for (int i=0; i<strlen(cipherText); i++) {
            printf("%c", cipherText[i]);

            cipherChar++;
            // Checks if the 80 limit has been met
            if (cipherChar >= 80) {
                printf("\n");
                cipherChar = 0;
            }
        }

        // Freeing memory to prevent memory leaks
        free(plainValue);
        free(cipherValue);
        free(cipherText);
    }
    printf("\n");

    // Freeing the memory for the columns in key
    for (int i=0; i<size; i++){
        free(key[i]);
    }      
    //Frees the rest of the key 
    free(key);

    // Closes the file to free the memory
    fclose(key_file);
    fclose(plain_file);

    return 0;
}

/*=============================================================================
| I Ezra Stone (ez245440) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/