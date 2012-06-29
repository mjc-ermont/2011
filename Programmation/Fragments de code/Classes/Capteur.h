#ifndef Capteur_h
#define Capteur_h

class Capteur{
   public:
	  Capteur();
      virtual void init();
      virtual void refresh() = 0;
      
      virtual bool flush() = 0;              //C'est du bluf, augmente la mise ...
   
   private:

};

#endif