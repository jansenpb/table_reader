#pragma once

#include <highfive/H5File.hpp>
#include <iostream>
#include <vector>

class Table {

    //////////// Data Members /////////////////// 

    public:

        std::vector<double> Z;     // mean_mixture_fraction
        std::vector<double> Zvar;  // variance_fraction
        std::vector<double> H;     // heat_loss_parameter
        std::vector<double> M0;    // soot moment 0 (progress variable)
        std::vector<double> Temperature;

        std::vector<std::vector<double>> Y_species;
        std::vector<std::string> species_names;
        size_t num_species;

        //std::vector<double> rad_source;
        //std::vector<double> edc_mixing;

        size_t Nz, Nv, Nh, Nm;          // points in the table -> mixture fraction, heat loss, variance 



    /////////// Member Functions //////////////// 

        double interpolation(const std::vector<double>& field, double Zq, double Vq, double Hq, double M0q) const;

        size_t find_lower_index(const std::vector<double>&axis, double value) const;
        
        size_t index(size_t i, size_t j, size_t k, size_t l) const;

        void query(double Zq, double Vq, double Hq, double M0q, double* Y_species_q, double& T_q) const;

        int get_num_species() const { return num_species;}
        std::string get_species_name(int i) const {return species_names[i];}

    /////////// Constructor functions /////////// 

        Table(const std::string& filename);

};
