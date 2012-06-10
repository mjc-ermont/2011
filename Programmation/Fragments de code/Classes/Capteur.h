#ifndef Capteur_h
#define Capteur_h

class Capteur{
   public:
	  Capteur();	
      virtual void refresh() = 0;
      virtual void getValue() = 0;
      
   private:   
      float value;
};

#endif