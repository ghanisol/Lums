#include "syscall.h"

void Extract(char* string, char** names, int NumNames);
int len(char* string);
void sort(char** names, int size);
void copy(char* src, char* dst);
int NamesNumber(char* string);
void Merge(char** names, char* string, int size);
int strcmpr(char *s1, char *s2);

main()
{
	char* string;
	// Read CS370Students.csv and save in string

	char names[100][15];
	int size;
	int i;
	/*
	for(i = 0; i<100; i++)
	{
		for (size = 0; size < 15; size++)
		{
			names[i][size] = 0;
		}
	}*/

	string = "Iqbal,Ahmed,Ahmed,Wahaj,Abbas,Hasan,Azmat,Ayan,Raza,Ali,Hassan,Shah,Sohail,Anam,Abbas,Hasan,Azmat,Ayan,Raza,Ali,Hassan,Shah,Sohail,Anam,Ahmad,Hayyaan,Alavi,Asad,Talat,Hassan,Mehfooz,Ahmed,Zaidi,Hassan,Khan,Zaid,Choudhary,Haris,Azam,Mohammad,Danial,Hayat,Hira,Azmat,Khaliq,Awais,Abdul,Gilani,Syed,Rizwan,Chaudhry,Ammad,Anjum,Pirzada,Hasnain,Ali,Asif,Muhammad,Sajid,Zainab,Khawar,Mohammad,Saad,Mubasher,Hasaan,Saad,Muhammad,AbdulRehman,Muzammil,Khan,Abdullah,Kamran,Huda,Farrukh,Sana,Bajwa,Qurat-Ul-Ann,Abid,Amna,Ali,Usman,Wajih,Mahboob,Muhammad,Raza";

	size = NamesNumber(string);

	Extract(string, names, size);
	sort(names, size);

	i = len(string);
	Merge(names, string, size);

	// Write String to file Sorted-CS370Students.csv
	Write(string, len(string), 1);
	Close(1);
	Exit(0);
	Halt();

}

void Merge(char** names, char* string, int size)
{
	int i;
	int main_count = 0;
	int sub_count = 0;

	for(i = 0; i < size; i++)
	{
		while(names[i][sub_count] != 0)
		{
			string[main_count] = names[i][sub_count];
			main_count++;
			sub_count++;
		}
		string[main_count] = ',';
		main_count++;
		sub_count = 0;
	}
}

void sort(char** names, int size)
{
	char temp[100];
	int i;
	int flag = 1;

	while(flag == 1)
	{
		flag = 0;
		for (i = 0; i < size-1; i++)
		{
			if(strcmpr(names[i], names[i+1]) > 0)
			{
				copy(names[i], temp);
				copy(names[i+1], names[i]);
				copy(temp, names[i+1]);
				flag = 1;
			}
		}
	}
}


void copy(char* src, char* dst)
{
	int count = 0;
	while(src[count]!=0)
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = 0;
}

int NamesNumber(char* string)
{
	int count = 0;
	int i;

	for (i = 0; i < len(string); i++)
	{
		if (string[i] == ',')
			count++;
	}

	return ++count;
}

void Extract(char* string, char** names, int NumNames)
{
	int i;
	int stringSize = len(string);
	int main_count = 0;
	int sub_count = 0;

	for (i = 0; i < NumNames; i++)
	{
		while((string[main_count] != ',') && (main_count < stringSize))
		{
			names[i][sub_count] = string[main_count];
			main_count++;
			sub_count++;
		}
		main_count++;
		sub_count = 0;
	}
}

int len(char* string)
{
	int count = 0;

	while(string[count]!=0)
		count++;

	return count;
}

int strcmpr(char *s1, char *s2)
{   
    int i = 0;
    while ( s1[i] != '\0' )
    {
        if( s2[i] == '\0' ) { return 1; }
        else if( s1[i] < s2[i] ) { return -1; }
        else if( s1[i] > s2[i] ) { return 1; }
        i++;
    }   
    return 0;
}
