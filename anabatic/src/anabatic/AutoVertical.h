// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC 2008-2013, All Rights Reserved
//
// +-----------------------------------------------------------------+
// |                   C O R I O L I S                               |
// |         A n a b a t i c  -  Routing Toolbox                     |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
// | =============================================================== |
// |  C++ Header  :  "./anabatic/AutoVertical.h"                     |
// +-----------------------------------------------------------------+


#pragma  once
#include "hurricane/Vertical.h"
#include "anabatic/AutoSegment.h"


namespace Anabatic {


// -------------------------------------------------------------------
// Class  :  "AutoVertical".

 
  class AutoVertical : public AutoSegment {
      friend class AutoSegment;

    public:
    // Predicates.                               
      virtual bool          _canSlacken             () const;
      virtual bool          canMoveULeft            ( float reserve=0.0 ) const;
      virtual bool          canMoveURight           ( float reserve=0.0 ) const;
    // Accessors.                                   
      virtual Segment*      base                    ();
      virtual Segment*      base                    () const;
      virtual Vertical*     getVertical             ();
      virtual DbU::Unit     getSourceU              () const;
      virtual DbU::Unit     getTargetU              () const;
      virtual DbU::Unit     getDuSource             () const;
      virtual DbU::Unit     getDuTarget             () const;
      virtual Interval      getSpanU                () const;
      virtual bool          getConstraints          ( DbU::Unit& min, DbU::Unit& max ) const;
      virtual Interval      getSourceConstraints    ( Flags flags=0 ) const;
      virtual Interval      getTargetConstraints    ( Flags flags=0 ) const;
      virtual Flags         getDirection            () const;
      virtual bool          getGCells               ( vector<GCell*>& ) const;
    // Modifiers.                                   
      virtual void          setDuSource             ( DbU::Unit );
      virtual void          setDuTarget             ( DbU::Unit );
      virtual void          _setAxis                ( DbU::Unit );
      virtual void          updateOrient            ();
      virtual void          updateNativeConstraints ();
      virtual bool          checkConstraints        () const;
      virtual Flags         _makeDogleg             ( GCell*, Flags );
      virtual bool          moveULeft               ();
      virtual bool          moveURight              ();
      virtual bool          _slacken                ( Flags );
#if THIS_IS_DISABLED                                
      virtual void          desalignate             ( AutoContact* );
#endif                                              
    // Inspector Management.                        
      virtual Record*       _getRecord              () const;
      virtual string        _getString              () const;
      virtual string        _getTypeName            () const;

    protected:
    // Internal: Attributes.
              Vertical*     _vertical;

    // Constructors.
    protected:
                            AutoVertical       ( Vertical* );
      virtual              ~AutoVertical       ();
      virtual void          _postCreate        ();
      virtual void          _preDestroy        ();
    private:
                             AutoVertical      ( const AutoVertical& );
              AutoVertical&  operator=         ( const AutoVertical& );
  };


} // End of Anabatic namespace.


INSPECTOR_P_SUPPORT(Anabatic::AutoVertical);
