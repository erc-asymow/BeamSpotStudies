 {
	ROOT::EnableImplicitMT();
  //TFile *f  = TFile::Open("ratio_2016_69200ub.root","READ");
  //TH1F* h = (TH1F*)f->Get("ratio_0_50");
  //auto weight = [&h](float z, float w)->float{  return (h->GetBinContent(h->FindBin(z)))*w; };

  //ROOT::RDataFrame d("demo/Events", "NanoAOD.root");
  ROOT::RDataFrame d("Events", "ReReco-Run2017E-SingleMuon-UL2017_MiniAODv2_NanoAODv9-00001_9.root");

  auto histo = d. //Filter("Muon_pt[0]>30 && Muon_pt[1]>25 && Muon_isGlobal[0] && Muon_isGlobal[1] && Muon_pfRelIso04_all[0]/Muon_pt[0]<0.15 && Muon_pfRelIso04_all[1]/Muon_pt[1]<0.15 && (PV_z<100 || PV_z>100)").
  //auto histo = d.Filter("(Muon_pt[0]>30 && Muon_pt[1]>25 && Muon_isGlobal[0] && Muon_isGlobal[1] && Muon_pfRelIso04_all[0]/Muon_pt[0]<0.15 && Muon_pfRelIso04_all[1]/Muon_pt[1]<0.15 && abs(PV_z)<100)").
    //Define("weight", weight, {"GenVertex_z","puWeight"}).
    //Histo1D<float>({"","", 100,-20,20}, "PV_z", "weight");
    Histo1D<float>({"","", 100,-20,20}, "PV_z");
  
  histo->Draw();
 }  
