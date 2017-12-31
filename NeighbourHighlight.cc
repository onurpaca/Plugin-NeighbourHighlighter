/*

  Written by Onur Paça, PhD student at Istanbul Technical University in 2017
  for the first homework of Advanced Mesh Processing Class instructued by 
  Asst. Prof. Dr. Erkan Günpınar

  paca[at]itu.edu.tr
  onurpaca[at]gmail.com
  opaca[at]rotorbit.com

*/

#include "NeighbourHighlight.hh"

NeighbourHighlightPlugin::NeighbourHighlightPlugin() :
        facenoSpinbox_(0)
{
}
void NeighbourHighlightPlugin::initializePlugin()
{
  // Create the Toolbox Widget
  QWidget* toolBox = new QWidget();
  QPushButton* highlightButton = new QPushButton("&Highlight", toolBox);
  facenoSpinbox_ = new QSpinBox(toolBox);
  facenoSpinbox_->setMinimum(1);
  facenoSpinbox_->setMaximum(1000);
  facenoSpinbox_->setSingleStep(1);
  QLabel* label = new QLabel("Face No:");
  QGridLayout* layout = new QGridLayout(toolBox);
  layout->addWidget(label, 0, 0);
  layout->addWidget(highlightButton, 1, 1);
  layout->addWidget(facenoSpinbox_, 0, 1);
  layout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0, 1, 2);
  connect(highlightButton, SIGNAL(clicked()), this, SLOT(findNeighbours()));
  emit addToolbox(tr("Neighbour Highlighter"), toolBox);
}
void NeighbourHighlightPlugin::findNeighbours(){


  for (PluginFunctions::ObjectIterator o_it(PluginFunctions::TARGET_OBJECTS); o_it != PluginFunctions::objectsEnd(); ++o_it) {

    int faceno = facenoSpinbox_->value();  

    if (o_it->dataType() == DATA_TRIANGLE_MESH){
      TriMesh* MESH = PluginFunctions::triMesh(*o_it);

      TriMesh::FaceHandle     FACE = MESH->face_handle(faceno);
      TriMesh::VertexHandle   VERTEX;
      TriMesh::FaceVertexIter fv_it = MESH->fv_iter(FACE);
  
      TriMesh::FaceIter f_it, f_end = MESH->faces_end();
      TriMesh::VertexIter v_it, v_end = MESH->vertices_end();
      for (f_it = MESH->faces_begin(); f_it != f_end; ++f_it) {
        MESH->status(*f_it).set_selected(false);
      }
  
      for (v_it = MESH->vertices_begin(); v_it != v_end; ++v_it) {
        MESH->status(*v_it).set_selected(false);
      }
  
      for (; fv_it; ++fv_it){
         TriMesh::VertexFaceIter vf_it = MESH->vf_iter(*fv_it);
         for (; vf_it; ++vf_it){
           MESH->status(*vf_it).set_selected(true);
         }
      }
  
      MESH->status(FACE).set_selected(false);


      if (!MESH->has_vertex_colors()){
        MESH->request_vertex_colors();
      }
    } 
    else if (o_it->dataType() == DATA_POLY_MESH){
      PolyMesh* MESH = PluginFunctions::polyMesh(*o_it);

      PolyMesh::FaceHandle     FACE = MESH->face_handle(faceno);
      PolyMesh::VertexHandle   VERTEX;
      PolyMesh::FaceVertexIter fv_it = MESH->fv_iter(FACE);

      PolyMesh::FaceIter   f_it, f_end = MESH->faces_end();
      PolyMesh::VertexIter v_it, v_end = MESH->vertices_end();
      for (f_it = MESH->faces_begin(); f_it != f_end; ++f_it) {
        MESH->status(*f_it).set_selected(false);
      }

      for (v_it = MESH->vertices_begin(); v_it != v_end; ++v_it) {
        MESH->status(*v_it).set_selected(false);
      }

      for (; fv_it; ++fv_it){
         PolyMesh::VertexFaceIter vf_it = MESH->vf_iter(*fv_it);
         for (; vf_it; ++vf_it){
           MESH->status(*vf_it).set_selected(true);
         }
      }

      MESH->status(FACE).set_selected(false);

      if (!MESH->has_vertex_colors()){
        MESH->request_vertex_colors();
      }
    }
    
    emit updatedObject(o_it->id(), UPDATE_ALL);

  } 

}
Q_EXPORT_PLUGIN2(neighbourhighlightplugin, NeighbourHighlightPlugin);
