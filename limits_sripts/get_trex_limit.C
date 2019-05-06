
double get_br(double limit ){
  // limit = #sigma_limit / #sigma_MG
  double xsec_MG = 11.82 * 2.0 * 2.0 * 0.428 * pow(0.01, 2);
  double xsec = limit * xsec_MG; // * 0.1 * 3069.; // 300 * 10^-6 -> 60 * 10^-6
  
  // #sigma_ttbar * 2 * Br_limit = #sigma_limit
  // 11.82 +- 0.07641 pb    = xsec tt pt   > 1000
  double branch = xsec / (11.82 * 2.0 * 2.0); // 6 * 10^-6

  // 2000 -> 100 = 1/20 3069 / 20

  // xsec(pp->tt->aut) = (Br(t->au) + Br(t->au)) * xsec(pp->tt)
  // xsec(pp->tt->aut) = 11.82 * 2.0 * 2 * 0.428 * kappa^2 = 
  
  return branch;
}

double get_kappa(double limit ){
  double branch = get_br( limit );

  // Br = 0.428 * kappa^2
  double kappa = TMath::Sqrt( branch / 0.428 );

  return kappa;
}

void get_trex_limit(string path){
  //path = "TRExFitter/OUTPUT/fcnc_apr_03_tune_2_BDT_0_000/tua/Limits/tua.root";
  //path = "TRExFitter/OUTPUT/fcnc_apr_03_tune_2_BDT_1_000/tua/Limits/tua.root";
  //path = "TRExFitter/OUTPUT/fcnc_apr_03_tune_2_BDT_2_000/tua/Limits/tua.root";
 
  //path = "OUTPUT/fcnc_may_05_tune_3_BDT_2_000/tua/Limits/tua.root";

  TFile * file = TFile::Open( path.c_str() );

  TH1D * hist = (TH1D*)file->Get("limit");
  double  expected = hist->GetBinContent(2);
  double sigma_2_p = hist->GetBinContent(3);
  double sigma_1_p = hist->GetBinContent(4);
  double sigma_1_m = hist->GetBinContent(5);
  double sigma_2_m = hist->GetBinContent(6);

  double  expected_br = get_br( expected );
  double sigma_2_p_br = get_br(sigma_2_p );
  double sigma_1_p_br = get_br(sigma_1_p );
  double sigma_1_m_br = get_br(sigma_1_m );
  double sigma_2_m_br = get_br(sigma_2_m );

  double  expected_kappa = get_kappa( expected );
  double sigma_2_p_kappa = get_kappa( sigma_2_p );
  double sigma_1_p_kappa = get_kappa( sigma_1_p );
  double sigma_1_m_kappa = get_kappa( sigma_1_m );
  double sigma_2_m_kappa = get_kappa( sigma_2_m );

  cout << "Raw limits " << sigma_2_m << " " << sigma_1_m << " ";
  cout << expected << " " << sigma_1_p << " " << sigma_2_p << endl;

  cout << "Br limits "  << sigma_2_m_br << " " << sigma_1_m_br << " ";
  cout << expected_br << " " << sigma_1_p_br << " " << sigma_2_p_br << endl;

  cout << "kappa limits "  << sigma_2_m_kappa << " " << sigma_1_m_kappa << " ";
  cout << expected_kappa << " " << sigma_1_p_kappa << " " << sigma_2_p_kappa << endl;
}





