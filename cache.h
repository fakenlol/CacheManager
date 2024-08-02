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

    map<string, pair<T, int>> cache_data; //<Clave ,<Obj, Indice de Uso >>
    map<string, T> file_data;           //Copy of file data

    T default_value;
    fstream disk;

    void write_file(string, T);
    void load_file();

    public:
        CacheManager(int); // recibe la capacidad en el int
        ~CacheManager();
        void insert(string key, T obj);
        T get(string key);
        void show_cache();

        //File management
        void show_file_copy();
};

template <class T>
CacheManager<T>::CacheManager(int cap){
    capacity = cap;
    current_mru = 0;
    load_file();
}

template <class T>
CacheManager<T>::~CacheManager() {
    // Cerrar el archivo al destruir el objeto
    if (disk.is_open()) {
        disk.close();
    }
}

// INSERT
template <class T>
void CacheManager<T>::insert(string key, T obj) {
    if (cache_data.count(key)) { // Existe
        cout << "Existe en RAM.\n";
        cache_data[key] = make_pair(obj, current_mru++);
    } else { // No existe
        if (cache_data.size() == capacity) { // No hay espacio
            auto mru = max_element(cache_data.begin(), cache_data.end(), [](const pair<string, pair<T, int>>& a, const pair<string, pair<T, int>>& b) {
                return a.second.second < b.second.second;
            });
            cache_data.erase(mru->first);
        }
        cache_data[key] = make_pair(obj, current_mru++);
    }
    write_file(key, obj);
}

template <class T>
T CacheManager<T>::get(string key) {
    
    if (cache_data.count(key)){
        cache_data[key].second++;
        return cache_data[key].first;
    } else if(file_data.count(key)) {
        if (cache_data.size() == capacity) {
            auto lru = min_element(cache_data.begin(), cache_data.end(), [](const pair<string, pair<T, int>>& a, const pair<string, pair<T, int>>& b) {
                return a.second.second < b.second.second;
            });
            cache_data.erase(lru->first);
        }
        cache_data[key] = make_pair(file_data[key], current_mru++);
        return cache_data[key].first;
    }
    return default_value; // no encontrado
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

//File management classes

template <class T>
void CacheManager <T>::load_file() {
    string line;

    if (disk.is_open()) {
        disk.clear();
        disk.seekg(0, ios::beg);
    } else {
        disk.open("disk.txt", ios::in | ios::out);
        if (!disk.is_open()) {
            cerr << "No se pudo abrir el archivo para lectura/escritura." << endl;
            return;
        }
    }

    while(getline(disk, line)){
        if(line == "")
            break;
        int space_pos = line.find(' ');
        string line_key = line.substr(0, space_pos);
        string line_obj = line.substr(space_pos + 1);       
        file_data[line_key] = T(line_obj);
    }
}

template <class T>
void CacheManager <T>::show_file_copy() {
    
    if (!disk.is_open()) {
        cerr << "Documento no abierto. " << endl;
        return;
    }
    cout << "Copia del archivo: " << endl;
    auto iter = file_data.begin();
    while (iter != file_data.end()) {
        cout << "[" << iter->first << ",";
        iter->second.print();
        cout << "]\n";
        iter++;
    }
}

// Maneja la inserción y modificación de los datos
template <class T>
void CacheManager<T>::write_file(string key, T obj) {

    cout << "Write file: " << key << ' ' << obj << endl;
    auto file_data_it = file_data.begin();
    disk.clear();

    if(file_data.count(key) > 0) {
        cout << "SE ENCONTRO" << endl;
        disk.seekp(0, ios::beg);
        file_data[key] = obj;
        while (file_data_it != file_data.end()){
            cout << "First: " << file_data_it->first << "f " << file_data_it->second << endl;
            disk << file_data_it->first << ' ' << file_data_it->second << endl;    
            file_data_it ++;
        }
    } else {
        disk.seekp(0, ios::end);
        disk << key << ' ' << obj << endl;
    }
}