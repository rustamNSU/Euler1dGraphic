//
// Created by rustam on 27.05.2020.
//

#include "FiguresWindow.h"

FiguresWindow::FiguresWindow(QWidget *parent) :
    QWidget(parent)
{
    int all_charts = chartsTitle.size();

    /* number of charts along side */
    int rows = 1;
    while (rows*rows < all_charts)
    {
        ++rows;
    }

    this->setWindowTitle("Solution of Euler problem in 1D");

    QGridLayout* grid = new QGridLayout(this);

    /* dynamic widget size */
    for (int i = 0; i < rows; ++i){
        grid->setColumnStretch(i, 1);
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            if (i * rows + j >= all_charts) {break;}
            QChart* chart = new QChart;
            chart->setTitle(chartsTitle.at(i * rows + j));

            QChartView* chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            grid->addWidget(chartView, i, j, 1, 1);

            charts.append(chart);
            chartsView.append(chartView);
        }
    }

    setLayout(grid);
}


void FiguresWindow::drawData(double time,
                             const QList<QVector<QPointF>>& exact_data,
                             const QList<QVector<QPointF>>& numerical_data)
{
    int index = 0;
    for (auto chart : charts)
    {
        if (index >= exact_data.size()){
            break;
        }

        chart->removeAllSeries();
        QLineSeries* exact_series = new QLineSeries;
        QLineSeries* numerical_series = new QLineSeries;
        for (const auto& point : exact_data.at(index))
        {
            exact_series->append(point);
        }
        for (const auto& point : numerical_data.at(index))
        {
            numerical_series->append(point);
        }
        auto time_title = chartsTitle.at(index) +
                          QString(", t = ") +
                          QString::number(time);
        chart->setTitle(time_title);
        chart->addSeries(exact_series);
        chart->addSeries(numerical_series);
        exact_series->setName(QString("exact ") + chartsTitle.at(index));
        numerical_series->setName(QString("numerical ") + chartsTitle.at(index));

        chart->createDefaultAxes();

        ++index;
    }
}


FiguresWindow::~FiguresWindow() noexcept
{

}

QSize FiguresWindow::sizeHint() const
{
    return QSize(700, 700);
}


