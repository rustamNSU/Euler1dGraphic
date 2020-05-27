#pragma once

#include <QtCore/QTimer>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QtCharts>
#include <QLabel>

#include "Euler1d.hpp"
#include "EulerRiemannProblem.hpp"
#include "InitialData.h"
#include "FiguresWindow.h"


class MainWindow : public QWidget {
Q_OBJECT // Macro for class which include own signals and slots
public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow();

    QSize sizeHint() const override;

    bool isOutTime();

public slots:

    /**
     * Return bool type:
     *   true - correct current layer number
     *   false - didn't plot graphics (out time boundary)
     */
    bool draw();

    void calculate();
    void next_layer();
    void previous_layer();

private:
    FiguresWindow* figuresWindow;
    InitialDataWindow* initialDataWindow;

    Euler1dState* numericalSolution = nullptr;
    EulerRiemannProblem* exactSolution = nullptr;

    bool isCalculated = false;
    int currentLayer = 0;
    double currentTime;
    QLabel* currentTimeLabel;
    Mesh mesh;
};
