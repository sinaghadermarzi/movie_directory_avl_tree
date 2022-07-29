
#include <iostream>
#include "MoviesDirectory.h"

using namespace std;

bool compare(char* s1,char * s2)
{
	
	char *c1 = s1;
	char *c2 = s2;
	if (c1 && c2)
	{
		while((*c1) && (*c2))
		{
			if ((*c1)!= (*c2))
				return 0;
			c1++;
			c2++;
		}
		if (*c1 == *c2)
			return 1;
		return 0;
	}
}


int main()
{
	MovieDirectory DATA;
	char  command[100];
	while(1)
	{
		cin>>command;
		if (compare(command ,"addmovie"))
			DATA.add_movie();
		if (compare(command, "deletemovie"))
			DATA.delete_movie();
		if (compare(command, "addactor"))
			DATA.add_actor();
		if (compare(command ,"deleteactor"))
			DATA.delete_actor();
		if (compare(command , "findmovie"))
			DATA.find_movie();
		if (compare(command, "findactor"))
			DATA.find_actor();
		if (compare(command , "findyear"))
			DATA.find_year();
		if (compare(command, "findyears"))
			DATA.find_years();
		if (compare(command ,"listmovies"))
			DATA.list_movies();
		if (compare(command , "exit"))
			return 0;
	}
}