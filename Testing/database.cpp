/**********************************************
CSCE-315
Project 1 - Checkpoint 1
9/24/17
Source code
database.cpp
**********************************************/

#include "database.h"


/**********************************************
 StringPointer is a pointer to strings. It allows strings to be null, but on a copy, it deep-copies the strings.
 **********************************************/

StringPointer::StringPointer(){ // constructors are not inherited
    
}

StringPointer::StringPointer(string* stringPointer){ // constructors are not inherited
    
}

StringPointer::StringPointer(const StringPointer& stringPointer){ // copy constructor to copy the unique pointer string, not the pointer itself
    
}



/**********************************************
 Record
 **********************************************/
// private functions:
bool Record::isInRange(int i) const{ // if the entry is in range of the entry vector
    
}

void Record::deleteEntryIndex(int i){ // delete the i-th string
    
}

void Record::addEntryValue(string entry){ // add new attribute value string to end of Record
    
}

Record::Record(){ // empty constructor
    
}

Record::Record(int size){ // constructor with number of attribute values initialized to null strings
    
}

Record::Record(vector<string> attributeValues){ // constructor with attribute values list
    
}

unsigned long Record::size() const{ // return number of strings in record
    
}

// Record::Record& operator =(vector<string> attributeValues){ //copy assignment operator, vector list to Record
    
// }

// Record::StringPointer operator [](int i) const{ // brackets to get string pointer, return copy
    
// }

// StringPointer::StringPointer& operator [](int i){ // brackets to set string pointer, return reference
    
// }



/**********************************************
 Table
 **********************************************/

// private functions:

// This function is used in the Database query function
// Return the indices of the records in the table that match the attribute value comparison with specified operator
// Valid operators: =, <>, >, <, >=, <=
vector<int> Table::compareAttributesOutputRecords(string attributeName, string attributeValue, string operatorString){
    
}

int Table::attributeNameToIndex(string attributeName){
    
}

Table::Table(){ // empty constructor
    
}

Table::Table(vector<string> attributes){ // constructor takes list of attribute names as vector of strings, cannot be NULL strings
    
}

void Table::addAttribute(string attribute){ // adds attributes to the table
    
}

void Table::deleteAttribute(string attribute){ // removes a single attribute and its column
    
}

void Table::add(Record record){ // add record to table
    
}

vector<string> Table::getAttributes(){ //returns a list of attributes
    
}

int Table::size(){ // returns the number of records
    
}

vector<Record>::iterator Table::getIteratorIndex(int i){ //get iterator to iterate through records, starting at record i
    
}

void Table::specifyKey(string key){ // set the key, only can be set once
    
}

Table Table::crossJoin(const Table& t1){ // takes 2 tables as input and produces 1 as output
    
}

Table Table::naturalJoin(const Table &t1){ // takes 2 tables as input and produces 1 as output
    
}

int Table::count(string attribute){ // attribute name count routine
    
}

int Table::min(string attribute){ // attribute name min routine
    
}

int Table::max(string attribute){ // attribute name max routine
    
}


/**********************************************
Database
**********************************************/
    
// for parsing nested parentheses in the query WHERE statement
// returns a list of indices of resulting rows from the FROM table
vector<int> Database::recursiveWhereQuery(istringstream& iss){
    
}

// for the query operation, get table by name
Table Database::getTable(string name){
    
}

Database::Database(){ // empty constructor
    
}

void Database::addTable(Table& t, const string& name){ //adds table to database
    
}

void Database::dropTable(const string& tableName){ //drops table from database
    
}

vector<string> Database::listTables(){ //lists all table names in database
    
}

vector<Table> Database::getTables(){ //gets all tables in database
    
}

Table Database::query(string select, string from, string where){ // query returns a table of resulting rows
    
}

//