#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

void RunGame(string s){
    int so_far_guessed_flag = 0;
    int incorrect_guesses_remaining = 6;
    int guessed_character_numbers = -1;
    
    //initialize the game, set the state of secret word to be _ _ _ , and so_far_guessed string to be spaces only
    string state = s + s;
    string so_far_guessed = state + "            ";
    for(int i = 0; i < state.length(); i++){
        if((i % 2) == 0) state[i] = '_';
        else state[i] = ' ';
    }
    
    for(int i = 0; i < so_far_guessed.length(); i++){
        so_far_guessed[i] = ' ';
    }
    

    while(incorrect_guesses_remaining > 0){
        int guessed_before_flag = 1;
        int correct_flag = 0;
        cout << "Secret word: " << state << endl;
        
        // if user has guessed words before, display them. otherwise don't display so far guessed:
        for(int i = 0; i < so_far_guessed.length(); i++){
            if(so_far_guessed[i] != ' ')
                so_far_guessed_flag = 1;
        }
        if(so_far_guessed_flag == 1){
            cout << "So far you guessed: "<<so_far_guessed << endl;
        }
        
        cout << "Incorrect guesses remaining: " << incorrect_guesses_remaining << "\n" << endl;
        cout << "Guess a letter: ";
        
        // read in a character, determine if it is legal.
        char guessed_letter;
        cin >> guessed_letter;
        
        while(!((guessed_letter >= 'a' && guessed_letter <='z') || (guessed_letter >= 'A' && guessed_letter <='Z'))){
            cout<< guessed_letter<<" is not a valid input."<<endl;
            cout << "Guess a letter:";
            cin >> guessed_letter;
        }
        guessed_letter = toupper(guessed_letter);
        
        // determine if the character has been guessed, if so then read in a new character
        while(guessed_before_flag == 1){
            guessed_before_flag = 0;
            
            for(int m = 0; m < so_far_guessed.length(); m++){
                if(guessed_letter == so_far_guessed[m]){
                    guessed_before_flag = 1;
                }
            }
            
            if(guessed_before_flag == 1){
                cout<<"Sorry, you already guessed that."<<endl;
                cout << "Guess a letter: ";
                cin >> guessed_letter;
                while(!((guessed_letter >= 'a' && guessed_letter <='z') || (guessed_letter >= 'A' && guessed_letter <='Z'))){
                    cout<< guessed_letter<<" is not a valid input."<<endl;
                    cout << "Guess a letter:";
                    cin >> guessed_letter;
                }
                guessed_letter = toupper(guessed_letter);
            }
        }
        // up to here, succesfully read in a legal ungessed character
        guessed_character_numbers ++;
        so_far_guessed[guessed_character_numbers * 2] = guessed_letter;
        
        //check if the letter is in secret word, if so, update correct_flag and state of the word
        for(int k = 0; k < s.length(); k++){
            if(guessed_letter == s[k]){
                correct_flag = 1;
                state[k * 2] = s[k];
            }
        }
        //if the letter is in secret word
        if(correct_flag == 1){
            cout << "Right!\n" << endl;
            int check = 0;
            while(check < state.length()){
                if(state[check] == '_')break;
                check = check + 2;
                if(check >= state.length()){
                    cout << "The secret word was " << s << endl;
                    cout << "You win!\n" << endl;
                    exit(1);
                }
            }
        }
        //if the letter is not in secret word
        else{
            cout << "Wrong!\n" << endl;
            incorrect_guesses_remaining --;
            if(incorrect_guesses_remaining == 0){
                cout << "The secret word was " << s << endl;
                cout << "You lose!\n" << endl;
                exit(1);
            }
            
        }
    }
}




int main(int argc, char** argv){
    ifstream infile(argv[1]);
    if( ! infile.is_open()){
        cout<< "Error: Opening file failed"; exit(1);
    }
    cout << "\n\nWelcome to Hangman!\n";
    
    //count the number of lines in the file
    char c;
    int count_lines;
    
    while(!infile.eof()){
        c = infile.get();
        if(c == '\n'){
            count_lines++;
        }
    }
    
    //generate a random number using the total number of lines in the file
    srand((unsigned)(time(0)));
    int randomNumber = rand() % count_lines;
    infile.close();
    
    //loop to a specific line using random number generated previously and get the content of that line
    string to_be_guessed;
    infile.open(argv[1]);
    
    for(int i = 0; i < randomNumber; ++i){
        getline(infile, to_be_guessed);
    }
    
    getline(infile, to_be_guessed);
    for(int i = 0; i < to_be_guessed.length(); i++){
        to_be_guessed[i] = toupper(to_be_guessed[i]);
    }
    
    //the game begins here.
    RunGame(to_be_guessed);
    infile.close();
}


