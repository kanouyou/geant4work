#include <cmath>
#include <TTree.h>
#include <TParticle.h>
#include "IPlot.h"

IPlot::IPlot(std::string fileName) : IAnalysis() {
  fScale = 1.;
  SetFile(fileName);
}

void IPlot::SetScale(double scale) {
  fScale = scale;
}

TH1F* IPlot::GetMomentumHist(int pdg) {
  TTree* tree = (TTree*)GetTree();
  TH1F*  hist = new TH1F(Form("p_%i",pdg), Form("p_%i",pdg), 128, 0, 1000);
  
  TParticle* particle = new TParticle();
  particle->SetPdgCode(pdg);
  double mass = particle->GetMass()*1000.;
  
  double p;

  for (int i=0; i<tree->GetEntries(); i++) {
    tree->GetEntry(i);
	if ( pdgcode == pdg ) {
	  if (tName=="tree")
	    //hist->Fill(energy);
	    hist->Fill(sqrt(pow(momentum[0],2) + pow(momentum[1],2) + pow(momentum[2],2)), fScale);
      else if (tName=="RooTracker") {
	    p = sqrt(pow((mass + energy),2) - pow(mass,2));
		hist->Fill(p*sqrt(pow(momentum[0],2) + pow(momentum[1],2) + pow(momentum[2],2)), fScale);
	    //hist->Fill(energy);
	  }
	}
  }

  return hist;
}

