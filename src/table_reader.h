#pragma once

#include <highfive/H5File.hpp>
#include <iostream>
#include <vector>

class Table {

    //////////// Data Members /////////////////// 

    public:

        std::vector<double> Z;     // mean_mixture_fraction
        std::vector<double> H;     // heat_loss_parameter
        std::vector<double> Zvar;  // variance_fraction

        std::vector<double> Temp;  // solution field for Temperature
        std::vector<double> Y_Fuel; // solution field for fuel mass fraction
        std::vector<double> Y_Oxid; // solution field for air mass fraction
        std::vector<double> Y_Prod; // solution field for product mass fraction

        size_t Nz, Nh, Nv;          // points in the table -> mixture fraction, heat loss, variance 



    /////////// Member Functions //////////////// 

        double interpolation(const std::vector<double>& field, double Zq, double Hq, double Vq) const;

        size_t find_lower_index(const std::vector<double>&axis, double value) const;
        
        size_t index(size_t i, size_t j, size_t k) const;

        void query(double Zq, double Hq, double Vq, double& T, double& Yf, double& Yo, double& Yp) const;

    /////////// Constructor functions /////////// 

        Table(const std::string& filename);

};
/*struct Table {
    // Axes
    std::vector<double> Z;      // mean_mixture_fraction (20)
    std::vector<double> H;      // heat_loss_parameter (5)
    std::vector<double> Zvar;   // variance_fraction (5)
    // Solution fields (flattened 3D arrays)
    std::vector<double> Temperature;
    std::vector<double> Y_Fuel;
    std::vector<double> Y_Oxidizer;
    std::vector<double> Y_Product;

    size_t Nz, Nh, Nv;


        auto it = std::lower_bound(axis.begin(), axis.end(), value);

        if (it == axis.begin())
            return {0, 0.0};

        if (it == axis.end())
            return {axis.size()-2, 1.0};

        size_t idx = std::distance(axis.begin(), it) - 1;

        double t = (value - axis[idx]) / (axis[idx+1] - axis[idx]);

        return {idx, t};
    }

    size_t index(size_t i, size_t j, size_t k) const; {
        return (i * Nh + j) * Nv + k;
    }

    // Interpolation
    double trilinear(const std::vector<double>& field,
                     double Zq,
                     double Hq,
                     double Vq) const;
    {
        AxisLookup az = lookup_axis(Z, Zq);
        AxisLookup ah = lookup_axis(H, Hq);
        AxisLookup av = lookup_axis(Zvar, Vq);

        size_t i = az.i;
        size_t j = ah.i;
        size_t k = av.i;

        double tz = az.t;
        double th = ah.t;
        double tv = av.t;

        double c000 = field[index(i,   j,   k)];
        double c100 = field[index(i+1, j,   k)];
        double c010 = field[index(i,   j+1, k)];
        double c110 = field[index(i+1, j+1, k)];
        double c001 = field[index(i,   j,   k+1)];
        double c101 = field[index(i+1, j,   k+1)];
        double c011 = field[index(i,   j+1, k+1)];
        double c111 = field[index(i+1, j+1, k+1)];

        double c00 = c000*(1-tz) + c100*tz;
        double c01 = c001*(1-tz) + c101*tz;
        double c10 = c010*(1-tz) + c110*tz;
        double c11 = c011*(1-tz) + c111*tz;

        double c0 = c00*(1-th) + c10*th;
        double c1 = c01*(1-th) + c11*th;

        return c0*(1-tv) + c1*tv;
    } 
    void query(double Zq,
               double Hq,
               double Vq,
               double& T,
               double& Yf,
               double& Yo,
               double& Yp) const;
    {
        T  = trilinear(Temperature, Zq, Hq, Vq);
        Yf = trilinear(Y_Fuel,      Zq, Hq, Vq);
        Yo = trilinear(Y_Oxidizer,  Zq, Hq, Vq);
        Yp = trilinear(Y_Product,   Zq, Hq, Vq);
    }
};

Table read_table(const std::string& filename);
{
    Table table;

    HighFive::File file(filename, HighFive::File::ReadOnly);

    // --------------------
    // Read axes
    // --------------------
    file.getDataSet("/axes/mean_mixture_fraction").read(table.Z);
    file.getDataSet("/axes/heat_loss_parameter").read(table.H);
    file.getDataSet("/axes/variance_fraction").read(table.Zvar);

    table.Nz = table.Z.size();
    table.Nh = table.H.size();
    table.Nv = table.Zvar.size();

    std::cout << "Axes sizes: "
              << table.Nz << " x "
              << table.Nh << " x "
              << table.Nv << std::endl;

    // --------------------
    // Read solution fields
    // --------------------
    auto read_solution = [&](const std::string& name,
                             std::vector<double>& data)
    {
        HighFive::DataSet ds = file.getDataSet(name);

        std::vector<size_t> dims = ds.getDimensions();

        std::cout << name << " dimensions: ";
        for (auto d : dims) std::cout << d << " ";
        std::cout << std::endl;

        // Compute total size 
        size_t total_size = 1;
        for (auto d : dims)
            total_size *= d;


        data.resize(total_size);

        ds.read_raw(data.data());
    };

    read_solution("/solution/Temperature", table.Temperature);
    read_solution("/solution/Y_Fuel",      table.Y_Fuel);
    read_solution("/solution/Y_Oxidizer",  table.Y_Oxidizer);
    read_solution("/solution/Y_Product",   table.Y_Product);

    return table;
}*/



/*int main()
{
    Table table = read_table("cfd_lookup_table_3d.h5");

    double T, Yf, Yo, Yp;

    table.query(0.04, 0.8, 0.01, T, Yf, Yo, Yp);

    std::cout << "Temperature = " << T  << std::endl;
    std::cout << "Y_fuel      = " << Yf << std::endl;
    std::cout << "Y_Oxidizer  = " << Yo << std::endl;
    std::cout << "Y_Product   = " << Yp << std::endl;

    return 0;
}*/
