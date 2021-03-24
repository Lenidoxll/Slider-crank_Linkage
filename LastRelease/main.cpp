#include "slider_crank_linkage.h"
#include "double_slider_crank_linkage.h"
#include "menu.h"
#include "mainwindow.h"
#include "menegement.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menegement w;
//    w.show();
    return a.exec();
}




/*
 *******************     ВОПРОСЫ     ***********************
1. Задать глобальные переменные в оном месте один раз:
    *погрешности вычислений (double error)
2. Были выкинуты:
    *CoordRotat2
    * QVector<double>& xapic, QVector<double>& yapic, QVector<double>& xbpic, QVector<double>& ybpic
    * bool& boolrot1
3. Как-то по-умному раскидать переменные по классам?
4. Подумать о том, как задать строгие размеры label и lineEdit
5. Настроить систему ловли ошибок
6. Настроить интернациональность
7. Поднастроить размеры values
8. Пока что для вода значений горячих клавиш нет. Нужны ли?
9. В конце сделать возможность настроек горячих клавиш
10. Настроить строку состояния.
11. Перейти, возможно, на QDataBasa и QSql.
12. Задать цвета виджетам через QPalette.
13. В чем проблема с QComboBox?
14. Прорисовка пути точек
15. Наладить ловлю ошибок
 */
