
TGraphErrors * get_graph_for_cone(double R_edge, TH2D * hist, int N_pt_points){
  TGraphErrors * gr = new TGraphErrors (100);

  for(int x = 1; x <= N_pt_points; x++){
    double pt = 1000. / N_pt_points * x - 1000. / N_pt_points * 0.5;

    double in_cone  = 0;
    double out_cone = 0;
    for(int y = 1; y <= 1000; y++){
      double R = 10. / 1000 * y - 10. / 1000 * 0.5;
      double entries = hist->GetBinContent(x, y);
      if(R < R_edge) in_cone  += entries;
      else        out_cone += entries;
    }
    cout << pt << " " << in_cone << " " << out_cone << endl;

    double frac_in_cone     = 0, frac_in_cone_err = 0;
    if(out_cone + out_cone > 1){
      frac_in_cone     = in_cone / (in_cone + out_cone);
      frac_in_cone_err = TMath::Sqrt(in_cone) / (in_cone + out_cone);
    }

    gr->SetPoint( x, pt, frac_in_cone );
    gr->SetPointError( x, 1000. / N_pt_points / 2., frac_in_cone_err );
  }

  return gr;
}

TGraphErrors * get_graph_cum(double R_edge, TH2D * hist, int N_pt_points){
  TGraphErrors * gr = new TGraphErrors (100);

  for(int x = 1; x <= N_pt_points; x++){
    double pt = 1000. / N_pt_points * x - 1000. / N_pt_points * 0.5;

    int binx1, binx2, biny1, biny2;
    
    binx1 = hist->GetXaxis()->FindBin( pt );
    binx2 = N_pt_points;
    biny1 = hist->GetYaxis()->FindBin( 0. );
    biny2 = hist->GetYaxis()->FindBin( R_edge );
    double N_ussefull = hist->Integral(binx1, binx2, biny1, biny2);
    
    binx1 = hist->GetXaxis()->FindBin( pt );
    binx2 = N_pt_points;
    biny1 = hist->GetYaxis()->FindBin( 0. );
    biny2 = hist->GetYaxis()->FindBin( hist->GetYaxis()->GetXmax() );
    double N_pt = hist->Integral(binx1, binx2, biny1, biny2);

    
    gr->SetPoint( x, pt, N_ussefull / N_pt );
    gr->SetPointError( x, 1000. / N_pt_points / 2., TMath::Sqrt(N_ussefull) / N_pt );
  }

  return gr;
}

void cone_drawer(){

  TFile * file_1 = TFile::Open("check_tree_2.root");
  TTree * tree = (TTree*) file_1->Get("events");
  
  double delta_R, gen_fcnc_t_pt;
  double gen_fcnc_b1_phi, gen_fcnc_b2_phi, gen_fcnc_b1_eta, gen_fcnc_b2_eta;
  tree->SetBranchAddress("delta_R", &delta_R);
  tree->SetBranchAddress("gen_fcnc_b1_eta", &gen_fcnc_b1_eta);
  tree->SetBranchAddress("gen_fcnc_b2_eta", &gen_fcnc_b2_eta);
  tree->SetBranchAddress("gen_fcnc_b1_phi", &gen_fcnc_b1_phi);
  tree->SetBranchAddress("gen_fcnc_b2_phi", &gen_fcnc_b2_phi);

  tree->SetBranchAddress("gen_fcnc_t_pt", &gen_fcnc_t_pt);
  
  int N_pt_points = 20;
  TH2D hist_2d("h2d", "h2d", N_pt_points, 0, 1000, 1000, 0, 10);

  int n_events = tree->GetEntries();
  for(int i = 0; i < n_events; i ++){
    tree->GetEvent( i );

    double dR = sqrt( pow(gen_fcnc_b1_phi - gen_fcnc_b2_phi, 2) + pow(gen_fcnc_b1_eta- gen_fcnc_b2_eta, 2) );
    hist_2d.Fill( gen_fcnc_t_pt, delta_R);
    // hist_2d.Fill( gen_fcnc_t_pt, dR);
  }
  
  TGraphErrors * gr_1 = get_graph_for_cone(0.8, &hist_2d, N_pt_points);
  TGraphErrors * gr_3 = get_graph_for_cone(0.6, &hist_2d, N_pt_points);
  TGraphErrors * gr_5 = get_graph_for_cone(0.4, &hist_2d, N_pt_points);
  
  gr_1 = get_graph_cum(0.8, &hist_2d, N_pt_points);
  gr_3 = get_graph_cum(0.6, &hist_2d, N_pt_points);
  gr_5 = get_graph_cum(0.4, &hist_2d, N_pt_points);
  
  
  
  TGraphErrors * gr_2 = new TGraphErrors(100);
  TGraphErrors * gr_4 = new TGraphErrors(100);
  TGraphErrors * gr_6 = new TGraphErrors(100);
  
  TCanvas * canv = new TCanvas("canv", "canv", 640, 480);
  gr_1->SetMarkerColor(2);
  gr_2->SetMarkerColor(2);

  gr_3->SetMarkerColor(4);
  gr_4->SetMarkerColor(4);
  gr_3->SetMarkerStyle(21);
  gr_4->SetMarkerStyle(22);

  gr_5->SetMarkerColor(3);
  gr_6->SetMarkerColor(3);
  gr_5->SetMarkerStyle(21);
  gr_6->SetMarkerStyle(22);

  gr_1->SetMarkerStyle(21);
  gr_1->SetMarkerSize(0.6);
  gr_2->SetMarkerStyle(22);
  gr_2->SetMarkerSize(0.6);
  gr_1->SetTitle("");
  gr_1->GetXaxis()->SetTitle("p_{T}(t), [GeV]");
  gr_1->GetYaxis()->SetTitle("fraction of events with #Delta R(#vec{u}, #vec{b}, #vec{b}) < R_{0}");

  gr_1->Draw("APC");
  gr_1->GetXaxis()->SetLimits(0, 1000);

   TLegend * leg = new TLegend(0.559561,0.0979955,0.901254,0.469933);
   //leg->AddEntry(gr_2,"R_{0} = 0.8, no p_{T}(t) cut","p");
   leg->AddEntry(gr_1,"R_{0} = 0.8","p");
   //leg->AddEntry(gr_4,"R_{0} = 0.6, no p_{T}(t) cut","p");
   leg->AddEntry(gr_3,"R_{0} = 0.6","p");
   //leg->AddEntry(gr_6,"R_{0} = 0.4, no p_{T}(t) cut","p");
   leg->AddEntry(gr_5,"R_{0} = 0.4","p");
   //leg->SetHeader("For |#eta| < 3, p_{T} > 30 [GeV]");
   leg->Draw();

  //gr_2->Draw("P same");
  gr_3->Draw("P same");
  //gr_4->Draw("P same");
  gr_5->Draw("P same");
  //gr_6->Draw("P same");



  canv->Update();
  canv->Print("delta_r.png");
}















