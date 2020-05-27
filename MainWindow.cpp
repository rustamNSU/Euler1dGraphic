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
    grid->addWidget(figuresWindow, 0, 1, 1, 1);
    grid->setColumnStretch(0, 0);
    grid->setColumnStretch(1, 1);


    auto panel = new QGridLayout;
    auto panel_title = new QLabel("Control panel", this);
    panel->addWidget(panel_title, 0, 0, 1, 3);
    panel_title->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    panel_title->setFrameStyle(QFrame::Panel | QFrame::Plain);
    panel_title->setLineWidth(2);

    auto current_time_title = new QLabel("current time = ");
    current_time_title->setAlignment(Qt::AlignLeft);
    panel->addWidget(current_time_title, 1, 0, 1, 2);

    currentTimeLabel = new QLabel(this);
    currentTimeLabel->setNum(currentTime);
    panel->addWidget(currentTimeLabel, 1, 1, 1, 1);

    auto calculate_btn = new QPushButton("Calculate");
    connect(calculate_btn, &QPushButton::clicked, this, &MainWindow::calculate);
    panel->addWidget(calculate_btn, 2, 0, 1, 1);

    auto next_btn = new QPushButton("next");
    connect(next_btn, &QPushButton::clicked, this, &MainWindow::next_layer);
    next_btn->setShortcut(QKeySequence(Qt::Key_Right));

    auto previous_btn = new QPushButton("prev.");
    connect(previous_btn, &QPushButton::clicked, this, &MainWindow::previous_layer);
    previous_btn->setShortcut(QKeySequence(Qt::Key_Left));

    panel->addWidget(next_btn, 2, 2, 1, 1);
    panel->addWidget(previous_btn, 2, 1, 1, 1);

    grid->addLayout(panel, 1, 0, 1, 1);

    setLayout(grid);
}

/**
 * Return bool type:
 *   true - correct current layer number
 *   false - didn't plot graphics (out time boundary)
 */
bool MainWindow::draw()
{
    if (isOutTime()) {return false;}
    double current_time = numericalSolution->GetLayerTime(currentLayer);
    currentTimeLabel->setNum(current_time);
    currentTime = current_time;

    QVector<QPointF> density;
    QVector<QPointF> pressure;
    QVector<QPointF> velocity;
    QVector<QPointF> energy;

    QVector<QPointF> numerical_density;
    QVector<QPointF> numerical_pressure;
    QVector<QPointF> numerical_velocity;
    QVector<QPointF> numerical_energy;
    for (int i = 0; i < mesh.GetSize(); ++i)
    {
        auto euler_variable = (*exactSolution)(mesh[i], current_time);
        density.push_back(QPointF(euler_variable.x, euler_variable.rho));
        pressure.push_back(QPointF(euler_variable.x, euler_variable.pressure));
        velocity.push_back(QPointF(euler_variable.x, euler_variable.u));
        energy.push_back(QPointF(euler_variable.x, euler_variable.energy));

        auto elv = numericalSolution->GetEulerVariables(currentLayer, i);
        numerical_density.push_back(QPointF(elv.x, elv.rho));
        numerical_pressure.push_back(QPointF(elv.x, elv.pressure));
        numerical_velocity.push_back(QPointF(elv.x, elv.u));
        numerical_energy.push_back(QPointF(elv.x, elv.energy));
    }

    figuresWindow->drawData(current_time,
                            QList{density, pressure, velocity, energy},
                            QList{numerical_density, numerical_pressure, numerical_velocity, numerical_energy});
    return true;
}

void MainWindow::calculate()
{
    if (exactSolution)
    {
        delete exactSolution;
    }
    if (numericalSolution)
    {
        delete numericalSolution;
    }

    initialDataWindow->updateInitialData();

    exactSolution = new EulerRiemannProblem;
    exactSolution->setInitialValues(
            initialDataWindow->getInitialData().rhol,
            initialDataWindow->getInitialData().ul,
            initialDataWindow->getInitialData().pl,
            initialDataWindow->getInitialData().rhor,
            initialDataWindow->getInitialData().ur,
            initialDataWindow->getInitialData().pr,
            initialDataWindow->getInitialData().gamma
    );

    exactSolution->DefineRiemannWaveType();

    numericalSolution = new Euler1dState(initialDataWindow->getInitialData().left,
                                         initialDataWindow->getInitialData().right,
                                         initialDataWindow->getInitialData().nodesNumber
    );

    // initial condition
    auto createStep = [](double left_value, double right_value)
    {
        auto result_lambda = [left_value, right_value](double x)
        {
            if (x < 0.0) {return left_value; }
            else {return right_value; }
        };
        return result_lambda;
    };

    numericalSolution->SetInitialValues(
            createStep(initialDataWindow->getInitialData().ul, initialDataWindow->getInitialData().ur),
            createStep(initialDataWindow->getInitialData().rhol, initialDataWindow->getInitialData().rhor),
            createStep(initialDataWindow->getInitialData().pl, initialDataWindow->getInitialData().pr)
    );

    numericalSolution->Calculate(RoeSolver, initialDataWindow->getInitialData().endTime);
    mesh = numericalSolution->GetMesh();

    currentLayer = 0;
    draw();
    isCalculated = true;
}

void MainWindow::next_layer()
{
    if (!isCalculated) {return;}
    ++currentLayer;
    if (draw())
    {
        return;
    }
    else {
        --currentLayer;
    }
}

void MainWindow::previous_layer()
{
    if (!isCalculated) {return;}
    if (currentLayer == 0)
    {
        return;
    }
    else{
        --currentLayer;
        draw();
    }
}

QSize MainWindow::sizeHint() const
{
    return QSize(1024, 780);
}

bool MainWindow::isOutTime()
{
    return currentLayer >= numericalSolution->GetLayersNumber();
}


MainWindow::~MainWindow()
{
    if (figuresWindow) {delete figuresWindow;}
    if (initialDataWindow) {delete initialDataWindow;}
    if (numericalSolution) {delete numericalSolution;}
    if (exactSolution) {delete exactSolution;}
}