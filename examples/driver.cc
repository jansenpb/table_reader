#include "table_reader.h"
#include <highfive/H5File.hpp>
#include <iostream>
#include <vector>
int main()
{
    Table table("../cfd_lookup_table_4d.h5");

    int num_species = table.get_num_species();
    std::vector<double> Y_species(num_species, 0.0);
    double T;

    table.query(0.055, 0.2, 100, 1e12, Y_species.data(), T);

    std::cout << "Temperature = " << T << std::endl;

    for (int i=0;i<std::min(num_species, 5); i++) {
        std::cout << "Y_" << table.get_species_name(i) << " = " << Y_species[i] << std::endl;
    }

    return 0;
}
