#include "Shape.h"

class BoxShape {
 public: 
        BoxShape         ( Symbol*, const  Box& );   
       ~BoxShape         ();
    Box getBoundingBox () const;
 private :
  Symbol* owner_;
  Box   box_;
};

