#include "table_reader.h"
#include <highfive/H5File.hpp>
#include <iostream>
#include <vector>
int main()
{
    Table table("cfd_lookup_table_3d.h5");

    double T, Yf, Yo, Yp;

    table.query(0.04, 0.3, 0.5, T, Yf, Yo, Yp);

    std::cout << "Temperature = " << T  << std::endl;
    std::cout << "Y_fuel      = " << Yf << std::endl;
    std::cout << "Y_Oxidizer  = " << Yo << std::endl;
    std::cout << "Y_Product   = " << Yp << std::endl;

    return 0;
}
