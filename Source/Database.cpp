#include "Database.h"
 
 
using namespace std;
 
/*----------------------------------//
//GETTER FUNCTIONS                  //
//----------------------------------*/
 
//List table function - : return a list of all table names in the database
vector<string> Database::list_table(){
    vector<string> result;
    for(int i = 0; i < tables.size(); i++) {
        result.push_back(tables[i].GetName());
    }
    return result;
}
 
//Get table function - : return all tables in the database
vector<Table> Database::list_all_table(){
    return tables;
}
 
/*----------------------------------//
//OPERATION FUNCTIONS               //
//----------------------------------*/
 
//Add Table Function - take table object and a name: add table to database
void Database::add_table (Table input, string input_name){
    input.SetName(input_name);
    tables.push_back(input);
}
 
//Drop function - takes table name: delete from database
void Database::drop (string input_name){
    for (unsigned int i = 0; i < tables.size(); i++){
        if(tables[i].GetName().compare(input_name) == 0){
            tables.erase(tables.begin() - i);
        }
    }
}
 
//Save function - takes file name: save database to file
void Database::save (string file_name){
    ofstream out;
    out.open(file_name);
        for(int i = 0; i < tables.size(); i++) {
            Table t = tables[i];
            string tableOut = "";
            tableOut += t.GetName();
            tableOut += "`";
            vector<string>* attrs = t.GetAttributes();
                for(int j = 0; j < attrs->size(); j++) {
                    string attrOut = attrs->at(j) + ",";
                    tableOut += attrOut;
                }
                tableOut += "|";
                for(int j = 0; j < t.GetSize(); j++) {
                    Record r = t.GetRecord(j);
                    string recordOut = "";
                        for(int k = 0; k < r.get_size(); k++) {
                            recordOut += r.get(k);
                            recordOut += ",";
                        }
                    recordOut += ";";
                    tableOut += recordOut;
                }
            tableOut += "\n";
            out << tableOut;
        }
    out.close();
}
 
//Load function - takes file name: load database from file
void Database::load (string file_name){
    string line;
    ifstream in;
    in.open(file_name);
    if(in.is_open()) {
        while(getline(in,line)) {
            Table t = *(new Table());
 
            int pos = 0;
            while((pos = line.find('`')) != string::npos) {
                t.SetName(line.substr(0, pos));
                line.erase(0, pos+1);
            }
           
            int seperatorPos = line.find("|");
           
            string attrList = line.substr(0, seperatorPos);
            while((pos = attrList.find(',')) != string::npos) {
                t.AddAttribute(attrList.substr(0, pos));
                attrList.erase(0, pos+1);
            }
           
            string recList = line.substr(seperatorPos+1);
            while((pos = recList.find(';')) != string::npos) {
                vector<string> recordContents = *(new vector<string>);
                string recContent = recList.substr(0, pos);
                int pos2 = 0;
                int index = 0;
                while((pos2 = recContent.find(',')) != string::npos) {
                    string stuff = recContent.substr(0, pos2);
                    recordContents.push_back(stuff);
                    recContent.erase(0, pos2+1);
                    index++;
                }
                Record r = *(new Record(index));
                for(int i = 0; i < recordContents.size(); i++) {
                    r.set(i,recordContents.at(i));
                }
                t.AddRecord(r);
                recList.erase(0, pos+1);
            }
            add_table(t,t.GetName());
        }
        in.close();
    }
}
 
//Merge function - takes another database: merge with target
void Database::merge (Database input_database){
    vector<Table> tb = input_database.list_all_table();
    for(int i = 0; i < tb.size(); i++) {
        Table t = tb[i];
        for(int j = 0; j < tables.size(); j++) {
            Table existingTable = tables[j];
            if(existingTable.GetName() == t.GetName()) {
                existingTable.CrossJoin(t);
            }
        }
    }
}
 
//Copy function - takes database: copy its entirety
void Database::copy (Database input_database){
    for(int i = 0; i < tables.size(); i++) { //remove stuff
        Table t = tables[i];
        string attrNames = "";
        vector<string>* attrs = t.GetAttributes();
        for(int j = 0; j < attrs->size(); j++) {
            attrNames += attrs->at(j);
        }
        obliterate(attrNames,t.GetName(),"");
    }
    vector<Table> tb = input_database.list_all_table();
    for(int i = 0; i < tb.size(); i++) { //add new stuff
        add_table(tb[i],tb[i].GetName());
    }
}
 
//help for query and getparamtype returns firsttokenend with the new token appended
string Database::cleanToken(string token) {
    int stackDepth = 0;
    int firstTokenEnd = 0;
    token = regex_replace(token, regex("^ +| +$|( ) +"), "$1");
    while(token.substr(0,1) == "(") {
        stackDepth = 1;
        firstTokenEnd = 0;
        for(int i = 0; i < token.length(); i++) {
            string curChar = token.substr(i,1);
            if(curChar == "(") {
                stackDepth++;
            } else if(curChar == ")") {
                stackDepth--;
            } else {
                continue;
            }
            if(stackDepth == 0) { //found end of a
                firstTokenEnd = i;
            }
        }
        if(firstTokenEnd == (token.length()-1)) { //first time hit the end of the parenthesis is at the end of the token aka token is wrapped in parens
            token = token.substr(1,token.length()-2); //clip ends off by 1, removing parens.
        } else {
            break; //first set of parens does not wrap token.
        }
    }
    if(firstTokenEnd == 0) { //no parens
        //first token must be a single word attr name (followed by an optional binary op for any and all) as all other ops require it.
        firstTokenEnd = token.find(' ') + 1;
        if(token.substr(firstTokenEnd,1) == "="
        || token.substr(firstTokenEnd,1) == "<"
        || token.substr(firstTokenEnd,1) == ">") { //if is std binary op
            firstTokenEnd = token.find(' ',firstTokenEnd); //set to next space.
        }
    }
    return to_string(firstTokenEnd) + token;
}
 
//helper func for query, returns 0 for unknown.
short Database::getParamType(string param) {
    short opType = 0; // 0: unknown, 1: exists, 2: not
    string temp = cleanToken(param);
    int firstTokenEnd = stoi(temp.substr(0,1));
    param = temp.substr(1);
   
    //check for unary operators.
    if(param.compare(0,6,"EXISTS") == 0) { //param.startsWith("EXISTS");
        opType = 1;
    } else if(param.compare(0,3,"NOT") == 0) {
        opType = 2;
    }
    if(opType != 0)
        return opType;
    //check for binary ops.
    param = param.substr(firstTokenEnd); //dont need the first token tbh, this just finds the type.
    if(param.compare(0,1,"=")) {
        opType = 3;
    } else if(param.compare(0,1,"<")) {
        opType = 4;
    } else if(param.compare(0,1,">")) {
        opType = 5;
    } else if(param.compare(0,2,"<>")) {
        opType = 6;
    } else if(param.compare(0,2,">=")) {
        opType = 7;
    } else if(param.compare(0,2,"<=")) {
        opType = 8;
    } else if(param.compare(0,2,"OR")) {
        opType = 9;
    } else if(param.compare(0,3,"AND")) {
        opType = 10;
    } else if(param.compare(0,3,"ANY")) {
        opType = 11;
    } else if(param.compare(0,3,"ALL")) {
        opType = 12;
    } else if(param.compare(0,2,"IN")) {
        opType = 13;
    }
    return opType;
}
 
//Query function ----- (SELECT ATTRIBUTE, FROM TABLE_NAME, WHERE - CONDITION)
//Since we are a 4 members team, AND, OR and NOT have to be written
//comma delimited attributes, spaces on either side of every operator.
Table* Database::query(string attributes, string table_name, string operators){
    //find main operation before recursing
    string origAttrs = attributes;
    attributes.erase(remove(attributes.begin(),attributes.end(),' '),attributes.end()); //remove all whitespace
    vector<string> attributeList = *(new vector<string>);
    int pos = 0;
    while((pos = attributes.find(',')) != string::npos) {
        attributeList.push_back(attributes.substr(0, pos));
        attributes.erase(0, pos+1);
    }
    if(!attributes.empty())
        attributeList.push_back(attributes); //the only remaining attribute
       
    bool tableFound = false;
    Table t;
    for(int i = 0; i < tables.size(); i++) {
        if(tables.at(i).GetName() == table_name) {
            t = tables.at(i);
            tableFound = true;
        }
    }
    if(!tableFound) {
        cerr << "TABLE NOT FOUND. ERROR LEVEL 9001\n";
    }
    vector<string>* attrs = t.GetAttributes();
    if(attributeList.size() == 1 && attributeList[0] == "*") {
        attributeList = *(new vector<string>(*attrs));
    }
   
    short opType = getParamType(operators);
    if(opType == 0) {
        cerr << "MALFORMED OPERATOR INPUT\n";
    }
    bool isUnary = (opType <= 2);
    if(isUnary) {
        if(opType == 1) { //EXISTS //returns a table of records that exist in the table in the subquery
            operators = operators.substr(6);
            int endOfSelect = operators.find("SELECT ")+7;
            int endOfFrom = operators.find("FROM ")+5;
            int endOfWhere = operators.find("WHERE ")+6;
            string select = operators.substr(endOfSelect,(endOfFrom-5)-endOfSelect);
            string from = operators.substr(endOfFrom,(endOfWhere-6)-endOfFrom);
            string where = operators.substr(endOfWhere,operators.find(")")-endOfWhere);
            Table* inputTable = query(select,from,where);
            Table* outputTable = new Table();
            outputTable->AddAttribute(attributeList[0]); //assume both tables have one attr
            for(int i = 0; i < t.GetSize(); i++) {
                Record r = t.GetRecord(i);
                Record ir = inputTable->GetRecord(i);
                if(r.get(0) == ir.get(0)) { //attrs have the same value
                    Record outR = *(new Record(1));
                    outR.set(0,r.get(0));
                    outputTable->AddRecord(outR);
                }
            }
            return outputTable;
        } else if (opType == 2) { //NOT //returns a table of any records not in the table returned by the condition
            operators = operators.substr(3);
            Table* inputTable = query(origAttrs, table_name, operators);
            if(attributeList.size() != inputTable->GetAttributes()->size()) { //no records can be the same, tables have different sizes
                cerr << "NOT OPERATOR USED ON DIFFERENT SIZED TABLES\n";
                return 0;
            }
            Table* outputTable = new Table();
            for(int i = 0; i < attributeList.size(); i++) {
                outputTable->AddAttribute(attributeList[i]);
            }
            for(int i = 0; i < t.GetSize(); i++) {
                Record r = t.GetRecord(i);
                Record ir = inputTable->GetRecord(i);
                bool sameRecord = true;
                for(int j = 0; j < r.get_size(); j++) {
                    if(r.get(j) != ir.get(j))
                        sameRecord = false;
                }
                if(!sameRecord) {
                    Record outR = *(new Record(attributeList.size()));
                    for(int j = 0; j < attributeList.size(); j++) {
                        outR.set(j,r.get(j));
                    }
                    outputTable->AddRecord(outR);
                }
            }
            return outputTable;
        }
    } else {
        if(opType >= 3 && opType <= 8) {//std op
            //first param is a attr name
            int firstSpc = operators.find(" ");
            string theAttr = operators.substr(0,firstSpc);
            operators = operators.substr(firstSpc+1);
            firstSpc = operators.find(" ");
            short quote = (operators.substr(firstSpc,1) == "'" || operators.substr(firstSpc,1) == "\"")? 1 : 0;
            string theValue = operators.substr(firstSpc+1+quote); //clipping off quotes included
            theValue = theValue.substr(0,theValue.length()-quote);
           
            int attrIndex = -1;
            Table* outputTable = new Table();
            for(int i = 0; i < attributeList.size(); i++) {
                outputTable->AddAttribute(attributeList[i]);
                attrIndex = (attributeList[i] == theAttr)? i : attrIndex;
            }
            if(attrIndex == -1) {
                cerr << "ATTRIBUTE '" << theAttr << "' NOT FOUND\n";
            }
            for(int i = 0; i < t.GetSize(); i++) {
                Record r = t.GetRecord(i);
                bool passes = false;
                if(opType == 3) {
                    if(r.get(attrIndex) == theValue)
                        passes = true;
                } else if(opType == 4) {
                    if(r.get(attrIndex) < theValue)
                        passes = true;
                } else if(opType == 5) {
                    if(r.get(attrIndex) > theValue)
                        passes = true;
                } else if(opType == 6) {
                    if(r.get(attrIndex) != theValue)
                        passes = true;
                } else if(opType == 7) {
                    if(r.get(attrIndex) >= theValue)
                        passes = true;
                } else if(opType == 8) {
                    if(r.get(attrIndex) <= theValue)
                        passes = true;
                }
                if(passes) {
                    Record outR = *(new Record(attributeList.size()));
                    for(int j = 0; j < attributeList.size(); j++) {
                        outR.set(j,r.get(j));
                    }
                    outputTable->AddRecord(outR);
                }
            }
            return outputTable;
        } else if(opType == 9) { //or
            string temp = cleanToken(operators);
            int firstTokenEnd = stoi(temp.substr(0,1));
            operators = temp.substr(1);
           
            string firstToken = operators.substr(0,firstTokenEnd+1); //+1 to catch last paren
            short param1opType = getParamType(firstToken);
            int secondTokenBegin = operators.find(" ",firstTokenEnd+2)+1;
            string secondToken = operators.substr(secondTokenBegin);
            short param2opType = getParamType(secondToken);
            Table* param1 = query(origAttrs,table_name,firstToken);
            Table* param2 = query(origAttrs,table_name,secondToken);
           
            //now do OR on the tables
            Table* outputTable = param1->CrossJoin(*param2);
            return outputTable;
        } else if(opType == 13) { //in
            string temp = cleanToken(operators);
            int firstTokenEnd = stoi(temp.substr(0,1));
            operators = temp.substr(1);
            string firstToken = operators.substr(0,firstTokenEnd);
            int secondTokenBegin = operators.find(" ",firstTokenEnd+1)+1;
            string secondToken = operators.substr(secondTokenBegin);
           
            secondToken.erase(remove(secondToken.begin(),secondToken.end(),' '),secondToken.end()); //remove all whitespace
            vector<string> param2Parts = *(new vector<string>);
            int pos = 0;
            while((pos = secondToken.find(',')) != string::npos) {
                param2Parts.push_back(secondToken.substr(0, pos));
                secondToken.erase(0, pos+1);
            }
            if(!secondToken.empty())
                param2Parts.push_back(secondToken); //the only remaining one
               
            int attrIndex = -1;
            Table* outputTable = new Table();
            for(int i = 0; i < attributeList.size(); i++) {
                outputTable->AddAttribute(attributeList[i]);
                attrIndex = (attributeList[i] == firstToken)? i : attrIndex;
            }
            if(attrIndex == -1) {
                cerr << "ATTRIBUTE '" << firstToken << "' NOT FOUND\n";
            }
            for(int i = 0; i < t.GetSize(); i++) {
                Record r = t.GetRecord(i);
                bool satisfied = false;
               
                for(int j = 0; j < param2Parts.size(); j++) {
                    if(param2Parts[j] == r.get(attrIndex)) {
                        satisfied = true;
                    }
                }
                if(satisfied) {
                    Record outR = *(new Record(attributeList.size()));
                    for(int j = 0; j < attributeList.size(); j++) {
                        outR.set(j,r.get(j));
                    }
                    outputTable->AddRecord(outR);
                }
            }
            return outputTable;
        } else if(opType == 10) { //AND
            string temp = cleanToken(operators);
            int firstTokenEnd = stoi(temp.substr(0,1));
            operators = temp.substr(1);
           
            string firstToken = operators.substr(0,firstTokenEnd+1); //+1 to catch last paren
            short param1opType = getParamType(firstToken);
            int secondTokenBegin = operators.find(" ",firstTokenEnd+2)+1;
            string secondToken = operators.substr(secondTokenBegin);
            short param2opType = getParamType(secondToken);
            Table* param1 = query(origAttrs,table_name,firstToken);
            Table* param2 = query(origAttrs,table_name,secondToken);
           
            //now do OR on the tables
            Table* outputTable;
            for(int j = 0; j < param1->GetSize(); j++) {
                Record p1r = param1->GetRecord(j);
                for(int k = 0; k < param2->GetSize(); k++) {
                    bool sameRecord = true;
                    Record p2r = param2->GetRecord(k);
                    for(int l = 0; l < p1r.get_size(); l++) {
                        if(p1r.get(l) != p2r.get(l)) {
                            sameRecord = false;
                        }
                    }
                    if(sameRecord) {
                        outputTable->AddRecord(p1r);
                        break;
                    }
                }
            }
            return outputTable;
        } else if(opType == 11) { //ANY
            string temp = cleanToken(operators);
            int firstTokenEnd = stoi(temp.substr(0,1));
            operators = temp.substr(1);
           
            string firstToken = operators.substr(0,firstTokenEnd);
            int secondTokenBegin = operators.find(" ",firstTokenEnd+1)+1;
            string secondToken = operators.substr(secondTokenBegin);
           
            int endOfSelect = operators.find("SELECT ")+7;
            int endOfFrom = operators.find("FROM ")+5;
            int endOfWhere = operators.find("WHERE ")+6;
            string select = operators.substr(endOfSelect,(endOfFrom-5)-endOfSelect);
            string from = operators.substr(endOfFrom,(endOfWhere-6)-endOfFrom);
            string where = operators.substr(endOfWhere,operators.find(")")-endOfWhere);
            Table* compareTable = query(select,from,where);
           
            int firstSpc = firstToken.find(" ");
            string theAttr = firstToken.substr(0,firstSpc);
            string op = firstToken.substr(firstSpc+1);
            firstSpc = op.find(" ");
            op = op.substr(0, firstSpc);
            short popType;
            if(op.compare(0,1,"=")) {
                popType = 3;
            } else if(op.compare(0,1,"<")) {
                popType = 4;
            } else if(op.compare(0,1,">")) {
                popType = 5;
            } else if(op.compare(0,2,"<>")) {
                popType = 6;
            } else if(op.compare(0,2,">=")) {
                popType = 7;
            } else if(op.compare(0,2,"<=")) {
                popType = 8;
            } else {
                cerr << "INVALID OP";
            }
           
            int attrIndex = -1;
            Table* outputTable = new Table();
            for(int i = 0; i < attributeList.size(); i++) {
                outputTable->AddAttribute(attributeList[i]);
                attrIndex = (attributeList[i] == theAttr)? i : attrIndex;
            }
            if(attrIndex == -1) {
                cerr << "ATTRIBUTE '" << theAttr << "' NOT FOUND\n";
            }
            for(int i = 0; i < t.GetSize(); i++) {
                Record r = t.GetRecord(i);
                if(popType == 3) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) == compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 4) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) < compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 5) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) > compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 6) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) != compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 7) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) >= compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 8) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) <= compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                }
            }
            return outputTable;
        } else if(opType == 12) { //ALL
            string temp = cleanToken(operators);
            int firstTokenEnd = stoi(temp.substr(0,1));
            operators = temp.substr(1);
           
            string firstToken = operators.substr(0,firstTokenEnd);
            int secondTokenBegin = operators.find(" ",firstTokenEnd+1)+1;
            string secondToken = operators.substr(secondTokenBegin);
           
            int endOfSelect = operators.find("SELECT ")+7;
            int endOfFrom = operators.find("FROM ")+5;
            int endOfWhere = operators.find("WHERE ")+6;
            string select = operators.substr(endOfSelect,(endOfFrom-5)-endOfSelect);
            string from = operators.substr(endOfFrom,(endOfWhere-6)-endOfFrom);
            string where = operators.substr(endOfWhere,operators.find(")")-endOfWhere);
            Table* compareTable = query(select,from,where);
           
            int firstSpc = firstToken.find(" ");
            string theAttr = firstToken.substr(0,firstSpc);
            string op = firstToken.substr(firstSpc+1);
            firstSpc = op.find(" ");
            op = op.substr(0, firstSpc);
            short popType;
            if(op.compare(0,1,"=")) {
                popType = 3;
            } else if(op.compare(0,1,"<")) {
                popType = 4;
            } else if(op.compare(0,1,">")) {
                popType = 5;
            } else if(op.compare(0,2,"<>")) {
                popType = 6;
            } else if(op.compare(0,2,">=")) {
                popType = 7;
            } else if(op.compare(0,2,"<=")) {
                popType = 8;
            } else {
                cerr << "INVALID OP";
            }
           
            int attrIndex = -1;
            Table* outputTable = new Table();
            for(int i = 0; i < attributeList.size(); i++) {
                outputTable->AddAttribute(attributeList[i]);
                attrIndex = (attributeList[i] == theAttr)? i : attrIndex;
            }
            if(attrIndex == -1) {
                cerr << "ATTRIBUTE '" << theAttr << "' NOT FOUND\n";
            }
            for(int i = 0; i < t.GetSize(); i++) {
                Record r = t.GetRecord(i);
                if(popType == 3) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) == compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 4) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) < compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 5) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) > compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 6) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) != compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 7) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) >= compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                } else if(popType == 8) {
                    for(int j = 0; j < compareTable->GetSize(); j++) {
                        if(r.get(attrIndex) <= compareTable->GetRecord(j).get(attrIndex))
                            outputTable->AddRecord(r);
                    }
                }
            }
            return outputTable;
        }
       
    }
   
    return 0;
}

//Delete function - takes table: delete the table from the target table
void Database::obliterate(string attributes, string table_name, string operators){
    
	try {
		Table* toDelete = query(attributes, table_name, operators);
		Table* base;
		for(int i = 0; i < tables.size(); i++) {
			Table t = tables.at(i);
			if(t.GetName() == table_name) {
				base = &t;
			}
		}
		//delete toDelete from base
		vector <string> deleteAttr = *toDelete->GetAttributes();
		for(int i = 0; i < deleteAttr.size(); i++){
			base->DeleteAttribute(deleteAttr[i]);
		}

	} catch(...) {}

}
 
//Update function - takes table name, where, set clause (reference attr): modify target table *support math op
void Database::update(string table_name, string where, string set_clause){
   
}
