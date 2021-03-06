//
// Created by rustam on 27.05.2020.
//

#ifndef EULER1DPLOT_INITIALDATA_H
#define EULER1DPLOT_INITIALDATA_H

#include <QtWidgets/QMainWindow>
#include <QtGlobal>
#include <QLineEdit>
#include <QString>

struct InitialData {
    qreal left = -2.0;
    qreal right = 2.0;
    int nodesNumber = 500;
    qreal gamma = 1.4;
    qreal endTime = 1.0;

    /* left */
    qreal ul = 0.0;
    qreal rhol = 1.0;
    qreal pl = 1.0;

    /* right */
    qreal ur = 0.0;
    qreal rhor = 0.125;
    qreal pr = 0.1;
};


class InitialDataWindow : public QWidget {
Q_OBJECT // Macro for class which include own signals and slots
public:
    explicit InitialDataWindow(QWidget* parent = nullptr);

    const InitialData& getInitialData() const;

    void updateInitialData();

    ~InitialDataWindow() noexcept ;

private:
    InitialData initialData;

    QLineEdit* line_p1;
    QLineEdit* line_u1;
    QLineEdit* line_rho1;

    QLineEdit* line_p2;
    QLineEdit* line_u2;
    QLineEdit* line_rho2;

    QLineEdit* line_Xmin;
    QLineEdit* line_Xmax;
    QLineEdit* line_N;

    QLineEdit* line_gamma;
    QLineEdit* line_endTime;
};


void transform_QLineEdit_to_qreal(QLineEdit* edit, qreal& item, qreal default_value = 0.0);
void transform_QLineEdit_to_int(QLineEdit* edit, int& item, int default_value = 0);


#endif //EULER1DPLOT_INITIALDATA_H
