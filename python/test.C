void test (const char* myString) {
  ROOT::EnableImplicitMT();
 
	TString str = myString;
  TChain chain("Events");

  if(str=="2017"){
	TString path = "/scratchnvme/wmass/NANOV9/y2017/DYJetsToMuMu_H2ErratumFix_TuneCP5_13TeV-powhegMiNNLO-pythia8-photos/NanoV9MC2017_2017test/230529_094542/0000/";
	chain.Add(path+"NanoV9MC2017_1.root");
	}
	else if(str=="2018"){
	TString path = "/scratchnvme/wmass/NANOV9/y2018/DYJetsToMuMu_H2ErratumFix_TuneCP5_13TeV-powhegMiNNLO-pythia8-photos/NanoV9MC2018_2018test/230530_220228/0000/"; 
	chain.Add(path+"NanoV9MC2018_1.root");
	chain.Add(path+"NanoV9MC2018_10.root");
	}
	else{
	std:cout << "Look for 2016 option"<<std::endl;
	}
  //ROOT::RDataFrame d("Events","../NanoV9MC2017_100.root");
	ROOT::RDataFrame d(chain);
  TFile *f  = TFile::Open("/scratchnvme/tanmay/BeamSpotRootFiles/output_file.root","READ");
	TFile *fpu  = TFile::Open("/scratchnvme/tanmay/BeamSpotRootFiles/ratio_PUera2017.root","READ");
  TH2D* h = (TH2D*)f->Get("combined_hist");
	TH1F* hpu = (TH1F*)fpu->Get("pileup");

// For 2016
	/*ROOT::RDataFrame d("Events","NanoV9MCPostVFP_100.root");

  TFile *f  = TFile::Open("vertexPileupWeights.root","READ");
  TFile *fpu  = TFile::Open("ratio_PUera2016.root","READ");
  TH2D* h = (TH2D*)f->Get("weight_vertexZ_pileup_GtoH");
  h->SetDirectory(0);

	TH1F* hpu = (TH1F*)fpu->Get("Pileup_nTrueInt_Wmunu_postVFP");
*/
	auto wfunc_vtx = [h](float z, float p) -> double {
				double vtxw = h->GetBinContent(h->FindBin(z, p));
				if(vtxw<0){
				std::cout<< "vtxw Weight = " << vtxw << endl;}
				if(vtxw>0){
				return vtxw;}
				else{
				return 1.;}
        //return h->GetBinContent(h->FindBin(z, p));
    };
	auto wfunc_pu = [hpu](float pubins, double w)->double{
		double puw = hpu->GetBinContent(hpu->FindBin(pubins));
				if(puw<=0){
				std::cout<< "pu Weight = " << puw << endl;}
		if(puw>0){
        return puw*w;
        }
        else{
        return 1.;
        }

	};
  auto d1 = d.Define("weightvtx", wfunc_vtx, {"GenVtx_z", "Pileup_nTrueInt"});
	auto d2 = d1.Define("weightpu", wfunc_pu, {"Pileup_nTrueInt", "weightvtx"});
  auto histovtx = d2.Histo1D({"Vtx_reweight", "Vtx_Z: [Weight by Beamspot Smearing factor]", 40, -20, 20}, "GenVtx_z", "weightvtx");
	auto histoW = d2.Histo1D({"weight_vtx_pu", "Weight: [Puweight Multiply vtxWeight]",100,0.,2}, "weightpu");
  std::cout<<  "Creating Files for "<< myString << ": " << endl;
	auto c1 = new TCanvas("c1","c1");
  histovtx->Draw();
	c1->SaveAs("gen_vtxz_with_vtxz_weight"+str+".png");
  histovtx->SaveAs("/scratchnvme/tanmay/BeamSpotRootFiles/gen_vtxz_with_vtxz_weight"+str+".root");

	auto c2 = new TCanvas("c2", "c2");
	histoW->Draw();
	c2->SaveAs("weight_pumultiplyvtxz"+str+".png");
  histoW->SaveAs("/scratchnvme/tanmay/BeamSpotRootFiles/weight_pumultiplyvtxz"+str+".root");
}
