/*

  Written by Onur Paça, PhD student at Istanbul Technical University in 2017
  for the first homework of Advanced Mesh Processing Class instructued by 
  Asst. Prof. Dr. Erkan Günpınar

  paca[at]itu.edu.tr
  onurpaca[at]gmail.com
  opaca[at]rotorbit.com

*/


#ifndef NEIGHBOURHIGHLIGHT_HH
#define NEIGHBOURHIGHLIGHT_HH

#include <algorithm>
#include <vector>
#include <iostream>

#include <QObject>

#include <OpenFlipper/BasePlugin/BaseInterface.hh>
#include <OpenFlipper/BasePlugin/ToolboxInterface.hh>
#include <OpenFlipper/BasePlugin/LoggingInterface.hh>
#include <OpenFlipper/common/Types.hh>
#include <ObjectTypes/TriangleMesh/TriangleMesh.hh>
#include <OpenFlipper/common/Types.hh>
#include <ObjectTypes/PolyMesh/PolyMesh.hh>
#include <OpenFlipper/BasePlugin/PluginFunctions.hh>
#include <OpenMesh/Core/Mesh/Attributes.hh>
#include <OpenMesh/Core/Utils/GenProg.hh>
#include <OpenMesh/Core/Utils/vector_traits.hh>
#include <OpenMesh/Core/Mesh/PolyConnectivity.hh>
#include <libs_required/OpenMesh/src/OpenMesh/Core/Mesh/PolyConnectivity.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <MeshTools/MeshNavigationT.hh>
#include <OpenMesh/Core/Geometry/MathDefs.hh>
#include <OpenFlipper/BasePlugin/BaseInterface.hh>
#include <OpenFlipper/BasePlugin/KeyInterface.hh>
#include <OpenFlipper/BasePlugin/MouseInterface.hh>
#include <OpenFlipper/BasePlugin/LoggingInterface.hh>
#include <OpenFlipper/BasePlugin/ToolboxInterface.hh>
#include <OpenFlipper/BasePlugin/ToolbarInterface.hh>
#include <OpenFlipper/BasePlugin/LoadSaveInterface.hh>
#include <OpenFlipper/BasePlugin/BackupInterface.hh>
#include <OpenFlipper/BasePlugin/INIInterface.hh>
#include <OpenFlipper/BasePlugin/ScriptInterface.hh>
#include <OpenFlipper/BasePlugin/SelectionInterface.hh>
#include <OpenFlipper/common/Types.hh>
#include <OpenFlipper/BasePlugin/PluginFunctions.hh>
#include <OpenFlipper/INIFile/INIFile.hh>
#include <ObjectTypes/PolyMesh/PolyMesh.hh>
#include <ObjectTypes/TriangleMesh/TriangleMesh.hh>
#include <ObjectTypes/PolyMesh/PolyMesh.hh>
#include <ObjectTypes/TriangleMesh/TriangleMesh.hh>
#include "OpenFlipper/BasePlugin/PluginFunctions.hh"



class NeighbourHighlightPlugin : public QObject, BaseInterface, ToolboxInterface, LoggingInterface
{
  Q_OBJECT
  Q_INTERFACES(BaseInterface)
  Q_INTERFACES(ToolboxInterface)
  Q_INTERFACES(LoggingInterface)
  signals:
    void updateView();
    void updatedObject(int _identifier, const UpdateType& _type);
    void log(Logtype _type, QString _message);
    void log(QString _message);
    void addToolbox( QString _name, QWidget* _widget );
  public:
    NeighbourHighlightPlugin();
    QString name() { return (QString("Neighbour Highlighter")); };
    QString description( ) { return (QString("Highlights the neighbours of a face")); };
   private:
    QSpinBox* facenoSpinbox_;
   private slots:
    void initializePlugin();
    void findNeighbours();
   public slots:
    QString version() { return QString("1.0"); };
};


#endif
