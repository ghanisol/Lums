#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	int length = 0;
   	cout << "Enter the word length" << endl;
    cin >> length;
    
    // determine the array length needed to store words
    ifstream in("words.txt");
    
    if (in.fail())
    {
       cout << "Opening of file failed.\n";
       return 0;
    }
	
	int a_length = 0;
    while (!in.eof())
    {
   		string line;
        in >> line;
    	if (line.length() == length)
        { 
          	a_length++;
        }
		   
    }
    
    in.close();
    
    
    in.open("words.txt");
    
    if (in.fail())
    {
       cout << "Opening of file failed.\n";
       return 0;
    }
	
	string words[a_length];
	
	int x = 0;
	for (int i = 0; !in.eof(); i++)	// could have used "i += ((words[i].length() == length)?1:0)"
    {
    	string line;
        in >> line;
    	if (line.length() == length)
        { 
          	words[x] = line;
          	x++;
        }
    	
	}

	/*for (int i = 0; i < a_length; i++)
	{
		cout << words[i] << endl;
	}*/
    
    
    // Evil hangman
    
    char letter;
    string word;
    bool flag = false;
    
    
    for (int guess = 0; guess < 10; guess++)
    {
    	cout << "Enter the letter" << endl;
    	cin >> letter;
    	
    	int n_a_length = 0;
    	
    	for (int i = 0, j = 0; i < a_length; i++)
    	{
    		word = words[i];
    		
    		if (word.length() == length)
    		{
 				flag = false;   			
    			for (int x = 0; x < word.length(); x++)
    			{
 
    				if (letter == word[x])
    				{
    					flag = true;
    					break;
    				}
    				
    			}
					
    			if (flag == false)
    			{
    				
    				words[j] = word;
    				n_a_length++;
    				j++;
    			}
    		}
		}
		
		string new_words[n_a_length];
		for (int i = 0; i < n_a_length; i++)
		{
			new_words[i] = words[i];
		}
		
		for(int i = 0; i < n_a_length; i++)
		{
			words[i] = new_words[i];
			cout << words[i] << endl;
		}
		a_length = n_a_length;
    	
	}
	

    in.close();
    
    return 0;
}
