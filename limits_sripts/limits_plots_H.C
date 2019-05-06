
#include "mRoot.cpp"
#include "mRootStyle.cpp"

using namespace mRoot;

class BrasilDrawer_fix{
    public:
    TCanvas * draw_brasil_plot(vector<double> * x_axis, vector<double> * sigma_2_down, vector<double> * sigma_1_down, vector<double> * central, vector<double> * sigma_1_up, vector<double> * sigma_2_up, vector<double> * central_median){

      cout << 1 << endl;
    
      HistDrawer<TH1D> * drawer = new HistDrawer<TH1D>();
      drawer->logY = true;
      TCanvas * canvas = drawer->GetCanvas("limits");
      // canvas->SetLogx();
      canvas->SetLeftMargin(0.22); 

      cout << 2 << endl;

      TGraph * gr_central = new TGraph( central->size() );
      TGraph * gr_central_alt = new TGraph( central->size() );
      FillGraph gr_2sigma, gr_1sigma;

      cout << 3 << endl;

      for(int i = 0; i < central->size(); i++){
        gr_central->SetPoint( i, x_axis->at(i), central->at(i) );
        gr_central_alt->SetPoint(i, x_axis->at(i), central_median->at(i) );
        gr_2sigma.AddPoint( x_axis->at(i), sigma_2_down->at(i), sigma_2_up->at(i) );
        gr_1sigma.AddPoint( x_axis->at(i), sigma_1_down->at(i), sigma_1_up->at(i) );
      }

      cout << 4 << endl;

      TGraph * gr_1_sigma = gr_1sigma.GetGraph();
      TGraph * gr_2_sigma = gr_2sigma.GetGraph();

      cout << 5 << endl;

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

      cout << 6 << endl;

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

      cout << 7 << endl;


      gr_central_alt->SetLineStyle(2);
      gr_central_alt->SetLineColor(4);
      gr_central_alt->SetLineWidth(2);
      gr_central_alt->Draw("L");


      TLegend * leg  = new TLegend(0.45,0.58,1.00,0.88);
      leg->SetHeader("95% CL Expected Limits on:");
      leg->AddEntry(gr_central, "Br(H #rightarrow b #bar{s} )", "l");
      leg->AddEntry(gr_1_sigma, "Br(H #rightarrow b #bar{s} ) #pm 1 #sigma", "f");
      leg->AddEntry(gr_2_sigma, "Br(H #rightarrow b #bar{s} ) #pm 2 #sigma", "f");
      leg->AddEntry(gr_central_alt, "Br(H #rightarrow b #bar{d} )", "l");
      leg->Draw();


/*
      TLegend * leg  = new TLegend(0.45,0.58,1.00,0.88);
      leg->SetHeader("95% CL Expected Limits on:");
      leg->AddEntry(gr_central, "#lambda_{sbH}", "l");
      leg->AddEntry(gr_1_sigma, "#lambda_{sbH} #pm 1 #sigma", "f");
      leg->AddEntry(gr_2_sigma, "#lambda_{sbH} #pm 2 #sigma", "f");
      leg->AddEntry(gr_central_alt, "#lambda_{dbH}", "l");
      leg->Draw();
*/

      cout << 8 << " " << drawer << endl;

      string rightText = "#bf{FCC-hh Simulation (Delphes)}";
      auto rtext  = drawer->GetRightText( rightText );
      cout << rtext << endl;
      rtext->Draw() ;

      cout << 9 << endl;

       TLatex latex;
       latex.SetTextSize( 0.045 );
       latex.SetNDC();

      cout << 10 << endl;

      canvas->RedrawAxis();
      canvas->GetFrame()->SetBorderSize( 12 );
      return canvas;
    }

    int font;
    bool logY, logX;
    string label_x, label_y;
    double xmin, xmax, ymin, ymax;
  };

double get_branch(double kappa){
  double width_H_all       = 0.004088;

  double gamma_fcnc_tot_H_q1q2 = 0.14918;

  double kappa_0 = 0.1;
  double Coff = gamma_fcnc_tot_H_q1q2 / (kappa_0 * kappa_0) ;

  double branch = kappa * kappa * Coff / (width_H_all + 2 * kappa * kappa * Coff) ;
  return branch;
}

double get_kappa(double limit, string channel){
  double xsec_def = 2.;
  if(channel == "bdH") xsec_def = 2801./1968. + 1.;
  double Br_yy = 2.270 / 1000;
  xsec_def /= Br_yy;

  double xsec_fcnc = 0.001 * xsec_def * limit ;

  cout << limit << " " << xsec_fcnc << " " << xsec_fcnc / ( 3.27 * 100000 ) << endl;
  double kappa_2 = 0;

  if(channel == "bsH") kappa_2 = xsec_fcnc / ( 3.27 * 100000 ) ;
  if(channel == "bdH") kappa_2 = xsec_fcnc / ( 4.77 * 100000 ) ;

  double kappa = TMath::Sqrt( kappa_2 );
  return kappa;
}

void limits_plots_H(){
  string mode = "bsH";// "dbH"
  string mode_alt = "bdH";

  vector<double> x_axis, sigma_2_down, sigma_1_down, central, sigma_1_up, sigma_2_up, central_alt;
  vector<double>         sigma_2_down_lamb, sigma_1_down_lamb, central_lamb, sigma_1_up_lamb, sigma_2_up_lamb, central_alt_lamb;

  vector <int> lumis = {1, 2, 3, 4, 5, 10, 20, 25, 50, 100, 200, 500, 1000};

  // lumis = {1};

  for(int lumi : lumis){
    string name     = "H/weight_BDT_3b_003_xfactor_25_" + to_string(lumi) + "_" + mode + ".root";
    string alt_name = "H/weight_BDT_3b_003_xfactor_25_" + to_string(lumi) + "_" + mode_alt + ".root";

    TFile * file = TFile::Open( name.c_str() );

    cout << "file " << file << " " << name.c_str() << endl;

    x_axis.push_back( 30. / lumi );
    //file->ls();
    TTree * tree = (TTree * ) file->Get("limit");
    //tree->Print();
  
    double lim;
    tree->SetBranchAddress("limit", &lim);
    tree->GetEntry(0); sigma_2_down.push_back( get_branch( get_kappa(lim, mode) ) ); sigma_2_down_lamb.push_back( get_kappa(lim, mode) );
    tree->GetEntry(1); sigma_1_down.push_back( get_branch( get_kappa(lim, mode) ) ); sigma_1_down_lamb.push_back( get_kappa(lim, mode) );

    tree->GetEntry(2); 
    double central_lim = lim;
    double central_kappa = get_kappa(lim, mode);
    double central_branch = get_branch(central_kappa);
    central.push_back     ( central_branch );
    central_lamb.push_back( central_kappa  );

    tree->GetEntry(3); sigma_1_up.push_back  ( get_branch( get_kappa(lim, mode) ) ); sigma_1_up_lamb.push_back  ( get_kappa(lim, mode)  );
    tree->GetEntry(4); sigma_2_up.push_back  ( get_branch( get_kappa(lim, mode) ) ); sigma_2_up_lamb.push_back  ( get_kappa(lim, mode)  );


    TFile * file_alt = TFile::Open( alt_name.c_str() );
    TTree * tree_alt = (TTree * ) file_alt->Get("limit");
    tree_alt->SetBranchAddress("limit", &lim);
    tree_alt->GetEntry(2);
    double central_alt_br    = get_branch( get_kappa(lim, mode_alt) );
    double central_kappa_br  = get_kappa(lim, mode_alt);
    central_alt.push_back     ( central_alt_br );
    central_alt_lamb.push_back( central_kappa_br );

    cout << 30. / lumi << " kappa = " << central_kappa << " " << central_kappa_br << endl;
    cout << 30. / lumi << " br = " << central_branch << " " << central_alt_br << endl;

    file->Close();
  }

  BrasilDrawer_fix * drawer = new BrasilDrawer_fix();
  drawer->xmin = 30 / 1000.;
  drawer->xmax = 30. ;
  drawer->ymin = 0.006;
  drawer->ymax = 0.30;

  drawer->label_x = "Integrated Luminosity [ab^{-1}]";
  drawer->label_y = "Branching ratio";

  TCanvas * canv = drawer->draw_brasil_plot(&x_axis, &sigma_2_down, &sigma_1_down, &central, &sigma_1_up, &sigma_2_up, &central_alt);

  canv->Print( ("lumi_H_" + mode + ".png").c_str() );
  canv->Print( ("lumi_H_" + mode + ".pdf").c_str() );

  BrasilDrawer_fix * drawer_2 = new BrasilDrawer_fix();
  drawer_2->xmin = 30 / 1000.;
  drawer_2->xmax = 30. ;
  drawer_2->ymin = 0.001;
  drawer_2->ymax = 0.02;

  drawer_2->label_x = "Integrated Luminosity [ab^{-1}]";
  drawer_2->label_y = "#lambda";

  canv = drawer_2->draw_brasil_plot(&x_axis, &sigma_2_down_lamb, &sigma_1_down_lamb, &central_lamb, &sigma_1_up_lamb, &sigma_2_up_lamb, &central_alt_lamb);

  canv->Print( ("lumi_H_kappa_" + mode + ".png").c_str() );
  canv->Print( ("lumi_H_kappa_" + mode + ".pdf").c_str() );

}

















