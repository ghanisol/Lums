
/**
 * Represents a book
 * Objects of type Book are immutable
 */
class Book : public Item {

 public:

    Book(int isbn, string title, string author);

    virtual Book* clone() const;
 
    string getAuthor() const;

    virtual bool matches(string keyword) const;

    virtual string toString() const;

 private:

    string _author;

};


