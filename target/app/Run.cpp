#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TText.h>
#include "IPlot.h"

using namespace std;

int main(int argc, char** argv) {
  
  TApplication* app = new TApplication("app", &argc, argv);
  
  const int n = 8;
  string file[n] = {"JAM_BERT", "JAM_INCL", "QGSP_BERT", "QGSP_INCL", "FTFP_BERT",
                    "QGSP_BIC", "FTFP_INCL", "FTFP_BIC"};

  int pdgcode = -211;
  int proton  = 100*1000;

  int color[n] = {kBlack, kRed, kAzure+8, kGreen+2, kOrange+7, kBlue, kMagenta, kYellow+2};

  IPlot* ana[n];
  TH1F* hist[n];
  
  TCanvas* c0 = new TCanvas("pion", "pion", 600, 500);
  c0->SetTicks(1,1);
  
  gStyle->SetTitleSize(0.045, "xy");
  gStyle->SetLabelSize( 0.04, "xy");
  gStyle->SetOptStat(0);
  gStyle->SetNumberContours(99);
  gStyle->SetPalette(51);

  for (int i=0; i<n; i++) {
    ana[i]  = new IPlot(file[i]+".root");
	//ana[i]->SetScale(1./proton);
	if (i<2) 
	  ana[i]->SetTreeName("RooTracker");
	hist[i] = (TH1F*)ana[i]->GetMomentumHist(pdgcode);
	hist[i]->SetLineWidth(2);
	hist[i]->SetLineColor(color[i]);
	hist[i]->SetFillColor(color[i]);
	if (i==0) hist[i]->Draw("e2");
	else      hist[i]->Draw("e2same");
  }
  hist[0]->GetXaxis()->SetTitleSize(0.05);
  hist[0]->GetXaxis()->SetLabelSize(0.045);
  hist[0]->GetYaxis()->SetTitleSize(0.05);
  hist[0]->GetYaxis()->SetLabelSize(0.045);
  hist[0]->SetTitle("; Momentum [MeV/c]; #pi^{-} [event]");

  TLegend* lg = new TLegend(0.7, 0.7, 0.89, 0.89);
  lg->SetTextSize(0.045);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  for (int i=0; i<n; i++)
    lg->AddEntry(hist[i], file[i].c_str(), "lfe");
  lg->Draw();
  
  //~~~~~~~~~~~~~~~~~~~
  // print
  //~~~~~~~~~~~~~~~~~~~
  double yield[n];
  for (int i=0; i<n; i++) {
    yield[i] = ana[i]->GetYield(pdgcode) / static_cast<double>(proton);
    cout << "Model: " << file[i] << " ; Pion Yield: " << yield[i] << " [pi/p]" << endl;
  }
  
  TCanvas* c1 = new TCanvas("dis", "dis", 600, 500);
  c1->SetTicks(1,1);
  c1->SetRightMargin(0.17);
  
  // y axis: cascade model (JAM, QGSP, FTFP)
  // x axis: inter cascade model? (BERT, INCLXX, BIC)
  string casHigh[3] = { "JAM",   "QGSP", "FTFP"};
  string casLow [3] = {"BERT", "INCLXX",  "BIC"};
  double x[3] = {0.5, 2., 3.5};

  TH2F* h2 = new TH2F("analysis", "analysis", 3, 0, 4, 3, 0, 4);
  h2->Fill(1., 1., yield[0]);
  h2->Fill(2., 1., yield[1]);
  h2->Fill(3., 1., 0.0);
  h2->Fill(1., 2., yield[2]);
  h2->Fill(2., 2., yield[3]);
  h2->Fill(3., 2., yield[5]);
  h2->Fill(1., 3., yield[4]);
  h2->Fill(2., 3., yield[6]);
  h2->Fill(3., 3., yield[7]);
  h2->GetXaxis()->SetLabelSize(0);
  h2->GetYaxis()->SetLabelSize(0);
  h2->GetZaxis()->SetLabelSize(0.045);
  h2->GetZaxis()->SetTitleSize(0.06);
  h2->SetTitle("Physics Model; ; ; Pion Yield [#pi^{-}/proton]");
  h2->Draw("colz text");
  
  TText* text = new TText();
  text->SetTextSize(0.045);
  text->SetTextAlign(22);
  text->SetTextFont(42);
  for (int i=0; i<3; i++) {
    text->SetTextAngle(0);
	text->DrawText(x[i], -0.2, casLow[i].c_str());
    text->SetTextAngle(90);
	text->DrawText(-0.2, x[i], casHigh[i].c_str());
  }

  app->Run();

  return 0;
}
