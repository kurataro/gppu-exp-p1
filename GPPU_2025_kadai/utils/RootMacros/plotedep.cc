int plotedep(){
    const char rootfilename[]="outGPPPU.root"; // Tuple file name
    const char figname[]="figGPPU.jpg"; // output file name of figure

    Double_t gammaenergy=1.0; // [MeV]
    
    TCanvas* c = new TCanvas("c","c",0,0,800,600);
    c->SetLogy(1);
    
    TFile* rootf = new TFile(rootfilename,"READ");
    TH1F* h = new TH1F("Energy","Energy",300,0,3);
    TTree* tree = (TTree*)rootf->Get("Edep");
    tree->Draw("edep>>Energy");
    h->SetMinimum(0.1);
    h->SetMaximum(1000000);

    c->Update();
    c->Print(figname);

    Int_t binnumber=h->FindBin(gammaenergy);
    Double_t entries=h->GetBinContent(binnumber);

    std::cout << gammaenergy << " " << entries << std::endl;

    return 0;
}
