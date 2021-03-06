///////////////////////////////////////////////////
/// \class RecoModule
/// \file RecoModule.h
/// \brief
/// \author V. Genty < vic.genty@gmail.com >
///////////////////////////////////////////////////

#ifndef RECOMODULE_H
#define RECOMODULE_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

#include "TGraphErrors.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"


#include "Fiber.h"
#include "Track.h"
#include "Geometry.h"

namespace reco {

  class RecoModule {

  private:
    //std::string fEventFile;
    std::string fPinFile;
    //int fEvent;
    //int fEvents;
    int fFiberLocations[4][64];
    int fPinsToPixels[32][2];
    int fPixelsToFibers[16][8];
    //std::map<int, std::vector<int> >   fEventData;
    std::map<int, std::vector<int> >   fHitFibers;
    std::map<int, std::map<int, std::pair<int,int> > > fFiberPinPixel;
    std::vector<reco::Fiber>  fFibers;
    std::vector<reco::Track>  fTracks;
    double fOffset;
    //double fAngleThreshold;
    int fGoodTrackIndex;
    reco::Geometry *g;
    double fId;
    double fGap;

    int goodpins[8] =  {8,9,10,11,12,13,14,15}; //this must be manually entered at the moment sorry
  
  public:
    RecoModule();
    RecoModule(int id,double gap);
    ~RecoModule();
    void getfiles(std::string pfile);
    void initpixels();
    void initpins();
    void initfibs();
    void initfile();
    bool check_event(std::vector<int>& pin_data);
    void find_hit_fibers(std::vector<int>& hit_pins);
    void init_module();
    void fill_fibers();
    //std::map<int, std::vector<int> > get_event_data(){return fEventData;}
    void clear(){fHitFibers.clear();fFibers.clear();fTracks.clear();fFiberPinPixel.clear(); fGoodTrackIndex = -1;}
    void get_location(int id, double *x, double *y, bool top); //i should pass by reference in future
    void get_pin(int id, int *pin ,bool top);
    void get_pixel(int id, int *pixel ,bool top);
    void print_fibers();
    void clusterize();
    void attach();
    void print_tracks();
    //void reconstruct();
    //void choose_angles();
  
  
    bool is_good_layers();
    bool is_good_track();
    //bool is_good_angle();
    bool conditions_are_met();
  
    // holy shit i'm a bad programmer
    // need only return the best track and the angle associated with it
  
    const std::vector<reco::Track>& get_Tracks() const { return fTracks; }


    bool one_each_layer(reco::Track trakk);
  
  };

}

#endif
