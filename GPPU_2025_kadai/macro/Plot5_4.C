// void PlotEdep(const Double_t Energy, const TString root_name){
void Plot5_4(){
  gROOT->SetBatch();
  gStyle->SetLineColor(kBlack);

  TString project = "P5-4";

  std::vector<TCanvas*> canvas_vec;
  canvas_vec.clear();

  TGraphErrors* gr_eff = new TGraphErrors();
  gr_eff->GetXaxis()->SetTitle("Beam Energy [MeV]");
  gr_eff->GetYaxis()->SetTitle("Efficiency [%]");

  for (Int_t i = 0; i < 10; ++i) {
    Double_t energy = 0.25 * (i + 1); // MeV
    TString root_name = Form("%s_%.2fMeV_1Mevents.root", project.Data(), energy);

    TString root_dir = "/home/gppuuser09/GPPU_2025/GPPU_2025_kadai/rootfile/";
    TString root = root_dir + root_name;
    TFile* file = TFile::Open(root);
    TTree* tree =file->Get<TTree>("Edep");
    if (!tree) {
      std::cerr << "#E: Cannot find the tree 'Edep' !!" << std::endl;
    }

    TCanvas* c_plot = new TCanvas("c_plot", "c_plot", 12000, 8000);
    c_plot->Divide(2, 2);
    canvas_vec.push_back(c_plot);

    auto c = canvas_vec.back();

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

    gr_eff->SetPoint(i, energy, eff*100);
    gr_eff->SetPointError(i, 0, err*100);

    std::cout << "Beam Energy: " << Form("%.2f", energy) << " [MeV]" << std::endl;
    std::cout << eff << ", " << err << std::endl;
  }

  TCanvas* c_gr = new TCanvas("c_gr", "c_gr", 12000, 8000);
  canvas_vec.push_back(c_gr);

  c_gr->cd();
  gr_eff->Draw("AP");


  TString pdf_dir = "/home/gppuuser09/GPPU_2025/GPPU_2025_kadai/fig/";
  TString pdf_name = pdf_dir + Form("%s.pdf", __func__);

  TString name;
  for (auto it = canvas_vec.begin(); it != canvas_vec.end(); ++it) {
    if (it == canvas_vec.begin()) {
      if (canvas_vec.size() == 1) name = pdf_name;
      else name = pdf_name + "(";
    } else if (std::next(it) == canvas_vec.end()) {
      name = pdf_name + ")";
    } else {
      name = pdf_name;
    }
    (*it)->Print(name);
  }
}
