// Social Network Program
// Author: Anthony Rinaldi
// CS 2506 Project

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include "linked_list.h"
#include "print.h"

// Delcare helper methods
void parse_command(char commStr[], int stringSize);

// Declare variables...
FILE* out;
FILE* in;
int userNum;
struct node *root;


int main(int argc, char* argv[])
{
	// set user number to userNum
	userNum = 0;
	// Create new llist root node
	
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
		} while (strncmp(buffer, "exit_program",12) != 0 );
		
	}
	else if (argc == 4 && strncmp(argv[1],"-f",2) == 0)
	{
		// -f input output, means load the commands from a file
		in = fopen(argv[2],"r");
		out = fopen(argv[3],"w");
		
		// take the buffer and check it out. Does EOF test, too...
		while (strncmp(buffer, "exit_program",12) != 0 && fgets(buffer, sizeof(buffer), in) != NULL)
		{
			//fprintf(out, buffer);
			parse_command(&buffer, 200);
		}
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

	// Add User
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
		if(temp < 4)
		{
			fprintf(out, "Useage: add_user name age gender location\n");
			// Not enough command parameters
		}
		// TODO: Check if already a user
		else
		{
			// Add the user to the llist.
			/*struct node add;
			add.name = str1;
			add.age = num1;
			add.location = str3;
			if (str2 == "male")
				add.age = 0;
			else
				add.age = 1;
			userNum++;
			if (root == NULL)
				root = add;
			else*/
			//fprintf(out, "Add User %s\n", str1);
			if (strncmp(str2,"male",4) == 0)
				append(&root, str1, str2, num1, 0);
			else if (strncmp(str2,"female",6) == 0)
				append(&root, str1, str2, num1, 1);

			fprintf(out, "%s joined facebook\n", str1);
		}
	}
	// Add Friend
	else if (strncmp(command,"add_friend",10) == 0 )
	{
		int temp = sscanf(commStr, "%s %s %s", command, str1, str2);
		/*
		str1 = friend1
		str2 = friend2
		*/
		if(temp < 3)
		{
			// Not enough command parameters
		}
		// TODO: Check isExist, Ensure not already friends
		else
		{
			// TODO: Make list sorted
			// TODO: Create friendNode LLIST
			struct node * fr1;
			struct node * fr2;
			fr1 = findName(&root, str1);
			fr2 = findName(&root, str2);
			
			// Only friend if they are not yet.
			if (isFriends(&fr1, &fr2) > 0)
			{
				appendF(&fr1, &fr2);
				fprintf(out, "%s and %s are now friends\n", str1, str2);
			}
			else
				fprintf(out, "%s and %s are already friends\n", str1, str2);
		}
		
	}	
	// Display the facebook graph
	else if (strncmp(command,"display_graph",13) == 0 )
	{
		int temp = sscanf(commStr, "%s %s", command, str1);
		/*
		str1 = friend1
		str2 = friend2
		*/
		if(temp < 1 || temp > 1)
		{
			fprintf(out, "Useage: display_graph");
			// Not enough/too many command parameters
		}
		else
		{
			/* EXAMPLE Useage
			user1 -> user3 -> NULL
			user2 -> user3 -> NULL
			user3 -> user1 -> user2 -> NULL
			*/
			struct node *t;
			t = root;
			if (t == NULL)
			{
				// PRINT EMPTY
				fprintf(out, "No users present on facebook\n");
			}
			else while (t != NULL)
			{
				// Print User
				fprintf(out, "%s -> ", (*t).name);
				// TODO: Print friends;
				fprintf(out, " FRIENDS\n");
				t = (*t).next;
			}
			
		}
		
	}
	else // Bad command
	{
		fprintf(out, "Bad command\n");
	}

}
