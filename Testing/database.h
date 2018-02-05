/**********************************************
CSCE-315
Project 1 - Checkpoint 1
9/24/17

Header file
database.h
**********************************************/

#ifndef header_hpp
#define header_hpp

// all includes are defined in header
#include <iostream>
#include <string>
#include <memory> // for unique pointer
#include <unordered_map>
#include <sstream> // string stream
#include <vector>
#include <stdexcept> // for exceptions
#include <unordered_set>
#include <algorithm> // for remove

using namespace std;


class DatabaseError;
class Database;
class Table;
class Record;
class StringPointer;



/**********************************************
Throw this class for error handling with try/catch blocks
**********************************************/
class DatabaseError : public runtime_error {
public:
    DatabaseError(string errorString);
};




/**********************************************
 StringPointer is a pointer to strings. It allows strings to be null, but on a copy, it deep-copies the strings.
 **********************************************/

class StringPointer : public unique_ptr<string> {
public:
    StringPointer(); // constructors are not inherited
    StringPointer(string* stringPointer); // constructors are not inherited
    StringPointer(const StringPointer& stringPointer); // copy constructor to copy the unique pointer string, not the pointer itself
    StringPointer& operator =(const StringPointer& stringPointer); //copy assignment operator to copy the unique pointer string
    
    StringPointer& operator =(const nullptr_t& nptr); //copy assignment operator, nullptr to StringPointer
    StringPointer& operator =(const string& str); // copy assignment operator, string to StringPointer
    
    operator string (); // conversion operator, string pointer to string
    
    friend ostream& operator <<(ostream& os, const StringPointer& stringPointer);
};






/**********************************************
 Record
 **********************************************/

class Record {
    friend class Table; // let Table access Record
    
private:
    
    // private data structures:
    vector<StringPointer> entries; //vector of unique pointer to string, can be null
    
    // private functions:
    bool isInRange(int i) const; // if the entry is in range of the entry vector
    void deleteEntryIndex(int i); // delete the i-th string
    void addEntryValue(string entry); // add new attribute value string to end of Record
    
public: // API functions:
    
    Record(); // empty constructor
    
    Record(int size); // constructor with number of attribute values initialized to null strings
    
    Record(vector<string> attributeValues); // constructor with attribute values list
    Record& operator =(vector<string> attributeValues); //copy assignment operator, vector list to Record
    
    unsigned long size() const; // return number of strings in record
    
    StringPointer operator [](int i) const; // brackets to get string pointer, return copy
   
    StringPointer& operator [](int i); // brackets to set string pointer, return reference
    
    friend ostream& operator <<(ostream& os, const Record& record); // << operator
};




/**********************************************
 Table
 **********************************************/

class Table {
    friend class Database; // let Database access Table
    
private:
    
    // private data structures:
    
    vector<string> attributes; // header row of table
    
    vector<Record> records; // rows of table
    
    // only used in join commands, set once
    StringPointer key; // unique pointer to string - can be NULL
    
    
    // private functions:
    
    // This function is used in the Database query function
    // Return the indices of the records in the table that match the attribute value comparison with specified operator
    // Valid operators: =, <>, >, <, >=, <=
    vector<int> compareAttributesOutputRecords(string attributeName, string attributeValue, string operatorString);
    
    int attributeNameToIndex(string attributeName);
    
public: // API functions:
    
    Table(); // empty constructor
    
    Table(vector<string> attributes); // constructor takes list of attribute names as vector of strings, cannot be NULL strings
    Table& operator =(vector<string> attributes); // copy assignment operator, vector list to Record
    
    void addAttribute(string attribute); // adds attributes to the table
    
    void deleteAttribute(string attribute); // removes a single attribute and its column
    
    void add(Record record); // add record to table
    
    vector<string> getAttributes(); //returns a list of attributes
    
    int size(); // returns the number of records
    
    vector<Record>::iterator getIteratorIndex(int i); //get iterator to iterate through records, starting at record i
    
    void specifyKey(string key); // set the key, only can be set once
    
    Table crossJoin(const Table& t1); // takes 2 tables as input and produces 1 as output
    
    Table naturalJoin(const Table &t1); // takes 2 tables as input and produces 1 as output
    
    int count(string attribute); // attribute name count routine
    int min(string attribute); // attribute name min routine
    int max(string attribute); // attribute name max routine
    
    Record operator [](int i) const; // brackets to get record, return copy
    Record& operator [](int i); // brackets to set record details, return reference
    
    friend ostream& operator <<(ostream& os, const Table& Table); // << operator
    
};



/**********************************************
Database
**********************************************/

class Database {
private:
    
    // private data structures:
    
    //unordered map from string to Table
    unordered_map<string, Table> listOfTables;
    
    // for parsing nested parentheses in the query WHERE statement
    // returns a list of indices of resulting rows from the FROM table
    vector<int> recursiveWhereQuery(istringstream& iss);

    
    // private functions:
    
    // for the query operation, get table by name
    Table getTable(string name);

public: // API functions:

	Database(); // empty constructor
    
    void addTable(Table& t, const string& name); //adds table to database
    
    void dropTable(const string& tableName); //drops table from database
    
    vector<string> listTables(); //lists all table names in database
	
	vector<Table> getTables(); //gets al tables in database

    Table query(string select, string from, string where); // query returns a table of resulting rows
    
    Table operator [](int i) const; // brackets to get table, return copy
    Table& operator [](int i); // brackets to set table details, return reference
    
    friend ostream& operator <<(ostream& os, const Database& Database); // << operator
};



#endif /* header_hpp */
