#include <vector>
#include <iostream>
using namespace std;

template <typename T>
void insertVector(vector<T>& v, int n){
    for(int i=0; i<n;i++){
        T x;
        cin >> x;
        v.push_back(x);
    }
}

template <typename T>
void printVector(vector<T>& v){
    /*
    for(typename vector<T>::iterator i=v.begin(); i!=v.end();i++){
        cout << *i << endl;
    }
    */
    for(const auto& i:v){
        cout << i << endl;
    }
}

void add10(vector<int>& v){
    for(int& x : v){
        x+=10;
    }
}

template <typename T>
void addk(vector<T>& v, const T& k){
    for(auto& x : v){
        x+=k;
    }
}

void appendChar(vector<string>& v, const char c){
    // pas de to_string car c'est pour un int
    // si to_string ca va transformer le char en int avant de le mettre en string
    addk(v,string(1,c));
}

int maint(){
    vector<int> v1;
    vector<float> v2;
    insertVector(v1, 2);
    insertVector(v2,2);

    vector<string> myStringVector;
    char car{'a'};
    appendChar(myStringVector,car);
    return 0;
}