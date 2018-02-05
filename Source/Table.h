#ifndef _Table_h_
#define _Table_h_

#include <iostream>
#include <string>
#include <vector>
#include "Record.h"

using namespace std;
class Table{
    private:
        //string table_name;
        string table_name;
        vector <string> key;
        vector <string> attributes;
        vector <Record> records;
    public:
        //----------------------------------//
        //CONSTRUCTORS                      //
        //----------------------------------//
        Table(); //default constructor
        Table(vector<string> vec); //constructor takes in a list of attribute names
        
        //----------------------------------//
        //GETTER FUNCTIONS                  //
        //----------------------------------//
                
        void AddAttribute(string s); //takes in a single attribute name to add to a table
        void DeleteAttribute(string s); //takes in a single attribute name to delete from a table
        void AddRecord(Record r); //insert a record and adds it to the table
        void SetName(string s); //set the name of the table.
        
        vector<string>* GetAttributes(); //return a list of attributes for the table
        int GetSize(); //returns the number of records in the table
        
        string GetName(); //returns the name of the table
        Record GetRecord(int r); //returns the rth record
        
        Table* CrossJoin(const Table& t1); //combine two tables
        Table* NaturalJoin(const Table& t1); //combine two tables
        
        int Count(string s); //takes in single sttribute name and counts non-null entries
        string Min(string s);
        string Max(string s);
        

        //----------------------------------//
        //OPERATION FUNCTIONS               //
        //----------------------------------//
        void rename(string s1, string s2); //rename s1 with s2
        void SpecifyKey(vector <string> s); //set s as being a key for the table
};
#endif
