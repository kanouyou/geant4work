#include <TFile.h>
#include "IAnalysis.h"

void IAnalysis::SetFile(std::string fileName) {
  fFileName = fileName;
  tName = "tree";
}

void IAnalysis::SetTreeName(std::string name) {
  tName = name;
}

TTree* IAnalysis::GetTree() {
  TFile* file = new TFile(fFileName.c_str());
  TTree* tree = (TTree*)file->Get(tName.c_str());
  
  position = new double[3];
  momentum = new double[3];
  tree->SetBranchAddress("pdgcode", &pdgcode);
  tree->SetBranchAddress("energy",  &energy);
  tree->SetBranchAddress( "x", &position[0]);
  tree->SetBranchAddress( "y", &position[1]);
  tree->SetBranchAddress( "z", &position[2]);
  tree->SetBranchAddress("px", &momentum[0]);
  tree->SetBranchAddress("py", &momentum[1]);
  tree->SetBranchAddress("pz", &momentum[2]);
  tree->SetBranchAddress("time", &time);

  return tree;
}

int IAnalysis::GetYield(int pdg) {
  TTree* tree = GetTree();
  int n = tree->GetEntries(Form("pdgcode==%i",pdg));
  return n;
}

double IAnalysis::GetMinimum(std::string entry) {
  TTree* tree = GetTree();
  double min = tree->GetMinimum(entry.c_str());
  return min;
}

double IAnalysis::GetMaximum(std::string entry) {
  TTree* tree = GetTree();
  double max = tree->GetMaximum(entry.c_str());
  return max;
}

