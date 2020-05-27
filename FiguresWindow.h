//
// Created by rustam on 27.05.2020.
//

#ifndef EULER1DPLOT_FIGURESWINDOW_H
#define EULER1DPLOT_FIGURESWINDOW_H

#include <QtCore/QTimer>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QtCharts>
#include <QList>
#include <QVector>

#include <vector>


class FiguresWindow : public QWidget {
Q_OBJECT // Macro for class which include own signals and slots
public:
    explicit FiguresWindow(QWidget* parent = nullptr);

    void drawData(double time,
                  const QList<QVector<QPointF>>& exact_data,
                  const QList<QVector<QPointF>>& numerical_data
    );

    ~FiguresWindow() noexcept;

private:
    QList<QChart*> charts;
    QList<QChartView*> chartsView;
    QList<QString> chartsTitle = {"density", "pressure", "velocity", "energy"};

private:
    QSize sizeHint() const override;
};

void draw_series(QChart* chart, QLineSeries* series, const QString &time_title);


#endif //EULER1DPLOT_FIGURESWINDOW_H
