#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    extern const double error;                      //погрешность вычислений

    enum orientation_l {    //ориентация (int2)
        right = 0,
        left = 1
    };

    enum On_or_off {
        on,
        off
    };

    enum Status_life {
        alive,
        dead
    };

    enum SpeedStatus {
        SHOWSPEED,
        SHOWV,
        SHOWVX,
        SHOWVY,
        SHOWVXY,
        SHOWVXV,
        SHOWVYV,
        SHOWNOTHINGSPEED
    };

    enum AccelStatus {
        SHOWACCEL,
        SHOWA,
        SHOWAX,
        SHOWAY,
        SHOWAXY,
        SHOWAXA,
        SHOWAYA,
        SHOWNOTHINGACCEL
    };

    enum status_pause_or_play {
        PAUSE,
        PLAY
    };
    enum status_mechanism_or_graphic {
        MECHANISM,
        GRAPHIC
    };

    double arcsin(double x);                        //вычисление арксинуса
    double arccos(double x);                        //вычисление арккосинуса
    double from_degrees_to_radians(double x);       //перевод из градусов в радианы
    double from_radians_to_degrees(double x);       //перевод из радиан в градусы

    void coord0(double x0, double y0, double x1h,
                double y1h, double fi1, double &x1, double &y1);                //перевод координат из одной системы счисления в другую
    void speed0(double vax, double vay, double om, double xbh,
                double ybh, double fi, double &vbx, double &vby, double &vb);   //перевод скоростей из одной системы счисления в другую
    void accel0(double aax, double aay, double om,
                double ep, double xbh, double ybh,
                double fi, double &abx, double &aby, double &ab);               //перевод ускорений из одной системы счисления в другую



}

#endif // CONSTANS_H
