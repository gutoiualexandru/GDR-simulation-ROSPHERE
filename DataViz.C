void DataViz()
{
    TFile *input = new TFile("31P_40Ca_71Br_2.58_1.00_1697011561.root", "read");
    TTree *tree = (TTree *)input->Get("geminitree");
    int Ngamma;
    int Nprod;
    tree->SetBranchAddress("Ngamma", &Ngamma);
    tree->SetBranchAddress("Nproducts", &Nprod);
    float Energy[50];
    float Theta[50];
    // TH1D *hist = new TH1D("hist", "N gamma", 30, 0, 30);
    TH2D *hist = new TH2D("hist", "Egamma", 30,0,30,6000, 0, 60);
    tree->SetBranchAddress("gammaECM", &Energy);
    tree->SetBranchAddress("Ngamma", &Ngamma);
    int entries = tree->GetEntries();
    for (int i = 0; i < entries; i++)
    {
        tree->GetEntry(i);
        float E = 0;
        for (int j = 0; j < Ngamma; j++)
        {
             E = E + Energy[j];
            //  cout << Energy[j] << " ";
            //hist->Fill(Energy[j]);
        }
         hist->Fill(Ngamma, E);
    }
    hist->Draw();
}
