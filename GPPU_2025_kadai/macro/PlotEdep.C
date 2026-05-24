// void PlotEdep(const Double_t Energy, const TString root_name){
void PlotEdep(){
  gROOT->SetBatch();
  gStyle->SetLineColor(kBlack);

  TString project = "P5-4";
  Double_t energy = 2.50; // MeV
  TString root_name = Form("%s_%.2fMeV_1Mevents.root", project.Data(), energy);

  TString root_dir = "/home/gppuuser09/GPPU_2025/GPPU_2025_kadai/rootfile/";
  TString root = root_dir + root_name;
  TFile* file = TFile::Open(root);
  TTree* tree =file->Get<TTree>("Edep");
  if (!tree) {
    std::cerr << "#E: Cannot find the tree 'Edep' !!" << std::endl;
  }

  TCanvas* c = new TCanvas("c", "c", 12000, 8000);
  c->Divide(2, 2);

  c->cd(1);
  gPad->SetLogy();
  TH1D* h_edep = file->Get<TH1D>("h_EdepTotal_Ge");
  h_edep->Draw("hist");
  h_edep->GetXaxis()->SetRangeUser(0., energy + 0.1);
  c->Update();

  // ----- Detection Efficiency -----
  const Double_t threshold = energy * 0.99; // MeV
  Double_t n_total = tree->GetEntries();
  Double_t n_detect = tree->GetEntries(Form("Edep_total > %f", threshold));

  Double_t eff = n_detect / n_total;
  Double_t err = TMath::Sqrt(eff * (1 - eff) / n_total);

  TLatex* latex = new TLatex();
  latex->DrawLatexNDC(0.3, 0.8, Form("Eff: %f #pm %f", eff, err));
  c->Update();

  TLatex* latex2 = new TLatex();
  latex2->DrawLatexNDC(0.3, 0.7, Form("Threshold: %.3f [MeV]", threshold));
  c->Update();

  c->cd(2);
  TH1D* h_costheta = file->Get<TH1D>("h_Dir_Z");
  h_costheta->Draw("hist");
  c->Update();

  c->cd(3);
  TH1D* h_phi = file->Get<TH1D>("h_Phi");
  h_phi->Draw("hist");
  c->Update();

  TString pdf_dir = "/home/gppuuser09/GPPU_2025/GPPU_2025_kadai/fig/";
  TString pdf_name = Form("%s_%.2fMeV_%s.pdf", project.Data(), energy, __func__);

  c->Print(pdf_dir + pdf_name);

  if (project == "P5-4") {
    std::cout << "Beam Energy: " << Form("%.2f", energy) << " [MeV]" << std::endl;
    std::cout << eff << ", " << err << std::endl;
  }
}
