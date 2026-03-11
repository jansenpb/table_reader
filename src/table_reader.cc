#include "table_reader.h"

using namespace std;

Table::Table(const string& filename)
{
    HighFive::File file(filename, HighFive::File::ReadOnly);

    // --------------------
    // Read axes
    // --------------------
    file.getDataSet("/axes/mean_mixture_fraction").read(Z);
    file.getDataSet("/axes/absolute_enthalpy").read(H);
    file.getDataSet("/axes/variance_fraction").read(Zvar);

    Nz = Z.size();
    Nh = H.size();
    Nv = Zvar.size();

    // --------------------
    // Read solution fields
    // --------------------
    auto read_solution = [&](const string& name,
                             vector<double>& data)
    {
        HighFive::DataSet ds = file.getDataSet(name);

        vector<size_t> dims = ds.getDimensions();

        cout << name << " dimensions: ";
        for (auto d : dims) cout << d << " ";
        cout << endl;

        // Compute total size 
        size_t total_size = 1;
        for (auto d : dims)
            total_size *= d;


        data.resize(total_size);

        ds.read_raw(data.data());
    };

    read_solution("/solution/Y_CH4", Y_CH4);
    read_solution("/solution/Y_O2",  Y_O2);
    read_solution("/solution/Y_CO2", Y_CO2);
    read_solution("/solution/Y_H2O", Y_H2O);
    read_solution("/solution/Y_CO",  Y_CO);
    read_solution("/solution/Y_OH",  Y_OH);
    read_solution("/solution/Y_O",   Y_O);
    read_solution("/solution/Y_H",   Y_H);
    read_solution("/solution/Y_H2",  Y_H2);
    read_solution("/solution/Y_C2H2", Y_C2H2);
    read_solution("/solution/Y_C6H6", Y_C6H6);
    read_solution("/solution/Y_C",    Y_C);
    read_solution("/solution/Y_N2",   Y_N2);
    read_solution("/solution/Temperature", Temperature);
    read_solution("/solution/radiative_source_term", rad_source);
    read_solution("/solution/mixing_rate_EDC",       edc_mixing);
}

size_t Table::index(size_t i, size_t j, size_t k) const {
    return (i * Nh + j) * Nv + k;
}

size_t Table::find_lower_index(const vector<double>& axis, double value) const {

    auto it = lower_bound(axis.begin(), axis.end(), value);

    if (it == axis.begin())
        return 0;

    if (it == axis.end())
        return axis.size() - 2;

    return distance(axis.begin(), it) - 1;
}
    // Interpolation
double Table::interpolation(const std::vector<double>& field,
                    double Zq,
                    double Hq,
                    double Vq) const
{
    size_t i = find_lower_index(Z, Zq);
    size_t j = find_lower_index(H, Hq);
    size_t k = find_lower_index(Zvar, Vq);

    double tz = (Zq - Z[i]) / (Z[i+1] - Z[i]);
    double th = (Hq - H[j]) / (H[j+1] - H[j]);
    double tv = (Vq - Zvar[k]) / (Zvar[k+1] - Zvar[k]);


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
void Table::query(double Zq, double Hq, double Vq,
                  double& Y_CH4_q, double& Y_O2_q, double& Y_CO2_q, double& Y_H2O_q,
                  double& Y_CO_q, double& Y_OH_q, double& Y_O_q, double& Y_H_q,
                  double& Y_H2_q, double& Y_C2H2_q, double& Y_C6H6_q, double& Y_C_q,
                  double& Y_N2_q, double& rad_q, double& edc_q, double& T_q) const
{
    Y_CH4_q = interpolation(Y_CH4, Zq, Hq, Vq);
    Y_O2_q  = interpolation(Y_O2,  Zq, Hq, Vq);
    Y_CO2_q = interpolation(Y_CO2, Zq, Hq, Vq);
    Y_H2O_q = interpolation(Y_H2O, Zq, Hq, Vq);
    Y_CO_q  = interpolation(Y_CO,  Zq, Hq, Vq);
    Y_OH_q  = interpolation(Y_OH,  Zq, Hq, Vq);
    Y_O_q   = interpolation(Y_O,   Zq, Hq, Vq);
    Y_H_q   = interpolation(Y_H,   Zq, Hq, Vq);
    Y_H2_q  = interpolation(Y_H2,  Zq, Hq, Vq);
    Y_C2H2_q = interpolation(Y_C2H2, Zq, Hq, Vq);
    Y_C6H6_q = interpolation(Y_C6H6, Zq, Hq, Vq);
    Y_C_q   = interpolation(Y_C,   Zq, Hq, Vq);
    Y_N2_q  = interpolation(Y_N2,  Zq, Hq, Vq);
    rad_q   = interpolation(rad_source, Zq, Hq, Vq);
    edc_q   = interpolation(edc_mixing, Zq, Hq, Vq);
    T_q     = interpolation(Temperature, Zq, Hq, Vq);
};


