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

public slots:
    void draw();

private:
    FiguresWindow* figuresWindow;
    InitialDataWindow* initialDataWindow;

    EulerRiemannProblem exactSolution;
    double currentTime;
    QLabel* currentTimeLabel;
    Mesh mesh;

};

void transform_QLineEdit_to_qreal(QLineEdit* edit, qreal* item, qreal default_value = 0.0);
