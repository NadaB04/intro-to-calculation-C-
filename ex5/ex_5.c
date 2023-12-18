#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


//Nadav Banay, 326277910
//structes:
typedef struct {
    char** translations;
    struct Word* next;
} Word;
typedef struct {
    char** languages;
    int numOfLanguages;
    Word* wordList;
} Dictionary;

Dictionary* dictionaries;
int numOfDictionaries = 0;

void createNewDictionary(), addWord(), deleteWord(), findWord(), searchWord(), deleteDictionary(), Exit();
void printDictionaries(), printDictionary(int Dictionary_index), storeWord(int chosenDictionaryIdx, int languageIdx, char str[], int str_len), storeWordInList(int chosen_dic_idx, Word word), freeListDictionary( Word* iter), freeDictionaryIdx(int chosen_dic_idx);
int countLettInDictionary(char a, char word[]), findWordIndex(int chosen_dic_idx, char word[]);



int main() {
    while(1){
        int option = 6;
        printf("Welcome to the dictionaries manager!\n"
               "Choose an option:\n"
               "1. Create a new dictionary.\n"
               "2. Add a word to a dictionary.\n"
               "3. Delete a word from a dictionary.\n"
               "4. Find a word in a dictionary.\n"
               "5. Delete a dictionary.\n"
               "6. Exit.\n");
        scanf("%d", &option);
        if (option == 1){
            createNewDictionary();
        } else if ((numOfDictionaries == 0) && ((option == 2) || (option == 3) || (option == 4) || (option == 5) || (option == 6))){
            printf("This option is not available right now, try again:\n");
        } else{
            if (option == 2 ){
                addWord();
            } else if (option == 3){
                deleteWord();
            } else if (option == 4){
                findWord();
            } else if (option == 5){
                deleteDictionary();
            } else if (option == 6){
                Exit();
                break;
            } else{
                printf("Wrong option, try again:\n");
            }
        }
    }
}



void createNewDictionary(){
    printf("Define a new dictionary:\n");
    //initialization:
    int clear_idx = 0, str_len = 2, current_language = 0;
    char let;
    char *temp_str = malloc(2*sizeof(char));
    if(temp_str == NULL){
        printf("The creation of the dictionary has failed!");
        return;
    }
    temp_str[1] = '\0';
    if(numOfDictionaries > 0){
        dictionaries = realloc(dictionaries, (numOfDictionaries+1)*sizeof(Dictionary));
        if(dictionaries == NULL){
            printf("The creation of the dictionary has failed!");
            return;
        }
    }
    else{
        dictionaries = malloc(sizeof(Dictionary));
        if(dictionaries == NULL){
            printf("The creation of the dictionary has failed!");
            return;
        }
    }
    numOfDictionaries++;
    clear_idx = (numOfDictionaries-1);


    dictionaries[clear_idx].wordList = malloc(1* sizeof(Word*));
    if(dictionaries[clear_idx].wordList == NULL){
        printf("The creation of the dictionary has failed!");
        return;
    }
    dictionaries[clear_idx].numOfLanguages = 0;
    dictionaries[clear_idx].wordList = NULL;
    //the code:
    scanf(" %c", &let);
    dictionaries[clear_idx].languages = malloc(1* sizeof(char *));
    while(let != '\n'){
        if(let == ','){
            storeWord(clear_idx, current_language, temp_str, str_len);
            current_language++;

            free(temp_str);
            temp_str = malloc(2*sizeof(char));
            if(temp_str == NULL){
                printf("The creation of the dictionary has failed!");
                return;
            }
            temp_str[1] = '\0';
            str_len = 2;
            scanf("%c", &let);
        }else{
            //expand the temp
            //insert the char to the temp str
            //get another char
            temp_str = realloc(temp_str, (str_len+1)*sizeof(char));
            if(temp_str == NULL){
                printf("The creation of the dictionary has failed!\n");
                return;
            }
            temp_str[str_len]='\0';
            str_len++;
            temp_str[str_len-3] = let;
            scanf("%c", &let);
        }
    }
    storeWord(clear_idx, current_language, temp_str, str_len);
    free(temp_str);
    printf("The dictionary has been created successfully!\n");
}

void addWord(){
    //initialization:
    int chosen_dic_idx = 0, word_idx = 0, clear_translation_idx=0, str_len = 2;
    char *temp_str = (char *)malloc(2*sizeof(char));
    temp_str[1] = '\0';
    char let;
    Word word;
    word.translations = (char **)malloc(sizeof(char *));
    word.next = NULL;
    //printing:
    printf("Choose a dictionary:\n");
    printDictionaries();
    //recieving:
    scanf("%d", &chosen_dic_idx);
    chosen_dic_idx = chosen_dic_idx-1;
    printf("Enter a word in ");
    printDictionary(chosen_dic_idx);
    printf(":\n");

    scanf(" %c", &let);
    while(let != '\n'){
        if(let == ','){
            word.translations = (char **)realloc(word.translations, (clear_translation_idx+2)*sizeof(char*));
            word.translations[clear_translation_idx] = (char *)malloc((str_len)*sizeof(char));
            word.translations[clear_translation_idx][str_len-1] = '\0';
            strcpy(word.translations[clear_translation_idx], temp_str);
            clear_translation_idx++;

            free(temp_str);
            temp_str = (char *)malloc(2*sizeof(char));
            temp_str[1] = '\0';
            str_len = 2;
            scanf("%c", &let);
        } else{
            temp_str = (char *)realloc(temp_str, str_len+1);
            str_len++;
            temp_str[str_len-1] = '\0';
            temp_str[str_len-3] = let;
            scanf("%c", &let);
        }
    }
    word.translations = (char **)realloc(word.translations, (clear_translation_idx+2)* sizeof(char *));
    word.translations[clear_translation_idx] = (char *)malloc((str_len+1)*sizeof(char));
    word.translations[clear_translation_idx][str_len] = '\0';
    strcpy(word.translations[clear_translation_idx], temp_str);

    //storing the word:
    Word* word_pointer = (Word*)malloc(sizeof(word));
    *word_pointer = word;
    word_pointer->next = dictionaries[chosen_dic_idx].wordList;
    dictionaries[chosen_dic_idx].wordList = word_pointer;


    printf("The word has been added successfully!\n");
}

void deleteWord(){
    //initializiation:
    int chosen_dic_idx = 0, str_len = 2;
    char *chosen_word = malloc(2*sizeof(char));
    chosen_word[1] = '\0';
    char lett;
    char is_sure;
    //printing
    printf("Choose a dictionary:\n");
    printDictionaries();
    //recieving:
    scanf("%d", &chosen_dic_idx);
    chosen_dic_idx = chosen_dic_idx-1;
    printf("Enter a word in %s:\n", dictionaries[chosen_dic_idx].languages[0]);
    scanf(" %c", &lett);
    while (lett != '\n'){
        chosen_word = realloc(chosen_word, (str_len + 1));
        chosen_word[str_len-1] = '\0';
        chosen_word[str_len-2] = lett;
        str_len++;
        scanf("%c", &lett);
    }

    printf("Are you sure? (y/n)\n");
    scanf("%c", &is_sure);
    //the code:
    if(is_sure == 'y'){
        //goes all over the list till finds
        //delete the word
        Word* list_iter = dictionaries[chosen_dic_idx].wordList;
        Word* previous;
        if(strcmp(list_iter->translations[0], chosen_word) == 0){
            dictionaries[chosen_dic_idx].wordList = list_iter->next;
            list_iter->next = NULL;
            return;
        }
        while (list_iter != NULL && (strcmp(list_iter->translations[0], chosen_word) != 0)){
            previous = list_iter;
            list_iter = list_iter->next;
        }
        if(list_iter == NULL){
            printf("The deletion of the word has failed!\n");
        }
        else if(strcmp(list_iter->translations[0], chosen_word) == 0){
            previous->next = list_iter->next;
            list_iter->next = NULL;
        }
    } else{
        printf("The deletion of the word has been canceled.\n");
    }

    free(chosen_word);
}

void findWord(){
    //Initialize:
    int chosen_dic_idx = 0, chosen_word_idx, str_len = 2;
    char *chosen_word = malloc(2*sizeof(char));
    chosen_word[1] = '\0';
    char lett;
    //printing options:
    printf("Choose a dictionary:\n");
    printDictionaries();
    //recieving:
    scanf("%d", &chosen_dic_idx);
    chosen_dic_idx = chosen_dic_idx-1;
    printf("Enter a word in %s:\n", dictionaries[chosen_dic_idx].languages[0]);
    scanf(" %c", &lett);
    while (lett != '\n'){
        chosen_word = (char *)realloc(chosen_word, (str_len+1)*sizeof(char));
        str_len++;
        chosen_word[str_len-3] = lett;
        chosen_word[str_len-1] = '\0';
        scanf("%c", &lett);
    }
    chosen_word[str_len-1] = '\0';
    //checks if the word is in the dictionary
    //stores its value
    //prints
    Word* iter = dictionaries[chosen_dic_idx].wordList;
    while((iter != NULL) && (strcmp(iter->translations[0], chosen_word) != 0)){
        iter = iter->next;
    }
    if (iter == NULL){
        printf("There are no translations for \"%s\" in this dictionary.\n", chosen_word);
    }
    else{
        printf("The translations are:\n");
        int i;
        for(i = 1; i < (dictionaries[chosen_dic_idx].numOfLanguages-1); i++){
            printf("%s: %s, ", dictionaries[chosen_dic_idx].languages[i], iter->translations[i]);
        }
        printf("%s: %s\n", dictionaries[chosen_dic_idx].languages[i], iter->translations[i]);

    }

}

void deleteDictionary(){
    printf("fuck you");
    /*
    //Initialization:
    int chosen_dic_idx = 0;
    char is_sure;
    //printing:
    printf("Choose a dictionary:\n");
    printDictionaries();
    //recieving:
    scanf("%d", &chosen_dic_idx);
    chosen_dic_idx = chosen_dic_idx-1;
    printf("Are you sure? (y/n)\n");
    scanf("%c", &is_sure);

    if(is_sure == 'y'){
        for(int j = (chosen_dic_idx); j < (numOfDictionaries-chosen_dic_idx-1); j++){
            dictionaries[j] = dictionaries[j+1];
        }
        freeDictionaryIdx((numOfDictionaries-1));
        numOfDictionaries=numOfDictionaries-1;
        printf("The dictionary has been deleted successfully!");
    } else{
        printf("The deletion of the dictionary has been canceled.");
    }*/
}

void Exit(){
    printf("stupid boomers");
    /*
    for(int i = 0; i < numOfDictionaries; i++){
        freeDictionaryIdx(i);
    }
    free(dictionaries);
    printf("Bye!");
    */
}











void storeWordInList(int chosen_dic_idx, Word word){
    printf("%s work printing\n", word.translations[0]);
    Word* word_pointer = (Word*)malloc(sizeof(word));
    *word_pointer = word;
    word_pointer->next = dictionaries[chosen_dic_idx].wordList;
    dictionaries[chosen_dic_idx].wordList = word_pointer;
    printf("%s", dictionaries[chosen_dic_idx].wordList->translations[0]);


   /*
    if(dictionaries[chosen_dic_idx].wordList == NULL){
        dictionaries[chosen_dic_idx].wordList = (Word *)malloc(sizeof(Word));
        *(dictionaries[chosen_dic_idx].wordList) = word;
    }
    else{
        Word* word_list_iterator;
        word_list_iterator = dictionaries[chosen_dic_idx].wordList;
        Word* word_pointer = malloc(sizeof(word));
        (*word_pointer) = word;
        while (word_list_iterator->next != NULL){
            word_list_iterator = word_list_iterator->next;
        }
        (word_list_iterator->next) = word_pointer;
    }
*/
}

void freeDictionaryIdx(int chosen_dic_idx){
    freeListDictionary(dictionaries[chosen_dic_idx].wordList);
    for(int i = 0; i < dictionaries[chosen_dic_idx].numOfLanguages; i++){
        free(dictionaries[chosen_dic_idx].languages[i]);
    }
    free(dictionaries[chosen_dic_idx].languages);
    free(dictionaries[chosen_dic_idx].numOfLanguages);
}

void freeListDictionary( Word* iter){
    if(iter != NULL){
        freeListDictionary(iter->next);
        free(iter);
        return;
    }
    return;
}

void storeWord(int chosenDictionaryIdx, int languageIdx, char str[], int str_len){
    dictionaries[chosenDictionaryIdx].languages = realloc(dictionaries[chosenDictionaryIdx].languages, (dictionaries[chosenDictionaryIdx].numOfLanguages+1)*sizeof(char *));
    dictionaries[chosenDictionaryIdx].languages[languageIdx] = malloc(str_len*sizeof(char));
    dictionaries[chosenDictionaryIdx].languages[languageIdx][str_len-1] = '\0';
    strcpy(dictionaries[chosenDictionaryIdx].languages[languageIdx], str);
    dictionaries[chosenDictionaryIdx].numOfLanguages++;
}

int findWordIndex(int chosen_dic_idx, char word[]){
    for(int i = 0; dictionaries[chosen_dic_idx].wordList[i].next != NULL; i++){
        if(strcmp(word,dictionaries[chosen_dic_idx].wordList[i].translations[0]) == 0){
            return i;
        }
    }
    return -1;

}

void printDictionaries(){
    //go all over the dictionaries and print, use iterator, use printDictionary().
    for(int i = 0; i < (numOfDictionaries); i++){
        printf("%d. ", (i+1));
        printDictionary(i);
        printf("\n");
    }
}

void printDictionary(Dictionary_idx){
    int i = 0;
    for(i = 0; i < (dictionaries[Dictionary_idx].numOfLanguages-1); i++){
        printf("%s,", dictionaries[Dictionary_idx].languages[i]);
    }
    printf("%s", dictionaries[Dictionary_idx].languages[i]);
}
