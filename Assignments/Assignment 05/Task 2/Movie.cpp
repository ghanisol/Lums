#include "Movie.h"



Movie::Movie(int isbn, string title, string artist) 
    : Item(isbn,title), 
      _artist(artist) {
}
       
Movie* 
Movie::clone() const { 
    return new Movie(*this); 
}

string
Movie::getArtist() const { 
    return _artist; 
}

bool 
Movie::matches(string keyword) const { 
    return ( (_artist.find(keyword) != string::npos)
             || Item::matches(keyword)); 
}

string 
Movie::toString() const {

    stringstream s;
    s << "Movie={" 
      << Item::toString()
      << ", artist=" << _artist
      << "}";
    return s.str();
}
