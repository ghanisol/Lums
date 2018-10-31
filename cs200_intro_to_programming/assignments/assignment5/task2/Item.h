
#include <string>
#include <sstream>

using namespace std;
/**
 * Represents an item in the book store
 */ 
class Item {

 public:

    Item(int isbn, string title);

    virtual Item* clone() const = 0;

    virtual ~Item();

    int getIsbn() const;
    
    string getTitle() const;

    /**
     * @return true if given keyword appears in the title
     * of this item, false otherwise
     */
    virtual bool matches(string keyword) const;
    
    virtual string toString() const;
    
 private:

    int _isbn;
    string _title;

};

