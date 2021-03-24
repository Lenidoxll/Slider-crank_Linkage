#include "plot.h"
#include <QtMath>

Plot::Plot(QWidget *parent) : QWidget(parent)
{
    //this->resize(600, 100);

    customPlot = new QCustomPlot(this);
    customPlot->setGeometry(0, 0, this->width(), this->height());
    customPlot->setInteraction(QCP::iRangeZoom, true);
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->axisRect()->setRangeZoom(Qt::Vertical);
    customPlot->axisRect()->setRangeDrag(Qt::Vertical);

    customPlot->xAxis->setLabel("fi1g");
    customPlot->yAxis->setLabel("Vc and Ac");
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    customPlot->xAxis->setRange(0, 360);
    customPlot->yAxis->setRange(0, 100);

    for (int i = 0; i < 4; i++) {
         for (int j = 0; j < 3; j++) {
             if (i == 0) {                //O1
                 penV[i][j] = QPen(Qt::black, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
                 penA[i][j] = QPen(Qt::black, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
             } else if (i == 1) {         //A
                 penV[i][j] = QPen(Qt::black, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
                 penA[i][j] = QPen(Qt::black, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
             } else if (i == 2) {         //B
                 penV[i][j] = QPen(Qt::black, 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
                 penA[i][j] = QPen(Qt::black, 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
             } else {                     //C
                 penV[i][j] = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                 penA[i][j] = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
             }
         }
    }

    for (int i = 0; i < 4; i++) {
        if (i == 3) {
            currentSpeedStatus[i] = Constants::SHOWV;        //рисуем вектора скорости и ускорения только для точки C
            currentAccelStatus[i] = Constants::SHOWA;
        } else {
            currentSpeedStatus[i] = Constants::SHOWNOTHINGSPEED;
            currentAccelStatus[i] = Constants::SHOWNOTHINGACCEL;
        }
    }

    customPlot->replot();
}

void Plot::setColorO1(QColor *colors)
{
    for (int i = 0; i < 6; i++) {
        if (i < 3)
            penV[0][i] = QPen(colors[i], 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
        else
            penA[0][i - 3] = QPen(colors[i], 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    }
    delete colors;
}

void Plot::setColorA(QColor *colors)
{
    for (int i = 0; i < 6; i++) {
        if (i < 3)
            penV[1][i] = QPen(colors[i], 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
        else
            penA[1][i - 3] = QPen(colors[i], 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    }
    delete colors;
}

void Plot::setColorB(QColor *colors)
{
    for (int i = 0; i < 6; i++) {
        if (i < 3)
            penV[2][i] = QPen(colors[i], 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
        else
            penA[2][i - 3] = QPen(colors[i], 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    }
    delete colors;
}

void Plot::setColorC(QColor *colors)
{
    for (int i = 0; i < 6; i++) {
        if (i < 3)
            penV[3][i] = QPen(colors[i], 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        else
            penA[3][i - 3] = QPen(colors[i], 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    }
    delete colors;
}

void Plot::changedSpeedStatusO1(Constants::SpeedStatus status)
{
    currentSpeedStatus[0] = status;
    draw_plot();
}

void Plot::changedSpeedStatusA(Constants::SpeedStatus status)
{
    currentSpeedStatus[1] = status;
    draw_plot();
}

void Plot::changedSpeedStatusB(Constants::SpeedStatus status)
{
    currentSpeedStatus[2] = status;
    draw_plot();
}

void Plot::changedSpeedStatusC(Constants::SpeedStatus status)
{
    currentSpeedStatus[3] = status;
    draw_plot();
}

void Plot::changedAccelStatusO1(Constants::AccelStatus status)
{
    currentAccelStatus[0] = status;
    draw_plot();
}

void Plot::changedAccelStatusA(Constants::AccelStatus status)
{
    currentAccelStatus[1] = status;
    draw_plot();
}

void Plot::changedAccelStatusB(Constants::AccelStatus status)
{
    currentAccelStatus[2] = status;
    draw_plot();
}

void Plot::changedAccelStatusC(Constants::AccelStatus status)
{
    currentAccelStatus[3] = status;
    draw_plot();
}

void Plot::_add_points(double fi1g, double vo1x, double vo1y, double vo1, double ao1x, double ao1y, double ao1,
                       double vax, double vay, double va, double aax, double aay, double aa,
                       double vbx, double vby, double vb, double abx, double aby, double ab,
                       double vcx, double vcy, double vc, double acx, double acy, double ac)
{
    int realfi1g = qFloor(fi1g) % 360;

    if (Fi1g.empty()) {
        Fi1g.append(realfi1g);
        VO1x.append(vo1x);      //O1
        VO1y.append(vo1y);
        VO1.append(vo1);
        AO1x.append(ao1x);
        AO1y.append(ao1y);
        AO1.append(ao1);
        VAx.append(vax);        //A
        VAy.append(vay);
        VA.append(va);
        AAx.append(aax);
        AAy.append(aay);
        AA.append(aa);
        VBx.append(vbx);        //B
        VBy.append(vby);
        VB.append(vb);
        ABx.append(abx);
        ABy.append(aby);
        AB.append(ab);
        VCx.append(vcx);        //C
        VCy.append(vcy);
        VC.append(vc);
        ACx.append(acx);
        ACy.append(acy);
        AC.append(ac);
    } else if (realfi1g != Fi1g.first() and currentStatusOfCompleteness == NOTFULL) {
        Fi1g.append(realfi1g);
        VO1x.append(vo1x);      //O1
        VO1y.append(vo1y);
        VO1.append(vo1);
        AO1x.append(ao1x);
        AO1y.append(ao1y);
        AO1.append(ao1);
        VAx.append(vax);        //A
        VAy.append(vay);
        VA.append(va);
        AAx.append(aax);
        AAy.append(aay);
        AA.append(aa);
        VBx.append(vbx);        //B
        VBy.append(vby);
        VB.append(vb);
        ABx.append(abx);
        ABy.append(aby);
        AB.append(ab);
        VCx.append(vcx);        //C
        VCy.append(vcy);
        VC.append(vc);
        ACx.append(acx);
        ACy.append(acy);
        AC.append(ac);

        if (realfi1g++ == qFloor(Fi1g.first()))
            currentStatusOfCompleteness = FULL;
    }

    draw_plot();
}

void Plot::_restart(double fi1g, double vo1x, double vo1y, double vo1, double ao1x, double ao1y, double ao1,
                    double vax, double vay, double va, double aax, double aay, double aa,
                    double vbx, double vby, double vb, double abx, double aby, double ab,
                    double vcx, double vcy, double vc, double acx, double acy, double ac)
{
    int realfi1g = qFloor(fi1g) % 360;

    Fi1g.clear();
    VO1x.clear();      //O1
    VO1y.clear();
    VO1.clear();
    AO1x.clear();
    AO1y.clear();
    AO1.clear();
    VAx.clear();        //A
    VAy.clear();
    VA.clear();
    AAx.clear();
    AAy.clear();
    AA.clear();
    VBx.clear();        //B
    VBy.clear();
    VB.clear();
    ABx.clear();
    ABy.clear();
    AB.clear();
    VCx.clear();        //C
    VCy.clear();
    VC.clear();
    ACx.clear();
    ACy.clear();
    AC.clear();

    Fi1g.append(realfi1g);
    VO1x.append(vo1x);      //O1
    VO1y.append(vo1y);
    VO1.append(vo1);
    AO1x.append(ao1x);
    AO1y.append(ao1y);
    AO1.append(ao1);
    VAx.append(vax);        //A
    VAy.append(vay);
    VA.append(va);
    AAx.append(aax);
    AAy.append(aay);
    AA.append(aa);
    VBx.append(vbx);        //B
    VBy.append(vby);
    VB.append(vb);
    ABx.append(abx);
    ABy.append(aby);
    AB.append(ab);
    VCx.append(vcx);        //C
    VCy.append(vcy);
    VC.append(vc);
    ACx.append(acx);
    ACy.append(acy);
    AC.append(ac);

    customPlot->clearGraphs();
    customPlot->replot();
}

void Plot::draw_graph(QVector<double>& vector, QString name, QPen pen)
{
    customPlot->addGraph();
    int i = customPlot->graphCount();
    customPlot->graph(i - 1)->setPen(pen);
    customPlot->graph(i - 1)->setName(name);
    customPlot->graph(i - 1)->addData(Fi1g, vector);
    //qDebug() << "i = " <<i << Qt::endl;
}

void Plot::draw_plot()
{
    customPlot->clearGraphs();

    for (int i = 0; i < 4; i++) {
        if(currentSpeedStatus[i] == Constants::SHOWSPEED
                or currentSpeedStatus[i] == Constants::SHOWVX
                or currentSpeedStatus[i] == Constants::SHOWVXV
                or currentSpeedStatus[i] == Constants::SHOWVXY) {
            if (i == 0)
                draw_graph(VO1x, QString(tr("vO1x")), penV[i][0]);          //VO1x
            else if (i == 1)
                draw_graph(VAx, QString(tr("vAx")), penV[i][0]);            //VAx
            else if (i == 2)
                draw_graph(VBx, QString(tr("vBx")), penV[i][0]);            //VBx
            else if (i == 3)
                draw_graph(VCx, QString(tr("vCx")), penV[i][0]);            //VCx
        }

        if(currentSpeedStatus[i] == Constants::SHOWSPEED
                or currentSpeedStatus[i] == Constants::SHOWVY
                or currentSpeedStatus[i] == Constants::SHOWVYV
                or currentSpeedStatus[i] == Constants::SHOWVXY) {
            if (i == 0)
                draw_graph(VO1y, QString(tr("vO1y")), penV[i][1]);          //VO1y
            else if (i == 1)
                draw_graph(VAy, QString(tr("vAy")), penV[i][1]);            //VAy
            else if (i == 2)
                draw_graph(VBy, QString(tr("vBy")), penV[i][1]);            //VBy
            else if (i == 3)
                draw_graph(VCy, QString(tr("vCy")), penV[i][1]);            //VCy
        }

        if(currentSpeedStatus[i] == Constants::SHOWSPEED
                or currentSpeedStatus[i] == Constants::SHOWV
                or currentSpeedStatus[i] == Constants::SHOWVXV
                or currentSpeedStatus[i] == Constants::SHOWVYV) {
            if (i == 0)
                draw_graph(VO1, QString(tr("vO1")), penV[i][2]);          //VO1
            else if (i == 1)
                draw_graph(VA, QString(tr("vA")), penV[i][2]);            //VA
            else if (i == 2)
                draw_graph(VB, QString(tr("vB")), penV[i][2]);            //VB
            else if (i == 3)
                draw_graph(VC, QString(tr("vC")), penV[i][2]);            //VC
        }

        if(currentAccelStatus[i] == Constants::SHOWACCEL
                or currentAccelStatus[i] == Constants::SHOWAX
                or currentAccelStatus[i] == Constants::SHOWAXA
                or currentAccelStatus[i] == Constants::SHOWAXY) {
            if (i == 0)
                draw_graph(AO1x, QString(tr("aO1x")), penA[i][0]);          //AO1x
            else if (i == 1)
                draw_graph(AAx, QString(tr("aAx")), penA[i][0]);            //AAx
            else if (i == 2)
                draw_graph(ABx, QString(tr("aBx")), penA[i][0]);            //ABx
            else if (i == 3)
                draw_graph(ACx, QString(tr("aCx")), penA[i][0]);            //ACx
        }

        if(currentAccelStatus[i] == Constants::SHOWACCEL
                or currentAccelStatus[i] == Constants::SHOWAY
                or currentAccelStatus[i] == Constants::SHOWAYA
                or currentAccelStatus[i] == Constants::SHOWAXY) {
            if (i == 0)
                draw_graph(AO1y, QString(tr("aO1y")), penA[i][1]);          //AO1y
            else if (i == 1)
                draw_graph(AAy, QString(tr("aAy")), penA[i][1]);            //AAy
            else if (i == 2)
                draw_graph(ABy, QString(tr("aBy")), penA[i][1]);            //ABy
            else if (i == 3)
                draw_graph(ACy, QString(tr("aCy")), penA[i][1]);            //ACy
        }

        if(currentAccelStatus[i] == Constants::SHOWACCEL
                or currentAccelStatus[i] == Constants::SHOWA
                or currentAccelStatus[i] == Constants::SHOWAXA
                or currentAccelStatus[i] == Constants::SHOWAYA) {
            if (i == 0)
                draw_graph(AO1, QString(tr("aO1")), penA[i][2]);          //AO1
            else if (i == 1)
                draw_graph(AA, QString(tr("aA")), penA[i][2]);            //AA
            else if (i == 2)
                draw_graph(AB, QString(tr("aB")), penA[i][2]);            //AB
            else if (i == 3)
                draw_graph(AC, QString(tr("aC")), penA[i][2]);            //AC
        }
    }

    customPlot->legend->setVisible(true);
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));

    customPlot->replot();
}

void Plot::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    customPlot->setGeometry(0, 0, this->width(), this->height());
}
