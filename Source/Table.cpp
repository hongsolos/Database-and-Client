#include "Table.h"

Table::Table(){
    //default constructor
} 

Table::Table(vector<string> vec){
    //constructor takes in a list of attribute names
    for(unsigned int i = 0; i < vec.size(); i++){
        attributes.push_back(vec[i]);
    }
}

void Table::AddAttribute(string s){
    //takes in a single attribute name to add to a table
    attributes.push_back(s);
}

void Table::DeleteAttribute(string s){
    //takes in a single attribute name to delete from a table
    int temp = 0;
    for(unsigned int i = 0; i < attributes.size(); i++){
        if(attributes[i]==s){
             attributes.erase(attributes.begin()+i);
             temp = i;
        }
    }
    for (unsigned int i = 0; i < records.size(); i++){
        records[i].data.erase(records[i].data.begin()+temp);
    }
}

void Table::AddRecord(Record r){
    //insert a record and adds it to the table
    records.push_back(r);
}

vector<string>* Table::GetAttributes(){
    //return a list of attributes for the table
    return &attributes; //nullptr
}

int Table::GetSize(){
    //returns the number of records in the table
    return records.size();
}

void Table::SetName(string s){
    //takes in the name of the table from user
    table_name = s;
}

string Table::GetName(){
    //returns the name of the table
    return table_name;
}

Record Table::GetRecord(int r){
    return records[r];
}

Table* Table::CrossJoin(const Table& t1){
    //combine two tables
    
    //add attributes from t1 to this
    for(unsigned int i = 0; i < t1.attributes.size(); i++){
        attributes.push_back(t1.attributes[i]);
    }
    
    //get records
    Record r(attributes.size());
    int originalSize = records.size();
    for(int i = 0; i < originalSize; i++){
        //copy first table record data
        for(int j = 0; j < originalSize; j++){
            r.set(j,records[i].get(j));
        }
        //copy second table record data
        for(unsigned int ii = 0; ii < t1.records.size(); ii++){
            for(unsigned int j = 0; j < t1.attributes.size(); j++){
                r.set(originalSize+j,t1.records[ii].get(j));
            }
            records.push_back(r);
        }
    }
    //clear old record data
    for(int i = 0; i < originalSize; i++){
        records.erase(records.begin());
    }
    return this;
}

Table* Table::NaturalJoin(const Table& t1){
    //variables
    vector <int> index_location;
    vector <int> index_location_t1;
    vector <int> new_attributes;
    int original_rec = records.size();
    int original_attr = attributes.size();
    
    //check if second table has key
    if(t1.key.size()==0){
        cout << "Error: a key is not specified for the input table!" << endl;
        return this;
    }
    
    //check if first table has all key attributes
    unsigned int attrMatch = 0;
    for(unsigned int i = 0; i < t1.key.size(); i++){
        for(unsigned int j = 0; j < attributes.size(); j++){
            if(attributes[j]==t1.key[i]){
                index_location.push_back(j); //get index of key attributes
                attrMatch++;
            }
        }
    }
    if(attrMatch != t1.key.size()){
        cout << "Error: first table does not match second table key!" << endl;
        return this;
    }
    
    //get index of t1 key attributes
    for(unsigned int i = 0; i < t1.key.size(); i++){
        for(unsigned int j = 0; j < t1.attributes.size(); j++){
            if(t1.attributes[j]==t1.key[i]){
                index_location_t1.push_back(j);
            }
        }
    }
    
    //get index of new attributes to add
    bool isKey = false;
    for(unsigned int i = 0; i < t1.attributes.size(); i++){ //checks a t1 attributes
        for(unsigned int j = 0; j < t1.key.size(); j++){ //checks all key attributes
            if(t1.attributes[i]==t1.key[j]){
                isKey = true;
            }
        }
        //add if not a key attribute
        if(isKey==false){
            new_attributes.push_back(i);
        }
        isKey = false;
    }
    
    // add new attributes
    for(unsigned int i = 0; i < new_attributes.size(); i++){
        attributes.push_back(t1.attributes[new_attributes[i]]);
    }
    
    //add records
    bool keyMatch = false;
    Record r(attributes.size());
    for(int i = 0; i < original_rec; i++){ //for each record in first table
        //copy first table record data
        for(int j = 0; j < original_attr; j++){
            r.set(j,records[i].get(j));
        }
        //find matching data record and copy
        for(unsigned int j = 0; j < t1.records.size(); j++){ //check records of second table
            for(unsigned int k=0; k<t1.key.size(); k++){ //compare key attributes
                if(records[i].get(index_location[k]).compare(t1.records[j].get(index_location_t1[k]))==0){
                    keyMatch = true;
                }
                //if key attribute does not match, break out to check next record
                else{
                    keyMatch = false;
                    break;
                }
            }
            //if key attributes match, add new record data then move on to next record
            if(keyMatch==true){
                for(unsigned int k = 0; k < new_attributes.size(); k++){
                    r.set(original_attr+k,t1.records[j].get(new_attributes[k]));
                } 
                break;
            }
        }
        records.push_back(r);
    }
    
    //clear old record data
    for(int i=0; i < original_rec; i++){
        records.erase(records.begin());
    }
    
    return this;
}

int Table::Count(string s){
    //takes in single attribute name and counts non-null entries
    int temp = 0; //temparary variable to store number of entries
    for(unsigned int i=0; i<attributes.size(); i++){
        if(attributes[i]==s){
            for(int j = 0; j < records[i].get_size(); j++){
                if(records[j].get(i)!=""){
                    temp++;
                }
            }
        }
    }
    return temp;
}
    
string Table::Min(string s){
    string temp = ""; //temporary variable to store the minimum value
    for(unsigned int i = 0; i < attributes.size(); i++){
        if(attributes[i]==s){
            temp = records[0].get(i); //initailze it with first element
            //if not numerical values
            if(temp.find_first_not_of("0123456789")!=string::npos){
                for(int j = 0; j < records[i].get_size(); j++){
                    if(records[j].get(i)<temp){
                        temp = records[j].get(i);
                    }
                }
            }
            //if numberical values
            else{
                for(int j=0; j < records[i].get_size(); j++){
                    if(stoi(records[j].get(i))<stoi(temp)){
                        temp = records[j].get(i);
                    }
                }
            }
        }
    }
    return temp;
}

string Table::Max(string s){
    string temp = ""; //temporary variable to store the minimum value
    for(unsigned int i=0; i<attributes.size(); i++){
        if(attributes[i]==s){
            temp = records[0].get(i); //initailze it with first element
            //if not numerical values
            if(temp.find_first_not_of("0123456789")!=string::npos){
                for(int j = 0; j< records[i].get_size(); j++){
                    if(records[j].get(i)>temp){
                        temp = records[j].get(i);
                    }
                }
            }
            //if numerical values
            else{
                for(int j = 0; j< records[i].get_size(); j++){
                    if(stoi(records[j].get(i))>stoi(temp)){
                        temp = records[j].get(i);
                    }
                }
            }
        }
    }
    return temp;
}
        
void Table::rename(string s1, string s2){
    //rename s1 with s2
    for(unsigned int i = 0; i < attributes.size(); i++){
        if(attributes[i] == s1){
             attributes[i] = s2;
        }
    }
}

void Table::SpecifyKey(vector <string> s){
    //set s as being a key for the table
    key = s;
}
