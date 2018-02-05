#include "Record.h"

//Returns the size of the record
int Record::get_size (){
    return data.size();
}

//Returns the entry at the index given
string Record::get(int index) const{
    return data[index];
}

//Adds an entry at the index given
void Record::set(int index, string entry){
    data[index] = entry;
}
