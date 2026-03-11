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
                         double& Y_CH4_q, double& Y_O2_q, double& Y_CO2_q, double& Y_H2O_q,
                         double& Y_CO_q, double& Y_OH_q, double& Y_O_q, double& Y_H_q,
                         double& Y_H2_q, double& Y_C2H2_q, double& Y_C6H6_q, double& Y_C_q,
                         double& Y_N2_q, double& rad_q, double& edc_q, double& T_q) {
        T_ptr->query(Zq_, Hq_, Vq_, 
                     Y_CH4_q, Y_O2_q, Y_CO2_q, Y_H2O_q,
                     Y_CO_q, Y_OH_q, Y_O_q, Y_H_q,
                     Y_H2_q, Y_C2H2_q, Y_C6H6_q, Y_C_q,
                     Y_N2_q, rad_q, edc_q, T_q);
    }
}
