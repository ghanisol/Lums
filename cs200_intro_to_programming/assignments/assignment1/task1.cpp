#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// prototype
int array_size(void);
void get_words(string words[]);
void sort(string words[], int a_size);
int small_word_length(string word_1, string word_2);
void print(string words[], string sub_str, int array_size);

int main()
{
	int a_size = array_size();
	
	string words[a_size];
	
	get_words(words);	// stores all words in an array
	
	sort(words, a_size); // sorts the words alphabetically
	
	string sub_str;
	cout << "Please enter the substring : ";
	cin >> sub_str;
	
	print(words, sub_str, a_size); // prints all the words wanted by the user
}

// Calculate required array size
int array_size(void)
{
	ifstream in_file;
	
	in_file.open("words.txt");
	
	if (in_file.fail())
	{
		cout << "Error : Reading file. \n";
		return 0; 
	}
	
	int a_size = 0;
	while (!in_file.eof())
	{
		string word;
		in_file >> word;
		a_size++;
	}
	
	in_file.close();
	
	return a_size;
};

// stores the words in the file to a string array
void get_words(string words[])
{
	ifstream in_file;
	
	in_file.open("words.txt");
	
	int i = 0;
	while (!in_file.eof())
	{
		string word;
		in_file >> word;
		words[i] = word;
		i++;
	}
	
	in_file.close();
	
}

// sorts the words alphabetically
void sort(string words[], int a_size)
{
	for (int i = 0; i < a_size - 1; i++)
	{
		for (int j = i + 1; j < a_size; j++)
		{
			string word_1 = words[i];
			string word_2 = words[j];
			
			int len = small_word_length(word_1, word_2);
			for (int z = 0; z < len; z++)
			{
				if (word_1[z] > word_2[z])
				{
					string temp = words[i];
					words[i] = words[j];
					words[j] = temp;
					break;
				}
				else if (word_1[z] < word_2[z])
				{
					break;
				}
			}	
		}
			
					
	}
}
		
// returns the smaller word's length required to run the array in sorting func.
int small_word_length(string word_1, string word_2)
{
	if (word_1 < word_2)
	{
		return word_1.length();
	}
	else
	{
		return word_2.length();
	}
}

// prints all the words wanted by the user
void print(string words[], string sub_str, int array_size)
{
	int len = sub_str.length();
		
	for (int i = 0; i < array_size; i++)
	{	
		bool flag = true;
		string word = words[i];
		for (int j = 0; j < len; j++)
		{
			if (sub_str[j] != word[j])
			{
				flag = false;
				break;
			}
		}
		if (flag == true)
		{
				cout << word << endl;
		}
	}
}




