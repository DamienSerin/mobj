




class  LineShape {
   public:
          LineShape       ( Symbol*, int x1, int y1 , int x2 , int y2 );
         ~LineShape        ();
     Box   getBoundingBox  ()  const;
   private:
     Symbol* owner_;
     int x1_ , y1_ , x2_ , y2_;


};

