#ifndef WINDOW_H
#define WINDOW_H

#include "transform3d.h"
#include "Vertex.h"

#include <QDebug>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLWindow>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

class QOpenGLShaderProgram;

class Window : public QOpenGLWindow,
               protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Window();

    // OpenGL Events

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void teardownGL();

protected slots:
    void update();

private:
    // OpenGL State Information
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram* m_program;
    QOpenGLBuffer m_vertex;


    // Shader Information
    int u_modelToWorld;
    int u_worldToView;
    QMatrix4x4 m_projection;
    Transform3D m_transform;

    // Private Helpers
    void printContextInformation();

};

#endif // WINDOW_H
