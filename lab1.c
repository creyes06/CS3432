#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c){
	return c == ' ' || c == '\t';
}



// counts the number of words or tokens
int count_tokens(char* str){
    	int i = 0;
    	int wordCount = 1;

    	//l oop until EOF
    	while(str[i] != '\0'){
        	//check if character is a whitespace character
        	if(str[i] == ' ' || str[i] == '\t'){
            		wordCount++;
        	}

        	i++;
    	}

    	printf("Total number of words in the string is : %d\n", wordCount);
    	return wordCount;
    

}

// counts the number of characters in a string
int string_length(char* str){
	int i = 0;
	int count = 0;
	// loop until EOF
	while (str[i] != '\0'){
		count++;
		i++;
	}
	return count;
}

// Returns a string of a single word
char *copy_str(char *inStr, short len){
	char* word = (char*) malloc(len * sizeof(char));
	
	// loop for size given
	for (int i = 0; i < len; i++){
		word[i] = inStr[i];
	}
	return word;
}


/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char** tokenize(char* str){
	bool isSpaceChar;
	int i = 0;
	int j = 0;
	int k = 0;
	char *word;

	// gets number of words or tokens
	int tokenAmount = count_tokens(str);
	// gets number of characters in full string
	int len = string_length(str);
	char** vector = (char**) malloc(tokenAmount * sizeof(char*));
	
	

	
	for (i = 0; i < len; i++) {
		// gets boolean og whether character is whitespace character or not
		isSpaceChar = delim_character(str[i]);
		if (isSpaceChar){
			// Sends word by word to copy_str()
			word = copy_str(&str[j],i-j);
			// adds word to vector
			vector[k] = word;
			j = i+1;
			k++;

		}
		

	}
	// gets last word
	word = copy_str(&str[j],i-j);
	// add last word to vector
	vector[k] = word;

	print_all_tokens(vector,k);
	return vector;
}

// prints all tokens
void print_all_tokens(char** tokens, short len){
	for (int i = 0; i<= len; i++){
		printf("Tokenize[%d] = %s\n",i,tokens[i]);
	}
}

int main(){
	
	char userStr[100];
	printf("Enter your string: ");
	fgets(userStr, 100, stdin);
	char **result = tokenize(&userStr);

	
	return 0;
}
