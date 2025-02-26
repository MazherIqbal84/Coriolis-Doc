// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC 2017-2018, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |          Alliance / Hurricane  Interface                        |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
// | =============================================================== |
// |  C++ Module  :  "./PyLefImport.cpp"                             |
// +-----------------------------------------------------------------+


#include "crlcore/PyLefImport.h"
#include "hurricane/isobar/PyLibrary.h"
#include "hurricane/isobar/PyLayer.h"
#include <string>
#include <sstream>


namespace  CRL {

  using std::cerr;
  using std::endl;
  using std::hex;
  using std::string;
  using std::ostringstream;
  using Hurricane::tab;
  using Hurricane::Exception;
  using Hurricane::Bug;
  using Hurricane::Error;
  using Hurricane::Warning;
  using Hurricane::Library;
  using Hurricane::Layer;
  using Isobar::ProxyProperty;
  using Isobar::ProxyError;
  using Isobar::ConstructorError;
  using Isobar::HurricaneError;
  using Isobar::HurricaneWarning;
  using Isobar::PyAny_AsLong;
  using Isobar::getPyHash;
  using Isobar::ParseOneArg;
  using Isobar::ParseTwoArg;
  using Isobar::__cs;
  using Isobar::PyLibrary_Link;
  using Isobar::PyTypeLibrary;
  using Isobar::PyLibrary;
  using Isobar::PyLayer_Link;
  using Isobar::PyTypeLayer;
  using Isobar::PyLayer;
  using Isobar::IsPyDerivedLayer;


extern "C" {


#if defined(__PYTHON_MODULE__)

// +=================================================================+
// |             "PyLefImport" Python Module Code Part               |
// +=================================================================+


  static PyObject* PyLefImport_load ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyLefImport_load()" << endl;

    Library* library = NULL;
    
    HTRY
      char* lefFile = NULL;
      
      if (PyArg_ParseTuple( args, "s:LefImport.load", &lefFile )) {
        library = LefImport::load( lefFile );
      } else {
        PyErr_SetString ( ConstructorError, "LefImport.load(): Bad type or bad number of parameters." );
        return NULL;
      }
    HCATCH

    return (PyObject*)PyLibrary_Link(library);
  }


  static PyObject* PyLefImport_reset ( PyObject*, PyObject* )
  {
    cdebug_log(30,0) << "PyLefImport_reset()" << endl;
    HTRY
      LefImport::reset();
    HCATCH
    Py_RETURN_NONE;
  }


  static PyObject* PyLefImport_setMergeLibrary ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyLefImport_setMergeLibrary()" << endl;
    HTRY
      PyObject* pyLibrary = NULL;
      if (PyArg_ParseTuple( args, "O:LefImport.setMergeLibrary", &pyLibrary )) {
        if (IsPyLibrary(pyLibrary)) {
          LefImport::setMergeLibrary( PYLIBRARY_O(pyLibrary) );
        } else {
          PyErr_SetString( ConstructorError, "LefImport.setMergeLibrary(): Bad parameter type (not a Library)." );
          return NULL;
        }
      } else {
        PyErr_SetString( ConstructorError, "LefImport.setMergeLibrary(): Bad number of parameters." );
        return NULL;
      }
    HCATCH
    Py_RETURN_NONE;
  }


  static PyObject* PyLefImport_setGdsForeignLibrary ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyLefImport_setGdsForeignLibrary()" << endl;
    HTRY
      PyObject* pyLibrary = NULL;
      if (PyArg_ParseTuple( args, "O:LefImport.setGdsForeignLibrary", &pyLibrary )) {
        if (IsPyLibrary(pyLibrary)) {
          LefImport::setGdsForeignLibrary( PYLIBRARY_O(pyLibrary) );
        } else {
          PyErr_SetString( ConstructorError, "LefImport.setGdsForeignLibrary(): Bad parameter type (not a Library)." );
          return NULL;
        }
      } else {
        PyErr_SetString( ConstructorError, "LefImport.setGdsForeignLibrary(): Bad number of parameters." );
        return NULL;
      }
    HCATCH
    Py_RETURN_NONE;
  }


  static PyObject* PyLefImport_setGdsForeignDirectory ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyLefImport_setGdsForeignDirectory()" << endl;
    HTRY
      char* path = NULL;
      if (PyArg_ParseTuple( args, "s:LefImport.setGdsForeignDirectory", &path )) {
        LefImport::setGdsForeignDirectory( path );
      } else {
        PyErr_SetString ( ConstructorError, "LefImport.setGdsForeignDirectory(): Bad type or bad number of parameters." );
        return NULL;
      }
    HCATCH
    Py_RETURN_NONE;
  }


  static PyObject* PyLefImport_setPinFilter ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyLefImport_setPinFilter()" << endl;
    HTRY
      PyObject*     pyXThreshold = NULL;
      PyObject*     pyYThreshold = NULL;
      unsigned int  flags        = 0;
      if (PyArg_ParseTuple( args, "OOI:LefImport.setPinFilter", &pyXThreshold, &pyYThreshold, &flags )) {
        LefImport::setPinFilter( PyAny_AsLong(pyXThreshold), PyAny_AsLong(pyXThreshold), flags );
      } else {
        PyErr_SetString ( ConstructorError, "LefImport.setPinFilter(): Bad type or bad number of parameters." );
        return NULL;
      }
    HCATCH
    Py_RETURN_NONE;
  }

  static PyObject* PyLefImport_getLayer ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyLefImport_getLayer()" << endl;
    Layer* layer = NULL;
    HTRY
      char* name = NULL;
      if (PyArg_ParseTuple( args, "s:LefImport.getLayer", &name )) {
        layer = LefImport::getLayer( name );
      } else {
        PyErr_SetString ( ConstructorError, "LefImport.getLayer(): Bad type or bad number of parameters." );
        return NULL;
      }
    HCATCH
    return (PyObject*)PyLayer_Link(layer);
  }


  static PyObject* PyLefImport_addLayer ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyLefImport_addLayer()" << endl;
    HTRY
      char*     name    = NULL;
      PyObject* pyLayer = NULL;
      if (PyArg_ParseTuple( args, "sO:LefImport.addLayer", &name, &pyLayer )) {
        if (not IsPyDerivedLayer(pyLayer)) {
          PyErr_SetString( ConstructorError
                        , "PyLefImport.addLayer(): Second parameter is not of Layer type" );
          return NULL;
        }
        Layer* layer = PYLAYER_O(pyLayer);
        LefImport::addLayer( name, layer );
      } else {
        PyErr_SetString ( ConstructorError, "LefImport.addLayer(): Bad type or bad number of parameters." );
        return NULL;
      }
    HCATCH
    Py_RETURN_NONE;
  }


  static PyObject* PyLefImport_clearLayer ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyLefImport_clearLayer()" << endl;
    HTRY
      char* name = NULL;
      if (PyArg_ParseTuple( args, "s:LefImport.clearLayer", &name )) {
        LefImport::clearLayer( name );
      } else {
        PyErr_SetString ( ConstructorError, "LefImport.clearLayer(): Bad type or bad number of parameters." );
        return NULL;
      }
    HCATCH
    Py_RETURN_NONE;
  }

  // Standart Destroy (Attribute).


  PyMethodDef PyLefImport_Methods[] =
    { { "load"                  , (PyCFunction)PyLefImport_load                  , METH_VARARGS|METH_STATIC
                                , "Load a complete Cadence LEF library." }
    , { "reset"                 , (PyCFunction)PyLefImport_reset                 , METH_NOARGS|METH_STATIC
                                , "Reset the Cadence LEF parser (clear technology)." }
    , { "setGdsForeignLibrary"  , (PyCFunction)PyLefImport_setGdsForeignLibrary  , METH_VARARGS|METH_STATIC
                                , "Sets the library from which FOREIGN GDS cells will be searched." }
    , { "setMergeLibrary"       , (PyCFunction)PyLefImport_setMergeLibrary       , METH_VARARGS|METH_STATIC
                                , "Merge into this library instead of creating a new one." }
    , { "setGdsForeignDirectory", (PyCFunction)PyLefImport_setGdsForeignDirectory, METH_VARARGS|METH_STATIC
                                , "Set the directory where to find FOREIGN GDS files." }
    , { "setPinFilter"          , (PyCFunction)PyLefImport_setPinFilter          , METH_VARARGS|METH_STATIC
                                , "Select the way Rectilinear pins are converted to one rectangle." }
    , { "getLayer"              , (PyCFunction)PyLefImport_getLayer              , METH_VARARGS|METH_STATIC
                                , "Get Layer from LefImport map." }
    , { "addLayer"              , (PyCFunction)PyLefImport_addLayer              , METH_VARARGS|METH_STATIC
                                , "Add Layer to LefImport map." }
    , { "clearLayer"              , (PyCFunction)PyLefImport_clearLayer          , METH_VARARGS|METH_STATIC
                                , "Remove Layer from LefImport map." }
  //, { "destroy"               , (PyCFunction)PyLefImport_destroy  , METH_VARARGS
  //                            , "Destroy the associated hurricane object. The python object remains." }
    , {NULL, NULL, 0, NULL}     /* sentinel */
    };


  NoObjectDeleteMethod(LefImport)
  PyTypeObjectLinkPyTypeWithoutObject(LefImport,LefImport)


#else  // End of Python Module Code Part.


// +=================================================================+
// |              "PyLefImport" Shared Library Code Part             |
// +=================================================================+

  // Type Definition.
  PyTypeObjectDefinitionsOfModule(CRL,LefImport)


  extern  void  PyLefImport_postModuleInit ()
  {
    PyObject* constant;
    LoadObjectConstant(PyTypeLefImport.tp_dict,LefImport::PinFilter_NOFLAGS,"PinFilter_NOFLAGS");
    LoadObjectConstant(PyTypeLefImport.tp_dict,LefImport::PinFilter_TALLEST,"PinFilter_TALLEST");
    LoadObjectConstant(PyTypeLefImport.tp_dict,LefImport::PinFilter_WIDEST ,"PinFilter_WIDEST" );
    LoadObjectConstant(PyTypeLefImport.tp_dict,LefImport::PinFilter_LARGEST,"PinFilter_LARGEST" );
  }


#endif  // End of Shared Library Code Part.

}  // extern "C".

}  // CRL namespace.
