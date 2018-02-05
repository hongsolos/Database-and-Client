#include <iostream>
#include <string>
#include <vector>
#include "database.h"

using namespace std;

bool compare_table (Table t1, Table t2){
    vector <string> r1 = t1.getAttributes();
    vector <string> r2 = t2.getAttributes();
    if (r1.size() != r2.size()){
        return false;
    }
    for (int i =0; i < r1.size(); i++){
        if (r1[i].compare(r2[i]) != 0)
            return false;
    }
    return true;
};

int main(){
    /*--------------------------------------/
    /Record                     Claire Duong/ 
    /--------------------------------------*/
        //Testing Constructor with size input
        //Record test_record;
        Record test_record(3);
        if(test_record.size()!=3){ //Result supposed to be 3
            printf("Constructor failed");
        }
        else{
            printf("Constructor success");
        }
        
        //Testing the constructor that takes attributes
        try{ 
            vector<string> r_test;
            r_test.push_back("007");
            r_test.push_back("James");
            r_test.push_back("SER");
            cout << "2nd Constructor passed";
        } catch (...){
            cout << "Overloaded failed";
        }
        
        
        //Testing accessor function -- Can't test until implemented
        // string test1 = "Test 1";
        // try{
        //     test_record[2] = "Test 1";
        //     if(test1.compare(test_record[2]) == 0){
        //         printf("Accessor failed");
        //     }
        //     else{
        //         printf("Accessor success");
        //     }
        // } catch (...) {
        //     cout << "Overloaded functions failed.";
        // }
        
        
    
    /*--------------------------------------/
    /Table                                 /
    /--------------------------------------*/
        //Assume that Record and its functions perform correctly
        Table test_table;
        
        //Constructor -- Adding 3 attributes to the table
        //Assume Table size() function works
            vector <string> tes_attri;
            tes_attri.push_back("ID");
            tes_attri.push_back("NAME");
            tes_attri.push_back("YEAR");
            
            Table tab_1(tes_attri);
            if (tab_1.getAttributes().size() != 3){ //3 Attributes
                printf("Table Constructor failed. Size is incorrect");
            } else {
                printf("Table Constructor passed.");
            }
            
        //Add attribute
            tab_1.addAttribute("K/D");
            if (tab_1.getAttributes().size() != 4){ //4 Attributes
                printf("Function addAttribute failed. Size is incorrect");
            } else {
                printf("Function addAttribute passed.");
            }
        
        //Delete attribute
            tab_1.deleteAttribute("K/D");
            if (tab_1.getAttributes().size() != 3){ //3 Attributes Now
                printf("Function deleteAttribute failed. Size is incorrect");
            }
            
            bool passed = true;
            for (int i = 0; i < tab_1.getAttributes().size(); i++){
                if (tab_1.getAttributes()[i].compare("K/D") == 0){
                    printf("Function deleteAttribute failed. Wrong deletion");
                    passed = false;
                    break;
                }
            }
            if (passed){
                printf("Function addAttribute passed.");
            }
   
        //Add record function
        //Assume Table's size function perform correctly
            //CREATE 3 RECORDS WITH 3 ATTRIBUTES
            vector <string> stds;
            stds.push_back("001");
            stds.push_back("Peter");
            stds.push_back("18");
            vector <string> std1;
            std1.push_back("002");
            std1.push_back("Clark");
            std1.push_back("25");
            vector <string> std2;
            std2.push_back("003");
            std2.push_back("Nancy");
            std2.push_back("20");
            
            Record ts(stds);
            Record ts1(std1);
            Record ts2(std2);
            //ADD THE NEWLY CREATED RECORDS INTO A TEST TABLE
            vector <string> new_table_attr;
            new_table_attr.push_back("ID");
            new_table_attr.push_back("NAME");
            new_table_attr.push_back("AGE");
            Table new_table(new_table_attr);
            
            new_table.add(ts);
            new_table.add(ts1);
            new_table.add(ts2);
            
            //CHECK CORRECTNESS
            if (new_table.size() != 3){
                printf("Table's add function failed. Incorrect number of inputed record");
            } else {
                printf("Table's add function passed.");
            }
            
        //Get attributes
            vector <string> attributes_test = tab_1.getAttributes();
            if (attributes_test[0].compare("ID") != 0 ||
                attributes_test[1].compare("NAME") != 0 ||
                attributes_test[2].compare("YEAR") != 0) 
            {
                printf("Function getAttributes failed. Incorrect attributes listed");
            } else {
                printf("Function getAttributes passed.");
            }
        
        //Get size
        //Follow add function above;
            if (new_table.size() != 3){
                printf("Table's add function failed. Incorrect number of inputted record");
            } else {
                printf("Table's add function passed.");
            }
        
        //Iterator
        //Can't test properly without a mean to compare two record object
            try{
                vector<Record>::iterator ty = new_table.getIteratorIndex(1); //Try to get record at index 1
            } catch (...){
                cout << "Function getIteratorIndex failed at run time.";
            }
        //Specify key
            //Check to see if it can set a key
            try {
                new_table.specifyKey("wow");
            } catch (...) {
                cout << "Function specifyKey failed at run time.";
            }
            
            //Check that it can only be set ONCE
            try {
                new_table.specifyKey("wew");
                new_table.specifyKey("waw");
            } catch (...) {
                cout << "Function passed";
            }
            cout << "Failed, key is set more than once";
        
        //Cross join
        int correct_size = tab_1.size() + new_table.size();
        Table tab_2 = tab_1;
        tab_2.crossJoin(new_table);
        if (correct_size != tab_2.size()){ //tab_1 has 0 RECORDS -- new_table has 3 RECORDS
            printf("Function Cross Join failed. Incorrect combined total of records");
        } else {
            printf("Function Cross Join passed.");
        }
        
        //Natural join
        int correct_size_n = tab_1.size() + new_table.size();
        tab_1.naturalJoin(new_table);
        if (correct_size_n != tab_1.size()){ //tab_1 has 0 RECORDS -- new_table has 3 RECORDS
            printf("Function Natural Join failed. Incorrect combined total of records");
        // } else if {
           //TEST CASE CAN'T BE WRITTEN, NO RETURN FUNCTION FROM RECORD TO COMPARE RECORDS 
        } else {
            printf("Function Natural Join passed.");
        }
        
        //Count
        if(new_table.count("ID") != 3){
            printf("Table's count function failed. Incorrect count");
        }
        else{
            printf("Table's count function passed.");
        }
        
        //Min
        if(new_table.min("AGE") != 18){
            printf("Table's min function failed. Incorrect minimum");
        }
        else{
            printf("Table's min function passed.");
        }
        
        //Max
        if(new_table.max("AGE") != 25){
            printf("Table's max function failed. Incorrect maximum");
        }
        else{
            printf("Table's max function passed.");
        }
            
    /*--------------------------------------/
    /Database                               /
    /--------------------------------------*/
        //Initilize database--
        Database test_database;
        Table table_t1;
        Table table_t2;
        
        //Test functions/ === Assume Table and all of its functions work, input are of correct type
        //Add Table
            //Assume getTables works
            test_database.addTable(table_t1, "Test Table 1"); //1st Table added
            test_database.addTable(table_t2, "Test Table 2"); //2nd Table added
            vector <Table> database_result_1;
            try {
                database_result_1 = test_database.getTables();
            } catch (...) { cout << "Get table function failed"; }
            
            if (database_result_1[0].getAttributes().size() != table_t1.getAttributes().size()){
                printf("Function addTable failed. Size is not as expected");
            } else if (!compare_table(database_result_1[0], table_t1)){
                printf("Function addTable failed. Object added is not the same");
            } else {
                printf("Function addTable passed");
            }
        
        //Drop Table
            //Assume database is not empty *implement check
            test_database.dropTable("Table Test 1"); //Drop the added Table Test 1
            vector <Table> database_result_2;
            
            try {
                database_result_2 = test_database.getTables();
            } catch (...) { cout << "Get table function failed"; }
            
            if (database_result_2.size() == 0){
                printf("Function dropTable failed on empty database");
            }
            if (database_result_2.size() != 1){
                printf("Function dropTable failed. Size is not as expected");
            } else if (!compare_table(database_result_2[0], table_t2)){
                printf("Function addTable failed. Wrong object is deleted");
            } else {
                printf("Function addTable passed");
            }
            
        
        //List Tables - The partner team didn't provide a way to get Table Name -> can't check
            test_database.addTable(table_t1, "Table Test 1"); //Added Table Test 1 back to the database
            
            vector <string> database_result_3 = test_database.listTables(); //Get the list
            if (database_result_3.size() != 2){ //We have 2 tables in the database
                printf("Function listTables failed. Size is not as expected");
            } else {
                printf("Funtion addTable passed, partially. Need a function to retun Table Name");
            }
        //Get Table
            vector <Table> database_result_4 = test_database.getTables();
            if (database_result_4.size() != 2){ //We have 2 tables in the database
                printf("Function getTables failed. Size is not as expected");
            } else if (!compare_table(database_result_4[0],table_t2) || !compare_table(database_result_4[1],table_t1)){
                printf("Function getTables failed. Return tables are not the same as Original");
            } else {
                printf("Function getTables passed");
            }
        
        //Query
            //Creating NEW Records with ID NAME YEAR
            vector <string> record_r;
            record_r.push_back("001");
            record_r.push_back("John");
            record_r.push_back("SER");
            vector <string> record_r1;
            record_r1.push_back("002");
            record_r1.push_back("Jacob");
            record_r1.push_back("JUR");
            vector <string> record_r2;
            record_r2.push_back("003");
            record_r2.push_back("Janes");
            record_r2.push_back("SSR");
            
            Record r(record_r);
            Record r1(record_r1);
            Record r2(record_r2);
            
            //Add records to table
            vector <string> t3_attr;
            t3_attr.push_back("ID");
            t3_attr.push_back("NAME");
            t3_attr.push_back("YEAR");
            
            Table table_t3(t3_attr);
            
            table_t3.add(r);
            table_t3.add(r1);
            table_t3.add(r2);
            
            //Add Table to the database 
            test_database.addTable(table_t3, "Table Test 3");
            
            //SELECT *, FROM TABLE TEST 3, WHERE ID 002
            Table database_result_5 = test_database.query("*","Table Test 3","ID = 002");
            
            vector <string> correct_input;
            correct_input.push_back("002");
            correct_input.push_back("Jacob");
            correct_input.push_back("JUR");
            Record correct_record(correct_input);
            
            Table correct_result(t3_attr);
            correct_result.add(correct_record);
            
            if (!compare_table(correct_result, database_result_5)){
                printf ("Function query failed. Result is incorrect");
            } else {
                printf ("Function query passed.");
            }
            
        //Overloader
            // test_database[];
            // &test_database[];
    return 1;
}
