#include "../table_reader.h"
#include <highfive/H5File.hpp>
#include <vector>
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////

extern "C" {

    // Interface for loading and reading the table /////// 

    Table *Table_Interface(const char* filename) {
        return new Table(string(filename));
    }

    void query_interface(Table *T_ptr, double Zq_, double Hq_, double Vq_,
                         double& T_, double& Yf_, double& Yo_, double& Yp_) {
        T_ptr->query(Zq_, Hq_, Vq_, T_, Yf_, Yo_, Yp_);
    }
}
