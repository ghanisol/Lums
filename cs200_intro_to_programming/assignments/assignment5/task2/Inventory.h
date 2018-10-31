#include <list>
#include <map>



typedef list<int> IsbnList;

/**
 * Represents the book inventory
 * 
 */
class Inventory {

 public:

    Inventory();
    Inventory(const Inventory& old);
    ~Inventory();

    /**
     * Add a new item to the inventory
     */
    void addItem(const Item& new_item);

    /**
     * Permanently remove an item from the inventory
     */
    void removeItem(int isbn);

    /**
     * Find an item given an ISBN number
     */
    Item* lookupItem(int isbn) const;

    /**
     * Find the ISBN numbers of all items that match
     * a keyword search
     */
    IsbnList
    lookupItemsByKeyword(string keyword) const;
    
    /**
     * @return a string representation of all books in inventory
     */
    string toString() const;


 private:

    // Maps each unique ISBN number to a book
    typedef map< int, Item* > ItemTable;
    ItemTable _table;


};

