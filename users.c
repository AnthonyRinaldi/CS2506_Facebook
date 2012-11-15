#include "users.h"

extern 

int adduser(struct user* array[], int freeEntry, char* n, char* l, int g, int a)
{
	struct user u;
	u->name = n;
	u->location = l;
	u->gender = g;
	u->age = a;

	array[freeEntry++] = &u;
	return freeEntry;
}

void removeuser(int)
{
	// TODO: Remove user from file.
}
