#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "mysquare.h"
#include "SimpleVector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_activated(int index); // использование класса объектов
    // следующие слоты работают для выделенных объектов
    void keyPressEvent(QKeyEvent *d); // при нажатии активируется триггер
    void on_RB_RED_clicked(); // перекрашивает объекты в КРАСНЫЙ
    void on_RB_BLUE_clicked(); // перекрашивает объекты в СИНИЙ
    void on_RB_GREEN_clicked(); // перекрашивает объекты в ЗЕЛЕНЫЙ
    void on_doubleSpinBox_valueChanged(double arg1); // устанавливает размер
    void on_pushButton_Delete_clicked(); // очистка формы от фигур
    void on_pushButton_Save_clicked(); // сохраняет выделенные фигуры из формы
    void on_pushButton_Out_clicked(); // извлекает фигуры из файла
    void CreateCircle(QRectF rect, QPen pen, QBrush br); // создает круг
    void CreateRectangle(QRectF rect, QPen pen, QBrush br); // создает квадрат
    void on_pushButton_clicked();

private:
    SimpleVector<MySquare*>stor; // хранилище фигур
    QGraphicsScene *scene; // инициализация сцены
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
