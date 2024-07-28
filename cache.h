#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template<class T>
class CacheManager {
    int capacity;

    map <string, pair<T, int>> cache_data; //<Clave ,<Obj, Indice de Uso >>

    bool write_file(string ,T);

    public:
        CacheManager(int); // recibe la capacidad en el int
        ~CacheManager ();
        void insert(string key , T obj);
        T get(string key);

        void show_cache();

        // Agregar todas las funciones necesarias
};

template <class T>
CacheManager <T>::CacheManager(int cap) {
    capacity = cap;
}

template <class T>
CacheManager <T>::~CacheManager () {}

template <class T>
bool CacheManager <T>::write_file(string key , T obj) {
    return true;
}

// INSERT
template <class T>
void CacheManager <T>::insert(string key , T obj) {
    cout << "hola" << '\n';
    cache_data[key] = make_pair(obj, 1);
    for(auto &item:cache_data){
        cout << &item.first << endl;
    }
}

template <class T>
T CacheManager <T>::get(string key) {

}

template <class T>
void CacheManager <T>::show_cache() {

    auto iter = cache_data.begin();
    
    while (iter != cache_data.end()) {
        cout << "[" << iter->first << "," << iter->second.second << "]\n";
        iter++;
    }
}