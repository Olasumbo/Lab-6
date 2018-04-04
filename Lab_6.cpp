//============================================================================
// Name        : Lab5.cpp
// Author      : Ola
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <limits.h>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

class Signal
{
private:
	double Max_Num;
	double Min_Num;
	double Avg;
	vector<double> data;

public:
	double length;
	vector<double> updateddata;
	void offset(double x);
	void scale(double x);
	void center();
	void normalize();
	void statistics();
	void menu();
	void Sig_info();
	void Save_file(int n);
	void getAverage(void);
	void getMax(void);

	//Operators (Member)
	void operator+(double x);
	void operator*(double rhs_factor);

	//Constructors
	Signal():Signal(1){}; // default file
	Signal(int n); // when given just a number it opens the file
	Signal(string filename);

	// Destructor
	~Signal(){};

};

Signal *operator+(const Signal &lhs, const Signal &rhs);

int main(int argc, char*argv[])
{
	int filenum;
	string filename;
	if(argc == 1)
	{
		Signal input;
		input.menu();
		delete &input;
	}
	else if (argc >= 3)
	{
		for( int i = 1; i <= argc; i++ )
		{
			if((argv[i][0] == '-') && (argv[i][1] == 'n'))
			{
				filenum = atoi(argv[2]);
				Signal input( filenum );
				cout << "File value: " << filenum << endl;
				input.menu();
				delete &input;
				break;
			}
			else if ((argv[i][0] == '-') && (argv[i][1] == 'f'))
			{
				filename = argv[2];
				Signal input(filename);
				cout << "Filename: " << filename << endl;
				input.menu();
				delete &input;
				break;
			}
		}
	}
	else
	{
		cerr << "Error! Wrong number of argument "<< endl;
	}
	//cout << "Everything is done!" << endl;
	return 0;
}

void Signal::menu()
{
	int opt;
	cout << "Welcome to a complicated life"<< endl;
	do
	{
		cout << "Here is a list of things you can do, Please pick your choices appropriately"<< endl;
		cout << "\n1) Offset " << endl;
		cout << "2) Scale" << endl;
		cout << "3) Center" << endl;
		cout << "4) Normalize" << endl;
		cout << "5) Statistics" << endl;
		cout << "6) Print Signal" << endl;
		cout << "7) Save Signal" << endl;
		cout << "8) New Stuff with Operator" << endl;
		cout << "9) Exit" << endl;

		cout << "Select an option: " <<endl;
		cin >> opt;

		switch(opt)
		{
		case 1:
		{
			cout << "\nEnter the offset value: ";
			double val;
			cin >> val;
			offset(val);
			break;
		}
		case 2:
		{
			cout << "\nEnter the scale value: ";
			double val;
			cin >> val;
			scale(val);
			break;
		}
		case 3:
		{
			center();
			break;
		}
		case 4:
		{
			normalize();
			break;
		}
		case 5:
		{
			statistics();
			break;
		}
		case 6:
		{
			Sig_info();
			break;
		}
		case 7:
		{
			cout << "Enter a filenumber: ";
			double num;
			cin >> num;
			Save_file(num);
			//delete num;
			break;
		}
		case 8:
		{
			// Demonstrate the non-member overloaded addition
			cout << "\nEnter a file number value: ";
			double val, val2;
			cin >> val;
			cout << "\nEnter a file number value: ";
			cin >> val2;
			Signal obj1 = Signal(val);
			Signal obj2 = Signal(val2);
			Signal *obj3;
			obj3 = obj1 + obj2;
			obj3->Sig_info();
			break;
		}
		case 9:
		{
			exit(EXIT_SUCCESS);
		}
		default:
		{
			cout << "Invalid option" << endl;
			break;
		}
		}
	}
	while(opt <= 8);
}

void Signal::offset(double x)
{
	/*for(int i = 0; i<length; i++)
	{
		cout << "Offset["<< i << "] -> "<< updateddata[i] << " by " << x << endl;
		updateddata[i] = updateddata[i] + x;
	}*/
	this->operator +(x);
	getAverage();
	getMax();
}

void Signal::scale(double x)
{
	/*for(int i = 0; i<length; i++)
	{
		cout << "Scaled[" << i << "] ->"<< updateddata[i] << " by " << x << endl;
		updateddata[i] = updateddata[i] * x;
	}*/
	this->operator*(x);
	getAverage();
	getMax();
}

void Signal::getAverage()
{
	Avg = 0;
	for(int i = 0; i<length; i++)
	{
		Avg = Avg + updateddata[i];
	}
	Avg = (Avg/(length));
}

void Signal::getMax()
{
	Max_Num = 0;
	for(int i = 0; i<length; i++)
	{
		if(updateddata[i] > Max_Num)//*(data+i) is an actual value in the vector/ or array
		{
			Max_Num = updateddata[i];
		}
	}
	//cout<<"Maxvalue is: "<< max << endl;
}

void Signal::center()
{
	getAverage();
	/*for(int i = 0; i<length; i++)
	{
		updateddata[i] -= Avg;
	}*/
	operator+(-Avg);
	getAverage();
	getMax();
}

void Signal::statistics()
{
	cout<<"Maxvalue is: "<< Max_Num<< endl;
	cout <<"Average is: " << Avg << endl;
}

void Signal::normalize()
{
	getMax();
	operator*(1/Max_Num);
	/*for(int i = 0; i < length; i++)
	{
		updateddata[i] /= Max_Num;
	}*/
	getAverage();
	getMax();
}

void Signal::Sig_info()
{
	Min_Num = Max_Num;
	for(int i = 0; i<length; i++)
	{
		if( updateddata[i] < Min_Num )//*(data+i) is an actual value in the vector/ or array
		{
			Min_Num = updateddata[i];
		}
	}
	int i = 0;
	while ( i < length )
	{
		cout << "DATA[" << i << "] -> " << data[i] << " --> " << updateddata[i] << endl;
		i++;
	}

	cout << "\nSignal length: " << length << endl;
	cout << "Maximum val:" << Max_Num << endl;
	cout << "Minimum val:" << Min_Num << endl;
	cout << "Average val:" << Avg << endl;

}

void Signal::Save_file(int n)
{
	/*FILE *fp_w = fopen(filename, "w");
		if(fp_w != NULL)
		{
			fprintf(fp_w, "%lf %0.4lf\n", length, Max_Num);
			for(int i = 0; i < length; i++)
			{
				fprintf(fp_w, "%0.4lf\n", *(data+i));
			}
			fclose(fp_w);
		}*/

	ostringstream fileNumStream;
	fileNumStream << setw(2) << setfill('0') << to_string(n); /// this is so that we could open files such as 10/11

	ofstream myfile ( "Raw_data_" + fileNumStream.str() + ".txt" );

	if( !myfile.is_open() )
	{
		cerr << "Could not open file "<< endl;
		return;
	}

	myfile << length << " " << Max_Num << endl;

	for( int i = 0; i < length; i++ )
	{
		myfile << updateddata[i] << endl;
	}

	myfile.close();

}

Signal::Signal(int n) /// It reads in my file.
{
	ostringstream fileNumStream;
	fileNumStream << setw(2) << setfill('0') << to_string(n);

	ifstream myfile ( "Raw_data_" + fileNumStream.str() + ".txt" );

	int i = 0;
	length = 0;

	if ( myfile.is_open() )
	{
		//cout << "I opened a file! I so cool!" << endl;
		myfile >> length >> Max_Num;
		myfile.ignore( 1,'\n' );
		cout << "Length: " << length << " | Max: " << Max_Num << endl;

		string line;
		while ( i < length )
		{
			//myfile >> test[i];
			getline( myfile, line );
			data.push_back( atof( line.c_str() ) );
			updateddata.push_back( data[i] );
			//cout << "Read the data for " << i << " : " << data[i] << endl;
			i++;
		}
		myfile.close();
	}
	else
	{
		cerr << "Could not open the file "<< endl;
	}

	Avg = 0;
	Max_Num = 0;
	Min_Num = 0;
}

Signal::Signal(string filename)
{
	ifstream myfile(filename);
	int i = 0;
	length = 0;
	if (myfile.is_open())
	{
		myfile >> length >> Max_Num; // the first value is length and the next one is Max
		myfile.ignore( 1,'\n' );
		cout << "Length: " << length << " | Max: " << Max_Num << endl;//printing them out
		string line;
		while ( i <= length)
		{
			//myfile >> test[i];
			getline( myfile, line );
			data.push_back( atof( line.c_str() ) ); // we need to use pushback for Vector
			updateddata.push_back( data[i] );
			cout << "Read the data for " << i << " : " << data[i] << endl;
			i++;
		}

	}
	else
	{
		cerr << "Could not open the file "<< endl;
	}

	Avg = 0;
	Max_Num = 0;
	Min_Num = 0;
}

//Operator
void Signal::operator+(double x)
{
	int i = 0;
	for(i = 0; i < length; i++)
	{
		updateddata[i] += x;
		cout << "Data[" << i << "] ->"<< updateddata[i] << endl;
	}

}

void Signal::operator*(double rhs_factor)
{
	for(int i = 0; i < length; i++)
	{
		updateddata[i] *= rhs_factor;
		cout << "Data[" << i << "] ->"<< updateddata[i] << endl;
	}
}

// -------- Operators can be Non-member functions -------------------
Signal *operator+(const Signal &lhs, const Signal &rhs)
{
	Signal *sum = new Signal;
	if(lhs.length != rhs.length)
	{
		cerr<< "Error: objects are not of same length" << endl;
	}
	else
	{
		sum->length = lhs.length;
		for(int i = 0; i < sum->length; i++)
		{
			// use push_back to grow vector
			sum->updateddata.push_back(lhs.updateddata[i]);
			sum->updateddata[i] += rhs.updateddata[i];
		}
		sum->getAverage();
		sum->getMax();
	}
	return sum;
}
