void PlotEfficiency(){

  gROOT->SetBatch();

  TCanvas* c = new TCanvas("c", "c", 1200, 800);
  TGraphErrors* gr = new TGraphErrors();
  gr->GetXaxis()->SetTitle("Beam Energy [MeV]");
  gr->GetYaxis()->SetTitle("Efficiency [%]");

  std::vector<std::array<Double_t, 3>> eff_array = {
    // {Beam Energy, Efficiency, Stat. Error}
    {0.25, 0.039323, 0.000194362},
    {0.50, 0.03407, 0.000181409},
    {0.75, 0.028909, 0.000167551},
    {1.00, 0.025871, 0.00015875},
    {1.25, 0.023601, 0.000151802},
    {1.50, 0.021483, 0.000144988},
    {1.75, 0.019426, 0.000138017},
    {2.00, 0.01808, 0.000133241},
    {2.25, 0.016693, 0.000128118},
    {2.50, 0.015326, 0.00012249},
  };

  static Int_t index = 0;
  for (const auto& eff : eff_array) {
    gr->SetPoint(index, eff.at(0), eff.at(1)*100);
    gr->SetPointError(index, 0, eff.at(2)*100);
    ++index;
  }

  gr->Draw("AP");

  TString pdf_dir = "/home/gppuuser09/GPPU_2025/GPPU_2025_kadai/fig/";
  TString pdf_name = "Efficiency.pdf";
  c->Print(pdf_dir + pdf_name);
}
