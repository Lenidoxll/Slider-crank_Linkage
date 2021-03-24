#ifndef PLOT_2_H
#define PLOT_2_H

#include <QWidget>
#include "qcustomplot.h"
#include "_constants.h"

class Plot_2 : public QWidget
{
    Q_OBJECT
public:
    explicit Plot_2(QWidget *parent = nullptr);
    void setColorO1(QColor *colors);
    void setColorA(QColor *colors);
    void setColorB(QColor *colors);
    void setColorC(QColor *colors);
    void setColorO2(QColor *colors);
    void changedSpeedStatusO1(Constants::SpeedStatus status);
    void changedSpeedStatusA(Constants::SpeedStatus status);
    void changedSpeedStatusB(Constants::SpeedStatus status);
    void changedSpeedStatusC(Constants::SpeedStatus status);
    void changedSpeedStatusO2(Constants::SpeedStatus status);
    void changedAccelStatusO1(Constants::AccelStatus status);
    void changedAccelStatusA(Constants::AccelStatus status);
    void changedAccelStatusB(Constants::AccelStatus status);
    void changedAccelStatusC(Constants::AccelStatus status);
    void changedAccelStatusO2(Constants::AccelStatus status);

    QCustomPlot *customPlot;

private:
    QVector <double> Fi1g;
    QVector <double> VO1x, VO1y, VO1, AO1x, AO1y, AO1;
    QVector <double> VAx, VAy, VA, AAx, AAy, AA;
    QVector <double> VBx, VBy, VB, ABx, ABy, AB;
    QVector <double> VCx, VCy, VC, ACx, ACy, AC;
    QVector <double> VO2x, VO2y, VO2, AO2x, AO2y, AO2;

    QPen penV[5][3], penA[5][3];                    //строки - точки; столбцы - проекции

    Constants::SpeedStatus currentSpeedStatus[5];   //VO1, VA, VB, VC, VO2
    Constants::AccelStatus currentAccelStatus[5];   //AO1, AA, AB, AC, AO2

    enum status_of_completeness {
        FULL,
        NOTFULL
    };
    status_of_completeness currentStatusOfCompleteness = NOTFULL;

    void draw_graph(QVector<double>& vector, QString name, QPen pen);
    void draw_plot();

public slots:
    void resizeEvent(QResizeEvent* event);

    void _add_points(double fi1g, double vo1x, double vo1y, double vo1, double ao1x, double ao1y, double ao1,
                     double vax, double vay, double va, double aax, double aay, double aa,
                     double vbx, double vby, double vb, double abx, double aby, double ab,
                     double vcx, double vcy, double vc, double acx, double acy, double ac,
                     double vo2x, double vo2y, double vo2, double ao2x, double ao2y, double ao2);
    void _restart(double fi1g, double vo1x, double vo1y, double vo1, double ao1x, double ao1y, double ao1,
                  double vax, double vay, double va, double aax, double aay, double aa,
                  double vbx, double vby, double vb, double abx, double aby, double ab,
                  double vcx, double vcy, double vc, double acx, double acy, double ac,
                  double vo2x, double vo2y, double vo2, double ao2x, double ao2y, double ao2);
    void incorrect_datas();

    inline void _add_VO1x(double vo1x) { VO1x.append(vo1x); }
    inline void _add_VO1y(double vo1y) { VO1y.append(vo1y); }
    inline void _add_VO1(double vo1) { VO1.append(vo1); }
    inline void _add_AO1x(double ao1x) { AO1x.append(ao1x); }
    inline void _add_AO1y(double ao1y) { AO1y.append(ao1y); }
    inline void _add_AO1(double ao1) { AO1.append(ao1); }

    inline void _add_VAx(double vax) { VAx.append(vax); }
    inline void _add_VAy(double vay) { VAy.append(vay); }
    inline void _add_VA(double va) { VA.append(va); }
    inline void _add_AAx(double aax) { AAx.append(aax); }
    inline void _add_AAy(double aay) { AAy.append(aay); }
    inline void _add_AA(double aa) { AA.append(aa); }

    inline void _add_VBx(double vbx) { VBx.append(vbx); }
    inline void _add_VBy(double vby) { VBy.append(vby); }
    inline void _add_VB(double vb) { VB.append(vb); }
    inline void _add_ABx(double abx) { ABx.append(abx); }
    inline void _add_ABy(double aby) { ABy.append(aby); }
    inline void _add_AB(double ab) { AB.append(ab); }

    inline void _add_VCx(double vcx) { VCx.append(vcx); }
    inline void _add_VCy(double vcy) { VCy.append(vcy); }
    inline void _add_VC(double vc) { VC.append(vc); }
    inline void _add_ACx(double acx) { ACx.append(acx); }
    inline void _add_ACy(double acy) { ACy.append(acy); }
    inline void _add_AC(double ac) { AC.append(ac); }

    inline void _clear_VO1x() { VO1x.clear(); }
    inline void _clear_VO1y() { VO1y.clear(); }
    inline void _clear_VO1() { VO1.clear(); }
    inline void _clear_AO1x() { AO1x.clear(); }
    inline void _clear_AO1y() { AO1y.clear(); }
    inline void _clear_AO1() { AO1.clear(); }

    inline void _clear_VAx() { VAx.clear(); }
    inline void _clear_VAy() { VAy.clear(); }
    inline void _clear_VA() { VA.clear(); }
    inline void _clear_AAx() { AAx.clear(); }
    inline void _clear_AAy() { AAy.clear(); }
    inline void _clear_AA() { AA.clear(); }

    inline void _clear_VBx() { VBx.clear(); }
    inline void _clear_VBy() { VBy.clear(); }
    inline void _clear_VB() { VB.clear(); }
    inline void _clear_ABx() { ABx.clear(); }
    inline void _clear_ABy() { ABy.clear(); }
    inline void _clear_AB() { AB.clear(); }

    inline void _clear_VCx() { VCx.clear(); }
    inline void _clear_VCy() { VCy.clear(); }
    inline void _clear_VC() { VC.clear(); }
    inline void _clear_ACx() { ACx.clear(); }
    inline void _clear_ACy() { ACy.clear(); }
    inline void _clear_AC() { AC.clear(); }

    inline void _add_VO2x(double vo1x) { VO2x.append(vo1x); }
    inline void _add_VO2y(double vo1y) { VO2y.append(vo1y); }
    inline void _add_VO2(double vo1) { VO2.append(vo1); }
    inline void _add_AO2x(double ao1x) { AO2x.append(ao1x); }
    inline void _add_AO2y(double ao1y) { AO2y.append(ao1y); }
    inline void _add_AO2(double ao1) { AO2.append(ao1); }
};

#endif // PLOT_2_H
