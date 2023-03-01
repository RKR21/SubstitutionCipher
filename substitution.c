#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int help(void){

    printf("Usage: <encrypt/decrypt(e/d)> <substitution map file> <string input(plain/cipher text)\n");
    return 0;
}

char ** validateKey(char * file, char key[27][27]){
    FILE * fp;
    char str[20];
    char left[27];
    char right[27];

    fp = fopen(file, "r");
    if(fp == NULL){
        perror("Error Opening File");
        exit(1);
        
    }
    int i = 0;
    while (!feof(fp)){
        fgets(str, 20, fp);
        left[i] = str[0];
        right[i] = str[2];
        i++;
        if(i == 26){
            left[26] = '\0';
            right[26] = '\0';
            break;
        }
        
    }


    for (i = 0; i < 26; i++){
        if(!isalpha(left[i])){
            perror("Error: Invalid character in key file\n");
            exit(1);
            break;
        }
        if(!isalpha(right[i])){
           perror("Error: Invalid character in key file\n");
           exit(1);
           break;
        }

    }
    for(i = 0; i < 25; i++){
        for(int j = i + 1; j < 25; j++){
            if(strcmp(&left[i], &left[j]) == 1){
                perror("Error: Duplicate Mapping\n");
                exit(1);
                
            }
            if(strcmp(&right[i], &right[j]) == 1){
                perror("Error: Duplicate Mapping\n");
                exit(1);
                
            }
        }
    }
    int n = (int)strlen(left);
    int m = (int)strlen(right);
    if(n != 26 || m != 26){
        perror("Incomplete mapping in key file\n");
        exit(1);
    }


    //load into 2d array
    for(i = 0; i < 1; i++){
        for(int j = 0; j < 26; j++){
            key[i][j] = left[j];
        }
    }
    for(i = 1; i < 2; i++){
        for(int j = 0; j < 26; j++){
            key[i][j] = right[j];
        }
    }

    // Read into two lists left and right. Check if all elements in each list are letters
    // and check that all elements in each list are not duplicates. No duplicates in either list.
    // Check that there are 26 elements in each list.

    return (char**)key;
}




char * encrypt(char key[27][27], char message[], int word_length){
    
    int numList[word_length];
    for(int i = 0; i < word_length; i++){
        //create list with the elements needed to map
        for(int j = 0; j < 26; j++){
            if(message[i] == key[0][j] || message[i] == key[0][j] + 32){
                numList[i] = j;
                
            }
        }
    }
    for(int i = 0; i < word_length; i++){
            message[i] = key[1][numList[i]];
    }
    printf("%s\n", message);
    return message;
}

char * decrypt(char key[27][27], char message[], int word_length){
    
    int numList[word_length];
    for(int i = 0; i < word_length; i++){
        //create list with the elements needed to map
        for(int j = 0; j < 26; j++){
            if(message[i] == key[1][j] || message[i] == key[1][j] + 32){
                numList[i] = j;
                
            }
        }
    }
    for(int i = 0; i < word_length; i++){
            message[i] = key[0][numList[i]];
    }
    printf("%s\n", message);
    return message;
}



int main(int argc, char * argv[]){
    int file_length = strlen(argv[2]);
    int word_length = strlen(argv[3]);
    char key[27][27];
    if(file_length >= 20){
        printf("File name is too big\n");
        return -1;
    }

    char mode = *argv[1];
    char file[20];
    char message[word_length];

    strncpy(file, argv[2], 20);
    
    strncpy(message, argv[3], 20);
 
    validateKey(file, key);
    if(mode == 'e'){
        encrypt(key, message, word_length);
    }
    if(mode == 'd'){
        decrypt(key, message, word_length);
    }



    return 0;


}
