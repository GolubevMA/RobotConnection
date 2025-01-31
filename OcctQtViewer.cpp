
//#ifdef _WIN32
#include <windows.h>
//#endif
#include <OpenGl_Context.hxx>

#include "OcctQtViewer.h"

#include "OcctGlTools.h"

#include <Standard_WarningsDisable.hxx>
#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>
#include <Standard_WarningsRestore.hxx>

#include <AIS_ViewCube.hxx>
#include  "Prs3d_Drawer.hxx"
#include "Prs3d_DatumAspect.hxx"
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeRevolution.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <TopoDSToStep.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include  <gp_Ax2.hxx>
#include <Message.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <OpenGl_FrameBuffer.hxx>
#include <QTranslator>
#include "fstream"
#include "qdebug.h"



//подкласс фреймбуффера Opengl FBO , использует GL_RGGBA8 формат текстуры
// вызывает  OpenGl_Context::SetFrameBufferSRGB() с флагом  sRGB=false
// что указывает OCCT отключить  GL_FRAMEBUFFER_SRGB и применить гамма коекицю sRGB
class OcctQtFrameBuffer : public OpenGl_FrameBuffer
{
  DEFINE_STANDARD_RTTI_INLINE(OcctQtFrameBuffer, OpenGl_FrameBuffer)
public:

  OcctQtFrameBuffer() {}
  \
  //прриыязываем вершинный FBO к текущеуму OPengl контектсу
  virtual void BindBuffer (const Handle(OpenGl_Context)& theGlCtx) override
  {
    OpenGl_FrameBuffer::BindBuffer (theGlCtx);
    theGlCtx->SetFrameBufferSRGB (true, false);
  }

  //прриыязываем графический FBO к текущеуму OPengl контектсу
  virtual void BindDrawBuffer (const Handle(OpenGl_Context)& theGlCtx) override
  {
    OpenGl_FrameBuffer::BindDrawBuffer (theGlCtx);
    theGlCtx->SetFrameBufferSRGB (true, false);
  }

  //читаем текщуий буффер из контестка Opengl
  virtual void BindReadBuffer (const Handle(OpenGl_Context)& theGlCtx) override
  {
    OpenGl_FrameBuffer::BindReadBuffer (theGlCtx);
  }
};

// ================================================================
//конструрктор
// ================================================================
OcctQtViewer::OcctQtViewer (QWidget* theParent)
: QOpenGLWidget (theParent),
  myIsCoreProfile (true)
{

    rotateDirections << gp_Ax1(gp_Pnt(0,0,0), gp_Dir(0,0,1)) << gp_Ax1(gp_Pnt(100,0,360),gp_Dir(1,0,0)) << gp_Ax1(gp_Pnt(0,0,720),gp_Dir(1,0,0))
                << gp_Ax1(gp_Pnt(0,0,720),gp_Dir(0,0,1)) <<gp_Ax1(gp_Pnt(100,0,1086),gp_Dir(1,0,0)) <<gp_Ax1(gp_Pnt(0,0,0),gp_Dir(0,0,1));

    Handle(Aspect_DisplayConnection) aDisp = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) aDriver = new OpenGl_GraphicDriver (aDisp, false);

    // lets QOpenGLWidget to manage buffer swap
    aDriver->ChangeOptions().buffersNoSwap = true;
    // don't write into alpha channel
    aDriver->ChangeOptions().buffersOpaqueAlpha = true;
    // offscreen FBOs should be always used
    aDriver->ChangeOptions().useSystemBuffer = false;

    //создаем 3d Viewer
    myViewer = new V3d_Viewer (aDriver);
    myViewer->SetDefaultBackgroundColor (Quantity_NOC_BLACK);
    myViewer->SetDefaultLights();
    myViewer->SetLightOn();
    myViewer->ActivateGrid (Aspect_GT_Rectangular, Aspect_GDM_Lines);

    //инициалищирем контекст Viewera
    myContext = new AIS_InteractiveContext (myViewer);

    //создаем куб смены вида
    myViewCube = new AIS_ViewCube();
    myViewCube->SetViewAnimation (myViewAnimation);
    myViewCube->SetFixedAnimationLoop (false);
    myViewCube->SetAutoStartAnimation (true);
    myViewCube->TransformPersistence()->SetOffset2d (Graphic3d_Vec2i (100, 100));

    //ининицилизируем лейблы на граянх
    myViewCube->SetBoxSideLabel(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Front, TCollection_AsciiString((wchar_t*)tr("FFront").utf16()));
    myViewCube->SetBoxSideLabel(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Left, TCollection_AsciiString((wchar_t*)tr("LLeft").utf16()));
    myViewCube->SetBoxSideLabel(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Bottom, TCollection_AsciiString((wchar_t*)tr("BBot").utf16()));
    myViewCube->SetBoxSideLabel(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Back, TCollection_AsciiString((wchar_t*)tr("BBAck").utf16()));
    myViewCube->SetBoxSideLabel(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Right, TCollection_AsciiString((wchar_t*)tr("RRight").utf16()));
    myViewCube->SetBoxSideLabel(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Top, TCollection_AsciiString((wchar_t*)tr("TTop").utf16()));

    //myViewCube->SetBoxSideLabel(V3d_TypeOfOrientation::V3d_Yneg, TCollection_AsciiString((wchar_t*)tr("Front").utf16()));
    //  const Handle(Prs3d_Drawer)& aDrawer = myViewCube->Attributes();
    //  aDrawer->SetDatumAspect(new Prs3d_DatumAspect());
    //  const Handle(Prs3d_DatumAspect)& aDatumAsp = aDrawer->DatumAspect();
    //  aDatumAsp->TextAspect(Prs3d_DatumParts_XAxis)->SetColor (Quantity_NOC_RED);
    //  aDatumAsp->TextAspect(Prs3d_DatumParts_YAxis)->SetColor (Quantity_NOC_GREEN);
    //  aDatumAsp->TextAspect(Prs3d_DatumParts_ZAxis)->SetColor (Quantity_NOC_BLUE);

  myView = myViewer->CreateView();
  myView->ChangeRenderingParams().ToShowStats = true;
  myView->ChangeRenderingParams().CollectedStats = (Graphic3d_RenderingParams::PerfCounters )
    (Graphic3d_RenderingParams::PerfCounters_FrameRate
   | Graphic3d_RenderingParams::PerfCounters_Triangles);

  //пареметры вилждета
  setMouseTracking (true);
  setBackgroundRole (QPalette::NoRole); // or NoBackground
  setFocusPolicy (Qt::StrongFocus); // set focus policy to threat QContextMenuEvent from keyboard
  setUpdatesEnabled (true);
  setUpdateBehavior (QOpenGLWidget::NoPartialUpdate);

  //настройки opengl
  QSurfaceFormat aGlFormat;
  aGlFormat.setDepthBufferSize(24);
  aGlFormat.setStencilBufferSize(8);
  aDriver->ChangeOptions().contextDebug = aGlFormat.testOption (QSurfaceFormat::DebugContext);
  //aGlFormat.setOption (QSurfaceFormat::DeprecatedFunctions, true);
  if (myIsCoreProfile)
  {
    aGlFormat.setVersion (4, 5);
  }
  aGlFormat.setProfile (myIsCoreProfile ? QSurfaceFormat::CoreProfile : QSurfaceFormat::CompatibilityProfile);

  // request sRGBColorSpace colorspace to meet OCCT expectations or use OcctQtFrameBuffer fallback.
/*#if (QT_VERSION_MAJOR > 5) || (QT_VERSION_MAJOR == 5 && QT_VERSION_MINOR >= 10)
  aGlFormat.setColorSpace (QSurfaceFormat::sRGBColorSpace);
  setTextureFormat (GL_SRGB8_ALPHA8);
#else
  Message::SendWarning ("Warning! Qt 5.10+ is required for sRGB setup.\n"
                        "Colors in 3D Viewer might look incorrect (Qt " QT_VERSION_STR " is used).\n");
  aDriver->ChangeOptions().sRGBDisable = true;
#endif*/

    setFormat (aGlFormat);

    // never use ANGLE on Windows, since OCCT 3D Viewer does not expect this
    QCoreApplication::setAttribute (Qt::AA_UseDesktopOpenGL);

}

// ================================================================
// ~OcctQtViewer
// ================================================================
OcctQtViewer::~OcctQtViewer()
{
  Handle(Aspect_DisplayConnection) aDisp = myViewer->Driver()->GetDisplayConnection();

  // release OCCT viewer
  myContext->RemoveAll (false);
  myContext.Nullify();
  myView->Remove();
  myView.Nullify();
  myViewer.Nullify();

  makeCurrent();
  aDisp.Nullify();
}

// ================================================================
// Получаем параметры Opengl
// ================================================================
void OcctQtViewer::dumpGlInfo (bool theIsBasic, bool theToPrint)
{
  TColStd_IndexedDataMapOfStringString aGlCapsDict;
  myView->DiagnosticInformation (aGlCapsDict, theIsBasic ? Graphic3d_DiagnosticInfo_Basic : Graphic3d_DiagnosticInfo_Complete);
  TCollection_AsciiString anInfo;
  for (TColStd_IndexedDataMapOfStringString::Iterator aValueIter (aGlCapsDict); aValueIter.More(); aValueIter.Next())
  {
    if (!aValueIter.Value().IsEmpty())
    {
      if (!anInfo.IsEmpty())
      {
        anInfo += "\n";
      }
      anInfo += aValueIter.Key() + ": " + aValueIter.Value();
    }
  }

  if (theToPrint)
  {
    Message::SendInfo (anInfo);
  }
  myGlInfo = QString::fromUtf8 (anInfo.ToCString());
}

// ================================================================
// initializeGL
// ================================================================
void OcctQtViewer::initializeGL()
{
  const QRect aRect = rect();
  const Graphic3d_Vec2i aViewSize (aRect.right() - aRect.left(), aRect.bottom() - aRect.top());

  Handle(OpenGl_Context) aGlCtx = new OpenGl_Context();
  if (!aGlCtx->Init (myIsCoreProfile))
  {
    Message::SendFail() << "Error: OpenGl_Context is unable to wrap OpenGL context";
    QMessageBox::critical (this, "Failure", "OpenGl_Context is unable to wrap OpenGL context");
    QApplication::exit (1);
    return;
  }

  //конуфигурием окно View
  Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast (myView->Window());
    if (!aWindow.IsNull())
    {
        aWindow->SetSize (aViewSize.x(), aViewSize.y());
        myView->SetWindow (aWindow, aGlCtx->RenderingContext());
        dumpGlInfo (true, true);
    }
    else
    {   
        aWindow = new Aspect_NeutralWindow();
        aWindow->SetVirtual (true);

        Aspect_Drawable aNativeWin = (Aspect_Drawable )winId();
      #ifdef _WIN32
        //HGLRC aWglCtx    = wglGetCurrentContext();
        HDC   aWglDevCtx = wglGetCurrentDC();
        HWND  aWglWin    = WindowFromDC (aWglDevCtx);
        aNativeWin = (Aspect_Drawable )aWglWin;
      #endif
        aWindow->SetNativeHandle (aNativeWin);
        aWindow->SetSize (aViewSize.x(), aViewSize.y());
        myView->SetWindow (aWindow, aGlCtx->RenderingContext());
        dumpGlInfo (true, true);

        //оирисовываем куб смены вида
        myContext->Display (myViewCube, 0, 0, false);

    }

    //тествоые фигуры
    TopoDS_Shape aCylc = BRepPrimAPI_MakeCylinder(10, 50).Shape();
    gp_Trsf trf;
    trf.SetTranslation(gp_Vec(gp_Pnt(0,0,0), gp_Pnt(0,0,20)));
    aCylc.Move(trf);
    aShape = new AIS_Shape(aCylc);
    myContext->Display (aShape, AIS_Shaded, 0, false);


    LoadStepShapes();
}

// ================================================================
//  closeEvent
// ================================================================
void OcctQtViewer::closeEvent (QCloseEvent* theEvent)
{
  theEvent->accept();
}
// ================================================================
// вращаем детали робота
// ================================================================
void OcctQtViewer::SetRobotAngles(QList<float> angles)
{
    int angl_count = angles.length();
    if (angl_count > rotateDirections.length()) return;

    //корфигруции поворта осей
    QList<gp_Trsf> trsf;
    //конфигруеруем квантернион поворта текщзуей детали робота
    for (int i = 0; i < angl_count ; i++)
    {
        gp_Trsf tmp;
        //угол на ктороый вращем текеую деталь робота в радианах
        double angle = angles[i] * M_PI / 180;
        tmp.SetRotation(rotateDirections[i], angle);
        trsf.append(tmp);
    }

    //повораичаем оси робота  (для поворота 1й оси используются кватернионы поворта 1й и 0й оси)
    //для 2й оси - кватрнины 2й 1й и 0й оси ...
    for (int axis  = 0; axis < angl_count; axis++)
    {
        gp_Trsf cur_trans = gp_Trsf();
        for (int dep_ax = 0; dep_ax <= axis; dep_ax++) {
            //произовдим оперцию умножнения квантерионов для всех зависмых осей
            cur_trans *= trsf.at(dep_ax);
        }
        robotShape[axis]->SetLocalTransformation(TopLoc_Location(cur_trans));
        myContext->Update(robotShape[axis], true);
    }

    updateView();
}
// ================================================================
//конверитрувем коды кнопок qt мыши в коды кнопок смыцши opecaccade
// ================================================================
Aspect_VKeyMouse OcctQtViewer::qtMouseButtons2VKeys (Qt::MouseButtons theButtons)
{
  Aspect_VKeyMouse aButtons = Aspect_VKeyMouse_NONE;
  if ((theButtons & Qt::LeftButton) != 0)
  {
    aButtons |= Aspect_VKeyMouse_LeftButton;
  }
  if ((theButtons & Qt::MiddleButton) != 0)
  {
    aButtons |= Aspect_VKeyMouse_MiddleButton;
  }
  if ((theButtons & Qt::RightButton) != 0)
  {
    aButtons |= Aspect_VKeyMouse_RightButton;
  }
  return aButtons;
}
// ================================================================
Aspect_VKeyFlags OcctQtViewer::qtMouseModifiers2VKeys (Qt::KeyboardModifiers theModifiers)
{
  Aspect_VKeyFlags aFlags = Aspect_VKeyFlags_NONE;
  if ((theModifiers & Qt::ShiftModifier) != 0)
  {
    aFlags |= Aspect_VKeyFlags_SHIFT;
  }
  if ((theModifiers & Qt::ControlModifier) != 0)
  {
    aFlags |= Aspect_VKeyFlags_CTRL;
  }
  if ((theModifiers & Qt::AltModifier) != 0)
  {
    aFlags |= Aspect_VKeyFlags_ALT;
  }
  return aFlags;
}
// ================================================================
// mousePressEvent
// ================================================================
void OcctQtViewer::mousePressEvent (QMouseEvent* theEvent)
{
  QOpenGLWidget::mousePressEvent (theEvent);
  const Graphic3d_Vec2i aPnt (theEvent->pos().x(), theEvent->pos().y());
  const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(theEvent->modifiers());
  if (!myView.IsNull() && UpdateMouseButtons(aPnt,
                           qtMouseButtons2VKeys (theEvent->buttons()),
                           aFlags,
                           false))
  {
    updateView();
  }
}

// ================================================================
// mouseReleaseEvent
// ================================================================
void OcctQtViewer::mouseReleaseEvent (QMouseEvent* theEvent)
{
  QOpenGLWidget::mouseReleaseEvent (theEvent);
  const Graphic3d_Vec2i aPnt (theEvent->pos().x(), theEvent->pos().y());
  const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(theEvent->modifiers());
  if (!myView.IsNull()
    && UpdateMouseButtons (aPnt,
                           qtMouseButtons2VKeys (theEvent->buttons()),
                           aFlags,
                           false))
  {
    updateView();
  }
}
// ================================================================
// Function : mouseMoveEvent
// ================================================================
void OcctQtViewer::mouseMoveEvent (QMouseEvent* theEvent)
{
  QOpenGLWidget::mouseMoveEvent (theEvent);
  const Graphic3d_Vec2i aNewPos (theEvent->pos().x(), theEvent->pos().y());
  if (!myView.IsNull()
    && UpdateMousePosition (aNewPos, qtMouseButtons2VKeys(theEvent->buttons()),
                            qtMouseModifiers2VKeys (theEvent->modifiers()),
                            false))
  {
    updateView();
  }
}
// ==============================================================================
// wheelEvent
// ==============================================================================
void OcctQtViewer::wheelEvent (QWheelEvent* theEvent)
{
  QOpenGLWidget::wheelEvent (theEvent);
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
  const Graphic3d_Vec2i aPos (Graphic3d_Vec2d (theEvent->position().x(), theEvent->position().y()));
#else
  const Graphic3d_Vec2i aPos (theEvent->pos().x(), theEvent->pos().y());
#endif
  if (myView.IsNull())
  {
    return;
  }

  if (!myView->Subviews().IsEmpty())
  {
    Handle(V3d_View) aPickedView = myView->PickSubview (aPos);
    if (!aPickedView.IsNull()
      && aPickedView != myFocusView)
    {
      // switch input focus to another subview
      OnSubviewChanged (myContext, myFocusView, aPickedView);
      updateView();
      return;
    }
  }

  if (UpdateZoom (Aspect_ScrollDelta (aPos, double(theEvent->angleDelta().y()) / 8.0)))
  {
    updateView();
  }
}

// =======================================================================
// function : updateView
// purpose  :
// =======================================================================
void OcctQtViewer::updateView()
{
  update();
  //if (window() != NULL) { window()->update(); }
}

// ================================================================
// Function : paintGL
// Purpose  :
// ================================================================
void OcctQtViewer::paintGL()
{
  if (myView->Window().IsNull())
  {
    return;
  }

  //получаем FBO из opengl контектса виджета
  //Handle(OpenGl_GraphicDriver) aDriver = Handle(OpenGl_GraphicDriver)::DownCast (myContext->CurrentViewer()->Driver());
  //Handle(OpenGl_Context) aGlCtx = aDriver->GetSharedContext();

  Handle(OpenGl_Context) aGlCtx = OcctGlTools::GetGlContext(myView);
  Handle(OpenGl_FrameBuffer) aDefaultFbo = aGlCtx->DefaultFrameBuffer();
  if (aDefaultFbo.IsNull())
  {
    aDefaultFbo = new OcctQtFrameBuffer();
    aGlCtx->SetDefaultFrameBuffer (aDefaultFbo);
  }
  if (!aDefaultFbo->InitWrapper (aGlCtx))
  {
    aDefaultFbo.Nullify();
    Message::DefaultMessenger()->Send ("Default FBO wrapper creation failed", Message_Fail);
    QMessageBox::critical (this, "Failure", "Default FBO wrapper creation failed");
    QApplication::exit (1);
    return;
  }

  Graphic3d_Vec2i aViewSizeOld;
  //const QRect aRect = rect(); Graphic3d_Vec2i aViewSizeNew(aRect.right() - aRect.left(), aRect.bottom() - aRect.top());
  Graphic3d_Vec2i aViewSizeNew = aDefaultFbo->GetVPSize();
  Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast (myView->Window());
  aWindow->Size (aViewSizeOld.x(), aViewSizeOld.y());

  if (aViewSizeNew != aViewSizeOld)
  {
    aWindow->SetSize (aViewSizeNew.x(), aViewSizeNew.y());
    myView->MustBeResized();
    myView->Invalidate();
    dumpGlInfo (true, false);

    for (const Handle(V3d_View)& aSubviewIter : myView->Subviews())
    {
        aSubviewIter->MustBeResized();
        aSubviewIter->Invalidate();
        aDefaultFbo->SetupViewport(aGlCtx);
    }
  }

  // flush pending input events and redraw the viewer
  Handle(V3d_View) aView = !myFocusView.IsNull() ? myFocusView : myView;
  aView->InvalidateImmediate();
  FlushViewEvents(myContext, aView, true);



}
// ================================================================
// handleViewRedraw
// ================================================================
void OcctQtViewer::handleViewRedraw (const Handle(AIS_InteractiveContext)& theCtx,
                                     const Handle(V3d_View)& theView)
{
  AIS_ViewController::handleViewRedraw (theCtx, theView);
  if (myToAskNextFrame)
  {
    // ask more frames for animation
    updateView();
  }
}

// ================================================================
// Function : OnSubviewChanged
// ================================================================
void OcctQtViewer::OnSubviewChanged (const Handle(AIS_InteractiveContext)&,
                                     const Handle(V3d_View)&,
                                     const Handle(V3d_View)& theNewView)
{
  myFocusView = theNewView;
}
// ================================================================
//загрука STEP модели  робота
// ================================================================
void OcctQtViewer::LoadStep(QString filename)
{
}

void OcctQtViewer::LoadStepShapes()
{
    //парсин STEP
    Standard_CString fname = "J:\\test\\occt-samples-qopenglwidget-master\\occt-qopenglwidget\\RS007N-BC01.stp";
    //Standard_CString fname(filename.toLocal8Bit().data());

    STEPControl_Reader step_reader;
    int ret  = step_reader.ReadFile(fname);
    if (ret != IFSelect_ReturnStatus::IFSelect_RetDone) return;

    //обьекты trnafer reader
    const Handle_XSControl_WorkSession & theSession = step_reader.WS();
    const Handle_XSControl_TransferReader & aReader = theSession->TransferReader();
    const Handle_Transfer_TransientProcess & tp = aReader->TransientProcess();

    IFSelect_PrintCount mode = IFSelect_PrintCount(1);
    step_reader.PrintCheckLoad(false, mode);
    Standard_Integer NbRoots = step_reader.NbRootsForTransfer();
    qDebug() << "Nbroot " << NbRoots;
    Standard_Integer NbTrans = step_reader.TransferRoots();
    qDebug() << "STEP roots transferred " << NbTrans;
    qDebug() << "Number of resulting shapes is " << step_reader.NbShapes();

    //выполеям преобразования обьектов step в обьекты opencacade
    step_reader.TransferRoots();
    TopoDS_Shape aShape = step_reader.OneShape();

    //фигруы подвижных осей робота
    QList<TopoDS_Shape> jt_solids;
    //остальбные фигуры модели
    QList<TopoDS_Shape> othetr_solids;

    //проходимся по всем фигурам в данном наборе
    for(TopoDS_Iterator anIt(aShape); anIt.More(); anIt.Next())
    {
        const TopoDS_Shape &curShape = anIt.Value();
        //TopoDS_Shape shape = TransferBRep::ShapeResult(tp, transient);
        TopAbs_ShapeEnum type = curShape.ShapeType();

        //твердое телло
        if(type==TopAbs_SOLID)
        {
            //преобразовым shape в entity
            Handle(Standard_Transient) anEntity = aReader->EntityFromShapeResult(curShape, 1);
            if(!anEntity.IsNull())
            {
                //получаем entity NextAssemblyUsageOccurrence
                if (strcmp ((anEntity->DynamicType())->Name(), "StepRepr_NextAssemblyUsageOccurrence") == 0)
                {
                    Handle(StepRepr_NextAssemblyUsageOccurrence) entity = Handle(StepRepr_NextAssemblyUsageOccurrence)::DownCast(anEntity);
                    QString derailName = QString::fromLocal8Bit(entity->Name()->ToCString());

                    //если в названии детали есть номер оси - деталь является подвижной осью робота
                    if (derailName.contains(QRegExp("\\w+\\-\\w+\\_J\\d+")))
                    {
                        //добвелям элмент в списко деталей робота
                        jt_solids << curShape;
                        qDebug() << "axis " << derailName;
                    }
                    else {
                        //добавляе в список остальных деталей
                        othetr_solids << curShape;
                    }
                }
            }
        }
        //соствное твердое тело
        if(type == TopAbs_COMPOUND)
        {
            qDebug() <<"____COMPOUND____" ;
            for(TopoDS_Iterator anExp(curShape); anExp.More(); anExp.Next())
            {
                const TopoDS_Shape &curShape1 = anExp.Value();
                TopAbs_ShapeEnum type1 = curShape1.ShapeType();
//                if(type1==TopAbs_SHELL) {
//                    for(TopExp_Explorer anExp(curShape1,TopAbs_FACE);anExp.More();anExp.Next())
//                    {
//                        const TopoDS_Shape &curShape2 = anExp.Current();
//                        aShellBuilder.Add(aShell,curShape2);
//                        faceCount++;
//                    }
//                }
//                else if(type1 == TopAbs_EDGE)  {
//                    aWireBuilder.Add(aWire,curShape1);
//                    edgeCount++;
//                }
                //здесть можно тоже проыерять, если явлеятся частью робота
                if (type1 == TopAbs_SOLID)
                {
                    //добавляе в список остальных деталей
                    othetr_solids << curShape;
                }
            }
        }
    }


    //фомриурем набор нормалей к плоскостям
    //отнсительно которых вращаются оси робота

//    rotateDirections.clear();
//    rotateDirections.append(gp_Ax1(gp_Pnt(0,0,0), gp_Dir(0,0,0)));

    for (int i = 1; i < jt_solids.length(); i++)
    {
        //пересечения текущей  детали  с предыдущей
        TopOpeBRep_ShapeIntersector inspect;
        inspect.InitIntersection(jt_solids.at(i-1), jt_solids.at(i));

        //поверхность  пересчения набо выбрасть меньшую по площаи
        TopoDS_Shape s1 = inspect.CurrentGeomShape(i == 4 ? 1 : 2);
        if( s1.ShapeType() == TopAbs_FACE)
        {
            qDebug() << "is Face";
            TopoDS_Face face = TopoDS::Face(s1);
            //елси повернсть является послоктью
            BRepAdaptor_Surface surface = BRepAdaptor_Surface(face);
            if (surface.GetType() == GeomAbs_Plane) {
                qDebug() << "is plnae ";
                //получаем нормаль к полсокости в точкре крепления
                rotateDirections[i] = surface.Plane().Axis();
            }
        }
    }


    //отриосваем сосотваные детали
    for(int i=0; i< othetr_solids.length(); i++)
    {
        const Handle(AIS_Shape) &anAIS_Shape = new AIS_Shape(othetr_solids.at(i));
        myContext->Display(anAIS_Shape,AIS_Shaded, 0 ,false);
    }
    //отрисовываем цельные детали (оси)
    for(int i=0; i< jt_solids.length(); i++)
    {
        jt_solids[i].Orientation(TopAbs_Orientation::TopAbs_FORWARD);
        Handle(AIS_Shape) anAIS_Shape = new AIS_Shape(jt_solids[i]);
        robotShape.append(anAIS_Shape);
        myContext->Display(anAIS_Shape,AIS_Shaded, 0 ,false);
    }

}
