#ifndef DataGeneratorFunctions_h
#define DataGeneratorFunctions_h
#include "DetSys.h"
// const int es = 1126; // efficiency of scintillators X100
// const int c = 215;   // probability of cross-talk X100
// const int et = 4743; // total efficiency of the set-up X100
const int N = 23; // number of detectors
const int es = 1035;
const int c = 200;
const int et = 4363;
void generate(vector<int> &M1, vector<int> &M2)
{
    int v1, v2, v3;
    v1 = rand() % 10000;
    if (v1 > et + c)
    {
        // M1.push_back(0);
    }
    else if (v1 < et)
    {

        v2 = rand() % N;
        if (v1 > es)
        {

            M2.push_back(1);
        }
        else
        {
            M2.push_back(0);
        }
        M1.push_back(v2);
    }
    else
    {
        // M1.push_back(2);
        v3 = rand() % et;
        v2 = rand() % N;
        if (v3 > es)
        {

            M2.push_back(1);
        }
        else
        {
            M2.push_back(0);
        }
        M1.push_back(v2);
        v3 = rand() % et;
        v2 = rand() % N;
        if (v3 > es)
        {

            M2.push_back(1);
        }
        else
        {
            M2.push_back(0);
        }
        M1.push_back(v2);
    }
}
void generate_scint(vector<int> &M1, vector<int> &M2, double eff)
{
    int v = rand() % 10000;
    double e0 = eff * 100;
    int e = (int)e0;
    if (v < e)
    {
        M2.push_back(1);
        M1.push_back(rand() % N);
    }
}
void pileuprejection(vector<int> &M1, vector<int> &M2)
{
    set<int> A, B;
    for (int i = 0; i < M1.size(); i++)
    {
        int item = M1[i] + M2[i] * N;
        int c = A.size();
        A.insert(item);
        if (c == A.size())
        {
            B.insert(item);
        }
    }
    M1.clear();
    M2.clear();
    for (int i : A)
    {
        if (B.find(i) == B.end())
        {
            M1.push_back(i % N);
            M2.push_back(i / N);
        }
    }
}
void pileupsumpeak(vector<int> &M1, vector<int> &M2)
{
    set<int> A;
    for (int i = 0; i < M1.size(); i++)
    {
        set<int> A;
        for (int i = 0; i < M1.size(); i++)
        {
            int item = M1[i] + M2[i] * N;
            A.insert(item);
        }
        M1.clear();
        M2.clear();
        for (int i : A)
        {
            M1.push_back(i % N);
            M2.push_back(i / N);
        }
    }
}

#endif
