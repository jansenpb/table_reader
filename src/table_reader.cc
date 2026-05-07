#include "table_reader.h"

using namespace std;

Table::Table(const string& filename)
{
    HighFive::File file(filename, HighFive::File::ReadOnly);

    // --------------------
    // Read axes
    // --------------------
    file.getDataSet("/axes/mean_mixture_fraction").read(Z);
    file.getDataSet("/axes/variance_fraction").read(Zvar);
    file.getDataSet("/axes/absolute_enthalpy").read(H);
    file.getDataSet("/axes/soot_moment_0").read(M0);

    Nz = Z.size();
    Nv = Zvar.size();
    Nh = H.size();
    Nm = M0.size();

    // --------------------
    // Read solution fields
    // --------------------
    auto read_solution = [&](const string& name,
                             vector<double>& data)
    {
        HighFive::DataSet ds = file.getDataSet(name);

        vector<size_t> dims = ds.getDimensions();

        /*cout << name << " dimensions: ";
        for (auto d : dims) cout << d << " ";
        cout << endl; */

        // Compute total size 
        size_t total_size = 1;
        for (auto d : dims)
            total_size *= d;


        data.resize(total_size);

        ds.read(data.data());
    };

    HighFive::Group solution_group = file.getGroup("/solution");
    vector<string> keys = solution_group.listObjectNames();

    for (const auto& key : keys) {
        if (key.substr(0,2) == "Y_") {
            species_names.push_back(key);
            vector<double> data;
            read_solution("/solution/" + key, data);
            Y_species.push_back(move(data));
        }
    }
    num_species = species_names.size();

   read_solution("/solution/Temperature", Temperature); 

}

size_t Table::index(size_t i, size_t j, size_t k, size_t l) const {
    return ((i * Nh + j) * Nv + k) * Nm + l;
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
double Table::interpolation(const std::vector<double>& field, double Zq, double Vq,double Hq,double M0q) const {
    size_t i = find_lower_index(Z, Zq);
    size_t k = find_lower_index(Zvar, Vq);
    size_t j = find_lower_index(H, Hq);
    size_t l = find_lower_index(M0, M0q);

    double tz = (Zq - Z[i]) / (Z[i+1] - Z[i]);
    double tv = (Vq - Zvar[k]) / (Zvar[k+1] - Zvar[k]);
    double th = (Hq - H[j]) / (H[j+1] - H[j]);
    double tm = (M0q - M0[l]) / (M0[l+1] - M0[l]);


    double c0000 = field[index(i,   j,   k,   l)];
    double c1000 = field[index(i+1, j,   k,   l)];
    double c0100 = field[index(i,   j+1, k,   l)];
    double c1100 = field[index(i+1, j+1, k,   l)];
    double c0010 = field[index(i,   j,   k+1, l)];
    double c1010 = field[index(i+1, j,   k+1, l)];
    double c0110 = field[index(i,   j+1, k+1, l)];
    double c1110 = field[index(i+1, j+1, k+1, l)];

    double c0001 = field[index(i,   j,   k,   l+1)];
    double c1001 = field[index(i+1, j,   k,   l+1)];
    double c0101 = field[index(i,   j+1, k,   l+1)];
    double c1101 = field[index(i+1, j+1, k,   l+1)];
    double c0011 = field[index(i,   j,   k+1, l+1)];
    double c1011 = field[index(i+1, j,   k+1, l+1)];
    double c0111 = field[index(i,   j+1, k+1, l+1)];
    double c1111 = field[index(i+1, j+1, k+1, l+1)];

    double c000 = c0000*(1-tz) + c1000*tz;
    double c010 = c0010*(1-tz) + c1010*tz;
    double c100 = c0100*(1-tz) + c1100*tz;
    double c110 = c0110*(1-tz) + c1110*tz;
    double c001 = c0001*(1-tz) + c1001*tz;
    double c011 = c0011*(1-tz) + c1011*tz;
    double c101 = c0101*(1-tz) + c1101*tz;
    double c111 = c0111*(1-tz) + c1111*tz;

    // Interpolate along V 
    double c00 = c000*(1-tv) + c100*tv;
    double c10 = c010*(1-tv) + c110*tv;
    double c01 = c001*(1-tv) + c101*tv;
    double c11 = c011*(1-tv) + c111*tv;

    // Interpolate along H 
    double c0 = c00*(1-th) + c10*th;
    double c1 = c01*(1-th) + c11*th;

    // Interpolate along M0

    return c0*(1-tm) + c1*tm;
} 
void Table::query(double Zq, double Vq, double Hq, double M0q, double* Y_species_q, double& T_q) const
{
    for (size_t i=0; i<num_species; i++) {
        Y_species_q[i] = interpolation(Y_species[i], Zq, Vq, Hq, M0q);
    }
    T_q     = interpolation(Temperature, Zq, Vq, Hq, M0q);
};


