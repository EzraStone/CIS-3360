/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Ezra Stone
| Language: c
|
| To Compile: gcc -o pa02 pa02.c
|
| To Execute: c -> ./pa02 inputFile.txt 
| 
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2024
| Instructor: McAlpin
| Due Date: 3/31/2024
|
+=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int checksum8Bit(const char *string) {
    int resultOf8 = 0;

    // Iterates throught every bit in the string and adds them to the running total 
    for (int i = 0; i < strlen(string); i++) {
        resultOf8 += string[i];
    }

    // Returns our answer
    return resultOf8;
}

int checksum16Bit(const char *string) {
    int resultOf16 = 0;

    // Iterate through the string in pairs of characters
    for (int i = 0; i < strlen(string); i += 2) {
        // Construct a 16-bit value from 2 characters by shifting the first left 8 positions and ORing the second
        int temp = (string[i] << 8) | (string[i + 1]);
        resultOf16 += temp; // Add the temp to checksum
    }

    // Return the answer
    return resultOf16;
}

int checksum32Bit(const char *string) {
    int resultOf32 = 0;

    // Iterate through the input string in 4-byte sections
    for (int i = 0; i < strlen(string); i += 4) {
        // Construct a 32-bit value from 4 characters 
        int temp = 0;
        // Will run as long as j is less than 4 and our string has not hit the null terminator
        for (int j = 0; j < 4 && string[i + j] != '\0'; j++) {
            temp <<= 8; // Shift bytes by 8 bits
            temp |= string[i + j]; // Or the string and temp
        }
        resultOf32 += temp;// Add the temp to our final answer
    }

    // Return the answer
    return resultOf32;
}

int main(int argc, char **argv) {
    FILE *checksumFile;
    char *string;
    char c = 'x';
    unsigned long int eight_bit = 0;
    unsigned long int sixteen_bit = 0;
    unsigned long int thirtytwo_bit = 0;
    int i = 0;
    int checksumNum = 0;

    // Convert string from the file to an interger and store it for comparisons
    checksumNum = atoi(argv[2]);

    // Checking if it is a valid checksum 
    if (!(checksumNum == 8 || checksumNum == 16 || checksumNum == 32)) {
        fprintf(stderr,"Valid checksum sizes are 8, 16, or 32\n");
    }

    checksumFile = fopen(argv[1],"r");

    // Safety Check
    if (checksumFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    // Allocate memory for our checksum string
    string = malloc(sizeof(char) * 1024);

    while (fscanf(checksumFile, "%c", &c) != EOF && i < 1024) {
        string[i] = c;
        i++;
    }
    string[i] = '\0';// Null character terminator for our string

    fclose(checksumFile);// Closing the file

    // 8 bit checksum check
    if(checksumNum == 8) {
        // Store checksum in variable
        eight_bit = checksum8Bit(string);

        // Padding
        for (int i = 0; i < strlen(string); i++) {
            if (i % 80 == 0)
                printf("\n");
            printf("%c", string[i]);
        }
        printf("\n");

        // Print the final output for 8 bit
        printf("%2d bit checksum is %8lx for all %4d chars\n", checksumNum, eight_bit & 0xff, (int)strlen(string));// 0xff will only display the 8 bits
    }
    // 16 bit
    else if(checksumNum == 16) {
        if (strlen(string) % 2){
            strcat(string, "X");
        }

        for (int i = 0; i < strlen(string); i++){
            if (i % 80 == 0)
                printf("\n");
            printf("%c", string[i]);
        }

        printf("\n");

        sixteen_bit = checksum16Bit(string);
        
        printf("%2d bit checksum is %8lx for all %4d chars\n", checksumNum, sixteen_bit & 0xffff, (int)strlen(string));//0xffff will only display the 16 bits
    }
    // 32 bit checksum
    else if(checksumNum == 32) {
        while (strlen(string) % 4)
                strcat(string,"X");

            for (int i = 0; i < strlen(string); i++){
                if (i % 80 == 0)
                    printf("\n");
                printf("%c",string[i]);
            }

            printf("\n");

            thirtytwo_bit = checksum32Bit(string);
            
            printf("%2d bit checksum is %8lx for all %4d chars\n", checksumNum, thirtytwo_bit & 0xffffffff, (int)strlen(string));//0xffffffff will only display the 32 bits
    }

    return 0;
}

/*=============================================================================
| I [Ezra Stone] (5602012) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+============================================================================*/