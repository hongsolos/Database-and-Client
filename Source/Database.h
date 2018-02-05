#ifndef _Database_h_
#define _Database_h_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include "Table.h"

using namespace std;
class Database{
    private:
        vector <Table> tables;
        
        string cleanToken(string token);
        short getParamType(string param);
        
        //For reference
        void ultility(string input, void* ptr);
        
    public:
        /*----------------------------------//
        //CONSTRUCTORS                      //
        //----------------------------------*/
        Database (): tables(0) {}
        /*----------------------------------//
        //GETTER FUNCTIONS                  //
        //----------------------------------*/
        
        //List table function - : return a list of all table names in the database
        vector<string> list_table ();
        
        //Get table function - : return all tables in the database
        vector<Table> list_all_table();
        
        /*----------------------------------//
        //OPERATION FUNCTIONS               //
        //----------------------------------*/
        
        //Add Table Function - take table object and a name: add table to database
        void add_table (Table input, string input_name);

        //Drop function - takes table name: delete from database
        void drop (string input_name);
        
        //Save function - takes file name: save database to file
        void save (string file_name);
        
        //Load function - takes file name: load database from file
        void load (string file_name);
        
        //Merge function - takes another database: merge with target
        void merge (Database input_database);
        
        //Copy function - takes database: copy its entirety
        void copy (Database input_database);
        
        //Query function
        Table* query(string attributes, string table_name, string operators);
        
        //Delete function - takes table: delete the table from the target table
        void obliterate(string attributes, string table_name, string operators);
        
        //Update function - takes table name, where, set clause (reference attr): modify target table *support math op
        void update(string table_name, string where, string set_clause);
        
        
        /*----------------------------------//
        //FORMAT PRINT                      //
        //----------------------------------*/
};
#endif
