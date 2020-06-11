#include<iostream>
#include<cstring>
using namespace std;


class Date
{
    
public:
    Date(int m=6, int d=21, int y=2019);
    Date setDate(int m,int d,int y);
    void print();
    
private:
    int month,day,year;
    
};



class Movie
{
    
public:
    
    Movie();
    Movie(string t,string d, char g, Date r, int nw, double wr[]);
    
    
    Movie setMovieData(string t,string d,char g,int m,int da,int y,int numberOfWeeks, double weeklyTake[]);
    
    ~Movie(); //destructor
    
    string getTitle() const;
    char getGenre() const;
    void display();
    double getBoxOffice();
    
    
private:
    string title,director;
    char genre;
    Date releaseDate;
    int numWeeks;       //number of things in the array
    double *weeklyRevenue;      //array
    
};




class MovieList
{
    
public:
    MovieList();
    int getCapacity();
    int getSize();
    ~MovieList();   //destructor
    
    void addMovie(string t,string d,char g,int m,int da,int y,int numberOfWeeks, double weeklyTake[]);
    void insertMovie(Movie , int position);
    void deleteMovie(string t);
    void displayList();
    void displayByGenre(const char g);
    int search (const string t);
    
private:
    int capacity,size;
    Movie *moviearray;      //array
    
};
