#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here
void reverse_string(char *, int);
void word_print(char *, int);
void search_replace(char *, char *, char *, int);



int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions
    char *src = user_str;
    char *dst = buff;
    int num = 0;
    int whitespace = 0;

    while (*src && num < len) {
        if (*src == ' ' || *src == '\t') {
            if (!whitespace && num > 0) { // Add a single space if not at the start
                *dst++ = ' ';
                num++;
                whitespace = 1;
            }
        } else {
            *dst++ = *src;
            num++;
            whitespace = 0;
        }
        src++;
    }


    if (num > 0 && *(dst - 1) == ' ') {
        dst--; // Move the destination pointer back
        num--; // Reduce the count to reflect the removed trailing space
    }


    if (*src) {
        return -1;
    }    


    while (num < len) {
        *dst++ = '.';
        num++;
    }



    return num; //for now just so the code compiles. 
}

void print_buff(char *buff, int len){
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    printf("]\n");
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    //YOU MUST IMPLEMENT
    char *ptr = buff;  
    int count = 0;     
    int in_word = 0;   

    for (int i = 0; i < str_len && i < len; i++) {
        if (*ptr == ' ' || *ptr == '\t') {
            in_word = 0;  // End of a word
        } else if (!in_word) {
            in_word = 1;  // Start of a new word
            count++;
        }
        ptr++;
    }

    return count; 
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

void reverse_string(char *buff, int len) {
    char *start = buff;
    char *end = buff + len - 1;

    // Skip '.' characters
    while (*end == '.') {
        end--;
    }

    // Reverse the characters between start and end
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

void word_print(char *buff, int str_len) {
    char *ptr = buff;
    int word_index = 1;
    int word_length = 0;
    int in_word = 0;

    printf("Word Print\n");
    printf("----------\n");

    // Traverse through the buffer to find and print each word
    for (int i = 0; i < str_len; i++) {
        if (*ptr == ' ' || *ptr == '\t' || *ptr == '.') {
            // End of the word
            if (in_word) {
                printf("%d. %.*s(%d)\n", word_index, word_length, ptr - word_length, word_length);
                word_index++;
                in_word = 0;
                word_length = 0;
            }
        } else {
            // Start of a new word or inside a word
            if (!in_word) {
                word_length = 1;
                in_word = 1;
            } else {
                word_length++;
            }
        }
        ptr++;
    }

    printf("\nNumber of words returned: %d\n", word_index - 1);

    // If there's a word at the end of the string, print it
    if (in_word) {
        printf("%d. %.*s(%d)\n", word_index, word_length, ptr - word_length, word_length);
    }
}

void search_replace(char *buff, char *target, char *replace, int len) {
    char *match = strstr(buff, target); // Find the first occurrence of the target in buff
    int find_len = strlen(target);  // Length of the target string
    int rep_len = strlen(replace);  // Length of the replacement string


    if (rep_len <= find_len) {
        strncpy(match, replace, rep_len);   // Replace target with replacement
        
        char *src = match + find_len;
        char *dst = match + rep_len;

        while (*src != '\0' && *src != '.') {
            *dst++ = *src++;
        }

        while (dst < buff + len) {
            *dst++ = '.';
        }

    } else {    // If the replacement is longer 
        int shift = rep_len - find_len; // Calculate length difference
        char *end = buff + strlen(buff);

        if (strlen(buff) + shift >= len) {
            end = buff + len - 1;
        }

        for (char *src = end; src >= match + find_len; src--) {
            *(src + shift) = *src;
        }

        strncpy(match, replace, rep_len);   // Copy replacement
        char *dst = buff + len;
        *dst = '\0';
    }

    // Target not found
    if (!match) {
        printf("Not Implemented!\n");
        exit(1);
    }
}


int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //      It is safe because argc < 2 ensures that argv[1] exists before accessing it, preventing out-of-bounds memory access. If argv[1] doesn't exist, the program exits safely. 
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //      The if statement ensures the user provides a string argument as the second argument. If not, it displays usage instructions and exits with an error.
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3

    buff = (char *)malloc(BUFFER_SZ * sizeof(char));

    if (buff == NULL) {
        printf("Memory allocation failed!\n");
        exit(99);
    }


    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        free(buff);
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        case 'r':
	        reverse_string(buff, user_str_len);
	        break;

        case 'w':
            word_print(buff, BUFFER_SZ);
            break;

        case 'x':
            search_replace(buff, argv[3], argv[4], BUFFER_SZ);
            break;

        default:
            usage(argv[0]);
            free(buff);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE
//          Providing both the pointer and its length ensures safety and flexibility.
//          It prevents buffer overflows by enforcing size boundaries and makes the function 
//          reusable for buffers of varying sizes.