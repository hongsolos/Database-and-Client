**API SPECIFICATION**
----

* **Introduction**
  
  This project provides structure and implementation of a Database. Through the included library file, a user can ultilize its functions to create and maintain his or her own database. 
  
* **Classes and Functions**

  * Record:
    - To create a record test: Record test(int size)
    - To get size of record test: test.get_size()
    - To get an entry from a test record at an index: test.get(int index)
    - To set an entry at an index of test record: test.set(int index, string entry)
    
  * Table:
    - To create a table test: Table test(vector <string\> attributes)
    - To add an attribute to the table test: test.AddAttribute(string attribute)
    - To delete an attribute from the table test: test.DeleteAttribute(string attribute)
    - To add a record to a table test: test.AddRecord(string recordName)
    - To set the name of a table test: test.SetName(string name)
    - To get a list of attributes from a table test: test.GetAttributes() will return a pointer to a vector of strings, containing all attributes
    - To get the number of records in a table test: test.GetSize()
    - To get the name of a table test: test.GetName()
    - To get the record at an index given from table test: test.GetRecord(int recordIndex)
    - To cross join tables test1 and test2: test1.CrossJoin(test2)
      * returns a pointer to test1 which is updated to be the joined table
    - To natural join tables test1 and test2: test1.NaturalJoin(test2)
      * returns a pointer to test1 which is updated to be the joined table
    - To count the non-empty entries of a table test attribute: test.Count(string attribute)
    - To get min of a table test attribute: test.Min(string attribute)
      * works with numerical and non-numerical attributes
    - To get max of a table test attribute: test.Max(string attribute)
      * works with numerical and non-numerical attributes
    - To rename an attribute "attr" to "attr1" in table test: test.rename(string attr, string attr1)
    - To set key attribute(s) for table test: test.SpecifyKey(string <vector\> attributes)
  
  * Database
    - To create a database "test": Database test()
    - To add a table to the database: test.add_table(Table input, string input_name)
    - To delete a table from the database: test.drop(string input_name)
    - To save a database to a file: test.save(string file_name)
    - To load a database from a file: test.load(string file_name)
    - To merge another database with 'test': test.merge(input_database)
    - To replace the contents of this database with the duplicated content of another: test.copy(input_database)
    - To retrieve a new table populated with the values of specfic attributes: test.query(string attributes, string table_name, string operators)
    - To delete particular values of a table: test.obliterate(string attributes, string table_name, string operators)
    - To modify a target table: test.update(string table_name, string where, string set_clause)
    
This library requires the use of 'Database.h', 'Table.h', and 'Record.h', as well as 'datalib.so'.

