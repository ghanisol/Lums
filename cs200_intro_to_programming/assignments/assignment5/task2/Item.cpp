#include "Item.h"



Item::Item(int isbn, string title) 
    : _isbn(isbn), _title(title) {
}

Item::~Item() {
}

int 
Item::getIsbn() const { 
    return _isbn; 
}

string 
Item::getTitle() const { 
    return _title; 
}

bool 
Item::matches(string keyword) const { 
    return (_title.find(keyword) != string::npos); 
}
    

string 
Item::toString() const {
        
    stringstream s;
    s << "Item={" 
      << "isbn=" << _isbn
      << ",title=" << _title
      << "}";
    return s.str();

}

