#include "ArrayList.cpp"
#include <assert.h>
#include <string.h>
#include <iostream>
using namespace std;

int main () {

//------------------------------
//          CONSTRUCTOR
//------------------------------

    ArrayList<int> array;

//------------------------------
//          INSERTION
//------------------------------

    cout << "\nTESTING INSERTION... ";

    for(int i = 5 ; i > 0  ; i--) {
        array.insertAtHead(i);
    }
	
    for(int i = 6 ; i < 11 ; i++) {
        array.insertAtTail(i);
    } 

	
    for(int i = 11 ; i < 16 ; i++) {
        array.insertAfter(i, (i - 1));  
    }
	
	
    for(int i = 16 ; i < 21 ; i++) {
        array.insertSorted(i);
    }

	
    for(int i = 0 ; i < 20 ; i++) {
        assert(array.getAt(i) == (i + 1));
    }

    ArrayList<char> characters;
    characters.insertAtHead('h');
    characters.insertAtTail('e');
    characters.insertAtTail('l');
    characters.insertAtTail('l');
    characters.insertAtTail('o');

    std::string check = "";
    for(int i = 0 ; i < 5 ; i++) {
        check = check + characters.getAt(i);
    }

    assert(check == "hello");

//------------------------------
//      COPY CONSTRUCTOR
//------------------------------

    cout << "DONE!\n\nTESTING COPY CONSTRUCTOR... ";

    ArrayList<int> copy(array);

    for(int i = 1 ; i < 21 ; i++) {
        assert(array.searchFor(i) == (i - 1));
    }

//------------------------------
//          DELETION
//------------------------------

    cout << "DONE!\n\nTESTING DELETE... ";

    for(int i = 0 ; i < 5 ; i++) {
        array.deleteHead();
    }

    for(int i = 0 ; i < 5 ; i++) {
        array.deleteTail();
    }

    for(int i = 6 ; i < 11 ; i++) {
        array.deleteElement(i);
    }   

    assert(array.length() == 5);
    for(int i = 0 ; i < 5 ; i++) {
        assert(array.getAt(i) == (i + 11));
    }

    array.deleteAt(0);
    array.deleteAt(1);
    array.deleteAt(2);

    assert(array.length() == 2);
    assert(array.getAt(0) == 12 && array.getAt(1) == 14);

    cout << "DONE!\n\nTESTING REVERSE... ";

    ArrayList<char> characters2;
    characters2.insertAtHead('h');
    characters2.insertAtTail('e');
    characters2.insertAtTail('l');
    characters2.insertAtTail('l');
    characters2.insertAtTail('o');
    characters2.insertAtTail('w');
    characters2.insertAtTail('o');
    characters2.insertAtTail('r');
    characters2.insertAtTail('l');
    characters2.insertAtTail('d');

    ArrayList<char> characters3 = characters2;
	
	
    characters2.reverse();
    
	
    for (int i = 0; i < characters2.length(); i++) {
        assert(characters2.getAt(i) == characters3.getAt(characters3.length()-1-i));
    }

    cout << "DONE!\n\nSUCCESS\n\n";

    return 0;
}
