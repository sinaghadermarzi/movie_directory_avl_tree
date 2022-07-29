#pragma once
#include <iostream>
using namespace std;

struct LinkedStringNode
{
	LinkedStringNode(){next = 0;}
	LinkedStringNode* next;
	char data;
};

class LinkedString
{
	friend char compare(const LinkedString &l1,const LinkedString &l2);
public:
	LinkedString(){ first = 0;}
	~LinkedString();
	LinkedString& operator=(const LinkedString& _rs);
	LinkedString& operator=(char * _rs);
	void print();
	void scan();
private:
	LinkedStringNode* first;
};
LinkedString::~LinkedString()
{
	LinkedStringNode *p,*q ;
	p = first;
	while(p)
	{
		q = p->next;
		delete p ;
		p = q;		
	}
}


LinkedString& LinkedString::operator =(char *_rs)
{
	this->~LinkedString();
	first = 0;
	char *c = _rs;
	LinkedStringNode *p;
	if (c)
	{
		if (*c)
		{
			p = first = new LinkedStringNode;
			first->data = *c;
			c++;
			while(*c)
			{
				p->next = new LinkedStringNode;
				p->next->data = *c;
				p = p->next;
				c++;
			}
			p->next  = 0;
		}
	}
	return *this;
}

LinkedString& LinkedString::operator =(const LinkedString & l1)
{
	this->~LinkedString();
	first =0;	
	LinkedStringNode *c = l1.first;
	LinkedStringNode *p;
	if (c)
	{
		p = first = new LinkedStringNode;
		first->data = c->data;
		c = c->next;	
		while(c)
		{
			p->next = new LinkedStringNode;
			p->next->data = c->data;
			p = p->next;
			c = c->next;
		}
		p->next  = 0;
	}
	return *this;
}
void LinkedString::print()
{
	LinkedStringNode* q =first;
	while(q)
	{
		putchar((int)(q->data));
		q = q->next;
	}
}
void LinkedString::scan()
{
	this->~LinkedString();
	first = 0;
	char c = getchar();
	while(c == '\n')
		c = getchar();
	LinkedStringNode *p;
	p = first = new LinkedStringNode();
	p->data = c;
	while((c = getchar())!='\n')
	{
		p->next = new LinkedStringNode();
		p->next->data = c;
		p = p->next;			
	}			
}
char compare(const LinkedString &l1,const LinkedString &l2)
{
	LinkedStringNode * p = l1.first;
	LinkedStringNode * q = l2.first;
	while(p && q)
	{
		if((p->data)>(q->data))
			return 1;
		else if ((p->data)<(q->data))
			return -1;
		else
		{
			p = p->next;
			q = q->next;
		}
	}
	if( p == q)
		return 0;
	if (p)
		return -1;
	if (q)
		return 1;
}



