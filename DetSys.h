#ifndef DetSys_h
#define DetSys_h

const double Pi = 3.14159265358979323846;
class DetSystem
{
public:
    void NoDet(int);
    void printNoDet();
    void InitCalib(string);
    void InitTCalib(string);
    void InitAngles(string);
    void InitDim(string);
    void InitEfficiency(string);
    double efficiency(double);
    double energy(int, double);
    double time(int, double);
    vector<double> angle(int);
    double SAngle(int);

private:
    int N = 0;
    vector<vector<double>> Calib;
    vector<double> TCalib;
    vector<vector<double>> Angles;
    vector<vector<double>> Dims;
    vector<double> SAngles;
    vector<vector<double>> Efficiency;
};
void DetSystem::InitEfficiency(string input)
{
    fstream ef;
    ef.open(input.c_str(), ios::in);
    Efficiency.clear();
    while (!ef.eof())
    {
        double energy2, efficiency2;
        ef >> energy2 >> efficiency2;
        Efficiency.push_back({energy2, efficiency2});
    }
}
double DetSystem::efficiency(double Energy)
{
    double min = 0;
    double max = 0;
    double ef_min, ef_max;
    for (vector<double> element : Efficiency)
    {
        if (element[0] < Energy)
        {
            min = element[0];
            ef_min = element[1];
        }
        if (element[0] > Energy)
        {
            max = element[0];
            ef_max = element[1];
        }
    }
    if (min == 0)
    {
        return ef_max;
    }
    if (max == 0)
    {
        return ef_min;
    }
    double out;
    out = ef_min + (ef_max - ef_min) / (max - min) * (Energy - min);
    return out;
}
vector<double> DetSystem::angle(int a)
{
    return {Angles[a][0], Angles[a][1]};
}
void DetSystem::InitDim(string num)
{
    int a;
    double p0, p1, sa;
    fstream f;
    f.open(num.c_str(), ios::in);
    for (int i = 0; i < N; i++)
    {
        f >> a >> p0 >> p1;
        Dims[a][0] = p0;
        Dims[a][1] = p1;
        sa = 1 / 2 * (1 - p0 / sqrt(p0 * p0 + p1 * p1));
        SAngles[a] = sa;
    }
    f.close();
}
double DetSystem::SAngle(int x)
{
    return SAngles[x];
}
void DetSystem::NoDet(int x)
{
    N = x;
    Calib.clear();
    TCalib.clear();
    Angles.clear();
    for (int i = 0; i < N; i++)
    {
        Calib.push_back({0, 1});
        TCalib.push_back(0);
        Angles.push_back({0, 0});
        Dims.push_back({0, 0});
        SAngles.push_back(0);
    }
    Efficiency.push_back({0, 1});
}
void DetSystem::printNoDet()
{
    cout << "Number of detectors: " << N << endl;
}
void DetSystem::InitCalib(string num)
{
    int a;
    double p0, p1;
    fstream f;
    f.open(num.c_str(), ios::in);
    for (int i = 0; i < N; i++)
    {
        f >> a >> p0 >> p1;
        Calib[a][0] = p0;
        Calib[a][1] = p1;
    }
    f.close();
}
void DetSystem::InitAngles(string num)
{
    int a;
    double p0, p1;
    fstream f;
    f.open(num.c_str(), ios::in);
    for (int i = 0; i < N; i++)
    {
        f >> a >> p0 >> p1;
        Angles[a][0] = p0;
        Angles[a][1] = p1;
    }
    f.close();
}
double DetSystem::energy(int a, double x)
{
    if (a < N)
    {
        return Calib[a][0] + Calib[a][1] * x;
    }
    else
    {
        return 0;
    }
}
void DetSystem::InitTCalib(string num)
{
    int a;
    double p0;
    fstream f;
    f.open(num.c_str(), ios::in);
    for (int i = 0; i < N; i++)
    {
        f >> a >> p0;
        TCalib[a] = p0;
    }
    f.close();
}
double DetSystem::time(int a, double x)
{
    return x - TCalib[a];
}
double Angle(DetSystem S1, int a, DetSystem S2, int b)
{
    double o1, o2, p1, p2;
    o1 = Pi / 180 * S1.angle(a)[0];
    o2 = Pi / 180 * S2.angle(b)[0];
    p1 = Pi / 180 * S1.angle(a)[1];
    p2 = Pi / 180 * S2.angle(b)[1];
    double result = sin(o1) * sin(o2) * cos(p1 - p2) + cos(o1) * cos(o2);
    result = acos(result);
    result = 180 / Pi * result;
    return result;
}
#endif
