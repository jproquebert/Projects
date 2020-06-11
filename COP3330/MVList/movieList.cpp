#include<iostream>
#include <cstring>
#include "movieList.hpp"

using namespace std;


Date::Date(int m, int d, int y)     //constructor for the date
{
    month=m;
    day=d;
    year=y;
}

Date Date::setDate(int m,int d,int y)
{
    month=m;
    day=d;
    year=y;
    if ((m<0) or (d<0) or (y<0))
    {
        month=6;
        day=21;
        year=2019;
    }
    return Date(month,day,year);
}

void Date::print()
{
    cout<<month<<"/"<<day<<"/"<<year;       //date printing
}

Movie::Movie()
{
    title="";
    director="";
    genre=' ';
    releaseDate.setDate(6,21,2019);     //default date 6/21/2019
    numWeeks=0;
    weeklyRevenue=NULL;
}


Movie::Movie(string t,string d, char g, Date r, int nw, double wr[])
{
    title=t;
    director=d;
    genre=g;
    releaseDate=r;
    
    weeklyRevenue= new double[nw];  //allocating space in array
    
    numWeeks=nw;
    
    for (int i=0;i<nw;i++)
    {
        weeklyRevenue[i]=wr[i];
    }
}



Movie Movie::setMovieData(string t,string d,char g,int m,int da,int y,int numberOfWeeks, double weeklyTake[])
{
    title=t;
    director=d;
    genre=g;
    releaseDate.setDate(m,da,y);
    
    weeklyRevenue= new double[numberOfWeeks];
    
    numWeeks= numberOfWeeks;
    
    for (int i=0;i<numberOfWeeks;i++)
    {
        weeklyRevenue[i]=weeklyTake[i];
    }
    return Movie(title,director,genre,releaseDate,numWeeks,weeklyRevenue);
}


string Movie::getTitle() const
{
    return title;
}

char Movie::getGenre() const
{
    return genre;
}

void Movie::display()
{
    string g;
    cout<<"\nTitle: "<<title;
    cout<<"\nDirector: "<<director;
    
    switch (genre)      //turning the genre into a string
    {
        case 'A': g="Action";
            break;
        case 'C': g="Comedy";
            break;
        case 'D': g="Drama";
            break;
        case 'F': g="Fantasy";
            break;
        case 'H': g="Horror";
            break;
        case 'S': g="Sci-Fi";
            break;
        case 'T': g="Thriller";
            break;
    }
    cout<<"\nGenre: "<<g;
    cout<<"\nRelease date: ";
    releaseDate.print();        //printing object's date
    cout<<"\nWeeks since release: "<<numWeeks;
    cout<<"\nBox Office: "<<getBoxOffice();
    cout<<"\n"<<endl;
} 

double Movie::getBoxOffice()
{
    double total=0;
    for (int i=0;i<numWeeks;i++)
    {
        total=weeklyRevenue[i]+total;   //adding revenues
    }
    return total;
}



MovieList::MovieList()
{
    capacity=5;
    size=0;
    moviearray=new Movie [capacity];        //capacity sets array space
}



int MovieList::getCapacity()
{
    return capacity;
}

int MovieList::getSize()
{
    return size;
}

void MovieList::addMovie(string t, string d, char g, int m, int da, int y, int numberOfWeeks, double weeklyTake[])
{
    moviearray[size].setMovieData(t,d,g,m,da,y,numberOfWeeks, weeklyTake);  //initializing movie
    cout<<"\nMovie added\n";
    size=size+1;
    if (size>capacity)
    {
        capacity=capacity+5;
    }
}

void MovieList::insertMovie(Movie m, int p)
{
    Movie temp;
    size=size+1;
    int counter=0;
    if (size>capacity)
    {
        capacity=capacity+5;
    }
    if ((p>=0) and (p<=size))
    {
        for (int i=p+1;i<=size;i++)     //shifting and storing array elements
        {
            counter=i;
            temp=moviearray[size];
            moviearray[size]=moviearray[i];
            moviearray[i]=temp;
        }
        moviearray[p+1]=m;
        cout<<"\nMoved "<<counter-p-2;      //counting amount of moved elements in the array
        cout<<"\nMovie successfully added"<<endl;
    }
    else
        cout<<"\nUnable to add\n";      //if p is outside of boundaries
}

void MovieList::deleteMovie(string t)
{
    int count=0;
    
    
    if (search(t)<0)        //testing if movie is within array
    {
        cout<<"\nMovie not found\n";
    }
    
    for (int i=0;i<size;i++)
    {
        if (moviearray[i].getTitle()==t)
        {
            cout<<"\nMovie deleted\n";
            for (int j=i;j<size;j++)
            {
                moviearray[j]=moviearray[j+1];     //shifting and overwriting array elements
            }
            size=size-1;        //deleting empty space at the very end
        }
    }
    
    if (capacity>5)
    {
        for (int i1=0;i1<capacity;i1++)
        {
            if ((moviearray[i1].getTitle()=="") and (moviearray[i1].getGenre()==' '))
            {
                count=count+1;
            }
            if (count==5)
            {
                capacity=capacity-5;
            }
        }
    }
}

void MovieList::displayList()
{
    for (int i=0;i<size;i++)
    {
        cout<<"Movie "<<i+1<<":";
        moviearray[i].display();        //printing entire movie array
    }
}

void MovieList::displayByGenre(const char g)
{
    for (int i=0;i<size;i++)
    {
        if (moviearray[i].getGenre()==g)        //testing genre character equality
        {
            cout<<"\nMovie "<<i+1<<":";     //position "0" displayed as 1
        moviearray[i].display();
        }
    }
}

int MovieList::search(const string t)
{
    for (int i=0;i<size;i++)        //testing for title equality
    {
        if (moviearray[i].getTitle()==t)
        {
            return i;
        }
    }
    return -1;
}

Movie::~Movie()     //movie destructor
{
    if(weeklyRevenue != NULL)
    {
        delete [] weeklyRevenue;
        weeklyRevenue = NULL;
    }
}

MovieList::~MovieList()     //movielist destructor
{
    if (moviearray!=NULL)
    {
        delete[] moviearray;
        moviearray=NULL;
    }
}


