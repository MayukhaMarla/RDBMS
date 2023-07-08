#include<iostream>
#include<string>
#include<tuple>
#include<vector>
#include<list>
#include "rdb.h"

using namespace std;
vector<Relation *> MasterTable;

vector<string> namesofRelations;

void typechoices(){
    cout<<"1. ==\n";
    cout<<"2. !=\n";
    cout<<"3. <\n";
    cout<<"4. <=\n";
    cout<<"5. >\n";
    cout<<"6. >=\n";
}


void subc1(){
    cout<<"Choose the tables you want to perform union on:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    int n,m;
    cin>>n>>m;
    Relation *a = MasterTable[n-1];
    Relation *b = MasterTable[m-1];
    Relation *c = a->Union(a, b);
    cout<<"Do you want to save the resultant table in the list of relations??\n";
    cout<<"1. Yes\n";
    cout<<"2. No\n";
    int c12;
    cin>>c12;
    if(c12 == 1){
        cout<<"Enter the name of the table:\n";
        string s;
        cin>>s;
        namesofRelations.push_back(s);
        MasterTable.push_back(c);
    }
    else if(c12 == 2){
        cout<<"The resultant table is:\n";
        c->printingRelation();
    }
    else{
        cout<<"Invalid choice\n";
    }
}

void subc2(){
    cout<<"Choose the tables you want to perform difference on:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    int n,m;
    cin>>n>>m;
    Relation *a = MasterTable[n-1];
    Relation *b = MasterTable[m-1];
    Relation *c = a->Difference(a, b);
    cout<<"Do you want to save the resultant table in the list of relations??\n";
    cout<<"1. Yes\n";
    cout<<"2. No\n";
    int c23;
    cin>>c23;
    if(c23 == 1){
        cout<<"Enter the name of the table:\n";
        string s;
        cin>>s;
        namesofRelations.push_back(s);
        MasterTable.push_back(c);
    }
    else if(c23 == 2){
        cout<<"The resultant table is:\n";
        c->printingRelation();
    }
    else{
        cout<<"Invalid choice\n";
    }
}

void subc3(){
    cout<<"Choose the tables you want to perform cartesian product on:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    int n,m;
    cin>>n>>m;
    Relation *a = MasterTable[n-1];
    Relation *b = MasterTable[m-1];
    Relation *c = a->cartesianProduct(a, b);
    cout<<"Do you want to save the resultant table in the list of relations??\n";
    cout<<"1. Yes\n";
    cout<<"2. No\n";
    int c1;
    cin>>c1;
    if(c1 == 1){
        cout<<"Enter the name of the table:\n";
        string s;
        cin>>s;
        namesofRelations.push_back(s);
        MasterTable.push_back(c);
    }
    else if(c1 == 2){
        cout<<"The resultant table is:\n";
        c->printingRelation();
    }
    else{
        cout<<"Invalid choice\n";
    }
}

void subc4(){
    int n;
    int m;
    cout<<"Choose the table you want to project:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    cin>>m;
    cout<<"Number of attributes you want to project:\n";
    cin>>n;
    cout<<"Enter the attributes you want to project:\n";
    list<string> proj;
    for(int i = 0; i< n;i++){
        string s;
        cin>>s;
        proj.push_back(s);
    }
    Relation *a = MasterTable[m-1];
    Relation *c = new Relation(proj.size(), a->nrecs);
    c = a->Projection(a, proj);
    cout<<"Do you want to save the resultant table in the list of relations??\n";
    cout<<"1. Yes\n";
    cout<<"2. No\n";
    int c1;
    cin>>c1;
    if(c1 == 1){
        cout<<"Enter the name of the table:\n";
        string s;
        cin>>s;
        namesofRelations.push_back(s);
        MasterTable.push_back(c);
    }
    else if(c1 == 2){
        cout<<"The resultant table is:\n";
        c->printingRelation();
    }
    else{
        cout<<"Invalid choice\n";
    }

}

void subc5(){
    cout<<"Choose the table you want to perform selection on:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    int n;
    cin>>n;
    Relation *a = MasterTable[n-1];
    DNFformula f;

    // f.ops = {{make_tuple("col", '0', new stringAttribute("iit")), make_tuple("mar", '0', new floatAttribute(30))}, {make_tuple("age", '0', new integerAttribute(20))}};
    // a.NaturalJoin(&a, &b);

    int total;
    int ineach;
    string s;
    char type;

    list<tuple<string, char, Attr*>> listofconditions;
    cout<<"Total number of terms:\n";
    cin>>total;
    for(int i = 0; i< total; i++){
        cout<<"Number of conditions in "<<i+1<<"th condition:\n";
        cin>>ineach;
        for(int j = 0; j< ineach; j++){
            cout<<"Type the string name:\n";
            cin>>s;
            cout<<"Which condition do you want?\n";
            typechoices();
            cin>>type;
            cout<<"Which type of attribute do you want it to be?\n";
            cout<<"1. Integer\n";
            cout<<"2. Float\n";
            cout<<"3. String\n";
            int data;
            cin>>data;
            if(data == 1){
                int temp;
                cout<<"Enter the value of the integer\n";
                cin>>temp;
                tuple<string, char, integerAttribute*> temptuple = make_tuple(s, type, new integerAttribute(temp));
                listofconditions.push_back(temptuple);
                
            }
            else if(data == 2){
                float temp2;
                cout<<"Enter the value of the float\n";
                cin>>temp2;
                tuple<string, char, floatAttribute*> temptuple = make_tuple(s, type, new floatAttribute(temp2));
                listofconditions.push_back(temptuple);
            }
            else if(data == 3){
                string temp3;
                cout<<"Enter the value of the string\n";
                cin>>temp3;
                tuple<string, char, stringAttribute*> temptuple = make_tuple(s, type, new stringAttribute(temp3));
                listofconditions.push_back(temptuple);
            }
        }
        f.ops.push_back(listofconditions);
        listofconditions.clear();
        
    }

    Relation* c = a->Selection(a,f);
    c->printingRelation();
    cout<<"Do you want to save the resultant table in the list of relations??\n";
    cout<<"1. Yes\n";
    cout<<"2. No\n";
    int c1;
    cin>>c1;
    if(c1 == 1){
        cout<<"Enter the name of the table:\n";
        string s;
        cin>>s;
        namesofRelations.push_back(s);
        MasterTable.push_back(c);
    }
    else if(c1 == 2){
        cout<<"The resultant table is:\n";
        c->printingRelation();
    }
    else{
        cout<<"Invalid choice\n";
    }
}

void subc6(){
    cout<<"Choose the table you want to perform union on:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    int n;
    cin>>n;
    Relation *a = MasterTable[n-1];
    cout<<"Choose the name of the attribute you want to rename:\n";
    for(int i = 0; i< a->nattr; i++){
        cout<<i+1<<"."<<a->attrnames[i]<<endl;
    }
    int m;
    cin>>m;
    string s1 = a->attrnames[m-1];
    // string s1;
    // cin>>s1;
    string s2;
    cout<<"What do you want to replace it with?\n";
    cin>>s2;
    a->Difference(a, s1, s2);
    // a->printingRelation();

}

void subc7(){
    cout<<"Choose the tables you want to perform union on:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    int n,m;
    cin>>n>>m;
    Relation *a = MasterTable[n-1];
    // a->printingRelation();
    Relation *b = MasterTable[m-1];
    // b->printingRelation();
    Relation *c = a->NaturalJoin(a,b);
    c->printingRelation();
    cout<<"Do you want to save the resultant table in the list of relations??\n";
    cout<<"1. Yes\n";
    cout<<"2. No\n";
    int c1;
    cin>>c1;
    if(c1 == 1){
        cout<<"Enter the name of the table:\n";
        string s;
        cin>>s;
        namesofRelations.push_back(s);
        MasterTable.push_back(c);
    }
    else if(c1 == 2){
        cout<<"The resultant table is:\n";
        c->printingRelation();
    }
    else{
        cout<<"Invalid choice\n";
    }
}


void choice1(){
    cout<<"Name of the table:\n";
    string s;
    cin>>s;
    namesofRelations.push_back(s);
    int c1;
    cout<<"Enter the no of columns for the table : "<<s<<endl;
    cin>>c1;
    // Relation a(c1, r1);
    Relation * a = new Relation(c1, 0);
    a->execute();
    // return a;
    MasterTable.push_back(a);
    

}

void choice2(){
    cout<<"Select the table to which you want to add a record:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    int n;
    cin>>n;
    Relation *a = MasterTable[n-1];
    Relation *b = new Relation(a->nattr, 1);
    for(int i =0; i<b->nattr; i++){
        b->attrnames.push_back(a->attrnames[i]);
        b->attrinds.push_back(a->attrinds[i]);
        b->dataType.push_back(a->dataType[i]);
    }
    b->enterDetails();
    Relation *c = a->Union(a, b);
    MasterTable[n-1] = c;

}

void choice3(){
    cout<<"Select the table to which you want to add a record:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    int n;
    cin>>n;
    Relation *a = MasterTable[n-1];
    Relation *b = new Relation(a->nattr, 1);
    // cout<<MasterTable[0]->nattr<<endl;
    // a->printingRelation();
    for(int i =0; i<b->nattr; i++){
        b->attrnames.push_back(a->attrnames[i]);
        b->attrinds.push_back(a->attrinds[i]);
        b->dataType.push_back(a->dataType[i]);
    }
    cout<<"Enter the record you want to delete:\n";
    b->enterDetails();
    MasterTable[n-1] = a->Difference(a, b);
}

void choice4(){
    int n;
    cout<<"Select the table to which you want to display:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    cin>>n;
    MasterTable[n-1]->printingRelation();
}

// void subc7(){

// }

void choice5(){
    cout<<"Choose the operation you want to perform:\n";
    cout<<"1. Union\n";
    cout<<"2. Difference\n";
    cout<<"3. Cartesian Product\n";
    cout<<"4. Projection\n";
    cout<<"5. Selection\n";
    cout<<"6. Rename\n";
    cout<<"7. Natural Join\n";
    int n;
    cin>>n;
    if(n == 1) subc1();
    else if(n == 2) subc2();
    else if(n == 3) subc3();
    else if(n == 4) subc4();
    else if(n == 5) subc5();
    else if(n == 6) subc6();
    else if(n == 7) subc7();
}

void choice6(){
    cout<<"Select the table you want to delete:\n";
    for(int i = 0; i< namesofRelations.size(); i++){
        cout<<i+1<<". "<<namesofRelations[i]<<endl;
    }
    int n;
    cin>>n;
    namesofRelations.erase(namesofRelations.begin() + n-1);
    MasterTable.erase(MasterTable.begin() + n-1);
}


int main(){


    int r1,c1;
    int choice;
    
    while(1){
        cout<<"Enter the operation you want to perform:\n";
        cout<<"1. Creating an empty table\n";
        cout<<"2. Inserting a record\n";
        cout<<"3. Deleting a record\n";
        cout<<"4. Printing a table\n";
        cout<<"5. Doing operations on tables\n";
        cout<<"6. Deleting a table\n";
        cout<<"7. Exit\n";
        cin>>choice;
        if(choice == 1)choice1();
        else if(choice == 2) choice2();
        else if(choice == 3) choice3();
        else if(choice == 4) choice4();
        else if(choice == 5) choice5();
        else if(choice == 6) choice6();
        else if(choice == 7) break;
        else cout<<"Invalid choice\n";
        cout<<endl;
        cout<<"Tables status atp:\n\n";
        for(int i = 0; i< MasterTable.size(); i++){
            cout<<namesofRelations[i]<<":\n";
            MasterTable[i]->printingRelation();
            cout<<endl;
        }
    }

    // choice;
    

    return 0;
}