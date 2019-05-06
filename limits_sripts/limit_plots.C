
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStyle.cpp"

using namespace mRoot;

class BrasilDrawer_fix{
    public:
    TCanvas * draw_brasil_plot(vector<double> * x_axis, vector<double> * sigma_2_down, vector<double> * sigma_1_down, vector<double> * central, vector<double> * sigma_1_up, vector<double> * sigma_2_up, vector<double> * central_median){
      HistDrawer<TH1D> * drawer = new HistDrawer<TH1D>();
      drawer->logY = true;
      TCanvas * canvas = drawer->GetCanvas("limits");
      canvas->SetLeftMargin(0.22); 

      TGraph * gr_central = new TGraph( central->size() );
      TGraph * gr_central_alt = new TGraph( central->size() );
      FillGraph gr_2sigma, gr_1sigma;

      for(int i = 0; i < central->size(); i++){
        gr_central->SetPoint( i, x_axis->at(i), central->at(i) );
        gr_central_alt->SetPoint(i, x_axis->at(i), central_median->at(i) );
        gr_2sigma.AddPoint( x_axis->at(i), sigma_2_down->at(i), sigma_2_up->at(i) );
        gr_1sigma.AddPoint( x_axis->at(i), sigma_1_down->at(i), sigma_1_up->at(i) );
      }

      TGraph * gr_1_sigma = gr_1sigma.GetGraph();
      TGraph * gr_2_sigma = gr_2sigma.GetGraph();

      set_style_FCC();
        gr_2_sigma->GetYaxis()->CenterTitle();
        gr_2_sigma->GetYaxis()->SetNdivisions(510);

        gr_2_sigma->GetYaxis()->SetLabelFont(132);
        gr_2_sigma->GetYaxis()->SetLabelOffset(0.02);
        gr_2_sigma->GetYaxis()->SetLabelSize(0.04);
        gr_2_sigma->GetYaxis()->SetTitleFont(132);
        gr_2_sigma->GetYaxis()->SetTitleOffset(2.00);
        gr_2_sigma->GetYaxis()->SetTitleSize(0.045);

        gr_2_sigma->GetXaxis()->SetNdivisions(512);
        gr_2_sigma->GetXaxis()->SetLabelFont(132);
        gr_2_sigma->GetXaxis()->SetLabelOffset(0.02);
        gr_2_sigma->GetXaxis()->SetLabelSize(0.04);
        gr_2_sigma->GetXaxis()->SetTitleFont(132);
        gr_2_sigma->GetXaxis()->SetTitleOffset(1.5);
        gr_2_sigma->GetXaxis()->SetTitleSize(0.045);

      gr_2_sigma->SetFillColor(kYellow);
      gr_2_sigma->GetXaxis()->SetRangeUser(xmin, xmax);
      gr_2_sigma->GetXaxis()->SetTitle(label_x.c_str());
      gr_2_sigma->GetYaxis()->SetTitle(label_y.c_str());
      gr_2_sigma->GetHistogram()->SetMaximum(ymax);   // along          
      gr_2_sigma->GetHistogram()->SetMinimum(ymin);  //   Y    
      gr_2_sigma->Draw("AF");

      gr_1_sigma->SetFillColor(kGreen);
      gr_1_sigma->Draw("F");

      gr_central->SetLineStyle(1);
      gr_central->SetLineWidth(2);
      gr_central->Draw("L");


      gr_central_alt->SetLineStyle(2);
      gr_central_alt->SetLineColor(4);
      gr_central_alt->SetLineWidth(2);
      gr_central_alt->Draw("L");


      TLegend * leg  = new TLegend(0.38,0.60,0.92,0.88);
      leg->AddEntry(gr_central, "Br(t #rightarrow u #gamma ) 95% CL Expected Limit", "l");
      leg->AddEntry(gr_1_sigma, "Br(t #rightarrow u #gamma ) #pm 1 std. deviation", "f");
      leg->AddEntry(gr_2_sigma, "Br(t #rightarrow u #gamma ) #pm 2 std. deviation", "f");
      leg->AddEntry(gr_central_alt, "Br(t #rightarrow c #gamma ) 95% CL Expected Limit", "l");
      leg->Draw();

      string rightText = "#bf{FCC-hh Simulation (Delphes)}";
      auto rtext  = drawer->GetRightText( rightText );
      rtext->Draw() ;

       TLatex latex;
       latex.SetTextSize( 0.045 );
       latex.SetNDC();
       latex.DrawLatex(0.21, 0.15, "1");

      canvas->RedrawAxis();
      canvas->GetFrame()->SetBorderSize( 12 );
      return canvas;
    }

    int font;
    bool logY, logX;
    string label_x, label_y;
    double xmin, xmax, ymin, ymax;
  };

double get_branch(double limit){
  // limit = #sigma_limit / #sigma_MG
  double xsec_MG = 213.5 * 2.0 * 2.0 * 0.428 * pow(0.001, 2); // 11.82 * 2.0 * 2.0 * 0.428 * pow(0.001, 2);
  double xsec = limit * xsec_MG; // * 0.1 * 3069.; // 300 * 10^-6 -> 60 * 10^-6
  
  // #sigma_ttbar * 2 * Br_limit = #sigma_limit
  // 11.82 +- 0.07641 pb    = xsec tt pt   > 1000
  double branch = xsec / (213.5 * 2.0 * 2.0); // 6 * 10^-6

  // 2000 -> 100 = 1/20 3069 / 20

  // xsec(pp->tt->aut) = (Br(t->au) + Br(t->au)) * xsec(pp->tt)
  // xsec(pp->tt->aut) = 11.82 * 2.0 * 2 * 0.428 * kappa^2 = 
  
  return branch;
}

double get_kappa(double br_limit){
  double kappa = TMath::Sqrt(br_limit / 0.428);
  return kappa;
}

void limit_plots(){
  string mode = "u";

  vector<double> x_axis, sigma_2_down, sigma_1_down, central, sigma_1_up, sigma_2_up, central_alt;
  vector <int> lumis = {1, 2, 3, 4, 5, 10, 20, 25, 50, 100, 200, 500, 1000};

  for(int lumi : lumis){
    string name = "combo_wd/weight_tune_5_cut_BDT_2_000_25_" + to_string(lumi) + "_CUT.root";
           name = "combo_wd_may_29/weight_tune_3_BDT_3_000_25_" + to_string(lumi) + "_tau.root";
           name = "combo_wd_may_29/weight_tune_5_BDT_3_000_25_" + to_string(lumi) + "_tau.root";
    string alt_name = "combo_wd/weight_tune_5_tac2_BDT_1_000_20_" + to_string(lumi) + "_CUT_tac.root";
           alt_name = "combo_wd_may_29/weight_tune_3_BDT_3_000_25_" + to_string(lumi) + "_tac.root";
           alt_name = "combo_wd_may_29/weight_tune_5_BDT_3_000_25_" + to_string(lumi) + "_tac.root";

    TFile * file = TFile::Open( name.c_str() );

    cout << "file " << file << endl;

    x_axis.push_back( 30. / lumi );
    //file->ls();
    TTree * tree = (TTree * ) file->Get("limit");
    //tree->Print();
  
    double lim;
    tree->SetBranchAddress("limit", &lim);
    tree->GetEntry(0); sigma_2_down.push_back( get_branch(lim) );
    tree->GetEntry(1); sigma_1_down.push_back( get_branch(lim) );
    tree->GetEntry(2); central.push_back     ( get_branch(lim) );
    // cout << lim << " " << get_branch(lim) << endl;
    double central_br    = get_branch(lim);
    double central_kappa = get_kappa(central_br);
    tree->GetEntry(3); sigma_1_up.push_back  ( get_branch(lim) );
    tree->GetEntry(4); sigma_2_up.push_back  ( get_branch(lim) );

    TFile * file_alt = TFile::Open( alt_name.c_str() );
    TTree * tree_alt = (TTree * ) file_alt->Get("limit");
    tree_alt->SetBranchAddress("limit", &lim);
    tree_alt->GetEntry(2); 
    // lim = lim * 0.00005 / (0.428 * pow(0.001, 2)) / 10;
    central_alt.push_back     ( get_branch(lim) );
    double central_alt_br    = get_branch(lim);
    double central_alt_kappa = get_kappa(central_alt_br);

    cout << 30. / lumi << " " << central_br << " " << central_kappa << " " << central_alt_br << " " << central_alt_kappa << endl;

    file->Close();
    file_alt->Close();
  }

  BrasilDrawer_fix * drawer = new BrasilDrawer_fix();
  drawer->xmin = 1.0;
  drawer->xmax = 30. ;
  drawer->ymin = 0.00000008;
  drawer->ymax = 0.00001;

  drawer->label_x = "Integrated Luminosity [ab^{-1}]";
  drawer->label_y = "Br(t #rightarrow #gamma q)";

  TCanvas * canv = drawer->draw_brasil_plot(&x_axis, &sigma_2_down, &sigma_1_down, &central, &sigma_1_up, &sigma_2_up, &central_alt);
  canv->Print( ("lumi_new_" + mode + ".png").c_str() );
  canv->Print( ("lumi_new_" + mode + ".pdf").c_str() );
}

















