#include </home/usr/vitaly/basf2/release/ecl/modules/eclTestTree/include/eclTestTreeModule.h>

using namespace std;
using namespace Belle2;
using namespace ECL;

REG_MODULE(ECLTestTree)

MODULENAME::MODULENAME() : HistoModule(){
//  string default_ROOTFile = string("input.root");
//  string default_m_ecl_tree_file = string("");
  setDescription("The module reads RawECL data from the DataStore and save a simple TTree to a file.");
  addParam("AmpMin",m_AmpMin,"Low threshold for amplitude",50);
  addParam("AmpMax",m_AmpMax,"High threshold for amplitude",3000);
//  addParam("ROOTFile",m_ROOTFile,"Input ROOT file",default_ROOTFile);
  addParam("NEvents",m_NEvents,"How many events to process",100000);
  addParam("SkipEvents",m_SkipEvents,"How many events to skip",0);
//  addParam("eclTTree",m_ecl_tree_file,"File with ECL TTree",default_m_ecl_tree_file);

//  m_ecl_root_file = TFile::Open("ecl_hists.root","RECREATE");
}

MODULENAME::~MODULENAME(){
}

void MODULENAME::defineHisto(){
//  m_amp_hist = new TH1I("amp_hist","amp_hist",100,-100,100);
//  m_amp_hist->Print();
//  if(m_ecl_tree_file == string("")){
    B2DEBUG(50,"Make default Tree");
    m_ecl_tree = new TTree("tree","tree");
    m_ecl_tree->Branch("time",&m_time,"time/I");
    m_ecl_tree->Branch("flag",&m_flag,"flag/I");
    m_ecl_tree->Branch("amp",&m_amp,"amp/I");
    m_ecl_tree->Branch("ch",&m_channel,"ch/I");
    m_ecl_tree->Branch("sh",&m_shaper,"sh/I");
    m_ecl_tree->Branch("evtn",&m_evtn,"evtn/I");
//  } else{
//    TFile* rfile = TFile::Open(m_ecl_tree_file.c_str());
//    m_ecl_tree = (TTree*)rfile->Get("tree");
//  }
//  m_amp_sh_scatter_plot = new TGraph();
    c1 = new TCanvas("c1","c1",800,600);
    c1->cd();
}

void MODULENAME::initialize(){
//  m_amp_hist = new TH1I("amp_hist","amp_hist",100,-100,100);
//  m_amp_hist->Print();
  StoreArray<RawCOPPER>::required();
  REG_HISTOGRAM
}

void MODULENAME::beginRun(){
  m_num_events = 0;
}

void MODULENAME::fillECLTTree(){

}

void MODULENAME::readECLEvent(RawCOPPER* raw_copper, int evtn){
  int sh_mask,shnum,buf_lenght,event_lenght,curmask;
  int pos,ich,iadc;// position in buffer, channel iterator, ADC iteraator;
  int ID;//current channel mask, copper ID;

  B2DEBUG(150,"readECLEvent:");
  unsigned int evnum = raw_copper->GetEveNo(evtn);
  B2DEBUG(150,"evnum " << evnum);
  ID = (int)raw_copper->GetCOPPERNodeId(evtn) - 83886081 + 1;// some magic
  B2DEBUG(150,"ID " << ID);

  for(int finesse_num=0; finesse_num<4; finesse_num++){
    B2INFO("Event number: " << evnum << ", FINESSE number: " << finesse_num+1);
    buf_lenght = raw_copper->GetDetectorNwords(evtn,finesse_num);
    if(buf_lenght<=0){
      B2DEBUG (50,"No data in this FINESSE. Skip it.");
      continue;
    }
    B2DEBUG(50,"FEE Buffer length is:" << buf_lenght);
    int* buf = raw_copper->GetDetectorBuffer(evtn,finesse_num);
    B2DEBUG(50,"buf " << *buf);
    pos = 0;//position of the COLLECTOR header (1 word)
    if(pos == buf_lenght){B2DEBUG (50,"Reached the end of the FINESSE buffer"); continue;}
    sh_mask = buf[pos] & 0xFFF; //DSP mask

    for(shnum=0; shnum<12; shnum++){
      pos++; if(pos == buf_lenght){B2DEBUG (50,"Reached the end of the FINESSE buffer"); continue;}
      event_lenght = buf[pos]&0xFFFF;// amount of words in DATA section (without COLLECTOR HEADER)
      pos++; if(pos == buf_lenght){B2DEBUG (50,"Reached the end of the FINESSE buffer"); continue;}
      curmask = pow(2,shnum);
      m_evtn = evnum;
      m_shaper = (shnum+1)+(ID-1)*24+finesse_num*12;
      m_sh_mask = sh_mask;

      m_ch_adc_num = (buf[pos]>>24)&0x1F;//number of channels with ADC data
      m_samplnum = (buf[pos]>>16)&0x7F;  //ADC samples per channel
      m_dspnum = (buf[pos]>>8)&0x1F;     //number of active channels in DSP
      m_trig_phase = buf[pos]&0xFF;      //trigger phase

      pos++; if(pos == buf_lenght){B2DEBUG (50,"Reached the end of the FINESSE buffer"); continue;}
      m_ch_mask = (buf[pos]>>16)&0xFFFF;//DSP channels mask
      m_trig_tag = buf[pos]&0xFFFF;     //trigger tag

      pos++; if(pos == buf_lenght){B2DEBUG (50,"Reached the end of the FINESSE buffer"); continue;}
      m_adc_mask = buf[pos]&0xFFFF;//with-ADC-channel mask
      B2DEBUG(50,"m_shaper " << m_shaper);
      B2DEBUG(50,"m_sh_mask " << m_sh_mask);
      B2DEBUG(50,"m_ch_adc_num " << m_ch_adc_num);
      B2DEBUG(50,"m_samplnum " << m_samplnum);
      B2DEBUG(50,"m_dspnum " << m_dspnum);
      B2DEBUG(50,"m_trig_phase " << m_trig_phase);
      B2DEBUG(50,"m_ch_mask " << m_ch_mask);
      B2DEBUG(50,"m_trig_tag " << m_trig_tag);

      for(ich = 0; ich<m_dspnum; ich++){
        m_channel = (m_shaper-1)*16 + ich;
        pos++; if(pos == buf_lenght){B2DEBUG (50,"Reached the end of the FINESSE buffer"); continue;}
        m_time = (buf[pos]>>18)&0xFFF;
        m_flag = (buf[pos]>>30)&0x3;
        m_amp  = (buf[pos]&0x3FFFF) - 128;
        B2DEBUG(50," " << m_flag << " " << m_time << " " << m_amp);
        if(m_amp > m_AmpMin && m_amp < m_AmpMax || m_amp == -128){
//          m_amp_hist->Fill(m_amp);
          m_ecl_tree->Fill();
//          m_amp_sh_scatter_plot->SetPoint(m_amp_hist->GetEntries(),m_shaper,m_amp);
        }
      }
    }
  }
}

void MODULENAME::event(){
  setReturnValue(0);
//  m_amp_hist->Print();
  if(!(++m_num_events % 250)){
    m_ecl_tree->Draw("amp","amp>250 && amp<2500");
    c1->Update();
//    m_ecl_tree->Print();
    cout << "event " << m_num_events << endl;
  }

//    if(++m_num_events >= m_NEvents){
//      return;
//      endRun();
//      terminate();
//    }
//  StoreArray<RawDataBlock> raw_datablkarray;
//  const int numBlocks = raw_datablkarray.getEntries();
//  for(int i=0; i<numBlocks; i++){
//    int numEvents = raw_datablkarray[i]->GetNumEntries();

    StoreArray<RawECL> raw_eclarray;
//    const int NTot = raw_eclarray.getEntries() > m_NEvents ? m_NEvents : raw_eclarray.getEntries();
//    StoreArray<RawCOPPER> raw_eclarray;
    for (int i = 0; i < raw_eclarray.getEntries(); i++) {
      for (int j = 0; j < raw_eclarray[i]->GetNumEntries(); j++) {
//        cout << "raw_eclarray entries[" << i << "]: " << raw_eclarray[i]->GetNumEntries() << endl;
//      printf("\n===== DataBlock(RawECL) : Block # %d ", i);
//      printCOPPEREvent(raw_eclarray[ i ], j);
        readECLEvent(raw_eclarray[ i ], j);
      }
    }
//  }
}

void MODULENAME::endRun(){
//  m_amp_hist->Write();
//  m_amp_sh_scatter_plot->Write();
//  m_ecl_root_file->Write();
//  m_ecl_root_file->Close();
}

void MODULENAME::terminate(){
}

