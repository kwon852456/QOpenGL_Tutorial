#include "window.h"

// Create a colored triangle
static const Vertex sg_vertexes[] = {
    Vertex( QVector3D( 0.00f, 0.75f, 1.0f ), QVector3D( 1.0f, 0.0f, 0.0f )),
    Vertex( QVector3D( 0.75f,-0.75f, 1.0f ), QVector3D( 0.0f, 1.0f, 0.0f )),
    Vertex( QVector3D(-0.75f,-0.75f, 1.0f ), QVector3D( 0.0f, 0.0f, 1.0f ))
};



Window::Window()
{
    makeCurrent();
//    teardownGL();
}

Window::~Window(){

}

void Window::initializeGL()
{
  // Initialize OpenGL Backend
  initializeOpenGLFunctions();
  printContextInformation();

  // Set global information
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Application-specific initialization
  {
      m_program = new QOpenGLShaderProgram(); // only one variable to be allocated dynamicaly.
      m_program->addShaderFromSourceFile(QOpenGLShader::Vertex  , ":/shaders/simple.vert");
      m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
      m_program->link();
      m_program->bind();

      // Create Buffer ( Do not release util VAO is created)
      m_vertex.create();
      m_vertex.bind();
      m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
      m_vertex.allocate( sg_vertexes, sizeof( sg_vertexes ));

      // Create Vertex Array Object
      m_object.create();
      m_object.bind();
      m_program->enableAttributeArray(0);
      m_program->enableAttributeArray(1);
      m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
      m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride() );

      // Release ( unbind ) all
      m_object.release();
      m_vertex.release();
      m_program->release();

  }

}

void Window::resizeGL(int width, int height)
{
  // Currently we are not handling width/height changes
  (void)width;
  (void)height;
}
void Window::paintGL()
{
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);

  // Render using out shader
  m_program->bind();

  {
      m_object.bind();
      glDrawArrays( GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]) ); // from 0th index of sg_vertexes to max index
      m_object.release();
  }

  m_program->release();

}

void Window::teardownGL()
{
  // Currently we have no data to teardown

    m_object.destroy();
    m_vertex.destroy();
    delete m_program;

}

void Window::printContextInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  // qPrintable() will print our QString w/o quotes around it.
  qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

