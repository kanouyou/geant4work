#ifndef IPlot_HH
#define IPlot_HH

#include <TH1F.h>
#include "IAnalysis.h"

class IPlot : public IAnalysis {
  public:
    IPlot(std::string fileName);
    ~IPlot() {}
    TH1F* GetMomentumHist(int pdg);
    void  SetScale(double scale);

  private:
    double fScale;
};

#endif
