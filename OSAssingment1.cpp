#include <iostream>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

using namespace std;

void Parse(char* args[], char line[]);
void fork(char* args[]);

int main(){
char line[256]; //entire line form user
char* args[64]; //pares arguments from line

while (strcmp(line,"exit") != 0){
	cout <<"Rolf>";
	cin.getline(line,255);
	if(strcmp(line,"exit") != 0){
		Parse(args, line);
		fork(args);
	}
}

cout << "goodbye\n";

return 0;
}

//******************************************************************************************
// input: line, args
// output: none
// dis: parses the command line into seperate arguments in the args[] Cstring array
//******************************************************************************************
void Parse(char* args[], char line[]){

while(*line != '\0'){
	while(*line == ' ' || *line == '\t'){
		*line++ = '\0'; // makes spaces null so we skip over
	}

	*args++ = line; // assignes current adress of line after the space skip to the args pointer array and increaments the args array by one

	while(*line != ' ' && *line != '\0' && *line != '\t'){
	line++; //does nothing with the values we want becuase it already has the address saved
	}

	*args = NULL; // assings the next pointer index to null
}

}

//*************************************************************************************
// input: args
// output: none
// dis: creates a fork and uses execvp to run the command put into the args array
//**************************************************************************************
void fork(char* args[]){

	pid_t pid = fork();
	if(pid == 0){
		//kid
		if(execvp(args[0], args) == -1){
			perror("exec");
			exit(0);
		}
	}
	if(pid > 0){
		//parent
		//cout << "parent:" << pid << "\n";
		wait(NULL);
	}

}

