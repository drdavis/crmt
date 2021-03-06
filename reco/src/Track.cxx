/////////////////////////////////////////////////////////////
/// \file Track.cxxx
/// \brief
/// \author V. Genty < vic.genty@gmail.com >
/////////////////////////////////////////////////////////////

#include "Track.h"

namespace reco {
  
  Track::Track() :
    fid(0),
    fHasOneEach(false)
  {}
  
  Track::~Track() {}

  void Track::add_fiber(Fiber a)
  {
    fFibers.push_back(a);
  }

  void Track::set_id(int a)
  {
    fid = a;
  }
  bool Track::contains(Fiber a) const
  {
    for(auto& fib : fFibers){
      if( fib.id() == a.id() &&
	  fib.x() == a.x() &&
	  fib.y() == a.y() ) return true;
    }
    return false;
  }

  void Track::dump()
  {
    std::cout << " track id " << id() << std::endl;
    for(auto& fib : fFibers){
      fib.dump();
    }

  }

  void Track::hasoneeach(bool a){
    fHasOneEach = a;
  }

}
