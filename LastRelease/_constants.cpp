#include "_constants.h"
#include <QtMath>

namespace Constants {
    extern const double error(0.0001);

    double arcsin(double x)
    {
        double xd; //дополнтельные переменные
        xd = 1 - x*x;
        if (qAbs(xd) <= Constants::error){ // if (xd == 0)
            if (x > Constants::error) // x > 0
                return M_PI_2;
            else
                return -M_PI_2;
        }
        return qAtan(x / qSqrt(xd));
    }

    double arccos(double x)
    {
        if (qAbs(x) <= Constants::error)
            return M_PI_2;
        double t = qSqrt(1 - x*x) / x;
        if (x > Constants::error)
            return qAtan(t);
        else
            return qAtan(t) + M_PI;
    }

    double from_degrees_to_radians(double x)
    {
        return x*M_PI/180;
    }

    double from_radians_to_degrees(double x)
    {
        return x*180/M_PI;
    }

    void coord0(double x0, double y0, double x1h, double y1h, double fi1,
                                      double &x1, double &y1)
    {
        x1 = x0 + x1h * qCos(fi1) - y1h * qSin(fi1);
        y1 = y0 + x1h * qSin(fi1) + y1h * qCos(fi1);
    }

    void speed0(double vax, double vay, double om, double xbh, double ybh, double fi,
                                      double &vbx, double &vby, double &vb)
    {
        vbx = vax - om*(xbh*qSin(fi) + ybh*qCos(fi));
        vby = vay + om*(xbh*qCos(fi) - ybh*qSin(fi));
        vb  = qSqrt(vbx*vbx + vby*vby);
    }

    void accel0(double aax, double aay, double om, double ep, double xbh, double ybh, double fi,
                                      double &abx, double &aby, double &ab)
    {
        double lsf, lcf;
        lsf = xbh*qSin(fi) + ybh*qCos(fi);
        lcf = xbh*cos(fi) - ybh*sin(fi);
        abx = aax - ep*lsf- om*om*lcf;
        aby = aay + ep*lcf- om*om*lsf;
        ab  = qSqrt(abx*abx + aby*aby);
    }

}
