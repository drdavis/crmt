/////////////////////////////////////////////////////////////
/// \file FileManager.cxxx
/// \brief
/// \author V. Genty < vic.genty@gmail.com >
/////////////////////////////////////////////////////////////

#include "FileManager.h"

namespace reco {

  FileManager::FileManager()
  {
    //empty constructor
  }

  FileManager::~FileManager() {}

  std::string FileManager::to_string(char let, int id)
  {
    std::ostringstream ss;
    ss << let << id;
    return ss.str();
  }

  std::map<int, std::vector<int> > FileManager::get_raw_data(const int event) {

    fRawEventData.clear();

    std::vector<int>* HitPinsTop0 = 0;
    std::vector<int>* HitPinsBot0 = 0;
    std::vector<int>* HitPinsTop1 = 0;
    std::vector<int>* HitPinsBot1 = 0;
    std::vector<int>* HitPinsTop2 = 0;
    std::vector<int>* HitPinsBot2 = 0;
    std::vector<int>* HitPinsTop3 = 0;
    std::vector<int>* HitPinsBot3 = 0;

    fMod0Tree->SetBranchAddress("HitPinsTop0",&HitPinsTop0);
    fMod0Tree->SetBranchAddress("HitPinsBot0",&HitPinsBot0);

    fMod1Tree->SetBranchAddress("HitPinsTop1",&HitPinsTop1);
    fMod1Tree->SetBranchAddress("HitPinsBot1",&HitPinsBot1);

    fMod2Tree->SetBranchAddress("HitPinsTop2",&HitPinsTop2);
    fMod2Tree->SetBranchAddress("HitPinsBot2",&HitPinsBot2);

    fMod3Tree->SetBranchAddress("HitPinsTop3",&HitPinsTop3);
    fMod3Tree->SetBranchAddress("HitPinsBot3",&HitPinsBot3);

    TBranch *b_HitPinsTop0 = fMod0Tree->GetBranch("HitPinsTop0");
    TBranch *b_HitPinsTop1 = fMod1Tree->GetBranch("HitPinsTop1");
    TBranch *b_HitPinsTop2 = fMod2Tree->GetBranch("HitPinsTop2");
    TBranch *b_HitPinsTop3 = fMod3Tree->GetBranch("HitPinsTop3");

    TBranch *b_HitPinsBot0 = fMod0Tree->GetBranch("HitPinsBot0");
    TBranch *b_HitPinsBot1 = fMod1Tree->GetBranch("HitPinsBot1");
    TBranch *b_HitPinsBot2 = fMod2Tree->GetBranch("HitPinsBot2");
    TBranch *b_HitPinsBot3 = fMod3Tree->GetBranch("HitPinsBot3");
      
    b_HitPinsTop0->GetEvent(event);
    b_HitPinsTop1->GetEvent(event);
    b_HitPinsTop2->GetEvent(event);
    b_HitPinsTop3->GetEvent(event);

    b_HitPinsBot0->GetEvent(event);
    b_HitPinsBot1->GetEvent(event);
    b_HitPinsBot2->GetEvent(event);
    b_HitPinsBot3->GetEvent(event);

    for ( auto const hit : *HitPinsTop0 )
      fRawEventData[0].push_back(hit);
    for ( auto const hit : *HitPinsBot0 )
      fRawEventData[0].push_back(hit);
    for ( auto const hit : *HitPinsTop1 )
      fRawEventData[1].push_back(hit);
    for ( auto const hit : *HitPinsBot1 )
      fRawEventData[1].push_back(hit);
    for ( auto const hit : *HitPinsTop2 )
      fRawEventData[2].push_back(hit);
    for ( auto const hit : *HitPinsBot2 )
      fRawEventData[2].push_back(hit);
    for ( auto const hit : *HitPinsTop3 )
      fRawEventData[3].push_back(hit);
    for ( auto const hit : *HitPinsBot3 )
      fRawEventData[3].push_back(hit);
      
    /*
    //bool coincidence;
    bool tMod0[32];
    bool tMod1[32];
    bool tMod2[32];
    bool tMod3[32];
  
    fRawDataTree->SetBranchAddress("PinsArray0",tMod0);
    fRawDataTree->SetBranchAddress("PinsArray1",tMod1);
    fRawDataTree->SetBranchAddress("PinsArray2",tMod2);
    fRawDataTree->SetBranchAddress("PinsArray3",tMod3);
    //fRawDataTree->SetBranchAddress("Coincidence",&coincidence);
    TBranch *b_PinsArray0  = fRawDataTree->GetBranch("PinsArray0");
    TBranch *b_PinsArray1  = fRawDataTree->GetBranch("PinsArray1");
    TBranch *b_PinsArray2  = fRawDataTree->GetBranch("PinsArray2");
    TBranch *b_PinsArray3  = fRawDataTree->GetBranch("PinsArray3");
    //TBranch *b_Coincidence = fRawDataTree->GetBranch("Coincidence");
  
    b_PinsArray0->GetEvent(event);   
    b_PinsArray1->GetEvent(event);
    b_PinsArray2->GetEvent(event);
    b_PinsArray3->GetEvent(event);
    //b_Coincidence->GetEvent(event);
  
    for (int xx = 0; xx < 32; ++xx){
    if (tMod0[xx]) fRawEventData[0].push_back(xx);
    if (tMod1[xx]) fRawEventData[1].push_back(xx);
    if (tMod2[xx]) fRawEventData[2].push_back(xx);
    if (tMod3[xx]) fRawEventData[3].push_back(xx);  
    }
    */
    return fRawEventData;
  }

  void FileManager::set_raw_data_name(std::string name){
  
    fRawDataFileName = name;
    fRawData        = new TFile(fRawDataFileName.c_str(),"READ");

    fMod0Tree = (TTree*)fRawData->Get("Mod0Tree");
    fMod1Tree = (TTree*)fRawData->Get("Mod1Tree");
    fMod2Tree = (TTree*)fRawData->Get("Mod2Tree");
    fMod3Tree = (TTree*)fRawData->Get("Mod3Tree");
    fNRawEvents = fMod1Tree->GetEntries();

    /* else {
       fRawDataTree = (TTree*)fRawData->Get("SimulationTree");
       fNRawEvents     = fRawDataTree->GetEntries();
       }*/
    fTestVolumeTree = (TTree*)fRawData->Get("TestVolumeTree");   
    set_gap_sim();
  }

  void FileManager::load_output_data(std::string file_name)
  {
  
    fReconData    = new TFile(file_name.c_str(), "RECREATE");
  
    fEventTreeXZ  = new TTree("Event Tree XZ","Recon Tree XZ");  
    fEventTreeXZ->Branch("Slope"          , &fSlope_XZ       , "Slope/D"       );
    fEventTreeXZ->Branch("SlopeErr"       , &fSlopeErr_XZ       , "SlopeErr/D"       );
    fEventTreeXZ->Branch("Yinter"         , &fYInter_XZ      , "Yinter/D"      );
    fEventTreeXZ->Branch("YinterErr"         , &fYInterErr_XZ      , "YinterErr/D"      );
    fEventTreeXZ->Branch("fChi"           , &fChi_XZ         , "Chi/D"         );
    fEventTreeXZ->Branch("fRChi"           , &fRChi_XZ         , "RChi/D"         );
    fEventTreeXZ->Branch("fNdf"           , &fNdf_XZ         , "Ndf/D"         );
  
    fEventTreeXZ->Branch("fPvalue"        , &fPvalue_XZ      , "Pvalue/D"      ); 
    fEventTreeXZ->Branch("fAngle"         , &fAngle_XZ       , "Angle/D"       ); 
    fEventTreeXZ->Branch("fAngleErr"         , &fAngleErr_XZ       , "AngleErr/D"       ); 
    fEventTreeXZ->Branch("fCosAngle"      , &fCosAngle_XZ    , "CosAngle/D"    ); 
    fEventTreeXZ->Branch("fFibXZX"        , &fFibsXZX); 
    fEventTreeXZ->Branch("fFibXZY"        , &fFibsXZY); 


      
  
    fEventTreeYZ  = new TTree("Event Tree YZ","Recon Tree YZ");  
    fEventTreeYZ->Branch("Slope"          , &fSlope_YZ       , "Slope/D"       );
    fEventTreeYZ->Branch("Yinter"         , &fYInter_YZ      , "Yinter/D"      );
    fEventTreeYZ->Branch("SlopeErr"          , &fSlopeErr_YZ       , "SlopeErr/D"       );
    fEventTreeYZ->Branch("YinterErr"         , &fYInterErr_YZ      , "YinterErr/D"      );
    fEventTreeYZ->Branch("fChi"           , &fChi_YZ         , "Chi/D"         );
    fEventTreeYZ->Branch("fRChi"           , &fRChi_YZ         , "RChi/D"         );
    fEventTreeYZ->Branch("fNdf"           , &fNdf_YZ         , "Ndf/D"         );
  
    fEventTreeYZ->Branch("fPvalue"        , &fPvalue_YZ      , "Pvalue/D"      ); 
    fEventTreeYZ->Branch("fAngle"         , &fAngle_YZ       , "Angle/D"       ); 
    fEventTreeYZ->Branch("fAngleErr"         , &fAngleErr_YZ       , "AngleErr/D"       ); 
    fEventTreeYZ->Branch("fCosAngle"      , &fCosAngle_YZ    , "CosAngle/D"    ); 
    fEventTreeYZ->Branch("fFibYZX"        , &fFibsYZX); 
    fEventTreeYZ->Branch("fFibYZY"        , &fFibsYZY); 

    fEventTree3D  = new TTree("Event Tree 3D","Recon Tree 3D");
    fEventTree3D->Branch("fPhi",            &fPhi,         "Phi/D");
    fEventTree3D->Branch("fTheta",            &fTheta,         "Theta/D");
    fEventTree3D->Branch("fGap",            &fGap,         "Gap/D");
    fEventTree3D->Branch("fSimID",          &fSimID,       "SimID/I");
  
  }


  void FileManager::fill_event_tree(const std::pair<reco::Line,reco::Line>& lines, int simid) {
  
    fSlope_XZ       =  lines.first.slope();
    fSlopeErr_XZ    =  lines.first.slopeerr();
    fYInter_XZ      =  lines.first.yinter();
    fYInterErr_XZ   =  lines.first.yintererr();
    fChi_XZ         =  lines.first.chi();
    fRChi_XZ        =  lines.first.rchi();
    fNdf_XZ         =  lines.first.ndf();
  
    fPvalue_XZ      =  lines.first.pvalue();
    fAngle_XZ       =  lines.first.angle();
    fAngleErr_XZ    =  lines.first.angleerr();
    fCosAngle_XZ    =  lines.first.cosangle();
  
    fSimID = simid;

    //Slightly more painful way to write this data to a tree
    //XZ
    for (const auto& fiber : lines.first.get_best_tracks().first.fibers()){
      fFibsXZX.push_back(fiber.coords().first);
      fFibsXZY.push_back(fiber.coords().second);
    }
    for (const auto& fiber : lines.first.get_best_tracks().second.fibers()){
      fFibsXZX.push_back(fiber.coords().first);
      fFibsXZY.push_back(fiber.coords().second);
    }
  
    //YZ
  
    for (const auto& fiber : lines.second.get_best_tracks().first.fibers()){
      fFibsYZX.push_back(fiber.coords().first);
      fFibsYZY.push_back(fiber.coords().second);
    }
    for (const auto& fiber : lines.second.get_best_tracks().second.fibers()){
      fFibsYZX.push_back(fiber.coords().first);
      fFibsYZY.push_back(fiber.coords().second);
    }
  
  
  
    fSlope_YZ       =  lines.second.slope();
    fSlopeErr_YZ    =  lines.second.slopeerr();
    fYInter_YZ      =  lines.second.yinter();
    fYInterErr_YZ   =  lines.second.yintererr();
    fChi_YZ         =  lines.second.chi();
    fRChi_YZ        =  lines.second.rchi();
    fNdf_YZ         =  lines.second.ndf();
  
    fPvalue_YZ      =  lines.second.pvalue();
    fAngle_YZ       =  lines.second.angle();
    fAngleErr_YZ    =  lines.second.angleerr();
    fCosAngle_YZ    =  lines.second.cosangle();
  
  

    fPhi            =  atan2(tan(fAngle_YZ),tan(fAngle_XZ)) + 3.14159265359;
 
    //for now use fAngleXZ, should decide later how to do this
    fTheta          =  atan(tan(fAngle_XZ)/cos(fPhi));
    //fTheta        =  atan(tan(fAngle_YZ)/sin(fPhi));
  
    
    fEventTreeXZ->Fill();
    fEventTreeYZ->Fill();
    fEventTree3D->Fill();
  
    cleanup();
  
  
  }


  void FileManager::cleanup(){
    fFibsXZX.clear();
    fFibsXZY.clear();
    fFibsYZX.clear();
    fFibsYZY.clear();
  }

  void FileManager::finish(){
    fEventTreeXZ->Write();
    fEventTreeYZ->Write();  
    fEventTree3D->Write();
    fReconData->Close();
  }

  void FileManager::setup_reco_viewer(std::string reco_file,int event){  
    fInputRecoData = new TFile(reco_file.c_str(),"READ");
    fXZTree = (TTree*)fInputRecoData->Get("Event Tree XZ");
    fYZTree = (TTree*)fInputRecoData->Get("Event Tree YZ");
    f3DTree = (TTree*)fInputRecoData->Get("Event Tree 3D");
    fEvent = event;
    set_gap_reco();
  }



  std::pair<std::pair<std::vector<double>,std::vector<double> >
	    ,std::pair<std::vector<double>,std::vector<double> > > FileManager::get_hit_points(){
  
  
    std::vector<double> *fibsXZX = 0;
    std::vector<double> *fibsXZY = 0;
    std::vector<double> *fibsYZX = 0;
    std::vector<double> *fibsYZY = 0;
    
    /*
      std::vector<double> *fibsXZX;
      std::vector<double> *fibsXZY;
      std::vector<double> *fibsYZX;
      std::vector<double> *fibsYZY;
    */
    /*
      std::vector<double> *fibsXZX = new std::vector<double>;
      std::vector<double> *fibsXZY = new std::vector<double>;
      std::vector<double> *fibsYZX = new std::vector<double>;
      std::vector<double> *fibsYZY = new std::vector<double>;
    */

    //TBranch *b_fibsXZX=0;
    //TBranch *b_fibsXZY=0;
    //TBranch *b_fibsYZX=0;
    //TBranch *b_fibsYZY=0; 
  
    /*
      fXZTree->SetBranchAddress("fFibXZX" ,&fibsXZX,&b_fibsXZX); //passing address of pointer
      fXZTree->SetBranchAddress("fFibXZY" ,&fibsXZY,&b_fibsXZY);
      fYZTree->SetBranchAddress("fFibYZX" ,&fibsYZX,&b_fibsYZX);
      fYZTree->SetBranchAddress("fFibYZY" ,&fibsYZY,&b_fibsYZY);
    */

    fXZTree->SetBranchAddress("fFibXZX" ,&fibsXZX); //passing address of pointer
    fXZTree->SetBranchAddress("fFibXZY" ,&fibsXZY);
    fYZTree->SetBranchAddress("fFibYZX" ,&fibsYZX);
    fYZTree->SetBranchAddress("fFibYZY" ,&fibsYZY);

    TBranch *b_fibsXZX = fXZTree->GetBranch("fFibXZX");
    TBranch *b_fibsXZY = fXZTree->GetBranch("fFibXZY");
    TBranch *b_fibsYZX=  fYZTree->GetBranch("fFibYZX");;
    TBranch *b_fibsYZY=  fYZTree->GetBranch("fFibYZY");; 
  
  
    b_fibsXZX->GetEvent(fEvent);
    b_fibsXZY->GetEvent(fEvent);
    b_fibsYZX->GetEvent(fEvent);
    b_fibsYZY->GetEvent(fEvent);
  

    // printf("fibsXZX.size(): %lu\n", fibsXZX->size());
    // printf("fibsXZY.size(): %lu\n", fibsXZY->size());
    // printf("fibsYZX.size(): %lu\n", fibsYZX->size());
    // printf("fibsYZY.size(): %lu\n", fibsYZY->size());
  
    // for(auto value : *fibsXZX)
    //   printf("fibsXZX value: %f\n",value);
    // printf("\n");
    // for(auto value : *fibsXZY)
    //   printf("fibsXZY value: %f\n",value);
    // printf("\n");
    // for(auto value : *fibsYZX)
    //   printf("fibsYZX value: %f\n",value);
    // printf("\n");
    // for(auto value : *fibsYZY)
    //   printf("fibsYZY value: %f\n",value);
   
  
    fXZTree->ResetBranchAddresses();
    fYZTree->ResetBranchAddresses();
  
  
    return std::make_pair(std::make_pair(*fibsXZX,*fibsXZY),
			  std::make_pair(*fibsYZX,*fibsYZY));
     
  
  }

  std::pair<std::pair<double,double>,std::pair<double,double> > FileManager::get_slope_yinter(){
  
  
    //std::pair<std::pair<double,double>,std::pair<double,double> > localinfo;
 
    double sXZ,yXZ,sYZ,yYZ;
  
    fXZTree->SetBranchAddress("Slope" ,&sXZ);
    fXZTree->SetBranchAddress("Yinter",&yXZ);
    fYZTree->SetBranchAddress("Slope" ,&sYZ);
    fYZTree->SetBranchAddress("Yinter",&yYZ);
  
    fXZTree->GetEntry(fEvent);
    fYZTree->GetEntry(fEvent);
    
    fXZTree->ResetBranchAddresses();
    fYZTree->ResetBranchAddresses();
  
    return std::make_pair(std::make_pair(sXZ,sYZ),std::make_pair(yXZ,yYZ));
  

  }

  void FileManager::print_reco_results(){

  
    double angleXZ,angleXZerr,angleYZ,angleYZerr,cosangleXZ,cosangleYZ;

    fXZTree->SetBranchAddress("fAngle"      ,&angleXZ);
    fXZTree->SetBranchAddress("fAngleErr"   ,&angleXZerr);
    fXZTree->SetBranchAddress("fCosAngle"   ,&cosangleXZ);
    fYZTree->SetBranchAddress("fAngle"      ,&angleYZ);
    fYZTree->SetBranchAddress("fAngleErr"   ,&angleYZerr);
    fYZTree->SetBranchAddress("fCosAngle"   ,&cosangleYZ);

  
    fXZTree->GetEntry(fEvent);
    fYZTree->GetEntry(fEvent);
  
    //this is necessary
    fXZTree->ResetBranchAddresses();
    fYZTree->ResetBranchAddresses();
  
    printf("----------Reco--Results----------\n");
    printf("Event       : %d         \n",fEvent);
    printf("AngleXZ     : %f +- %f   \n",angleXZ,angleXZerr);
    printf("CosAngleXZ  : %f         \n",cosangleXZ);
    printf("AngleYZ     : %f +- %f   \n",angleYZ,angleYZerr);
    printf("CosAngleYZ  : %f         \n",cosangleYZ);
  
  
  
    //printf("Phi     : %f +- err  \n");
    //printf("Theta   : %f +- err  \n");
  
  
  }
  //xx
  void FileManager::set_gap_sim(){
    double _gap;
  
    fTestVolumeTree->SetBranchAddress("Gap" ,&_gap);
    fTestVolumeTree->GetEntry(0);
 
    fGap = _gap/10.; //Doug uses mm stupid kid

   
    fTestVolumeTree->ResetBranchAddresses();
  
 
  
  }

  void FileManager::set_gap_reco(){
    double _gap;
    f3DTree->SetBranchAddress("fGap",&_gap);
    f3DTree->GetEntry(fEvent);

    fGap = _gap; //Vic uses cm oh yeah

    f3DTree->ResetBranchAddresses();
  
  
  }

  int FileManager::print_sim_event(){
    int _simid;
    f3DTree->SetBranchAddress("fSimID",&_simid);
    f3DTree->GetEntry(fEvent);
  
    std::cout << "looing at sim event number: " << _simid << std::endl;
    f3DTree->ResetBranchAddresses();
    return -1;
  }
}
