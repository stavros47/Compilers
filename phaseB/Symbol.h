#include <iostream>
#include <string>
#include <list>

using namespace std;

class Symbol {
    
    private:
        string name;
        string type;

        // union {
        //     int intValue;
        //     string stringValue;
        //     double doubleValue;
        // }values;
        
        list<Symbol> functionArguments;
        int scope;
        int lineNumber;

    public:
        Symbol();
       
        void setName(string name);
        string getName();

        void setType(string type);
        string getType();

        void setScope(int scope);
        int getScope();

        void setLineNumber(int lineNumber);
        int getLineNumber();

        void insertFunctionArgument(Symbol newArgument);
    
};


