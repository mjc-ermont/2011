#ifndef Capteur_h
#define Capteur_h

class Capteur{
   public:
      virtual void refresh();
      virtual void getValue();
      
   private:   
      float value;
}

#endif