
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QTimer>

#include <GL/gl.h>
#include <GL/glut.h>

class GLTestWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit GLTestWidget(QWidget *parent = nullptr)
        : QOpenGLWidget(parent)
    {
        QTimer *t = new QTimer(this);
        t->start();

        connect(t, &QTimer::timeout, this, [=] {update();});
    }

protected:
    void initializeGL()
    {
        glClearColor(0.3, 0.3, 0.6, 1);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_NORMALIZE);
        // glEnable(GL_POLYGON_OFFSET_FILL);
        // glPolygonMode(GL_FRONT, GL_LINE);
        glShadeModel(GL_SMOOTH);
        // QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        // f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // f->glClearDepthf(1.0f);
        // f->glEnable(GL_DEPTH_TEST);
        // f->glDepthFunc(GL_LEQUAL);
        // // f->glShadeModel(GL_SMOOTH);
        // f->glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    }

    void resizeGL(int w, int h)
    {
        glViewport(0, 0, w, h);
        // QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        // f->glViewport(0, 0, w, h);
    }

    void paintGL()
    {

        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();


            //Add ambient light
    GLfloat ambientColor[] = {0.6f, 0.2f, 0.4f, 1.0f}; //Color(0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    GLfloat lightColor0[] = {0.4f, 0.2f, 0.7f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 10.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

        //Add directed light
        GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
        //Coming from the direction (-1, 0.5, 0.5)
        GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

        // glColor3f(0.3, 0.4, 0.7);
        glRotatef(m_xRotated, 1.0, 0.0, 0.0);
        glRotatef(m_yRotated, 0.0, 1.0, 0.0);
        glRotatef(m_zRotated, 0.0, 0.0, 1.0);
        glScalef(.4, .4, .4);
        glColor3f(0.3, 0.4, 0.7);
        glutSolidTeapot(1.0f);
        glFlush();
        m_xRotated += 0.5;
        m_yRotated += 0.5;
        m_zRotated += 0.5;
    }

private:
    float m_xRotated, m_yRotated, m_zRotated;
};

class GLTestWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GLTestWindow(QWidget *parent = nullptr) 
        : QWidget(parent)
    {
        m_acceptBtn = new QPushButton(tr("OK"));
        m_cancelBtn = new QPushButton(tr("Cancel"));

        m_glTestWidget = new GLTestWidget;

        QHBoxLayout *btnsLayout = new QHBoxLayout;
        btnsLayout->addStretch();
        btnsLayout->addWidget(m_cancelBtn);
        btnsLayout->addWidget(m_acceptBtn);
        btnsLayout->addStretch();

        QVBoxLayout *centralLayout = new QVBoxLayout;
        centralLayout->addWidget(m_glTestWidget);
        centralLayout->addLayout(btnsLayout);

        setLayout(centralLayout);
    }

protected:
    void keyPressEvent(QKeyEvent *e)
    {
        switch (e->key())
        {
#ifdef QT_DEBUG
        case Qt::Key_Escape:    qApp->quit();       break;
#endif
        default:;
        }
    }

private:
    GLTestWidget *m_glTestWidget;
    QPushButton *m_acceptBtn;
    QPushButton *m_cancelBtn;
};

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication app(argc, argv);

    GLTestWindow *w = new GLTestWindow;
    w->showFullScreen();

    return app.exec();
}

#include "main.moc"