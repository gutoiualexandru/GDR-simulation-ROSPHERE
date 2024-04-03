#include "DetSys.h"
#include "DataGeneratorFunctions.h"

void DataGenerator()
{
    DetSystem Scint;
    Scint.NoDet(21);
    Scint.InitEfficiency("Efficiency.txt");
    float Energy[50];
    vector<int> id;
    vector<int> type;
    TFile *input = new TFile("31P_40Ca_71Br_2.58_1.00_1697011561.root", "read");
    TTree *tree1 = (TTree *)input->Get("geminitree");
    int Ngamma;
    tree1->SetBranchAddress("Ngamma", &Ngamma);
    tree1->SetBranchAddress("gammaECM", &Energy);
    TFile *f = new TFile("ROSPHERE_response.root", "RECREATE");
    TTree *tree = new TTree("tree", "tree");
    // tree->Branch("Energy", &Energy);
    tree->Branch("id", &id);
    tree->Branch("type", &type);
    TH1D *hist = new TH1D("hist", "N gamma", 30, 0, 30);
    TH1D *hist2 = new TH1D("hist2", "N detected", 30, 0, 30);
    int entries = tree1->GetEntries();
    cout << entries << endl;
    for (int i = 0; i < entries; i++)
    {
        tree1->GetEntry(i);
        int N = 0;
        for (int j = 0; j < Ngamma; j++)
        {
            double E_double = (double)Energy[j];
            E_double = E_double * 1000;
            double eff = Scint.efficiency(E_double);
            generate_scint(id, type, eff);
            N++;
        }
        pileuprejection(id, type);
        if (N > 0)
        {
            hist->Fill(N);
            hist2->Fill(id.size());
        }

        tree->Fill();
        id.clear();
        type.clear();
    }

    f->Write();
    // f->Close();
    TCanvas *c1 = new TCanvas();
    hist->Draw();
    TCanvas *c2 = new TCanvas();
    hist2->Draw();
}
