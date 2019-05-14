
#include "shta_core.hh"

using namespace shta;
using namespace std;

struct Limit{
  public:
  Limit(){
  }

  void GetLimits(TH1D * hist){
    double CL_2sigma = 1. - 0.05;
    l_2s = root::get_th1d_limit_upper(hist, CL_2sigma + (1.-CL_2sigma)*0.5);
    c_2s = root::get_th1d_limit_upper(hist, 0.5);
    u_2s = root::get_th1d_limit_upper(hist, 0.05);
    double CL_1sigma = 1. - 0.3173;
    l_1s = root::get_th1d_limit_upper(hist, CL_1sigma + (1.-CL_1sigma)*0.5);
    c_1s = root::get_th1d_limit_upper(hist, 0.5);
    u_1s = root::get_th1d_limit_upper(hist, (1.-CL_1sigma)*0.5);
  }

  void Print(){
    cout << l_1s << " " << c_1s << " " << u_1s << endl;
    cout << l_2s << " " << c_2s << " " << u_2s << endl;
  }

  TTree * tree;
  std::string name;
  double l_1s, c_1s, u_1s, l_2s, c_2s, u_2s, def_val;
};



std::vector<shta::MarkovChain *> *  GenerateMC(Function * pdf, int n_chains, int lenght){
  shta::ProposalGauss * prop = new shta::ProposalGauss();
  prop->step_factor = 0.08;
  shta::MetropolisHastings mh = shta::MetropolisHastings(pdf, dynamic_cast<shta::ProposalFunction *>(prop) );
  std::vector<shta::MarkovChain *> * chains_from_true = new std::vector<shta::MarkovChain *>;

  for(int i = 0; i < n_chains; i++){
    shta::MarkovChain * chain = mh.ConstructChain(lenght);
    chains_from_true->push_back( chain );
  }
  return chains_from_true;
}

void WriteMC(string file_name, vector<shta::MarkovChain *> * chains, Function * pdf, bool force_rewrite){
  TFile * out_file = new TFile(file_name.c_str(), "READ");
  if(out_file->IsOpen() and not force_rewrite){
    msg("file already exist",  file_name,"; return");
    return;
  }
  delete out_file;
  out_file = new TFile(file_name.c_str(), "RECREATE");

  auto vars = pdf->used_variables;
  for(int i = 0; i < chains->size(); i++){
    chains->at(i)->Write("base_chain_" + std::to_string(i));

    for(auto var : vars){
      TH1D * hist = chains->at(i)->DrawVariable(var, 500);
      hist->Write();
    }

    out_file->cd();
  }

  auto pars = pdf->used_parameters;
  TTree * generation_tree = new TTree("gen_description", "gen_description");
  vector<string> names; 
  vector<double> values;
  for(auto var : pars){
    names.push_back(var->name);
    values.push_back(var->value);
  }

  generation_tree->Branch("gen_par_names", &names);
  generation_tree->Branch("gen_par_values", &values);

  int size = chains->size();
  chains->at(0)->FindChainWeightedLenght();
  int lenght = chains->at(0)->GetChainWeightedLenght();
  msg("n_chains, lenght = ", size, lenght);
  generation_tree->Branch("n_chains", &size);
  generation_tree->Branch("lenght", &lenght);

  generation_tree->Fill();
  generation_tree->Write();

  out_file->Close();
}

int main(int argc, char** argv){
  /*

double N_obs_def  = 94;
double N_back_def = 22.01 + 2.09 + 13.52;
double N_sm_def   = 57.79;
double Br_H_ZZ_SM = 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026;
double G_SM_tot = 0.004088;
double G_ZZ_SM  = G_SM_tot * Br_H_ZZ_SM;
double lumi = 35.9 * 1000.;

  double G_FNCN     = 14.918 * lambda*lambda;
  double Br_H_ZZ_FCNC = G_ZZ_SM / (G_SM_tot + 2*G_FNCN) ;

  double Br_H_ZZ_FCNC = 0.004515839999999999 * 0.00010628799999999998 / (0.004088 + 2 * 14.918 * lambda*lambda) ;


  double N_fcnc_def = eff_proc * factor_proc * lambda*lambda * lumi * Br_H_ZZ_SM;
  N_fcnc_def = 4.81 * 10000 * 0.178593392464 * 35.9 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 36209.022938384296 * lambda*lambda
               2.32 * 10000 * 0.244923069982 * 35.9 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 23951.02047389787 * lambda*lambda

  $qq \rightarrow ZZ$   & 1.17        &  3.99  \\
  $gg \rightarrow ZZ$   & 1.13        &  4.03  \\
  ``$Z+X$''             & 1.11        &  3.02  \\
  SM Higgs              & 1.13        &  3.02  \\
  FCNC Higgs ($dbH$)    & 1.10        &  2.45  \\
  FCNC Higgs ($sbH$)    & 1.13        &  2.88  \\

  (1.17 * 22 + 1.13 * 2.09 + 1.11 * 13.52) / (22 + 2.09 + 13.52) = 1.1462084551980856
  (3.99 * 22 + 4.03 * 2.09 + 3.02 * 13.52) / (22 + 2.09 + 13.52) = 3.6435283169369845

  3 ab$^{-1}$
  1.10 * 4.81 * 10000 * 0.178593392464 * 3000 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 3328406.008263739 * lambda*lambda
  1.13 * 2.32 * 10000 * 0.244923069982 * 3000 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 2261670.1784544224 * lambda*lambda
  N_back = 1.1462084551980856 * 37.62 * 3000 / (35.9 ) = 3603.3728761464045
  N_sm   = 1.13 * 57.79 * 3000 * 1000. / (35.9 * 1000.) = 5457.050139275764

  15 ab$^{-1}$
  2.45 * 4.81 * 10000 * 0.178593392464 * 15000 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 37066339.63748253 * lambda*lambda
  2.88 * 2.32 * 10000 * 0.244923069982 * 15000 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 28821283.69003866 * lambda*lambda
  N_back = 3.6435283169369845 * 37.62 * 15000 * 1000. / (35.9 * 1000.) = 57271.39357235488
  N_sm   = 3.02 * 57.79 * 15000 * 1000. / (35.9 * 1000.) = 72921.643454039

  double N_back_point = N_back_def - (N_back_point_i - 0.5) * 5.5 * N_back_def*0.0736;
  double N_sm_point   = N_sm_def   - (N_sm_point_i - 0.5)   * 5.5 * N_sm_def*0.0736;
  double N_fcnc_point = N_fcnc_def - (N_fcnc_point_i - 0.5) * 5.5 * N_fcnc_def*0.23;
       
    
  double N_sm   = N_sm_point    / Br_H_ZZ_SM * Br_H_ZZ_FCNC;
  double N_fcnc = N_fcnc_point  / Br_H_ZZ_SM * Br_H_ZZ_FCNC;

  return TMath::Gaus(N_obs_def, N_back_point + N_sm + N_fcnc, sqrt(N_obs_def)) 
         * TMath::Gaus(N_back_point, N_back_def, N_back_def*0.0736)
         * TMath::Gaus(N_sm_point,   N_sm_def,   N_sm_def*0.0736)
         * TMath::Gaus(N_fcnc_point, N_fcnc_def, N_fcnc_def*0.23)
         ;

  // bdH
  factor_proc = 4.81 * 10000;
  eff_proc    = 0.178593392464;
  if(false){ // bsH
    factor_proc = 2.32 * 10000;
    eff_proc    = 0.244923069982;
  }
  */

  shta::FunctionBuilder fbuilder;
/*
  auto N_back = fbuilder.DefineVariable( "N_back"  ,  100, 20., 60,  shta::vartype::VARIABLE );
  auto N_sm   = fbuilder.DefineVariable( "N_sm"    ,  50,  20., 80,  shta::vartype::VARIABLE );
  auto N_fcnc = fbuilder.DefineVariable( "N_fcnc"  ,  50,   0., 5000,  shta::vartype::VARIABLE );
  auto lambda = fbuilder.DefineVariable( "lambda"  ,  0.01,   0., 0.02,  shta::vartype::VARIABLE );
  
  auto PDF_BASE = fbuilder.DefineFunction("pdf_true",  "TMath::Gaus(94, N_back + (N_sm + N_fcnc) / 0.00011741183999999998 * 0.004515839999999999 * 0.00010628799999999998 / (0.004088 + 2 * 14.918 * lambda*lambda), sqrt(94)) * TMath::Gaus(N_back, 37.62, 37.62*0.0736) * TMath::Gaus(N_sm,   57.79,   57.79*0.0736) * TMath::Gaus(N_fcnc, 36209.022938384296 * lambda*lambda, 36209.022938384296 * lambda*lambda*0.20)");
*/


/*
  3 ab$^{-1}$
  1.10 * 4.81 * 10000 * 0.178593392464 * 3000 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 3328406.008263739 * lambda*lambda
  1.13 * 2.32 * 10000 * 0.244923069982 * 3000 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 2261670.1784544224 * lambda*lambda
  N_back = 1.1462084551980856 * 37.62 * 3000 * 1000. / (35.9 * 1000.) = 3603.3728761464045
  N_sm   = 1.13 * 57.79 * 3000 * 1000. / (35.9 * 1000.) = 5457.050139275764
  N_obs  = 3603.3728761464045 + 5457.050139275764

  0.00092288 0.00267996 0.00413332
  0.0008978 0.00264032 0.00407284

  fcnc_error = 0.23 / pow(3000 / 35.9, 0.5)
*/


  auto N_back = fbuilder.DefineVariable( "N_back"  ,  100, 2000., 5000,  shta::vartype::VARIABLE );
  auto N_sm   = fbuilder.DefineVariable( "N_sm"    ,  50,  4000., 8000,  shta::vartype::VARIABLE );
  auto N_fcnc = fbuilder.DefineVariable( "N_fcnc"  ,  50,   0., 250,  shta::vartype::VARIABLE );
  auto lambda = fbuilder.DefineVariable( "lambda"  ,  0.01,   0., 0.02,  shta::vartype::VARIABLE );

  auto PDF_BASE = fbuilder.DefineFunction("pdf_true",  "TMath::Gaus(9060.42301542217, N_back + (N_sm + N_fcnc) / 0.00011741183999999998 * 0.004515839999999999 * 0.00010628799999999998 / (0.004088 + 2 * 14.918 * lambda*lambda), sqrt(9060.42301542217)) * TMath::Gaus(N_back, 3603, 3603*0.0736 * 0.5) * TMath::Gaus(N_sm,  5457,   5457*0.0736 * 0.5) * TMath::Gaus(N_fcnc, 3328406.008263739 * lambda*lambda, 3328406.008263739 * lambda*lambda*0.23 * 0.5)");


/*
  15 ab$^{-1}$
  2.45 * 4.81 * 10000 * 0.178593392464 * 15000 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 37066339.63748253 * lambda*lambda
  2.88 * 2.32 * 10000 * 0.244923069982 * 15000 * 1000. * 4 * 3.36 * 3.36 * 0.01 * 0.01 * 0.026 = 28821283.69003866 * lambda*lambda
  N_back = 3.6435283169369845 * 37.62 * 15000 * 1000. / (35.9 * 1000.) = 57271.39357235488
  N_sm   = 3.02 * 57.79 * 15000 * 1000. / (35.9 * 1000.) = 72921.643454039
  N_obs  = 57271.39357235488 + 72921.643454039

  0.00108196 0.00369244 0.0058824
  0.0013695 0.00369832 0.00576784

  auto N_back = fbuilder.DefineVariable( "N_back"  ,  57271,  40000, 80000,  shta::vartype::VARIABLE );
  auto N_sm   = fbuilder.DefineVariable( "N_sm"    ,  72921,  60000, 95000,  shta::vartype::VARIABLE );
  auto N_fcnc = fbuilder.DefineVariable( "N_fcnc"  ,  500,    0., 3000,  shta::vartype::VARIABLE );
  auto lambda = fbuilder.DefineVariable( "lambda"  ,  0.001,   0., 0.01,  shta::vartype::VARIABLE );

  auto PDF_BASE = fbuilder.DefineFunction("pdf_true",  "TMath::Gaus(130193.03702639388, N_back + (N_sm + N_fcnc) / 0.00011741183999999998 * 0.004515839999999999 * 0.00010628799999999998 / (0.004088 + 2 * 14.918 * lambda*lambda), sqrt(130193)) * TMath::Gaus(N_back, 57271.39357235488, 57271.39357235488*0.0736) * TMath::Gaus(N_sm,  72921.643454039,   72921.643454039*0.0736) * TMath::Gaus(N_fcnc, 28821283.69003866 * lambda*lambda, 28821283.69003866 * lambda*lambda*0.23)");
*/


  msg("build model ... ");
  fbuilder.BuildFunctions("negative_scripts");

  msg("generate and write mc data ... ");
  int number_of_chains = 1;
  int chains_lenght    = 6000000;

  auto chains_A = GenerateMC(PDF_BASE, number_of_chains, chains_lenght);
  for(auto chain : *chains_A) chain->Print();
  WriteMC("ns_0_PDF_BASE_a.root", chains_A, PDF_BASE, true);

  int limit_hist_bins = 500000;
  TH1D * hist = lambda->GetTH1D(limit_hist_bins);
  chains_A->at(0)->FillHist( lambda->name, hist );
  Limit * limit = new Limit();
  limit->GetLimits(hist);
  limit->Print();

  return 0;
}

/*

0.014  bdH

0.014 * 0.014 * 14.918 / (2 * 0.014 * 0.014 * 14.918 + 0.004)

0.013 * 0.013 * 14.918 / (2 * 0.013 * 0.013 * 14.918 + 0.004)

0.013   bsH

*/







