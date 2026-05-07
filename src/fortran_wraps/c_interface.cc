#include "../table_reader.h"
#include <highfive/H5File.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//////////////////////////////////////////////////////////

extern "C" {

    // Interface for loading and reading the table /////// 

    Table *Table_Interface(const char* filename) {
        return new Table(string(filename));
    }

    void query_interface(Table *T_ptr, double Zq_, double Vq_, double Hq_, double M0q_, double* Y_species_q, double& T_q) {
        T_ptr->query(Zq_, Vq_, Zq_, M0q_, Y_species_q, T_q); 
    }

    int get_num_species_interface(Table *T_ptr) {
        return T_ptr->get_num_species();
    }

    void get_species_name_interface(Table *T_ptr, int i, char* names, int max_len) {
        string s_names = T_ptr->get_species_name(i);
        int len = min((int)s_names.length(), max_len - 1);
        for (int j=0; j<len; j++) {
            names[j] = s_names[j];
        }
        for (int j=len; j<max_len; j++) {
            names[j] = ' ';
        }
    }
}
