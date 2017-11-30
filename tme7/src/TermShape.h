




class  TermShape {
     public:
           TermShape       ( Symbol*, string  name , int x1 , int y1 );
          ~TermShape        ();
          Box    getBoundingBox  () const;
inline   Term* getTerm          ()  const;
inline   int    getX             ()  const;
inline   int    getY             ()  const;
     private:
        Symbol* owner_;
        Term* term_;
        int x1_ , y1_;
  };
