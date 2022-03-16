#include <assert>
#include <vector>
#include <iostream>
using namespace std;

class

class Option<string>{
public:
    Option(): valid{false} {}
    Option(const T& x): valid{true}, value(x) {}

    inline bool valid(){
        return valid;
    }

    inline const T& value() const {
        // assert ==> si valid alors ca retournera valued
        assert(valid);
        return value;
    }

    inline operator bool() const { return valid(); }
    inline const T& operator*() const { return value; }

    void do_if(function<void(const T&)> f) const {
    if(valid){ f(value); }


private:
    bool valid;
    T value;
}

template <typename T>
Option<T> some(const T& x) {
    return Option<T>(x);
}

Option<string> read_string(){
    if(cin.eof()){
        //return Option<string>();
        return none;
    }
    else{
        string s;
        cin >> s;
        //return Option<string>(s);        
        return some(s);
    }
}



int main(){
    x=read_string();
    while(x.valid()){
        cout << x.value() << endl;
        x=read_string();
    }



    return 0;
}