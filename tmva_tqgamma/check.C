
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootStyle.cpp"

using namespace mRoot;

void check(){
   THStack *hs = new THStack();
cout << hs->GetXaxis() << endl;

   TH1D *h1 = new TH1D("h1","test hstack",10,-4,4);
   h1->FillRandom("gaus",20000);
   h1->SetFillColor(kRed);
   hs->Add(h1);
   
   TCanvas *cs = new TCanvas("cs","cs",10,10,700,900);

 cout << hs->GetXaxis() << endl; 
   hs->Draw();
 cout << hs->GetXaxis() << endl;  hs->GetXaxis()->SetTitle("123");
   hs->Draw("nostack");
 cout << hs->GetXaxis() << endl;  hs->GetXaxis()->SetTitle("123");
   hs->Draw("nostackb");
 cout << hs->GetXaxis() << endl;  hs->GetXaxis()->SetTitle("123");
   hs->Draw("lego1");

 cout << hs->GetXaxis() << endl;  hs->GetXaxis()->SetTitle("123");


set_style_FCC();
HistDrawer * drawer = new HistDrawer();
TCanvas * canvas = drawer->GetCanvas( "asd.png" );
drawer->backgrounds.push_back( h1 );
drawer->DrawHistsTMVA();

}
