/************************************************************
Lab 4: Sorting Movie from different catagories and print reports
CIS 22B - Lab 4
Author:Yi Wang
Date: 05/16/2015
*************************************************************/
/*This program will ask the name of input file and read movie data seperated by ','. 
Then, it will adjust the length of string attributes of strucutre used to store the movie data for report purpose.
After that, user can choose 1 of 4 option to call sort and report function in order to see result sorted by chosen catagory.
At last, it will repeat until user type n or N while the program ask user if continuing after each report.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/*Define the structure used to store movie information*/
struct Movie {
	string title;
	string director;
	string year;
	string duration;
};

/*Those 4 functions are used in sorting function as comparison method for different attributes*/
bool stringCmp(Movie , Movie );
bool intCmp(Movie, Movie);
bool durationCmp(Movie a, Movie b);
bool yearCmp(Movie a, Movie b);

/*Those 4 functions are used as sorting and reporting function*/
void TitleReport(vector <Movie>, int);
void DirectorReport(vector <Movie>, int);
void YearReport(vector <Movie>, int);
void DurationReport(vector <Movie>, int);

/*Those 4 functions are used to get the maximum length of different attributes from Movie structure vector*/
int DurationL(vector<Movie>, int);
int YearL(vector<Movie>, int);
int DirectorL(vector<Movie>, int);
int TitleL(vector<Movie>, int);

int main()
{
	vector<Movie> movie;//used to store all movie data
	Movie temp;//used to temperarily store a movie entry read from the file
	ifstream inputFile;
	string line, FileName;
	int Length=0;//counter for vector length
	char choice;
	int a, b, c, d;//used to store the maximum length of different attributes from Movie structure vector

	/*asking user the name of input file name*/
	cout << "Please type the file name: ";
	cin >> FileName;
	inputFile.open(FileName);//initial the first attempt to open the file

	/*if file opining failed, do another file open assuming user doesn't put .txt at the end of the file name*/
	if (inputFile.fail())
	{
		inputFile.clear();
		inputFile.open(FileName.append(".txt"));//adding .txt to the end of the input file name
	}

    /*if the file still can't be open, assume the file name is wrong and do a loop try to open the file with 
	input file name and,if still failed, input file name with .txt adding to the end of it*/
	while (inputFile.fail())
	{
		cout << "File isn't found. Please type again:";
		cin >> FileName;
		inputFile.open(FileName);
		if (inputFile.fail())
		{
			inputFile.clear();
			inputFile.open(FileName.append(".txt"));
		};

	};

	/*reading data from file from line to line*/
	while (getline(inputFile, line))   // reads a line from the file
	{	
		stringstream lineStream(line);   // transforms the line into a stream

		/*using tmp as a Movie structure entry to store all the info after 
		getting different types of info which separated by comma*/
		getline(lineStream, temp.title, ',');
		getline(lineStream, temp.director, ',');
		getline(lineStream, temp.year, ',');
		getline(lineStream, temp.duration, ',');	
		movie.push_back(temp);//using push_back and add a complete movie entry to the end of the Movie type vector
		Length++;//recording the length
	}
	inputFile.close();//close the file

	/*call the 4 functions to get maximum length from different attributes and store them in a,b,c and d*/
	a = DirectorL(movie, Length);
	b = YearL(movie, Length);
	c = DurationL(movie, Length);
	d = TitleL(movie, Length);

	/*Adjust the length of different attributes:
	assume a=6,which is the maximum string length of director attributes,
	assume the string length of direcotr string from the 1st and 2nd element in the vector are 4 and 6,
	adding 6-4+2 which 4 space at the end of the string to the 1st, adding 6-6+2 which is 2 space at the end of the second one,
	so both string length will be 8 and ending with space, making report look much better
	*/
	for (int i = 0; i < Length; i++)
	{
		movie[i].director.append(a + 2 - movie[i].director.length(), ' ');
		movie[i].year.append(b + 2 - movie[i].year.length(), ' ');
		movie[i].duration.append(c + 2 - movie[i].duration.length(), ' ');
		movie[i].title.append(d + 2 - movie[i].title.length(), ' ');

	};


	/*Menu:asking option and call for certain function to give sorted reports*/
	while (true)
	{
		cout << "-------------------------------------------" << endl;
		cout << "1,Show movie report sorted by Title"<<endl;
		cout << "2,Show movie report sorted by Director"<<endl;
		cout << "3,Show movie report sorted by Year"<<endl;
		cout << "4,Show movie report sorted by Duration"<<endl;
		cout << "-------------------------------------------" << endl;

		cin >> choice;

		switch (choice)
		{
		    case'1':
				TitleReport(movie, Length);
				break;
			case'2':
				DirectorReport(movie, Length);
				break;
			case'3':
				YearReport(movie, Length);
				break;
			case'4':
				DurationReport(movie, Length);
				break;
		}
		/*continue or not*/
		cout << "Continue?y/n:";
		cin >> choice;
		if (tolower(choice) == 'n')
		{
			break;
		}
	}
	
	
	
	
	
	
}

int DirectorL(vector<Movie> m,int Length)
{   /*used to compare all director string length, get the maximum and return the value*/
	int a = m[0].director.length();
		

	for (int i = 1; i < Length; i++)
	{
		if (a< m[i].director.length())
		{
			a = m[i].director.length();
		};
		
	}

	return a;
}

int YearL(vector<Movie> m, int Length)
{   /*used to compare all movie Length string length, get the maximum and return the value*/
	int a = m[0].year.length();
	for (int i = 1; i < Length; i++)
	{
		if (a < m[i].year.length())
		{
			a = m[i].year.length();
		};
	}
	return a;
}

int DurationL(vector<Movie> m, int Length)
{   /*used to compare all movie duration string length, get the maximum and return the value*/
	int a =  m[0].duration.length();
		for (int i = 1; i < Length; i++)
		{
            if (a< m[i].duration.length())
			{
				a = m[i].duration.length();
			};
		}
	return a;
}

int TitleL(vector <Movie> m, int Length)
{   /*used to compare all movie title string length, get the maximum and return the value*/
	int a = m[0].title.length();
	for (int i = 1; i < Length; i++)
	{
		if (a < m[i].title.length())
		{
			a = m[i].title.length();
		};
	}
	return a;
}


bool titleCmp(Movie a, Movie b){ return(a.title < b.title); }/*comparison between title string alphabetically*/

bool directorCmp(Movie a, Movie b){ return(a.director < b.director); }/*comparison between director string alphabetically*/

bool yearCmp(Movie a, Movie b){ return(a.year < b.year); }/*comparison between year string alphabetically(since they're in same digits)*/

bool durationCmp(Movie a, Movie b){ return(stoi(a.duration )<stoi (b.duration)); }/*comparison between converted int from duration string(since they might not have same digits)*/

void TitleReport(vector <Movie> m, int Length)
{   /*used to sort by title and report in alphabetical order*/
	sort(m.begin(), m.end(), titleCmp);

	cout << "Report sorted by title:" << endl<< endl;
	for (int i = 0; i < Length; i++)
	{
		cout << m[i].title  << m[i].director  << m[i].year << m[i].duration << endl;

	};
	cout << endl;
}

void YearReport(vector <Movie>m, int Length)
{   /*used to sort by year and report in order*/
	sort(m.begin(), m.end(), yearCmp);

	cout << "Report sorted by year:" << endl << endl;
	for (int i = 0; i < Length; i++)
	{
		cout << m[i].year << m[i].title << m[i].director << m[i].duration << endl;

	};
	cout << endl;
}

void DirectorReport(vector<Movie>m, int Length)
{   /*used to sort by director and report in alphabetical order*/
	sort(m.begin(), m.end(), directorCmp);

	cout << "Report sorted by director:" << endl << endl;
	for (int i = 0; i < Length; i++)
	{
		cout << m[i].director << m[i].title << m[i].year << m[i].duration << endl;

	};
	cout << endl;
}

void DurationReport(vector <Movie>m, int Length)
{   /*used to sort by duration and report in order*/
	sort(m.begin(), m.end(), durationCmp);

	cout << "Report sorted by duration:" << endl<<endl;
	for (int i = 0; i < Length; i++)
	{
		cout << m[i].duration << m[i].title << m[i].director << m[i].year << endl;

	};
	cout << endl;
}
