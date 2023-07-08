/*Assignment # 10
Department maintains a student information.
The file contains roll number, name, division and address.
Write a program to create a sequential file to store and maintain student data.
It should allow the user to add, delete information of student.
Display information of particular student.
If record of student does not exist an appropriate message is displayed.
If student record is found it should display the student details. */


#include<iostream>
#include<fstream>
#include<string.h>
#define MAX 20

using namespace std;
class student
{
   	int rollno;
   	char name[MAX];
   	int division;
   	char address[MAX];

   	public:

   	//Constructor initializing data members
   	student()
   	{
   	  	rollno=-1;
        strcpy(name,"");
        strcpy(address,"");
        division=-1;
   	}
   	void get_data();
   	void put_data();
	int return_roll()
   	{
		return rollno;
	}
};

void student::get_data() //Accept the student details
{
	cout<<"\nEnter Student Data:";
    cout<<"\nRoll Number : ";
    cin >> rollno;
	cout<<"Name :";
	cin.ignore();
	cin.getline(name, MAX-1);
    cout<<"Division :";
	cin >> division;
	cout<<"Address :";
	cin.ignore();
	cin.getline(address, MAX-1);
}

void student::put_data() //Display data of one student
{
	cout<<"\n"<<rollno<<"\t"<<name<<"\t\t"<<division<<"\t"<<address;
}

class seqfile
{
		char filename[MAX];
		public:
		seqfile();
		void displayrecords();
		void addrecord();
		bool searchrecord(int);
		bool deleterecord(int);
};

//Use Constructor to create the file
seqfile::seqfile()
{
	ofstream File("Student.data",ios::binary);
	strcpy(filename,"Student.data");
	if(File)
	{
		cout<<"\nFile Student.data created Successfully!";
		File.close();
	}
	else cout<<"\nFile creation Error";
}

//Add a record in sequential file
void seqfile::addrecord()
{
	ofstream  File;
	student S;
	File.open(filename,ios::app | ios::binary);
	S.get_data();
	File.write((char*)(&S),sizeof(S));
	File.close();
}

//Display all records in sequential file
void seqfile::displayrecords()
{
	ifstream  File;  //read
	student S;
	File.open(filename, ios::binary);
	File.read((char*)(&S),sizeof(S));
	if(!File.eof())
	{
		cout<<"\nRoll No\t Student Name \t Division \t Address";
		while(!File.eof())
        {
            S.put_data();
			File.read((char*)(&S),sizeof(S));
		}
	}
	else
		cout <<"No Records!!\n";
	File.close();
}

/*Delete a record from sequential file by copying all records into a temporary file
(Temp.dat) except the one to be deleted. Then delete(remove) the original file (Student.data) and
rename the temporary file (Temp.data) to the original file name.(Student.data) */
bool seqfile::deleterecord(int roll)
{
	ifstream File;
	ofstream tempfile;
	student S;
	int flag=0;
	File.open(filename, ios::binary);
	tempfile.open("Temp.data", ios::binary);
	File.read((char*)(&S),sizeof(S));
	while(!File.eof())
    {
		if(roll==S.return_roll())
        {
			S.put_data();
			flag=1;
		}
        else
            tempfile.write((char*)(&S),sizeof(S));
        File.read((char*)(&S),sizeof(S));
	}
	File.close();
	tempfile.close();
	remove(filename);
	rename("Temp.data",filename);
 	if(flag==0)
	{
		cout<<"Record for Roll No. "<<roll<<" not found! \n";
		return 0;
	}
	else
	{
		cout<< "\nRecord Deleted Successfully!\n";
		return 1;
	}
}
/*To search, read one record from the file and compare it's roll no with the one
to be searched. If it matches, record is found. Else keep reading and comparing next
record till the end of file is reached. if EOF is reached without any match,
the record is not present in the file.*/
bool seqfile::searchrecord(int roll)
{
	ifstream File;
	student S;
	int flag=0;
	File.open(filename, ios::binary);
	File.read((char*)(&S),sizeof(S));
	while(!File.eof())
    {
		if(roll==S.return_roll())
        {
			flag=1;
			cout << "Record Found!\n";
			S.put_data();
			break;
		}
		File.read((char*)(&S),sizeof(S));
    }
    if(flag == 0)
            cout << "Record NOT Found.\n";
   	File.close();
 	return(flag);
}

int main()
{
	int ch;
	char fname[MAX];
	int roll;
	seqfile sfile;
	int count=0;
	bool dele=0;
	do
	{
	  	cout << "\n1: Add a record \n2: Display records\n3: Search a record\n";
	  	cout << "4: Delete a record\n5: Exit\nEnter your choice: ";
	  	cin >> ch;
		switch(ch)
        {
	   		case 1:
	        		sfile.addrecord();
                    count++;
                    break;
            case 2:
                    if(count!=0)
                    {
                        sfile.displayrecords();
                    }
                    else
                        cout<< "No Records!\n";
                    break;
            case 3:
                    if(count!=0)
                    {
                        cout<<"\nEnter Roll No to search : ";
                        cin>>roll;
                        sfile.searchrecord(roll);
                    }
                    else
                        cout<< "No Records!\n";
                    break;
            case 4:
                    if(count!=0)
                    {
                        cout<<"\nEnter Roll No to delete : ";
                        cin>>roll;
                        dele=sfile.deleterecord(roll);
                        if(dele)
                            count--;
                    }
                    else
                        cout<< "No Records!\n";
                    break;
        }
	}while(ch < 5);
 	return 0;
}
