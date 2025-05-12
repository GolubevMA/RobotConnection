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

#include "vars.h"

#include <Standard_WarningsDisable.hxx>
#include <QOpenGLWidget>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_View.hxx>
#include  "BRepBuilderAPI_Transform.hxx"
#include "robotmotion.h"


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

  //загружаем модель сисетмы контроля
  void SetControlModel(ControlSystemModel * model) { robotModel = model;}

  //парметтыр opengl
  const QString& getGlInfo() const { return myGlInfo; }
  virtual QSize minimumSizeHint() const override { return QSize(200, 200); }
  virtual QSize sizeHint()        const override { return QSize(720, 480); }

  virtual void OnSubviewChanged(const Handle(AIS_InteractiveContext)&,
                                const Handle(V3d_View)&,
                                const Handle(V3d_View)& theNewView) override;

  //обновление углов осей работа
  void SetRobotAngles(JTPoint point);


private:

  Handle(V3d_Viewer)             myViewer;
  Handle(V3d_View)               myView;
  Handle(AIS_InteractiveContext) myContext;

  //куб смены вида
  Handle(AIS_ViewCube)           myViewCube;
  Handle(V3d_View)               myFocusView;

  Handle(AIS_Shape)              aShape;  

  QString myGlInfo;
  bool myIsCoreProfile;

  //струкутра визулаиции робота
  ControlSystemModel *robotModel;

  Aspect_VKeyMouse qtMouseButtons2VKeys (Qt::MouseButtons theButtons);
  Aspect_VKeyFlags qtMouseModifiers2VKeys (Qt::KeyboardModifiers theModifiers);

  //выводоит информцию opengl
  void dumpGlInfo (bool theIsBasic, bool theToPrint);
  //иницирует перерисовку виджета PaitGl
  void updateView();
  //обработчки события перерисовки обтекта view
  virtual void handleViewRedraw (const Handle(AIS_InteractiveContext)& theCtx,
                                 const Handle(V3d_View)& theView) override;

protected:
  virtual void initializeGL() override;
  virtual void paintGL() override;
  virtual void closeEvent       (QCloseEvent*  theEvent) override;
  virtual void mousePressEvent  (QMouseEvent*  theEvent) override;
  virtual void mouseReleaseEvent(QMouseEvent*  theEvent) override;
  virtual void mouseMoveEvent   (QMouseEvent*  theEvent) override;
  virtual void wheelEvent       (QWheelEvent*  theEvent) override;

};

#endif // _OcctQtViewer_HeaderFile
