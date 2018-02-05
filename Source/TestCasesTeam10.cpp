// TestCasesTeam10.cpp : Defines the entry point for the console application.
//

// --- Test file for database
// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"
#include "Database.h"
#include "Record.h"
#include "Table.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

void testDatabase() {
	vector<string> s;
	s.push_back("attribute1");
	s.push_back("attribute2");
	bool pass = true;

	Database dummydb;
	Database loaddb;
	Database mergedb;
	Database copydb;

	Table dummyt(s);
	Table queryt(s);
	Table* t;
    
    Record r = *(new Record(1));
    r.set(0,"test");
    Record r2 = *(new Record(2));
    r2.set(0,"test1");
    r2.set(1,"test2");
    dummyt.AddRecord(r);
    dummyt.AddRecord(r2);

	// Test for the adding a table to a database
	try {
		dummydb.add_table(dummyt, "Table1");
	}
	catch (...) {
		cout << "Table insertion failed!" << endl;
		pass = false;
	}
	if (pass) {
		cout << "Table insertion passed!" << endl;
	}
	else {
		pass = true;
	}

	// Test for saving a database to a file
	try {
		dummydb.save("DankTestFile.txt");
	}
	catch (...) {
		cout << "File saving failed!" << endl;
		pass = false;
	}
	if (pass) {
		cout << "File saving passed!" << endl;
	}
	else {
		pass = true;
	}

	// Test for loading a databse from a file
	try {
		loaddb.load("DankTestFile.txt");
	}
	catch (...) {
		cout << "File loading failed!" << endl;
		pass = false;
	}
	if (pass) {
		cout << "File loading passed!" << endl;
	}
	else {
		pass = true;
	}

	// Test for merge a database with current database
	try {
		mergedb.merge(dummydb);
	}
	catch (...) {
		cout << "Merge failed!" << endl;
		pass = false;
	}
	if (pass) {
		cout << "Merge passed!" << endl;
	}
	else {
		pass = true;
	}

	// Test for copying a database
	try {
		copydb.copy(dummydb);
	}
	catch (...) {
		cout << "Copying failed!" << endl;
		pass = false;
	}
	if (pass) {
		cout << "Copying passed!" << endl;
	}
	else {
		pass = true;
	}

	// Test for query
	try {
		t = dummydb.query("attribute2", "Table1", "attribute2 == 5");
	}
	catch (...) {
		cout << "Query failed!" << endl;
		pass = false;
	}
	if (pass) {
		cout << "Query passed!" << endl;
	}
	else {
		pass = true;
	}


	// Test for obliterate attribute from table
	try {
		dummydb.obliterate("attribute2", "Table1", "==");
	}
	catch (...) {
		cout << "Obliterate failed!" << endl;
		pass = false;
	}
	if (pass) {
		cout << "Obliterate passed!" << endl;
	}
	else {
		pass = true;
	}


	// Test for update table
	try {
		dummydb.update("Table1", "attribute1 > 2", "attribute1 = attribue1 + 2");
	}
	catch (...) {
		cout << "Update failed!" << endl;
		pass = false;
	}
	if (pass) {
		cout << "Update passed!" << endl;
	}
	else {
		pass = true;
	}


	// Test for the deleting a table from a database
	try {
		dummydb.drop("Table1");
	}
	catch (...) {
		cout << "Table deletion failed!" << endl;
		pass = false;
	}
	if (pass) {
		cout << "Table deletion passed!" << endl;
	}
	else {
		pass = true;
	}

	cout << "Database testing is concluded!" << endl;


	return;
}

//==============================================================
//		TABLE TEST CASE
void testtable(){
    //Assume that Record and its functions perform correctly
    Table test_table;
        
    //Constructor -- Adding 3 attributes to the table
    //Assume Table Getsize() function works
    	vector <string> tes_attri;
        tes_attri.push_back("ID");
        tes_attri.push_back("NAME");
        tes_attri.push_back("YEAR");
            
        Table tab_1(tes_attri);
        if ((*tab_1.GetAttributes()).size() != 3){ //3 Attributes
            printf("Table Constructor failed. Size is incorrect\n");
        } else {
            printf("Table Constructor passed.\n");
        }
            
        //Add attribute
        tab_1.AddAttribute("K/D");
        if ((*tab_1.GetAttributes()).size() != 4){ //4 Attributes
            printf("Function addAttribute failed. Size is incorrect\n");
        } else {
            printf("Function addAttribute passed.\n");
        }
        
        //Delete attribute
        tab_1.DeleteAttribute("K/D");
        if ((*tab_1.GetAttributes()).size() != 3){ //3 Attributes Now
            printf("Function deleteAttribute failed. Size is incorrect\n");
        }
        
        bool passed = true;
        for (unsigned int i = 0; i < (*tab_1.GetAttributes()).size(); i++){
            if ((*tab_1.GetAttributes())[i].compare("K/D") == 0){
                printf("Function deleteAttribute failed. Wrong deletion\n");
                passed = false;
                break;
            }
        }
        if (passed){
            printf("Function deleteAttribute passed.\n");
        }
		
        //Add record function
        //Assume Table's size function perform correctly
            //CREATE 3 RECORDS WITH 3 ATTRIBUTES
            Record ts(3);
            ts.set(0, "001");
            ts.set(1, "Peter");
            ts.set(2, "18");
            Record ts1(3);
            ts1.set(0, "002");
            ts1.set(1, "Clark");
            ts1.set(2, "25");
            Record ts2(3);
            ts2.set(0, "003");
            ts2.set(1, "Nancy");
            ts2.set(2, "20");
            
            //ADD THE NEWLY CREATED RECORDS INTO A TEST TABLE
            vector <string> new_table_attr;
            new_table_attr.push_back("ID");
            new_table_attr.push_back("NAME");
            new_table_attr.push_back("AGE");
            Table new_table(new_table_attr);
            
            new_table.AddRecord(ts);
            new_table.AddRecord(ts1);
            new_table.AddRecord(ts2);
            
            //CHECK CORRECTNESS
            if (new_table.GetSize() != 3){
                printf("Table's add function failed. Incorrect number of inputed record\n");
            } else {
                printf("Table's add function passed.\n");
            }
          
        //Get attributes
            vector <string> attributes_test = (*tab_1.GetAttributes());
            if (attributes_test[0].compare("ID") != 0 ||
                attributes_test[1].compare("NAME") != 0 ||
                attributes_test[2].compare("YEAR") != 0) 
            {
                printf("Function GetAttributes failed. Incorrect attributes listed\n");
            } else {
                printf("Function GetAttributes passed.\n");
            }
        
        //Get size
        //Follow add function above;
            if (new_table.GetSize() != 3){
                printf("Table's add function failed. Incorrect number of inputted record\n");
            } else {
                printf("Table's add function passed.\n");
            }
        
        //Get record
        if(new_table.GetRecord(0).get(1).compare("Peter") != 0){
        	printf("Table's GetRecord function failed. Incorrect record data\n");
        }
        else{
        	printf("Table's GetRecord function passed.\n");
        }
        
        //Cross join VanTypes and SeatsAndPaint
        vector <string> vt_attr;
        vt_attr.push_back("Make");
        vt_attr.push_back("Model");
        Table VanTypes(vt_attr);
        Record vt1(2);
        vt1.set(0,"Dodge");
        vt1.set(1,"Caravan");
        Record vt2(2);
        vt2.set(0,"Honda");
        vt2.set(1,"Odyssey");
        VanTypes.AddRecord(vt1);
        VanTypes.AddRecord(vt2);
        
        vector <string> sp_attr;
        sp_attr.push_back("Seats");
        sp_attr.push_back("Paint");
        Table SeatsAndPaint(sp_attr); 
        Record sp1(2);
        sp1.set(0,"Cloth");
        sp1.set(1,"Standard");
        Record sp2(2);
        sp2.set(0,"Leather");
        sp2.set(1,"Standard");
        Record sp3(2);
        sp3.set(0,"Leather");
        sp3.set(1,"Premium");
        SeatsAndPaint.AddRecord(sp1);
        SeatsAndPaint.AddRecord(sp2);
        SeatsAndPaint.AddRecord(sp3);
        
        int correct_size = VanTypes.GetSize() * SeatsAndPaint.GetSize();
        Table cJoin = *VanTypes.CrossJoin(SeatsAndPaint);
        if (correct_size != cJoin.GetSize()){ //VanTypes has 2 RECORDS -- new_table has 3 RECORDS
            printf("Function CrossJoin failed. Incorrect combined total of records\n");
        } else if(cJoin.GetRecord(0).get(2).compare("Cloth") != 0) {
            printf("Function CrossJoin failed. Incorrect data copied\n");
        } else {
            printf("Function CrossJoin passed.\n");
        }
        
        //Natural join Students and SchoolLocations
        vector <string> st_attr;
        st_attr.push_back("Name");
        st_attr.push_back("School");
        Table Students(st_attr);
        Record st1(2);
        st1.set(0,"Joe Smith");
        st1.set(1,"Rice");
        Record st2(2);
        st2.set(0,"Jill Smith");
        st2.set(1,"LSU");
        Record st3(2);
        st3.set(0,"Sam Jones");
        st3.set(1,"Texas A&M");
        Record st4(2);
        st4.set(0,"Sue Jones");
        st4.set(1,"Rice");
        Students.AddRecord(st1);
        Students.AddRecord(st2);
        Students.AddRecord(st3);
        Students.AddRecord(st4);
        
        vector <string> scl_attr;
        scl_attr.push_back("School");
        scl_attr.push_back("City");
        Table SchoolLocations(scl_attr);
        Record scl1(2);
        scl1.set(0,"Texas A&M");
        scl1.set(1,"College Station");
        Record scl2(2);
        scl2.set(0,"Rice");
        scl2.set(1,"Houston");
        Record scl3(2);
        scl3.set(0,"LSU");
        scl3.set(1,"Baton Rouge");
        SchoolLocations.AddRecord(scl1);
        SchoolLocations.AddRecord(scl2);
        SchoolLocations.AddRecord(scl3);
        
        vector <string> scl_key;
        scl_key.push_back("School");
        SchoolLocations.SpecifyKey(scl_key);
        
        Table nJoin = *Students.NaturalJoin(SchoolLocations);
        
        if (nJoin.GetAttributes()->size() != 3){ //should have attributes Name, School, City
            printf("Function NaturalJoin failed. Incorrect number of attributes\n");
        } else if (nJoin.GetRecord(0).get(2).compare("Houston") != 0){
            printf("Function NaturalJoin failed. Incorrect data copied\n");
        } else {
            printf("Function NaturalJoin passed.\n");
        }
        
        //Count
        if(new_table.Count("ID") != 3){
            printf("Table's Count function failed. Incorrect count\n");
        }
        else{
            printf("Table's Count function passed.\n");
        }
        
        //Min
        if(stoi(new_table.Min("AGE")) != 18){
            printf("Table's Min function failed. Incorrect minimum\n");
        }
        else{
            printf("Table's Min function passed.\n");
        }
        
        //Max
        if(stoi(new_table.Max("AGE")) != 25){
            printf("Table's Max function failed. Incorrect maximum\n");
        }
        else{
            printf("Table's Max function passed.\n");
        }
        
        //rename
        new_table.rename("NAME","FIRST");
        if((*new_table.GetAttributes())[1].compare("FIRST") != 0){
            printf("Table's rename function failed. Incorrect name\n");
        }
        else{
            printf("Table's rename function passed.\n");
        }
}
/* ==================================================
		RECORD TEST CASE
*/
void TestRecord() {

	//test CONSTRUCTORS

	Record record(10);

	//test int get_size()

	int getsize = record.get_size();
	cout << "The test result for int get_size is : " << getsize << endl;
	cout << "The correct result for int get_size is : " << 10 << endl;

	if (getsize == 10) cout << "The test for get_size has passed." << endl;
	else cout << "Your test for get_size hasn't passed." << endl;

	//test set and return entry

	record.set(0, "Hello");
	string result = record.get(0);
	if (result == "Hello")
		cout << "The test for set and return has passed." << endl;
	else cout << "The test for set and return hasn't passed" << endl;
}

int main(int argc, char* const argv[])
{
	//Database test case
	testDatabase();
	//Record test case
	TestRecord();
	
	//Table test case
	testtable();

	//int result = Catch::Session().run(argc, argv);

	//while (true);
	//return result;
	return 1;
}
