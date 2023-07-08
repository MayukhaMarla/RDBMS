#include "rdb.h"
#include <iostream>
#include <vector>
#include <list>
#include <tuple>

using namespace std;

void Record::print(){
    for(int i = 0; i < attrptr.size(); i++){
        Attr* pointer = attrptr[i];
        cout<<setw(10);
        if (typeid(*pointer) == typeid(integerAttribute))
            cout << static_cast<integerAttribute *>(pointer)->columnData << " ";
        else if (typeid(*pointer) == typeid(stringAttribute))
            cout << static_cast<stringAttribute *>(pointer)->columnData << " ";
        else{
            cout << static_cast<floatAttribute *>(pointer)->columnData << " ";
        }
    }
}

 void Relation::execute(){
    cout << "Enter the name of columns  " << endl;
    for(int i = 0; i < nattr; i++){
        cout<<"Enter heading for column " << i+1;
        string heading;
        cin >> heading;
        int choice = enterDataType(heading);
        attrnames.push_back(heading);
        dataType.push_back(choice);
    }

    for(int i = 0; i < nattr; i++){
        attrinds.push_back(i);
    }
    enterDetails();
}

void Relation::enterDetails(){
    for(int i = 0; i < nrecs; i++){
        vector<Attr*> v;
        for(int j = 0; j < nattr; j++){
            cout << "Enter " << attrnames[j] <<" of row " << i+1<<":  ";
            if(dataType[j] == 1){
                int num;
                cin >> num;
                v.push_back(new integerAttribute(num));                        
            }  
            else if(dataType[j] == 2){
                float flt;
                cin >> flt;
                v.push_back(new floatAttribute(flt));                        
            } 
            else{
                string somestring;
                cin >> somestring;
                v.push_back(new stringAttribute(somestring));                        
            } 
        }
        recs.push_back(new Record(v));
    }
}

int Relation::enterDataType(string s){
    cout << "Enter data type for " << s <<":"<< endl;
    cout << "1. Integer\n2. Float\n3. String\n" << endl;
    int a;
    cin >> a;
    return a;
}

void Relation::printingRelation(){
    for(int i = 0; i < nattr; i++){
        cout<<setw(10);
        cout<<attrnames[i];
        //cout << endl;
    }
    //  cout<<attrnames
    cout << endl;
    for(int i = 0; i < nrecs; i++){
        //cout<<setw(10);
        recs[i]->print();
        cout << endl;
    }
}

void Relation::addRecord(Record *R){
    nrecs++;
    recs.push_back(R);
}

bool Relation::compare(Record * r1, Record * r2){
    if(r1->attrptr.size() != r2->attrptr.size()) return 0;
    else{
        for(int i = 0;i < r1->attrptr.size(); i++){

            Attr *p1 = r1->attrptr[i];
            Attr *p2 = r2->attrptr[i];
            
            if(typeid(*p1) == typeid(*p2)){
                if(typeid(*p1) == typeid(integerAttribute)){
                    int a = static_cast<integerAttribute*>(p1)->columnData;
                    int b = static_cast<integerAttribute*>(p2)->columnData;

                    if(a != b){
                        return 0;
                    }
                }
                else if(typeid(*p1) == typeid(stringAttribute)){
                    string a = static_cast<stringAttribute*>(p1)->columnData;
                    string b = static_cast<stringAttribute*>(p2)->columnData;
                    if(a != b){
                        return 0;
                    }
                }
                else{
                    float a = static_cast<floatAttribute*>(p1)->columnData;
                    float b = static_cast<floatAttribute*>(p2)->columnData;
                    if(a != b){
                        return 0;
                    }
                }
            }else{
                return 0;
            }
        }
        return 1;
    }
}

Relation* Relation::Union(Relation *R1, Relation *R2){
    Relation &temp = *R1;
    // Relation R(temp);
    Relation *R = new Relation(temp);
    int a1 = R1->attrnames.size();
    int a2 = R2->attrnames.size(), flag = 0;

    if(a1 == a2){
        for(int i = 0; i < a1; i++){
            if(R1->attrnames[i] != R2->attrnames[i]){
                flag = 1;
            }
        }
        if(!flag){
            for(int i = 0; i < R2->nrecs; i++){
                int flag1 = 0;
                for(int j = 0; j < R1->nrecs; j++){
                    
                    if(compare(R2->recs[i], R1->recs[j])){
                        flag1 = 1;
                        break;
                    }
                }

                if(!flag1){
                    R->addRecord(R2->recs[i]);
                }
            } 
        }
    }
    return R;
}

Relation * Relation::Difference(Relation * R1, Relation * R2){

    Relation *R = new Relation(R1->nattr, 0);
    for(int i=0; i< R1->attrnames.size(); i++){
        R->attrnames.push_back(R1->attrnames[i]);
        R->attrinds.push_back(R1->attrinds[i]);
        R->dataType.push_back(R1->dataType[i]);
    }            
    for(int i = 0; i < R1->nrecs; i++){
        int flag1 = 0;
        for(int j = 0; j < R2->nrecs; j++){
                    
            if(compare(R1->recs[i], R2->recs[j])){
                flag1 = 1;
                break;
            }
        }

        if(!flag1){
            R->addRecord(R1->recs[i]);
        }
    }
    return R;
}

Relation * Relation::cartesianProduct(Relation *R1, Relation *R2){
    Relation * R = new Relation(R1->nattr+ R2->nattr, 0);
    for(int i=0; i< R1->attrnames.size(); i++){
        R->attrnames.push_back(R1->attrnames[i]);
        R->attrinds.push_back(R1->attrinds[i]);
        R->dataType.push_back(R1->dataType[i]);
    } 
    for(int i=0; i< R2->attrnames.size(); i++){
        R->attrnames.push_back(R2->attrnames[i]);
        R->attrinds.push_back((R1->attrnames.size()) + R2->attrinds[i]);
        R->dataType.push_back(R2->dataType[i]);
    } 
    for(int i=0; i< R1->nrecs; i++){
        vector <Attr*> vec;
        for(int j = 0; j< R2->nrecs; j++){
            for(int k = 0;k < R1->recs[i]->attrptr.size(); k++){
                vec.push_back(R1->recs[i]->attrptr[k]);
            }
            for(int l = 0;l < R2->recs[j]->attrptr.size(); l++){
                vec.push_back(R2->recs[j]->attrptr[l]);
            }
            R->addRecord(new Record(vec));
            vec.clear();
        }
    }
    return R;
}

Relation * Relation::Projection(Relation * R1, list<string> projectattrs){
    Relation * R = new Relation(projectattrs.size(), 0);
    vector<int> reference;
    for(auto str: projectattrs){
        for(int j = 0; j< R1->nattr ; j++){
            if(str == R1->attrnames[j]) {
                reference.push_back(j);
            }
        }
    }
    for(int i=0; i< reference.size(); i++){
        R->attrnames.push_back(R1->attrnames[reference[i]]);
        R->attrinds.push_back(i);
        R->dataType.push_back(R1->dataType[reference[i]]);
    }
    
    for(int i=0; i< R1->nrecs ; i++){
        vector<Attr*> vec;
        for(int j=0; j< reference.size(); j++){
            vec.push_back(R1->recs[i]->attrptr[reference[j]]);
        }
        R->addRecord(new Record(vec));
    }
    return R;
}

Relation* Relation::Difference(Relation * R1, string s1, string s2){
    for(int i=0 ;i< R1->nattr; i++){
        if(s1 == R1->attrnames[i]){
            R1->attrnames[i] = s2;
            break;
        }
    }
    return R1;
}

bool Relation::selectionCheck(Record *r, list<tuple<string, char, Attr*>> L, Relation *R1){
    for(auto itr2 = (L).begin(); itr2 != (L).end(); itr2++){  
        tuple<string, char, Attr*> temptuple = *itr2;        
        string s = get<0>(temptuple);
        char c = get<1>(temptuple);
        Attr *p1 = get<2>(temptuple);
        for(int l = 0; l< R1->nattr; l++){
            if(R1->attrnames[l] == s){  
                Attr *p2 = r->attrptr[l];                        
                  
                if(typeid(*p2) == typeid(integerAttribute)){
                    
                    int b = static_cast<integerAttribute*>(p2)->columnData;
                    int a = static_cast<integerAttribute*>(p1)->columnData;
                    
                    if(c == '1'){
                        if(a != b) return 0;
                    }else if(c == '2'){
                        if(b == a) return 0;
                    }else if(c == '3'){
                        if(b >= a) return 0;
                    }else if(c == '4'){
                        if(b > a) return 0;
                    }else if(c == '5'){
                        if(b <= a) return 0;
                    }else{
                        if(b < a) return 0;
                    }
                }
                else if(typeid(*p2) == typeid(stringAttribute)){
                    
                    string b = static_cast<stringAttribute*>(p2)->columnData;
                    string a = static_cast<stringAttribute*>(p1)->columnData;
                    
                    if(c == '1'){
                        if(a != b) return 0;
                    }else if(c == '2'){
                        if(b == a) return 0;
                    }else if(c == '3'){
                        if(b >= a) return 0;
                    }else if(c == '4'){
                        if(b > a) return 0;
                    }else if(c == '5'){
                        if(b <= a) return 0;
                    }else{
                        if(b < a) return 0;
                    }
                }
                else{
                    
                    float b = static_cast<floatAttribute*>(p2)->columnData;
                    float a = static_cast<floatAttribute*>(p1)->columnData;
                    
                    if(c == '1'){
                        if(a != b) return 0;
                    }else if(c == '2'){
                        if(b == a) return 0;
                    }else if(c == '3'){
                        if(b >= a) return 0;
                    }else if(c == '4'){
                        if(b > a) return 0;
                    }else if(c == '5'){
                        if(b <= a) return 0;
                    }else{
                        if(b < a) return 0;
                    }
                }                        
                
            }              
        }         
 
         
    }
    return 1;
}

Relation * Relation::Selection(Relation * R1, DNFformula &f){
    int flag[R1->nrecs];
    for(int i = 0; i < R1->nrecs; i++){
        flag[i] = 0;
    }

    Relation *R = new Relation(R1->nattr,0);
    for(int i=0; i< R1->attrnames.size(); i++){
        R->attrnames.push_back(R1->attrnames[i]);
        R->attrinds.push_back(R1->attrinds[i]);
        R->dataType.push_back(R1->dataType[i]);
    }
    for(int i = 0; i< R1->nrecs; i++){
        for(auto itr = (f.ops).begin(); itr!= (f.ops).end(); itr++){
            
            list<tuple<string, char, Attr*>> templist = *itr;
            
            if(selectionCheck(R1->recs[i], templist, R1) && flag[i] == 0){
                R->addRecord(new Record(R1->recs[i]->attrptr));
                flag[i] = 1;
            }
            
        }
    }
    R->printingRelation();
    cout<<"gorink\n\n";
    return R; 
}




