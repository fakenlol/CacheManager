#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template<class T>
class CacheManager {
    int capacity;
    int current_mru;

    map <string, pair<T, int>> cache_data; //<Clave ,<Obj, Indice de Uso >>

    T default_value;
    fstream disk;

    bool open_file();
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
    current_mru = 0;
}

template <class T>
CacheManager <T>::~CacheManager () {
    disk.close();
}

template<class T>
bool CacheManager <T>::open_file() {
    string filename = "disk.txt";

    disk.open(filename, ios::app);
    if (ios::goodbit == 0)
        return true;
    else
        return false;
}

template <class T>
bool CacheManager <T>::write_file(string key , T obj) {
    if (!disk.is_open())
        open_file();
    else
        disk << key << ' ' << obj;
    return true;
}

// INSERT
template <class T>
void CacheManager <T>::insert(string key , T obj) {
    write_file(key,obj);
    if (cache_data.count(key)){ //Existe
        cache_data[key] = make_pair(obj, current_mru++);
        return;
    }
    //No existe
    if (cache_data.size() == capacity) // No hay espacio
    {
        auto mru = max_element(cache_data.begin(), cache_data.end(), [](const pair<string, pair<T, int>>& a,const pair<string, pair<T, int>>& b) {
            return a.second.second < b.second.second;
        });
        cache_data.erase(mru->first);
    }
    cache_data[key] = make_pair(obj, current_mru++);
}

template <class T>
T CacheManager <T>::get(string key) {
    if(cache_data.count(key))
        return cache_data[key].first;   //encontrado
    else
        return default_value;   //no encontrado
}

template <class T>
void CacheManager <T>::show_cache() {

    auto iter = cache_data.begin();
    
    while (iter != cache_data.end()) {
        cout << "[" << iter->first << ",";
        iter->second.first.print();
        cout << "]\n";
        iter++;
    }
}