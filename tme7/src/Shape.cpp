#include"Symbol.h"

namespace Netlist{
    
}
/*
class Shape {
public:
    Shape            ( Symbol* );
    ~Shape            ();
    inline    Symbol* getSymbol        ()  const;
    Box      getBoundingBox  ()  const;
private:
    Symbol* owner_;
};
inline  Symbol* Shape:: getSymbol  ()  const { return  owner_; }
Shape :: Shape ( Symbol* owner ) : owner_(owner)
{ owner ->add(this);}
Shape ::~ Shape ()
{ owner_ ->remove( this ); }


class BoxShape {
public:
    BoxShape         ( Symbol*, const  Box& );
    ~BoxShape         ();
    Box getBoundingBox () const;
    private :
    Symbol* owner_;
    Box   box_;
};




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

class  LineShape {
public:
    LineShape       ( Symbol*, int x1, int y1 , int x2 , int y2 );
    ~LineShape        ();
    Box   getBoundingBox  ()  const;
private:
    Symbol* owner_;
    int x1_ , y1_ , x2_ , y2_;
};
Shape* Shape::fromXml ( Symbol* owner, xmlTextReaderPtr reader )
{
    // Factory-like method.

    const xmlChar* boxTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
    const xmlChar* ellipseTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
    const xmlChar* arcTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
    const xmlChar* lineTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
    const xmlChar* termTag
    = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
    const xmlChar* nodeName
    = xmlTextReaderConstLocalName( reader );

    Shape* shape = NULL;
    if (boxTag == nodeName)
    shape = BoxShape::fromXml( owner, reader );
    if (ellipseTag == nodeName)
    shape = EllipseShape::fromXml( owner, reader );
    if (arcTag == nodeName)
    shape = ArcShape::fromXml( owner, reader );
    if (lineTag == nodeName)
    shape = LineShape::fromXml( owner, reader );
    if (termTag == nodeName)
    shape = TermShape::fromXml( owner, reader );

    if (shape == NULL)
    cerr << "[ERROR] Unknown or misplaced tag <" << nodeName << "> (line:"
    << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;

    return shape;*/
