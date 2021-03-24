#include "menegement.h"
#include <QDebug>
#include <QEvent>

Menegement::Menegement(QWidget *parent) : QWidget(parent)
{
    MainWindow* firstMainWindow = new MainWindow();
    firstMainWindow->installEventFilter(this);
    firstMainWindow->setIdentification(0);
    manager.append(firstMainWindow);
    manager[0]->show();
    connect(manager[0]->newAct, &QAction::triggered, this, &Menegement::_new_mainWindow);
}

bool Menegement::eventFilter(QObject *pObject, QEvent *pEvent)
{
    for (int i = 0; i < manager.size(); i++) {
        if (manager[i] == pObject and pEvent->type() == QEvent::Close) {
                if (manager[i]->getIdentification() == i) {
                qDebug() << "count was = " << manager.size() << Qt::endl;
                delete manager[i];
                manager.remove(i);
                qDebug() << "count is = " << manager.size() << Qt::endl;
                while (i < manager.size()) {
                    manager[i]->setIdentification(i);
                    i++;
                }
                return true;
            }
        }
    }
    return false;
}

void Menegement::_new_mainWindow()
{
    qDebug() << "new count was = " << manager.size() << Qt::endl;
    MainWindow* window = new MainWindow();
    window->installEventFilter(this);
    window->setIdentification(manager.size());
    manager.append(window);
    qDebug() << "new count is = " << manager.size() << Qt::endl;
    manager[manager.size()-1]->show();
    connect(manager[manager.size()-1]->newAct, &QAction::triggered, this, &Menegement::_new_mainWindow);
}
