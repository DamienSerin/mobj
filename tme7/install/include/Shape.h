#include"Symbol.h"
#include"Box.h"

namespace Netlist {

    class Cell;
    class Term;

    class Shape {
    public:
                Shape   (Symbol*);
        virtual ~Shape  ();

        inline  Symbol*     getSymbol           ()  const;
        virtual Box         getBoundingBox      ()  const = 0;
        static Shape*       fromXml             (Symbol*, xmlTextReaderPtr);
    private:
        Symbol* owner_;
    };

    inline  Symbol* Shape::getSymbol()  const { return  owner_; }

    class BoxShape : public Shape {
    public:
        BoxShape    (Symbol*, const  Box&);
        BoxShape    (Symbol *, int x1 , int y1 , int x2 , int y2);
        ~BoxShape   ();

                Box         getBoundingBox      () const;
        virtual void        toXml               (std::ostream&);
        static  BoxShape*   fromXml             (Symbol*, xmlTextReaderPtr);
    private:
        Box   box_;
    };

    class  TermShape : public Shape {
    public:
        enum NameAlign{ TopLeft=1, TopRight=2, BottomLeft=3, BottomRight=4};

        TermShape   (Symbol*, std::string  name , int x1 , int y1);
        ~TermShape  ();

                    Box         getBoundingBox  () const;
        static      std::string toString        (NameAlign);
        static      NameAlign   toAlign         (std::string);
        inline      Term*       getTerm         () const;
        inline      int         getX            () const;
        inline      int         getY            () const;
        inline      void        setAlign        (NameAlign);
        virtual     void        toXml           (std::ostream&);
        static      TermShape*  fromXml         (Symbol*, xmlTextReaderPtr);
    private:
        Term* term_;
        int x1_ , y1_;
        NameAlign align_;
    };

    inline int      TermShape::getX() const {return x1_;}
    inline int      TermShape::getY() const {return y1_;}
    inline Term*    TermShape::getTerm() const {return term_;}
    inline void     TermShape::setAlign(NameAlign n){align_ = n;}


    class  LineShape : public Shape {
    public:
        LineShape       (Symbol*, int x1, int y1 , int x2 , int y2 );
        ~LineShape      ();

                Box             getBoundingBox  ()  const;
        virtual void            toXml           (std::ostream&);
        static  LineShape*      fromXml         (Symbol*, xmlTextReaderPtr);
    private:
        int x1_ , y1_ , x2_ , y2_;
    };

    class ArcShape : public Shape {
    public:
        ArcShape(Symbol*, const Box&, int startAngle, int spanAngle);
        ArcShape(Symbol*, int x1, int y1, int x2, int y2, int startAngle, int spanAngle);
        ArcShape(const ArcShape&);
        virtual ~ArcShape();

        virtual     Box         getBoundingBox  () const;
        inline      int         getStart        () const;
        inline      int         getSpan         () const;
        virtual     void        toXml           (std::ostream&);
        static      ArcShape*   fromXml         (Symbol*, xmlTextReaderPtr);

    private:
        Box box_;
        int startAngle_;
        int spanAngle_;
    };
    inline int ArcShape::getStart() const {return startAngle_;}
    inline int ArcShape::getSpan() const {return spanAngle_;}

    class EllipseShape : public Shape {
    public:
        EllipseShape(Symbol*, const Box&);
        EllipseShape(Symbol *, int x1 , int y1 , int x2 , int y2);
        virtual ~EllipseShape();

        virtual     Box             getBoundingBox  () const;
        virtual     void            toXml           (std::ostream&);
        static      EllipseShape*   fromXml         (Symbol*, xmlTextReaderPtr);
    private:
        Box box_;
    };

}
