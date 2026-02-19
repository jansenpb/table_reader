#include "table_reader.h"

using namespace std;

Table::Table(const string& filename)
{
    HighFive::File file(filename, HighFive::File::ReadOnly);

    // --------------------
    // Read axes
    // --------------------
    file.getDataSet("/axes/mean_mixture_fraction").read(Z);
    file.getDataSet("/axes/heat_loss_parameter").read(H);
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

    read_solution("/solution/Temperature", Temp);
    read_solution("/solution/Y_Fuel",      Y_Fuel);
    read_solution("/solution/Y_Oxidizer",  Y_Oxid);
    read_solution("/solution/Y_Product",   Y_Prod);
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
    double th = (Hq - H[i]) / (H[i+1] - H[i]);
    double tv = (Vq - Zvar[i]) / (Zvar[i+1] - Zvar[i]);


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
void Table::query(double Zq,
            double Hq,
            double Vq,
            double& T,
            double& Yf,
            double& Yo,
            double& Yp) const
{
    T  = interpolation(Temp  , Zq, Hq, Vq);
    Yf = interpolation(Y_Fuel, Zq, Hq, Vq);
    Yo = interpolation(Y_Oxid, Zq, Hq, Vq);
    Yp = interpolation(Y_Prod, Zq, Hq, Vq);
};


