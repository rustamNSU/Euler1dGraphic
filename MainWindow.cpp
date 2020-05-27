#include <iostream>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
        QWidget(parent)
{
    this->setWindowTitle("Solution of Euler problem in 1D");
    figuresWindow = new FiguresWindow(this);
    initialDataWindow = new InitialDataWindow(this);

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(initialDataWindow, 0, 0, 1, 1);
    grid->addWidget(figuresWindow, 0, 1, 2, 1);
    grid->setColumnStretch(0, 0);
    grid->setColumnStretch(1, 1);


    auto panel = new QGridLayout;
    auto panel_title = new QLabel("Control panel", this);
    panel->addWidget(panel_title, 0, 0, 1, 2);
    panel_title->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    panel_title->setFrameStyle(QFrame::Panel | QFrame::Plain);
    panel_title->setLineWidth(2);

    auto current_time_title = new QLabel("current time = ");
    current_time_title->setAlignment(Qt::AlignLeft);
    panel->addWidget(current_time_title, 1, 0, 1, 1);

    currentTimeLabel = new QLabel(this);
    currentTimeLabel->setNum(currentTime);
    panel->addWidget(currentTimeLabel, 1, 1, 1, 1);

    auto calculate_btn = new QPushButton("Calculate");
    connect(calculate_btn, &QPushButton::clicked, this, &MainWindow::draw);
    panel->addWidget(calculate_btn, 2, 0, 1, 2);

    grid->addLayout(panel, 1, 0, 1, 1);

    setLayout(grid);

    exactSolution.setInitialValues(
            initialDataWindow->getInitialData().rhol,
            initialDataWindow->getInitialData().ul,
            initialDataWindow->getInitialData().pl,
            initialDataWindow->getInitialData().rhor,
            initialDataWindow->getInitialData().ur,
            initialDataWindow->getInitialData().pr,
            initialDataWindow->getInitialData().gamma
    );

    exactSolution.DefineRiemannWaveType();
    mesh.SetMesh(initialDataWindow->getInitialData().nodesNumber,
                 initialDataWindow->getInitialData().left,
                 initialDataWindow->getInitialData().right
    );

}

void MainWindow::draw()
{
    currentTime += 0.1;
    currentTimeLabel->setNum(currentTime);

    QVector<QPointF> density;
    QVector<QPointF> pressure;
    QVector<QPointF> velocity;
    for (int i = 0; i < mesh.GetSize(); ++i)
    {
        auto euler_variable = exactSolution(mesh[i], currentTime);
        density.push_back(QPointF(euler_variable.x, euler_variable.rho));
        pressure.push_back(QPointF(euler_variable.x, euler_variable.pressure));
        velocity.push_back(QPointF(euler_variable.x, euler_variable.u));
    }

    figuresWindow->drawData(currentTime, QList{density, pressure, velocity});
}

QSize MainWindow::sizeHint() const
{
    return QSize(1024, 780);
}


MainWindow::~MainWindow()
{
}


void transform_QLineEdit_to_qreal(QLineEdit* edit, qreal* item, qreal default_value)
{
    if (edit->text().isEmpty())
    {
        *item = default_value;
        edit->setText(QString::number(default_value));
    }
    else
    {
        *item = edit->text().toDouble();
    }
}
