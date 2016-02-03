#ifndef ECLTESTTREEMODULE_H
#define ECLTESTTREEMODULE_H

#include </home/usr/vitaly/basf2/release/framework/datastore/include/StoreArray.h>
#include </home/usr/vitaly/basf2/release/rawdata/dataobjects/include/RawDataBlock.h>
#include </home/usr/vitaly/basf2/release/rawdata/dataobjects/include/RawCOPPER.h>
#include </home/usr/vitaly/basf2/release/rawdata/dataobjects/include/RawECL.h>

//#include <framework/core/Module.h>
#include <framework/core/HistoModule.h>

#include <TH1I.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>

#define MODULENAME ECLTestTreeModule
namespace Belle2{
  namespace ECL{

//  class MODULENAME : public Module {
  class MODULENAME : public HistoModule {
  public:
    MODULENAME();
    virtual ~MODULENAME();

    virtual void initialize();
    virtual void beginRun();
    virtual void event();
    virtual void endRun();
    virtual void terminate();

    virtual void defineHisto();

    void fillECLTTree();
    void readECLEvent(RawCOPPER* raw_copper, int evtn);
  protected:
    int m_AmpMin;
    int m_AmpMax;
//    std::string m_ROOTFile;
    int m_NEvents;
    int m_SkipEvents;
//    std::string m_ecl_tree_file;
  private:
    int m_evtn;
    int m_shaper;
    int m_channel;
    int m_sh_mask;
    int m_ch_adc_num;
    int m_samplnum;
    int m_dspnum;
    int m_trig_phase;
    int m_ch_mask;
    int m_trig_tag;
    int m_adc_mask;
    int m_time;
    int m_flag;
    int m_amp;
    std::vector<int> m_time_v;
    std::vector<int> m_flag_v;
    std::vector<int> m_amp_v;
    int m_num_events;

//    TFile* m_ecl_root_file;

//    TH1I* m_amp_hist;
    TTree* m_ecl_tree;
    TCanvas* c1;
////    TChain* m_ecl_tree;
//    TGraph* m_amp_sh_scatter_plot;
  };
 }//namespace ECL
}//namespace Belle2

#endif

