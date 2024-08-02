#include <string>
#include <iostream>
#include "cache.h"
#include <sstream>

using namespace std;

class Student{
    int id;
    int value;
    string data;

    public:
        static const string class_name; //Cada clase tiene un static llamado: class_name
        Student() : id(0), value(0), data("") {} // Constructor predeterminado
        Student(int _key , int _value , string _data): id(_key), value(_value), data(_data) {}
        Student(string);
        friend ostream& operator <<(ostream&, Student );
        void print () {
            cout <<"Student Object: ("<<id<<", "<<value <<", "<<data<<")";
        };
        
        ~Student (){};
};

Student::Student(string student_string) {

    string val_str;

    stringstream ss(student_string);

    vector<string> values;

    while (getline(ss,val_str,' ')) {
        values.push_back(val_str);
    }
    id = stoi(values[0]);
    value = stoi(values[1]);
    data = values[2];
}

ostream& operator <<(ostream& os, Student student) {
    os << student.id << ' ' << student.value << ' ' << student.data << ' ';
    return os;
}

const string Student :: class_name = "StudentClass";

int main() {
    CacheManager<Student> my_cache(3);
    
    my_cache.show_file_copy();
    my_cache.insert("0", Student(0,22,"student22"));
    // my_cache.insert("37", Student(1,23,"studiante"));
    // my_cache.insert("0", Student(2,24,"student4"));
    // my_cache.insert("2", Student(2,25,"student5"));
    // my_cache.insert("3", Student(3,29,"student4"));
    cout << "\nCache snapshot: \n";
    my_cache.show_cache();

    cout << "Get: " << endl;
    cout << my_cache.get("0") << endl;
    my_cache.show_cache();

    // cout << "---------------------- UPDATE----------------------- " << endl;
    
    // my_cache.insert("2", Student (22,222,"EZE"));
    // my_cache.show_cache ();

    // cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    // Student return_obj = my_cache.get("0"); //not in cache but in filesystem

    // cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    // my_cache.insert("2", Student (2,25,"EZE"));
    // my_cache.show_cache ();

    // my_cache.insert("9", Student(1,5,"Nine"));
    // my_cache.insert("9", Student(1,5,"Nine"));
    // my_cache.insert("9", Student(1,5,"Nine"));
    // my_cache.show_cache ();
    return 0;
}