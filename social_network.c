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
void parse_command(char * commStr, int stringSize);

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

	//char * buffer;
	//buffer = malloc(sizeof(char) * 2000);
	char buffer[2000];
	int count = 0;
	while (count < 2000)
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
			fgets(buffer, sizeof(buffer), in);
			//fprintf(out, buffer);
			parse_command((char *)&buffer, 200);
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
			parse_command((char *)&buffer, 200);
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

void parse_command(char commStr[200], int stringSize)
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
	//int num3;
	// Get the first command
	sscanf(commStr, "%s", command);
	if (strncmp(command,"exit_program",13) == 0)
	{/* Do nothing!!! It is handled in the parent method */
	}

	// Display Friends
	else if (strncmp(command, "display_friends", 15) == 0)
	{
		int temp = sscanf(commStr, "%s %s %s", command, str1, str2);	
		if (temp < 2 || temp > 2)
		{
			fprintf(out, "\"display_friends\" is not correctly called. The usage is: display_friends username. Please try again.\n");
			// Print Usage
		}
		else
		{

			struct node * node1;
			struct friendNode * fr1;
			node1 = findName(root, str1);
			fr1 = (node1->fr);
			if (fr1->nextFriend == NULL)
			{
				fprintf(out, "%s has no friends.\n", str1);
			}
			else
			{
				// TODO Continue writing display_friends
			}
		}
		
	}
	// Search Users
	else if (strncmp(command, "search_users", 12) == 0)
	{
		int temp = sscanf(commStr, "%s %s %s %s", command, str1, str2, str3);	

		if (temp < 3 || temp > 3)
		{
			fprintf(out, "\"search_users\" is not correctly called. The usage is: search_users name|location|age|gender username|location|age|male/female. Please try again.\n");
		}
		else
		{
			if (strncmp(str1, "name", 4) == 0)
			{
				struct node * tname;
				tname = findName(root, str2);
				if (tname == NULL)
				{
					fprintf(out, "%s not found.\n", str2);
				} else
				{
					if (tname->gender == 0)
						fprintf(out, "%s/%d/male/%s\n", str2, tname->age, tname->location);
					else
						fprintf(out, "%s/%d/female/%s\n", str2, tname->age, tname->location);
				}
			}
			else if (strncmp(str1, "location", 8) == 0)
			{
				// Search by location
				if (count(root) == 0)
				{
					fprintf(out, "No users found in %s.\n", str2);
				}
			}
			else if (strncmp(str1, "age", 8) == 0)
			{

			}
			else if (strncmp(str1, "gender", 8) == 0)
			{
				if (strncmp(str2, "male", 5) != 0 || strncmp(str2, "female", 7) != 0)
				{
					fprintf(out, "For gender based searching, users can be searched only by either \"male\" or \"female\". Please try again.");
				}
			}
			else
			{
				fprintf(out, "\"search_users\" cannot search by \"%s\". The correct usage is: search_users name|location|age|gender username|location|age|male/female. Please try again.\n", str1);
			}
		}
	}
	else if (strncmp(command, "suggest_friends", 15) == 0)
	{
		int temp = sscanf(commStr, "%s %s %s", command, str1, str2);	

		if (temp < 2 || temp > 2)
		{
			// Print Usage
		} else
		{
			if (count(root) ==  0 || findName(root, str1) == NULL)
			{
				fprintf(out, "User %s does not exist. Please try again.\n", str1);
			}
			else //if (count(root) == 1) TODO FIX!!!
			{
				fprintf(out, "Sorry, there are no friend suggestions for %s.\n", root->name);
			}
		}
	}
	// Delete Friend
	else if (strncmp(command, "delete_friend", 13) == 0)
	{
		int temp = sscanf(commStr, "%s %s %s %s", command, str1, str2, str3);
		
		// Make lowercase
		int counter = 0;
		char tempchar;
		while (str1[counter])
		{
			tempchar=str1[counter];
			str1[counter] = (tolower(tempchar));
			counter++;
		}
		counter = 0;
		while (str2[counter])
		{
			tempchar=str2[counter];
			str2[counter] = (tolower(tempchar));
			counter++;
		}
		

		// str1 User1
		// str2 User2
		struct node * fr1;
		struct node * fr2;
		fr1 = findName(root, str1);
		fr2 = findName(root, str2);
		if (temp < 3 || temp > 3)
		{
			fprintf(out, "\"delete_friend\" is not correctly called. The usage is: delete_friend username1 username2. Please try again.\n");
		}
		else if (count(root) == 0 || findName(root, str1) == NULL)
		{
			fprintf(out, "User %s does not exist. Please try again.\n", str1);

		}
		else if (findName(root, str2) == NULL)
		{
			fprintf(out, "User %s does not exist. Please try again.\n", str2);
		}
		else
		{
			// REMOVE FRIENDSHIP!
			delFriend(&fr1, &fr2);
			delFriend(&fr2, &fr1);
			fprintf(out, "%s and %s are not friends on facebook.\n", str1, str2);
		}
		// Now, verify that the two are friends
	}
	else if (strncmp(command,"delete_user",8) == 0 )
	{
		int temp = sscanf(commStr, "%s %s %s", command, str1, str2);

		if (temp > 2 || temp < 2)
		{
			// Print Usage
		}
		else 
		{
			// Delete all it's friendships, then delete it from the user list.
			//struct node * fr1;
			//fr1 = findName(root, str1);

			struct node **t;
			t = (struct node **)malloc(sizeof(struct node*));
			*t = root;
			if (*t == NULL)
			{
				// PRINT EMPTY
				fprintf(out, "No users present on facebook\n");
			}
			else 
			{
				while (*t != NULL)
				{
					//delFriend(&fr1, t);
					//delFriend(t, &fr1);

					t = &(**t).next;
				}

				// Friendships removed, now delete it.
				//delete(&root, str1);
				// Free the memory.
				//free(fr1);
			}
		}
		
	}

	// Add User
	else if (strncmp(command,"add_user",9) == 0 )
	{
		int temp = sscanf(commStr, "%s %s %d %s %s %d", command, str1, &num1, str2, str3, &num2);


		// Make lowercase
		int counter = 0;
		char tempchar;
		while (str1[counter])
		{
			tempchar=str1[counter];
			str1[counter] = (tolower(tempchar));
			counter++;
		}
		counter = 0;
		while (str2[counter])
		{
			tempchar=str2[counter];
			str2[counter] = (tolower(tempchar));
			counter++;
		}
		counter = 0;
		while (str3[counter])
		{
			tempchar=str3[counter];
			str3[counter] = (tolower(tempchar));
			counter++;
		}

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
			fprintf(out, "\"add_user\" is not correctly called. The usage is: add_user name age gender location. Please try again.\n");
			// Not enough command parameters
		}
		else if(num1 < 0)
		{
			fprintf(out, "The given age \"%d\" is negative, which is not allowed. Please try again.\n", num1);
		}
		else if(num1 > 100 || num1 == 0)
		{
			fprintf(out, "The age given for the user is not between 1 and 100. Please try again.\n");
		}
		// TODO: Check if already a user

		else
		{
			if (findName(root, str1) != NULL)
			{
				fprintf(out, "%s already exists. Please try again.\n", str1);
			}
			//else if ()
			else
			{
				if (strncmp(str2,"male",5) == 0)
					{append(&root, str1, str3, num1, 0);fprintf(out, "%s joined facebook.\n", str1);}
				else if (strncmp(str2,"female",7) == 0)
					{append(&root, str1, str3, num1, 1);fprintf(out, "%s joined facebook.\n", str1);}
				else
					fprintf(out, "The gender of the user can be either \"male\" or \"female\". Please try again.\n");
			}
			
		}
	}
	// Add Friend
	else if (strncmp(command,"add_friend",12) == 0 )
	{
		int temp = sscanf(commStr, "%s %s %s %s", command, str1, str2, str3);

		/*
		str1 = friend1
		str2 = friend2
		*/
		// Make them lowercase
		int counter = 0;
		char tempchar;
		while (str1[counter])
		{
			tempchar=str1[counter];
			str1[counter] = (tolower(tempchar));
			counter++;
		}
		counter = 0;
		while (str2[counter])
		{
			tempchar=str2[counter];
			str2[counter] = (tolower(tempchar));
			counter++;
		}

		if(temp < 3)
		{
			// Not enough command parameters
			fprintf(out, "\"add_friend\" is not correctly called. The usage is: add_friend username1 username2. Please try again.\n");
		}
		// TODO: Check isExist, Ensure not already friends
		else if (count(root) == 0 || findName(root, str1) == NULL)
		{
			fprintf(out, "User %s does not exist. Please try again.\n", str1);

		}
		else if (findName(root, str2) == NULL)
		{
			fprintf(out, "User %s does not exist. Please try again.\n", str2);
		}
		else if (findName(root, str2) == findName(root, str1))
		{
			fprintf(out, "%s is trying to add himself as a friend, which is not allowed. Please try again.\n", str1);	
		}
		else
		{
			// TODO: Make list sorted
			// TODO: Create friendNode LLIST
			struct node * fr1;
			struct node * fr2;
			fr1 = findName(root, str1);
			fr2 = findName(root, str2);

			struct friendNode * q;
			q = (struct friendNode *) malloc(sizeof(struct friendNode));
			((*q).user) = fr2;
			((*q).nextFriend) = NULL;
			//fprintf(out, "Try to friend: %s and %s\n", fr1->name, fr2->name);
			
			// Only friend if they are not yet.
			//if (isFriends(&fr1, &fr2) == 0)
			
			//appendF(&fr1, &fr2);
			addFriend(&fr1, &q);
			struct friendNode * s;
			s = (struct friendNode *) malloc(sizeof(struct friendNode));
			((*s).user) = fr1;
			((*s).nextFriend) = NULL;
			addFriend(&fr2, &s);
			fprintf(out, "%s and %s are friends now.\n", str1, str2);
			//else
			//	fprintf(out, "%s and %s are already friends\n", str1, str2);
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
			fprintf(out, "\"display_graph\" is not correctly called. The usage is: display_graph. Please try again.\n");
			// Not enough/too many command parameters
		}
		else
		{
			/* EXAMPLE Useage
			user1 -> user3 -> NULL
			user2 -> user3 -> NULL
			user3 -> user(*r)->fr1 -> user2 -> NULL
			*/
			struct node **t;
			t = (struct node **)malloc(sizeof(struct node*));
			*t = root;
			if (*t == NULL)
			{
				// PRINT EMPTY
				fprintf(out, "No users present on facebook.\n");
			}
			else while (*t != NULL)
			{
				// Print User
				fprintf(out, "%s", (**t).name);
				// Print friends;
				//fprintf(out, "FRIENDS\n");
				// First, check for start.
				struct friendNode **x;
				x = (struct friendNode **)malloc(sizeof(struct friendNode*));
				*x = ((*(**t).fr).nextFriend);
				int count = 0;
				while (*x != NULL)
				{
					fprintf(out, " -> %s", ((*(**x).user)).name);
					count++;
					x = &((**x).nextFriend);
				}
				if (count == 0)
					fprintf(out, " -> No Friends\n");
				else
					fprintf(out, " -> NULL\n");

				t = &(**t).next;
			}
			
		}
		
	}
	else // Bad command
	{
		fprintf(out, "ERROR -- The given string: '%s' is not a part of the valid functions. Please try again.\n", command);
	}

}
