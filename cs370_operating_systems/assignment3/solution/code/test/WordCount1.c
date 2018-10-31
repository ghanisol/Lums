#include <syscall.h>

void Extract(char* string, char names[][15], int NumNames);
int len(char* string);
int NamesNumber(char* string);
int strcmpr(char *s1, char *s2);

main()
{
	char* string;
	// Read CS370WordList.csv and save in string
	char *key;
	char names[100][15];
	int size;
	int i;
	int count;
	for (i = 0; i<100; i++)
	{
		for (size = 0; size < 15; ++i)
		{
			names[i][size] = 0;
		}
	}
	Read(key, 10, 0);
	key[10] = 0;
	count = 0;
	string = "Apple,Dell,hewlett packard,HP,Dell,Sony,Toshiba,Toshiba,Apple,Dell,hewlett packard,HP,Dell,Sony,Toshiba,Toshiba,Apple,Dell,hewlett packard,HP,Dell,Sony,Toshiba,Toshiba,NEC,ASUS,NEC,ASUS,HP,Dell,Sony,Toshiba";

	size = NamesNumber(string);
	Extract(string, names, size);

	for(i = 0; i< size; i++)
	{
		if (strcmpr(key, names[i])==0)
		{
			count++;
		}
	}


	string[0] = (count%10) + '0';
	string[1] = ((count%100)/10) + '0';
	string[2] = 0;

	Write("Count: \0", 8, 1);
	Write(string, 2, 1);
	Close(1);
	Exit(0);
	Halt();
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

void Extract(char* string, char names[][15], int NumNames)
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