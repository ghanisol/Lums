

/**
 * Represents a movie DVD
 * Objects of type movie are immutable
 */
class Movie : public Item {

 public:
    Movie(int isbn, string title, string artist);
       
    virtual Movie* clone() const;

    string getArtist() const;

    virtual bool matches(string keyword) const;
    virtual string toString() const;

 private:

    string _artist;

};



