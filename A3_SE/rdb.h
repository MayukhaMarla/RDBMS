#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <iomanip>
// #include <typeinfo>

using namespace std;

class Attr{
    public: virtual bool operator== (const Attr & right) = 0;
    public: virtual bool operator!= (const Attr & right) = 0;
    public: virtual bool operator>= (const Attr & right) = 0;
    public: virtual bool operator<= (const Attr & right) = 0;
    public: virtual bool operator> (const Attr & right) = 0;
    public: virtual bool operator< (const Attr & right) = 0;

    friend class Record;
    friend class Relation;
};

class integerAttribute: public Attr{
    public:
        int columnData;
    public:
        integerAttribute(int a): columnData(a){}
        ~integerAttribute(){}

        bool operator==(const Attr &right);
        bool operator!=(const Attr &right);
        bool operator>=(const Attr &right);
        bool operator<(const Attr &right);
        bool operator<=(const Attr &right);
        bool operator>(const Attr &right);
         

    
    friend class Record;  
    friend class Relation;
};

class floatAttribute : public Attr{
    public:
        float columnData;
    public:
        floatAttribute(float a): columnData(a){}
        ~floatAttribute(){}

        bool operator==(const Attr &right);
        bool operator!=(const Attr &right);
        bool operator>=(const Attr &right);
        bool operator<(const Attr &right);
        bool operator<=(const Attr &right);
        bool operator>(const Attr &right);
         

    
    friend class Record;  
    friend class Relation;
};
class stringAttribute : public Attr{
    public:
        string columnData;
    public:
        stringAttribute(string a): columnData(a){}
        ~stringAttribute(){}

        bool operator==(const Attr &right);
        bool operator!=(const Attr &right);
        bool operator>=(const Attr &right);
        bool operator<(const Attr &right);
        bool operator<=(const Attr &right);
        bool operator>(const Attr &right);
         

    
    friend class Record;  
    friend class Relation;
};

typedef struct DNFformula
{
    list<list<tuple<string, char, Attr*>>> ops;
}DNFformula;

class Record{
    private:
        vector<Attr*> attrptr;
    public:
        Record(vector<Attr*> v): attrptr(v){}
        ~Record(){}

        void print();

        
        friend class Relation;

        friend void subc1();
        friend void subc2();
        friend void subc3();
        friend void subc4();
        friend void subc5();
        friend void subc6();
        friend void subc7();

        friend void choice1();
        friend void choice2();
        friend void choice3();
        friend void choice4();
        friend void choice5();
        friend void choice6();
};

class Relation{
    private:
        int nattr, nrecs;
        vector<string> attrnames;
        vector<int> attrinds;
        vector<int> dataType;
        vector<Record *> recs;

    public:
        Relation(int a, int b): nattr(a), nrecs(b){
            
        }

        Relation(Relation &R): nattr(R.nattr), nrecs(R.nrecs){
            for(int i=0; i< R.attrnames.size(); i++){
                attrnames.push_back(R.attrnames[i]);
                attrinds.push_back(R.attrinds[i]);
                dataType.push_back(R.dataType[i]);
            }
            for(int i = 0; i < nrecs; i++){
                recs.push_back(new Record(R.recs[i]->attrptr));
            }
        }

        ~Relation(){}
        void execute();
        void enterDetails();
        int enterDataType(string s);
        void printingRelation();
        void addRecord(Record*);
        bool compare(Record*, Record*);

       

        Relation * Union(Relation *R1, Relation *R2);
        Relation * Difference(Relation * R1, Relation * R2);
        Relation * cartesianProduct(Relation *R1, Relation *R2);
        Relation * Projection(Relation * R1, list<string> projectattrs);
        Relation * Difference(Relation * R1, string s1, string s2);
        bool selectionCheck(Record *r, list<tuple<string, char, Attr*>> L, Relation *R1);
        Relation * Selection(Relation * R1, DNFformula f);
        Relation* NaturalJoin(Relation * R1, Relation *R2);
        Relation* NaturalJoinImple(Relation * R1, Relation *R2, list<string> joinattr, vector<int> attrnum1, vector<int> attrnum2, list<string> unionattr);


        friend void subc1();
        friend void subc2();
        friend void subc3();
        friend void subc4();
        friend void subc5();
        friend void subc6();
        friend void subc7();

        friend void choice1();
        friend void choice2();
        friend void choice3();
        friend void choice4();
        friend void choice5();
        friend void choice6();

};

