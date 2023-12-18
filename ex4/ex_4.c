/***********************
* Nadav Banay
* 326277910
* ex_4
***********************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int Order(),IsinWord(char), IsGussd(char), Gamesetup(), IsWin();
void Orderarr(char string[]), PrintHanged(), DismbleWords(char string[]), PrintGame(), PrintrvlWord(), PrintprvsGuss();
char words[15][20];
char guss[20];
int clurvl = 0;
char prvsguss[20];
char clue[20];
int choice;
int num_mstks = 0;
int guss_clear_idx = 0;


int main() {
    choice = Gamesetup();
    while( (num_mstks < 5)  && (!IsWin())) {
        PrintGame();
    }
    if(num_mstks == 5){
        PrintHanged();
        printf("The word is %s, GAME OVER!", words[choice]);
    }
    else {
        printf("The word is %s, good job!", words[choice]);
    }
}


void PrintGame(){
/******************
* Function Name: PrintGame
* Input: None
* Output: None(prints)
* Function Operation: the function handles all the printings in the game - hangman, revalved chars, guessed chars...
******************/
    char lett = 'a';
    PrintHanged();
    PrintrvlWord();
    if( !clurvl ){//works if the clue isnt revealed
        printf("do you want a clue? press -> *\n");
        PrintprvsGuss();
        printf("please choose a letter:\n");
        scanf(" %c", &lett);
        if(IsGussd(lett)){
            printf("You've already tried that letter.\n");
        }
        else if(lett == '*'){
            printf("the clue is: %s.\n", clue);
            clurvl = 1;
        } else{
            //updates the guesses, checks if it's a mistake;
            if(!IsinWord(lett)){
                num_mstks++;
            }
            guss[guss_clear_idx] = lett;
            guss_clear_idx++;
        }
    }else{
        PrintprvsGuss();
        printf("please choose a letter:\n");
        scanf(" %c",&lett);
        if(IsGussd(lett)){
            printf("You've already tried that letter.\n");
        }
        else{
            //updates the guesses, checks if it's a mistake;
            if(!IsinWord(lett)){
                num_mstks++;
            }
            guss[guss_clear_idx] = lett;
            guss_clear_idx++;

        }
    }
}

void PrintprvsGuss(){
/******************
* Function Name: PrintprvsGuss
* Input: None
* Output: None(prints)
* Function Operation: the function prints all the letters that
  had been guessed in the game so far
******************/

    int i = 0;
    printf("The letters that you already tried:");
    while (guss[i+1] != NULL){
        printf(" %c,", guss[i]);
        i++;
    }
    if (guss[i] != NULL){
        printf(" %c\n", guss[i]);
    } else{
        printf("\n");
    }

}

void PrintrvlWord(){
/******************
* Function Name: PrintrvlWord
* Input: None
* Output: None(prints)
* Function Operation: the function prints the chosen word using
  the guess that was made so far, if the function cant match a
  guessed letter to one of its word's characters - it will print
  '_' or ' ' or space in case the character is a space.
******************/
    char word[20];
    strcpy(word, words[choice]);
    int i = 0;
    while (word[i] != NULL){
        int isfound = 0;
        for(int j = 0; j < strlen(guss); j++){
            if(guss[j] == word[i]){
                isfound = 1;
                printf("%c",word[i]);
                break;
            }
        }
        if(!isfound){
            if(word[i] == ' '){
                printf(" ");
            } else{
                printf("_");
            }
        }
        i++;
    }

    printf("\n");
}

int Gamesetup(){
/******************
* Function Name: Gamesetup
* Input: None
* Output: None(prints)
* Function Operation: the function recieves the initiatory string, and breaks
  it to a clue and an array of words(strings).
  Afterwards the function orders the words in accending order by the
  lexicographical order and prints them and recieves the choice.
******************/
    char inp[300];//may be need to be intialized with none
    int us_choice;
    printf("Enter your words:\n");
    gets(inp);
    Orderarr(inp);

    printf("choose an option:\n");
    int i = 0;
    while(words[i][0] != NULL){
        printf("%d: %s\n", (i+1), words[i]);
        i++;
    }

    scanf("%d", &us_choice);
    us_choice = (us_choice-1);
    return us_choice;

}

void DismbleWords(char string[]){
/******************
* Function Name: DismbleWords
* Input: char strings[](with a word followed by ':', and words seperated by comma.
* Output: None
* Function Operation: the function breaks the string to a clue and an array
  of words according to the format.
******************/
    char temp_str[20];
    int i = 0, clear_idx = 0, clear_str_idx=0;
    while (string[i] != ':'){
        clue[i] = string[i];
        i++;
    }
    i++;

    while(string[i] != NULL){
        if(string[i] == ','){
            clear_str_idx++;
            clear_idx=0;
        } else{
            words[clear_str_idx][clear_idx] = string[i];
            clear_idx++;
        }
        i++;
    }

}

void Orderarr(char string[]){
/******************
* Function Name: Orderarr
* Input: char string[]
* Output: None
* Function Operation: the function breaks the string using the DismbleWords
  function and orders the words by the lexicographical order
******************/
    DismbleWords(string);
    char temp_str[20];
    for(int i = 0; words[i][0] != NULL; i++){
        for(int j = 0; words[j][0] != NULL; j++){
            if((strcmp(words[j+1], words[j]) < 0) && (words[j+1][0] != NULL)){
                //swaps the words
                strcpy(temp_str,words[j]);
                strcpy(words[j], words[j+1]);
                strcpy(words[j+1],temp_str);
            }
        }
    }

}
void PrintHanged(){
/******************
* Function Name: PrintHanged
* Input: None
* Output: None(prints)
* Function Operation: the function prints the appropriate hanged-man picture
  according to the format.
******************/
    if (num_mstks == 0){
        printf(" _________________\n"
               "|                |\n"
               "|                |\n"
               "|                |\n"
               "|                |\n"
               "|                |\n"
               "|________________|\n");
    }
    else if (num_mstks == 1){
        printf(" _________________\n"
               "|                |\n"
               "|  **            |\n"
               "|  **            |\n"
               "|                |\n"
               "|                |\n"
               "|________________|\n");
    } else if (num_mstks == 2){
        printf(" _________________\n"
               "|                |\n"
               "|  **        **  |\n"
               "|  **        **  |\n"
               "|                |\n"
               "|                |\n"
               "|________________|\n");
    } else if (num_mstks == 3){
        printf(" _________________\n"
               "|  --            |\n"
               "|  **        **  |\n"
               "|  **        **  |\n"
               "|                |\n"
               "|                |\n"
               "|________________|\n");
    } else if (num_mstks == 4){
        printf(" _________________\n"
               "|  --        --  |\n"
               "|  **        **  |\n"
               "|  **        **  |\n"
               "|                |\n"
               "|                |\n"
               "|________________|\n");
    }
    else if (num_mstks == 5){
        printf(" _________________\n"
               "|  --        --  |\n"
               "|  **        **  |\n"
               "|  **        **  |\n"
               "|                |\n"
               "| \\/\\/\\/\\/\\/\\/\\  |\n"
               "|________________|\n");
    }
}

int IsGussd(char a){
/******************
* Function Name: IsGussd
* Input: char a
* Output: int (0 or 1)
* Function Operation: the function checks if the given letter is in the guss array.
******************/
    int i = 0;
    while(guss[i] != NULL){
        if(a == guss[i]){
            return 1;
        }
        i++;
    }
    return 0;
}

int IsinWord(char a){
/******************
* Function Name: IsinWord
* Input: char a
* Output: int (0 or 1)
* Function Operation: the function checks if the given letter is in the chosen word string.
******************/
    int i = 0;
    while(words[choice][i] != NULL){
        if(a == words[choice][i]){
            return 1;
        }
        i++;
    }
    return 0;
}

int IsWin(){
/******************
* Function Name: IsWin
* Input: None
* Output: int (0 or 1)
* Function Operation: the function checks if the user won - all the word can be
  made using the guessed words.
******************/

    for(int i = 0; words[choice][i] != NULL; i++){
        if (!IsGussd(words[choice][i])){
            return 0;
        }
    }
    return 1;
}