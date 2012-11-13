// Social Network Program
// Author: Anthony Rinaldi
// CS 2506 Project

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include "linked_list.h"
#include "print.h"
#include "users.h"

// Delcare helper methods
void parse_command(char commStr[], int stringSize);

// Declare variables...
FILE* out;
FILE* in;
// Total number of users
int firstFreeEntry;
// User Array
struct user users[];


int main(int argc, char* argv[])
{
	// set user number to userNum
	userNum = 0;
	// Create new llist root node
	struct node *root;
	root = NULL;

	char buffer[200];
	int count = 0;
	while (count < 200)
	{
		buffer[count] = '\0';
		count++;
	}

	if (argc == 2 && strncmp(argv[1],"-h",2) == 0)
	{
		out = stdout;
		// Just print useage for -h
		printUseage();
		return 0;
	}
	else if (argc >= 2 && strncmp(argv[1],"-i",2) == 0)
	{
		out = stdout;
		in = stdin;
		// Run in interactive StdIO mode.
		
		do
		{
			fgets(buffer, sizeof(buffer), in) != NULL;
			//fprintf(out, buffer);
			parse_command(&buffer, 200);
		} while (strncmp(buffer, "exit_program",12) != 0);
		
	}
	else if (argc == 4 && strncmp(argv[1],"-f",2) == 0)
	{
		// -f input output, means load the commands from a file
		in = fopen(argv[2],"r");
		out = fopen(argv[3],"w");
		
		// take the buffer and check it out.
		do
		{
			fgets(buffer, sizeof(buffer), in) != NULL;
			//fprintf(out, buffer);
			parse_command(&buffer, 200);
		} while (strncmp(buffer, "exit_program",12) != 0);
	}
	else
	{
		out = stdout;
		// Incorrect switch, so print useage and error.
		printUseage();
		printf("INVALID SWITCH PROVIDED\n");
		return 1;
	}
	
	return 0;

}

void parse_command(char commStr[], int stringSize)
{

	char* command;
	command = malloc(stringSize * sizeof(char *));
	char* str1;
	str1 = malloc(stringSize * sizeof(char *));
	char* str2;
	str2 = malloc(stringSize * sizeof(char *));
	char* str3;
	str3 = malloc(stringSize * sizeof(char *));
	int num1;
	int num2;
	int num3;
	// Get the first command
	sscanf(commStr, "%s", command);
	if (strncmp(command,"exit_program",13) == 0)
	{/* Do nothing!!! It is handled in the parent method */}
	// fibonacci_ser
	else if (strncmp(command,"add_user",8) == 0 )
	{
		int temp = sscanf(commStr, "%s %s %d %s %s", command, str1, &num1, str2, str3);
		/*
		str1 = name
		num1 = age
		str2 = gender
		str3 = location
		*/

		/*int i; int dig;
		for (i = 0; i < strlen(str1); i++)
		{
			dig = dig * isdigit(str1[i]);
		}*/
// Put the info into command and the number in num1
		if(temp < 5)
		{
			// Not enough command parameters
		}
		else
		{
			// Add the user to the llist.
			
			fprintf(out, "%s joined facebook\n", str1);
		}
	}

}
