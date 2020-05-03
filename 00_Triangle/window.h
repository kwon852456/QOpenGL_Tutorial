#ifndef WINDOW_H
#define WINDOW_H

#include "Vertex.h"

#include <QDebug>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLWindow>
#include <QOpenGLBuffer>




class QOpenGLShaderProgram;

class Window : public QOpenGLWindow,
               protected QOpenGLFunctions
{
public:
    Window();
    ~Window();

    // OpenGL Events

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void teardownGL();

private:
    // OpenGL State Information
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram* m_program;
    QOpenGLBuffer m_vertex;

    // Private Helpers
    void printContextInformation();

};

#endif // WINDOW_H
