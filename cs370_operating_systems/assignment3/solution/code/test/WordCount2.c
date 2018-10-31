#include <syscall.h>

void Extract(char* string, char names[100][15], int NumNames);
int len(char* string);
void sort(char names[100][15], int size);
void copy(char* src, char* dst);
int NamesNumber(char* string);
void Merge(char names[100][15], char* string, int size, int array[]);
int unique(char names[100][15], int size);
int check(char names[100][15], char* key, int size);
void getUnique(char names[100][15], char unique_names[100][15], int size);
int strcmpr(char *s1, char *s2);

main()
{
	char* string;
	// Read CS370SomeText.csv and save in string
	char* key;
	char names[100][15];
	int size;
	int i;
	int unique_size;
	char unique_names[100][15];
	int array[100];

	for (i = 0; i<100; i++)
	{
		for (size = 0; size < 15; ++i)
		{
			names[i][size] = 0;
		}
	}

	for (i = 0; i<100; i++)
	{
		for (size = 0; size < 15; ++i)
		{
			unique_names[i][size] = 0;
		}
	}

	key = "Dell";
	string = "Apple,Dell,hewlett packard,HP,Dell,Sony,Toshiba,Toshiba,Apple,Dell,hewlett packard,HP,Dell,Sony,Toshiba,Toshiba,Apple,Dell,hewlett packard,HP,Dell,Sony,Toshiba,Toshiba,NEC,ASUS,NEC,ASUS,HP,Dell,Sony,Toshiba";
	size = NamesNumber(string);

	Extract(string, names, size);
	sort(names, size);
	unique_size = unique(names, size);

	getUnique(names, unique_names, size);
	for (i = 0; i < unique_size; i++)
	{
		array[i] = check(names, unique_names[i], size);
	}

	i = len(string);
	Merge(unique_names, string, unique_size, array);

	Create("WordCount-CS370SomeText.csv");
	Open("ghani.txt");
	Write(string ,len(string), 2);
	Close(2);
	Exit(0);
	Halt();
	// Write String to file WordCount-CS370SomeText.csv
}

void getUnique(char names[100][15], char unique_names[100][15], int size)
{
	int i = 0;
	int j = 0;

	while(i<size)
	{
		copy(names[i], unique_names[j]);
		i++;
		while((strcmpr(names[i], unique_names[j]) == 0) && (i < size))
		{
			i++;
			if (i >= size)
				break;
		}
		j++;
	}
}

int check(char names[100][15], char* key, int size)
{
	int i;
	int count = 0;

	for (i = 0; i < size; i++)
	{
		if(strcmpr(names[i], key) == 0)
			count++;
	}
	return count;
}

int unique(char names[100][15], int size)
{
	int count = 0;
	char temp[100];
	int i = 0;

	while(i<size)
	{
		copy(names[i], temp);
		i++;
		count++;
		while((strcmpr(names[i], temp) == 0) && (i < size))
		{
			i++;
			if (i>=size)
				break;
		}
	}

	return count;
}

void Merge(char names[100][15], char* string, int size, int array[])
{
	int i;
	int main_count = 0;
	int sub_count = 0;

	for(i = 0; i < size; i++)
	{
		string[main_count] = (char) array[i];
		string[main_count+1] = " ";
		main_count += 2;
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

void sort(char names[100][15], int size)
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

void Extract(char* string, char names[100][15], int NumNames)
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