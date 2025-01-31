// Copyright (c) 2021 OPEN CASCADE SAS
//
// This file is part of the examples of the Open CASCADE Technology software library.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE

#ifndef OCCTQTVIEWER_H
#define OCCTQTVIEWER_H

#include <Standard_WarningsDisable.hxx>
#include <QOpenGLWidget>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_View.hxx>
#include "STEPControl_Reader.hxx"
#include "STEPCAFControl_Reader.hxx"
#include "STEPControl_Controller.hxx"
#include  "BRepBuilderAPI_Transform.hxx"
#include <AIS_Shape.hxx>
#include <AIS_Point.hxx>
#include <Geom_Point.hxx>
#include "StepData_StepModel.hxx"
#include  "Standard_Transient.hxx"
#include  "Interface_EntityIterator.hxx"
#include  "XSControl_TransferReader.hxx"
#include  "XSControl_WorkSession.hxx"
#include  "StepRepr_NextAssemblyUsageOccurrence.hxx"
#include  "Transfer_Binder.hxx"
#include  "TransferBRep.hxx"
#include  "Transfer_TransientProcess.hxx"
#include  "StepBasic_ProductDefinition.hxx"
#include  "StepBasic_Product.hxx"
#include  "XSControl_WorkSession.hxx"
#include  "StepRepr_RepresentationItem.hxx"
#include  "StepBasic_PlaneAngleUnit.hxx"
#include  "gp_Quaternion.hxx"
#include  "Graphic3d_TransformPers.hxx"
#include  "Geom2d_Circle.hxx"
#include  "gp_Circ2d.hxx"
#include  "BRepBuilderAPI_MakeVertex.hxx"
#include  "TopOpeBRep_ShapeIntersector.hxx"
#include  "TopoDS.hxx"


class AIS_ViewCube;

/*
    Виджет Viwrer
*/


class OcctQtViewer : public QOpenGLWidget, public AIS_ViewController
{
  Q_OBJECT
public:

  OcctQtViewer (QWidget* theParent = nullptr);
  virtual ~OcctQtViewer() override;

  //возращеам обьект viewer
  const Handle(V3d_Viewer)& Viewer() const { return myViewer; }
  //возращеам обьект view
  const Handle(V3d_View)& View() const { return myView; }
  //возращет контектс opengl
  const Handle(AIS_InteractiveContext)& Context() const { return myContext; }

  //парметтыр opengl
  const QString& getGlInfo() const { return myGlInfo; }
  virtual QSize minimumSizeHint() const override { return QSize(200, 200); }
  virtual QSize sizeHint()        const override { return QSize(720, 480); }

  virtual void OnSubviewChanged(const Handle(AIS_InteractiveContext)&,
                                const Handle(V3d_View)&,
                                const Handle(V3d_View)& theNewView) override;

  void SetRobotAngles(QList<float> angles);

  void LoadStep(QString fname);
  void LoadStepShapes();

protected:
  virtual void initializeGL() override;
  virtual void paintGL() override;

protected: // user input events
  virtual void closeEvent       (QCloseEvent*  theEvent) override;  
  virtual void mousePressEvent  (QMouseEvent*  theEvent) override;
  virtual void mouseReleaseEvent(QMouseEvent*  theEvent) override;
  virtual void mouseMoveEvent   (QMouseEvent*  theEvent) override;
  virtual void wheelEvent       (QWheelEvent*  theEvent) override;

private:

  Aspect_VKeyMouse qtMouseButtons2VKeys (Qt::MouseButtons theButtons);
  Aspect_VKeyFlags qtMouseModifiers2VKeys (Qt::KeyboardModifiers theModifiers);

  //выводоит информцию opengl
  void dumpGlInfo (bool theIsBasic, bool theToPrint);
  //иницирует перерисовку виджета PaitGl
  void updateView();
  //обработчки события перерисовки обтекта view
  virtual void handleViewRedraw (const Handle(AIS_InteractiveContext)& theCtx,
                                 const Handle(V3d_View)& theView) override;

private:
  Handle(V3d_Viewer)             myViewer;
  Handle(V3d_View)               myView;
  Handle(AIS_InteractiveContext) myContext;

  //куб смены вида
  Handle(AIS_ViewCube)           myViewCube;
  Handle(V3d_View)               myFocusView;

  Handle(AIS_Shape)              aShape;  
  //список AIS предствлений подвижный осей робота в модели
  QList<Handle(AIS_Shape)>       robotShape;  

  QString myGlInfo;
  bool myIsCoreProfile;

  //здесь храним точки вокруг которой вращаются соовтветсвующеи оси робота (точки крепления)
  //и единичиниые векторы, описывающие тракетории  вращенмя
  QList<gp_Ax1> rotateDirections;




};

#endif // _OcctQtViewer_HeaderFile
