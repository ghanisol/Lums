#include "queue.cpp"
#include <iostream>
#include <string>
using namespace std; 

int main()
{
	int score = 0;
	Queue<string> myQueue;

	cout << "Starting test 1" << endl; 
	
	myQueue.enqueue("h");
	myQueue.enqueue("e");
	myQueue.enqueue("l");
	myQueue.enqueue("l");
	myQueue.enqueue("o");
	myQueue.AddVip("W");
	myQueue.AddVip("o");
	myQueue.AddVip("r");
	myQueue.AddVip("l");
	myQueue.AddVip("d");

	string output = "";

	for (int i = 0; i < 10; i++) {
		output.append(myQueue.dequeue());
	}

	if (output.compare("Worldhello") == 0) {
		score += 10;
		cout << "Test 1 Passed" << endl;
	} else {
		cout << "Test 1 Failed" << endl;
	}

	cout << "Starting test 2" << endl;
	
	myQueue.enqueue("S");
	myQueue.AddVip("D");
	myQueue.enqueue("t");
	myQueue.enqueue("r");
	myQueue.AddVip("a");
	myQueue.AddVip("t");
	myQueue.enqueue("u");
	myQueue.enqueue("c");
	myQueue.AddVip("a");
	myQueue.enqueue("t");
	myQueue.enqueue("u");
	myQueue.enqueue("r");
	myQueue.enqueue("e");
	myQueue.enqueue("s");
	
	output = "";

	for (int i = 0; i < 14; i++) {
		output.append(myQueue.dequeue());
	}

	if (output.compare("DataStructures") == 0) {
		score += 10;
		cout << "Test 2 Passed" << endl;
	} else {
		cout << "Test 2 Failed" << endl;
	}		

	cout << "Total score: " << score << " out of 20" << endl;
	
	if (score == 20) {
		cout << "Overall Test Successful" << endl;
	} else {
		cout << "Overall Test Failed" << endl;	
	}

	return 0;
}
