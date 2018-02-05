#ifndef _Record_h_
#define _Record_h_

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Record{
        friend class Table;
    private:
        vector <string> data;
        
    public:        
        /*----------------------------------//
        //CONSTRUCTORS                      //
        //----------------------------------*/
        Record (int s): data(s,""){};
        
        /*----------------------------------//
        //GETTER FUNCTIONS                  //
        //----------------------------------*/
        //Returns the size of the record
        int get_size ();
        
        //Returns the entry at the index given
        string get(int index) const;
        
        /*----------------------------------//
        //OPERATION FUNCTIONS               //
        //----------------------------------*/
        
        //Adds an entry at the index given
        void set(int index, string entry);
        
};
#endif
