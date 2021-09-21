#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c){

  if(c == ' ' || c == '\t'){
    return true;
  }

  return false;
}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space or a new line).
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c){

  if(c != ' ' && c != '\t' && c != '\n'){
    return true;
  }

  return false;
}

/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char* str){

  while(delim_character(*str)){
    //iterate if white space
    str++;

    //non-whitespace character found
    if(non_delim_character(*str)){
      return str;
    }
  }

  return str;
}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){

  while(non_delim_character(*str)){
    //iterate if not white space
    str++;
    
    //white space character found
    if(delim_character(*str)){
      return str;
    }
  }

  return "\n";
}

// counts the number of words or tokens
int count_tokens(char* str){

  int num = 0;

  //continues while not pointing to new line
  while(*str != '\n'){
    str = word_start(str);
    num++;
    str = end_word(str);
  }
  
  return num;
}

//count number of characters for each word
int string_length(char *str){
  
  char *start = str;
  while(*str){
    str++;
  }

  return str - start;
}

char** tokenize(char* str){
  int numWords = count_tokens(str);
  int arr[numWords];

  //copy of str
  char* newWord = str;
  
  char** tokens = malloc((sizeof(char*) * numWords) + 1);

  //place size of a word into array
  for(int i = 0; i < numWords; i++){
    //
    arr[i] = string_length(word_start(newWord)) - string_length(end_word(newWord));
    //go to end of current word then to start of next word
    newWord = end_word(newWord);
    newWord = word_start(newWord);
  }

  int pointer = 0;
  for(int i = 0; i < numWords; i++){
    //allocate memory to tokens to store word
    tokens[i] = malloc((sizeof(char*) * arr[i]));

    while(pointer < arr[i]){
      //word found
      if(non_delim_character(*str)){
        tokens[i][pointer] = *str;
        str++;
        pointer++;
      }
      //delim character found
      else{
        str++;
        pointer = 0;
      }
    }

    pointer = 0;
  }

  return tokens;
}

void print_all_tokens(char** tokens){

  int i = 0;
  while(*tokens != NULL){
    printf("Tokens[%d]: %s\n", i, *tokens);
    tokens++;
    i++;
  }
}

int main(){

  printf("Please enter the input string: ");
  char* p = malloc(1000 * sizeof(char));
  fgets(p, 1000, stdin);

  char** tokens = tokenize(p);
  print_all_tokens(tokens);
}