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


void FiguresWindow::drawData(double time, const QList<QVector<QPointF>>& data)
{
    int index = 0;
    for (auto chart : charts)
    {
        if (index >= data.size()){
            break;
        }
        chart->removeAllSeries();
        QLineSeries* series = new QLineSeries;
        for (const auto& point : data.at(index))
        {
            series->append(point);
        }
        auto time_title = chartsTitle.at(index) +
                          QString(", t = ") +
                          QString::number(time);
        draw_series(chart, series, time_title);

        ++index;
    }
}


FiguresWindow::~FiguresWindow() noexcept
{

}


void draw_series(QChart* chart, QLineSeries* series, const QString& time_title)
{
    chart->addSeries(series);
    chart->legend()->markers(series)[0]->setVisible(false);
    chart->setTitle(time_title);
    chart->createDefaultAxes();
}

QSize FiguresWindow::sizeHint() const
{
    return QSize(700, 700);
}


