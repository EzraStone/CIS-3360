# CIS-3360

Security in Computing is a comprehensive course exploring various security practices. This course helps teach proficiency in both classic and contemporary cryptographic methods, covering topics such as key exchange mechanisms, malware defense, network security, digital rights management, and legal and ethical considerations. Through a blend of lectures, programming assignments, research papers, and exams, I learned about areas such as symmetric and public key cryptography, operating system security, web security, and cloud security. 

## Projects

### Hill Cipher encryption

- This assignment tasked me with implementing a program to encrypt text using the Hill cipher, with a matrix size ranging from 2x2 to 9x9. I was required to handle command-line input for the encryption key and plaintext file, ensuring proper file processing and outputting ciphertext to the console. The assignment includes specifications for key file format, plaintext file format, and output format, emphasizing the handling of uppercase and lowercase letters, padding, and non-alphabetic characters.

__How to compile the program__

```
gcc -o pa01 pa01.c
```

__How to execute code__

```
bash pa01test.sh pa01.c
```

### Checksums

- In this assigmnet I was tasked with developing a program to calculate checksums for text files of varying sizes. The program takes two command-line parameters: the input file for checksum calculation and the desired checksum size (8, 16, or 32 bits). It must then output the processed input text, formatted in rows of 80 characters, followed by the calculated checksum. The assignment emphasizes handling input parameters, file processing, output formatting, and checksum calculation based on the specified size.

__How to compile the program__

```
gcc -o pa02 pa02.c
```

__How to execute code__

```
bash pa02test.sh pa02.c
```
