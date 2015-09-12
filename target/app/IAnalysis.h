#ifndef IAnalysis_HH
#define IAnalysis_HH

#include <string>
#include <TH1F.h>
#include <TTree.h>

class IAnalysis {
  public:
    IAnalysis() {}
	~IAnalysis() {}
    void   SetFile(std::string fileName);
    TTree* GetTree();
	void   SetTreeName(std::string name);
    int    GetYield(int pdg);
    double GetMinimum(std::string entry);
	double GetMaximum(std::string entry);

  protected:
    int     pdgcode;
	double  energy;
	double* position;
	double* momentum;
	double  time;
    std::string tName;
  
  private:
    std::string fFileName;
};

#endif
