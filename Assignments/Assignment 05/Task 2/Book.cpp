#include "Book.h"



Book::Book(int isbn, string title, string author)
    : Item(isbn,title),
      _author(author) {
}

Book* 
Book::clone() const { 
    return new Book(*this); 
}
 
string 
Book::getAuthor() const { 
    return _author; 
}


bool 
Book::matches(string keyword) const { 
    return ( (_author.find(keyword) != string::npos)
             || Item::matches(keyword)); 
}
    

string 
Book::toString() const {

    stringstream s;
    s << "Book={" 
      << Item::toString()
      << ", author=" << _author
      << "}";
    return s.str();
}

