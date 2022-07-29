#include <iostream>
#include "LinkedString.h"
#include "AVL.h"

using namespace std;

class ActorAVL:AVL<LinkedString,char>
{
	friend class MovieDirectory;
	friend struct MovieProperties;
};

struct MovieProperties
{
	MovieProperties(){year =0; duration = 0;}
	MovieProperties & operator=(const MovieProperties & _rs);
	int year;
	int duration;
	ActorAVL actors;
};
MovieProperties & MovieProperties::operator=(const MovieProperties & _rs)
{
	delete actors.root;
	actors.root  = _rs.actors.root;
	duration = _rs.duration;
	year =_rs.year;
	return *this;
}

class MovieDirectory:AVL<LinkedString,MovieProperties>
{
public:
	void add_movie();
	void delete_movie();
	void add_actor();
	void delete_actor();
	void find_movie();
	void find_actor();
	void find_year();
	void find_years();
	void list_movies();
private:
	void printactornames(AVLNode<LinkedString,char>*);
	void printmovietitles(AVLNode<LinkedString,MovieProperties>*);
	int printactormovies(AVLNode<LinkedString,MovieProperties>*,LinkedString*);
	int printyearmovies(AVLNode<LinkedString,MovieProperties>*,int);
	int printyearsmovies(AVLNode<LinkedString,MovieProperties>*,int,int);
};



void MovieDirectory::add_movie()
{
	LinkedString l,Title;
	MovieProperties* m = new MovieProperties();
	Title.scan();
	cin>>(m->year);
	cin>>(m->duration);
	int i,N ;
	cin>>N ;
	for(i = 0; i < N;i++)
	{
		l.scan();
		m->actors.insert(l,0);
	}
	insert(Title,*m);
	m->actors.root = 0;
	delete m;
}
void MovieDirectory::delete_movie()
{

	LinkedString l;
	l.scan();
	Delete(l);

}

void MovieDirectory::add_actor()
{
	LinkedString l;
	l.scan();
	AVLNode<LinkedString,MovieProperties> *q = Search(l);
	if (!q)
	{
		return;
	}
	l.scan();
	q->SD.actors.insert(l,0);
}
void MovieDirectory::delete_actor()
{
	LinkedString l;
	l.scan();
	AVLNode<LinkedString,MovieProperties> *q = Search(l);
	l.scan();
	if (!q)
	{
		return;
	}
	q->SD.actors.Delete(l);
}
void MovieDirectory::find_movie()
{

	LinkedString l;
	l.scan();
	AVLNode<LinkedString,MovieProperties> *q = Search(l);
	if (!q)
	{
		cout<<"not found"<<endl;
		return;
	}		
	else
	{
		q->Key.print();
		cout<<endl;
		cout<<q->SD.year<<endl;
		cout<<q->SD.duration<<endl;
		printactornames(q->SD.actors.root);
	}	
}
void MovieDirectory::find_actor()
{
	LinkedString l;
	l.scan();
	AVLNode<LinkedString,MovieProperties> *q = root;
	if (!printactormovies(root,&l))
		cout<<"not found"<<endl;
}
void MovieDirectory::find_year()
{
	int year;
	cin>>year;
	if (!printyearmovies(root , year))
		cout<<"not found"<<endl;
}
void MovieDirectory::find_years()
{
	int year1,year2;
	cin>>year1;
	cin>>year2;
	if(!printyearsmovies(root,year1,year2))
		cout<<"not found"<<endl;
}

void MovieDirectory::list_movies()
{
	printmovietitles(root);
}

void  MovieDirectory::printactornames(AVLNode<LinkedString,char>* q)
{
	if(!q) return;
	if(q->LC)
		printactornames(q->LC);

	q->Key.print();
	cout<<endl;

	if (q->RC)
		printactornames(q->RC);
}
void MovieDirectory::printmovietitles(AVLNode<LinkedString,MovieProperties>* q)
{
	if(!q) return;

	if(q->LC)
		printmovietitles(q->LC);

	q->Key.print();
	cout<<endl;

	if (q->RC)
		printmovietitles(q->RC);
}
int MovieDirectory::printactormovies(AVLNode<LinkedString,MovieProperties>* q,LinkedString* nameptr)
{
	int res = 0;
	if(!q) return 0;
	if(q->LC)
	{
		if(printactormovies(q->LC,nameptr))
			res = 1;
	}
	if(q->SD.actors.Search(*nameptr))
	{
		q->Key.print();
		cout<<endl;
		res = 1;
	}
	if (q->RC)
	{
		if(printactormovies(q->RC,nameptr))
			res = 1;
	}
	return res;
}
int MovieDirectory::printyearmovies(AVLNode<LinkedString,MovieProperties> *q,int year)
{
	int res = 0;
	if(!q) return 0;

	if(q->LC)
	{
		if (printyearmovies(q->LC,year))
			res = 1;
	}
	if(q->SD.year == year)
	{
		q->Key.print();
		cout<<endl;
		res = 1;
	}
	if (q->RC)
	{
		if(printyearmovies(q->RC,year))
			res = 1; 
	}

}
int MovieDirectory::printyearsmovies(AVLNode<LinkedString,MovieProperties> *q, int year1, int year2)
{
	int res = 0;
	if(!q) return 0;
	if(q->LC)
		if(printyearsmovies(q->LC,year1,year2))
			res = 1;
	if((q->SD.year >= year1)&&(q->SD.year <= year2))
	{
		q->Key.print();
		cout<<endl;
		res = 1;
	}
	if (q->RC)
		if (printyearsmovies(q->RC,year1,year2))
			res = 1;
	return res;
}

