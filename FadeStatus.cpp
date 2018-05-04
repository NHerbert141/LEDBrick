#include "Arduino.h"
#include "FadeStatus.h"

unsigned int FadeStatus::_interval = 50;
unsigned int FadeStatus::_millisLast = 0;
byte FadeStatus::_ledCount = 0;
FadeStatus* FadeStatus::_ledList[FADE_STATUS_MAX_LED];

FadeStatus::FadeStatus(byte pin) :
  FadeStatus(pin, FadeStatusGammaTable, 100)
{
  
}

FadeStatus::FadeStatus(byte pin, const flvar_t* gammaLookup, flvar_t biggestStep) :
  _pin(pin),
  _count(0),
  _countMax(40),
  //_countMax(2000 / _interval),
  _constTime(false),
  _gammaLookup(gammaLookup),
  _biggestStep(biggestStep)
{  
  //only add it if it fits
  if(_ledCount < FADE_STATUS_MAX_LED){
    _ledList[_ledCount++] = this;
  }
}

FadeStatus::FadeStatus(byte pin, bool hasGammaTable) :
  FadeStatus(pin, nullptr, FADE_STATUS_RESOLUTION)
{  
  if(hasGammaTable){
    _gammaLookup = FadeStatusGammaTable;
    _biggestStep = 100;
  }
}

FadeStatus::~FadeStatus(){
  //Find current possition of this object
  byte posThis=0;
  while((posThis < _ledCount) && (_ledList[posThis] != this)){
    posThis++;
  }
  
  //if not in the list (how weird), it's done
  if(posThis == _ledCount){
    return;
  }
  
  //Otherwise, delete this object by shifting in the rest
  _ledCount--;
  for(byte i = posThis; i < _ledCount; i++){
    _ledList[i] = _ledList[i + 1];
  }
}

void FadeStatus::begin(flvar_t val){
  //set to both so no fading happens
  _setVal = val;
  _curVal = val;
  analogWrite(this->_pin, getGamma(_curVal));
}

void FadeStatus::set(flvar_t val){
  
  /** edit 2016-11-17
   *  Fix so you can set it to a new value while 
   *  fading in constant speed. And impossible to set 
   *  a new value in constant time.
   */
  if(_setVal != val){
    /** edit 2016-11-30
     *  Fixed out of range possibility
     */
    //check for out of range
    if(val > _biggestStep){
      //if bigger then allowed, use biggest value
      val = _biggestStep;
    }    
    
    //if it's now fading we have to check how to change it
    if(!done()){
      //setting new val while fading in constant time not possible
      if(_constTime){
        return;
      }
      //if in constant speed the new val is in same direction and not passed yet
      else if(( (_startVal < _setVal) && (_curVal < val)) || //up
              ( (_startVal > _setVal) && (_curVal > val)) ){ //down
        //just set a new val
        _setVal = val;
        return;
      }
    }
    
    //if we make it here it's or finished fading
    //or constant speed in other direction
    //save and reset
    _setVal = val;
    _count = 1;
    
    //and start fading from current position
    _startVal = _curVal;
  }
  
  
   /* Old code 2016-11-17
  if(_setVal != val){
    //save and reset counter
    _setVal = val;
    _count = 1;

    //so we know where to fade from
    _startVal = _curVal;
  }*/
}

flvar_t FadeStatus::get(){
  return _setVal;
}

flvar_t FadeStatus::getCurrent(){
  return _curVal;
}

bool FadeStatus::done(){
  return _curVal == _setVal;
}

void FadeStatus::on(){
  this->set(_biggestStep);
}

void FadeStatus::off(){
  this->set(0);
}

void FadeStatus::beginOn(){
  this->begin(_biggestStep);
}

void FadeStatus::setTime(unsigned long time, bool constTime){
  //Calculate how many times interval need to pass in a fade
  this->_countMax = time / _interval;
  this->_constTime = constTime;
}

bool FadeStatus::rising(){
  return (_curVal < _setVal);
}

bool FadeStatus::falling(){
  return (_curVal > _setVal);
}

void FadeStatus::stop(){
  _setVal = _curVal;
}

void FadeStatus::setGammaTable(const flvar_t* table, flvar_t biggestStep){
  //stops the current fading for no funny things
  stop();
  
  //Next time fade from 0
  _setVal = 0;
  _curVal = 0;
  _count = 1;
  
  //Sets up the new gamma table
  _gammaLookup = table;
  _biggestStep = biggestStep;
}

void FadeStatus::noGammaTable(){
  setGammaTable(nullptr, FADE_STATUS_RESOLUTION);
}

flvar_t FadeStatus::getGammaValue(flvar_t step){
  if(step > _biggestStep){
    step = _biggestStep;
  }
  return FadeStatus::getGamma(step);
}

flvar_t FadeStatus::getBiggestStep(){
  return _biggestStep;
}

void FadeStatus::updateThis(){
  //need to fade up
  if(_curVal < _setVal){
    flvar_t newVal;
    
    //we always start at the current level saved in _startVal
    if(_constTime){
      //for constant fade time we add the difference over countMax steps
      newVal = _startVal + _count * (_setVal - _startVal) / _countMax;
    }
    else{
      //for constant fade speed we add the full resolution over countMax steps
      newVal = _startVal + _count * _biggestStep / _countMax;
    }
    
    //check if new
    if(newVal != _curVal){
      //check for overflow
      if(newVal < _curVal){
        _curVal = _biggestStep;
      }
      //Check for overshoot
      else if(newVal > _setVal){
        _curVal = _setVal;
      }
      //Only if the new value is good we use that
      else{
        _curVal = newVal;
      }
          
      analogWrite(this->_pin, getGamma(_curVal) );
    }
    _count++;
  }
  //need to fade down
  else if(_curVal > _setVal){
    flvar_t newVal;
    
    //we always start at the current level saved in _startVal
    if(_constTime){
      //for constant fade time we subtract the difference over countMax steps
      newVal = _startVal - _count * (_startVal - _setVal) / _countMax;
    }
    else{
      //for constant fade speed we subtract the full resolution over countMax steps
      newVal = _startVal - _count * _biggestStep / _countMax;
    }
    
    //check if new
    if(newVal != _curVal){
      //check for overflow
      if(newVal > _curVal){
        _curVal = 0;
      }
      //Check for overshoot
      else if(newVal < _setVal){
        _curVal = _setVal;
      }
      //Only if the new value is good we use that
      else{
        _curVal = newVal;
      }
          
      analogWrite(this->_pin, getGamma(_curVal) );
    }
    _count++;
  }
  
}

void FadeStatus::setInterval(unsigned int interval){
  _interval = interval;
}

void FadeStatus::update(){
  unsigned int millisNow = millis();
  
  if(!_ledCount){
    return;
  }
  
  if(millisNow - _millisLast > _interval){
    /**
     *  Fix issue #13
     *  Weird fade when not calling update() while not fading     
     */
    if(millisNow - _millisLast > (_interval << 1)){
      _millisLast = millisNow;
    }
    else{
      _millisLast += _interval;
    }
        
    //update every object
    for(byte i = 0; i < _ledCount; i++){
      _ledList[i]->updateThis();
    }
  }
}

