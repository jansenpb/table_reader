#include "table_reader.h"
#include <highfive/H5File.hpp>
#include <iostream>
#include <vector>
int main()
{
    Table table("../cfd_lookup_table_3d.h5");

    double Y_CH4, Y_O2, Y_CO2, Y_H2O, Y_CO, Y_OH, Y_O, Y_H, Y_H2, Y_C2H2, Y_C6H6, Y_C, Y_N2, rad, edc, T;
    table.query(0.04, 0.3, 0.5, Y_CH4, Y_O2, Y_CO2, Y_H2O, Y_CO, Y_OH, Y_O, Y_H, Y_H2, Y_C2H2, Y_C6H6, Y_C, Y_N2, rad, edc, T);

    std::cout << "Temperature = " << T << std::endl;
    std::cout << "Y_fuel      = " << Y_CH4 << std::endl;
    std::cout << "Y_Oxidizer  = " << Y_O2 << std::endl;
    std::cout << "Rad Source  = " << rad << std::endl;

    return 0;
}
