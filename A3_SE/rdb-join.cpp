#include<iostream>
#include<string>
#include<tuple>
#include<vector>
#include<list>
#include "rdb.h"

using namespace std;

Relation* Relation::NaturalJoin(Relation * R1, Relation *R2){
    list<string> common;
    list<string> total;
    vector<int> attrnum1;
    vector<int> attrnum2;
    for(int i=0; i< R1->nattr; i++){
        total.push_back(R1->attrnames[i]);
        for(int j = 0; j< R2->nattr; j++){
            if(R1->attrnames[i] == R2->attrnames[j]){

                common.push_back(R1->attrnames[i]);
                
                attrnum2.push_back(j);
                attrnum1.push_back(i);
            }
            
        }
    }

    for(int i = 0; i < R2->nattr; i++){
        string name = R2->attrnames[i];
        int flag = 0;
        for(auto itr = common.begin(); itr != common.end(); itr++){
            if(*itr == name){
                flag = 1;
                break;
            }
        }
        if(flag != 1) total.push_back(name);
            
    }

    
    return NaturalJoinImple(R1, R2, common, attrnum1, attrnum2, total);
}

Relation* Relation::NaturalJoinImple(Relation * R1, Relation *R2, list<string> joinattr, vector<int> attrnum1, vector<int> attrnum2, list<string> unionattr){
    // R1->printingRelation();
    // R2->printingRelation();
    // cout<<"\n\n\n\n\nHEREEEEEEEEE\n\n";
    for(auto itr = joinattr.begin(); itr != joinattr.end(); itr++){
        for(int j = 0; j< R2->nattr; j++){
            if(R2->attrnames[j] == *itr){
                R2 = R2->Difference(R2, R2->attrnames[j], R2->attrnames[j]+"_" );    
            }
        }
    }
    Relation *R  = R1->cartesianProduct(R1, R2);
    list<tuple<string, char, Attr*>> l1;
    DNFformula g;
    for(int i=0 ; i< R->nrecs; i++){
        for(int j =0; j<attrnum1.size(); j++){

            tuple<string, char, Attr*> temptuple = make_tuple((R->attrnames[attrnum1[j]]), '0', R->recs[i]->attrptr[R1->nattr+ attrnum2[j]]);
            tuple<string, char, Attr*> temptuple2 = make_tuple((R->attrnames[attrnum1[j]] + "_"), '0', R->recs[i]->attrptr[R1->nattr+ attrnum2[j]]);
            // cout<<"here\n\n\n";
            Attr * p1 = get<2>(temptuple);

            Attr * p2 = get<2>(temptuple2);
            l1.push_back(temptuple);
            l1.push_back(temptuple2);
            
            
        }
        g.ops.push_back(l1);

        
        l1.clear();
    }
    // for(auto it = g.ops.begin(); it != g.ops.end(); it++){
    //     for(auto itr = it->begin(); itr != it->end(); itr++){
    //         cout<<get<0>(*itr)<<" "<<get<1>(*itr)<<" "<<get<2>(*itr)->col<<"\n";
    //     }
    //     cout<<"\n";
    // }

    // return R;

    // tuple<string, char, Attr*> temptuple = make_tuple("DeptName", '0', R->recs[i]->attrptr[R1->nattr+ attrnum2[j]]);
    // tuple<string, char, Attr*> temptuple2 = make_tuple("DeptName"+ "_", '0', R->recs[i]->attrptr[R1->nattr+ attrnum2[j]]);
    Relation *R4 = R->Selection(R, g);
    // R4->printingRelation();
    // cout<<"\n\nhee";
    
    Relation *R3 = R4->Projection(R, unionattr);
    // R3->printingRelation();
    

    return R3;

    
}