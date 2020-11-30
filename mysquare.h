#ifndef MYSQUARE_H
#define MYSQUARE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QMouseEvent>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <fstream>
#include <string>
#include "SimpleVector.h"

using namespace std;

class MySquare : public QGraphicsItem // класс фигур
{
public:
    MySquare(); // конструктор
    bool Pressed = false; // если кнопка нажата
    // Методы не определны и строго указываем что у этих методов нет реализации
    // и все кто отнаследовались обязаны реализовать эти методы сами
    virtual QRectF boundingRect() const = 0; // отрисовывает матрицу для манипуляции с объектами
    virtual string whatThis() = 0; // возвращает тип фигуры
    virtual bool ThisAlloc() = 0; // возвращает "выделены или круг"
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0; // отрисовка фигур
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) = 0; // триггер двойоного нажатия мыши
    virtual void setBrush(QBrush brush) = 0; // установить кисть

protected slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event); // проверка нажатия кнопки мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); // проверка отжатия кнопки мыши
    QPen TempPen(); // обводка для выделенных фигур
    QBrush AllocSquare(); // заливка для выделенных фигур
};

class CCircle : public MySquare { // класс Круга
private:
    QRectF rect_; // фигура
    QBrush brush_; // кисть
    QPen pen_; // ручка обводки
    QPainter *painter; // метод отрисовки
    bool isAlloc = false; // хранит выделения фигуры
    string WhatThis = "Circle"; // определение фигуре
public:
    CCircle(); // конструктор
    CCircle(QRectF Rect, QPen Pen, QBrush Brush); // конструктор с параметрами, принимающий фигуру, обрисовку и кисть
    QRectF boundingRect() const override; // отрисовка рабочей матрицы для фигуры
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // отрисовщик фигур
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override; // выделение при двойном нажатии
    void setBrush(QBrush brush) override; // установить кисть заливки
    string whatThis() override; // возвращает тип фигуры
    bool ThisAlloc() override; // отрисовка фигур
};

class CRect : public MySquare { // класс Прямоугольника
private:
    QRectF rect_; // фигура
    QBrush brush_; // кисть
    QPen pen_; // ручка обводки
    QPainter *painter; // метод отрисовки
    bool isAlloc = false; // хранит выделения фигуры
    string WhatThis = "Rectangle"; // определение фигуре
public:
    CRect(); // конструктор
    CRect(QRectF Rect, QPen Pen, QBrush Brush); // конструктор с параметрами, принимающий фигуру, обрисовку и кисть
    QRectF boundingRect() const override; // отрисовка рабочей матрицы для фигуры
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // отрисовщик фигур
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override; // выделение при двойном нажатии
    void setBrush(QBrush brush) override; // установить кисть заливки
    string whatThis() override; // возвращает тип фигуры
    bool ThisAlloc() override; // отрисовка фигур
};

class FactoryMethod { // фабрика
public:
    virtual MySquare* create(QRectF Rect, QPen Pen, QBrush Brush) = 0; // переопределнный метод создания фигуры
    virtual ~FactoryMethod(){}
};

class CCircleFactory : public FactoryMethod { // Создается производство
public:
    MySquare* create(QRectF Rect, QPen Pen, QBrush Brush) override { // создание круга
        return new CCircle(Rect, Pen, Brush);
    }
};

class CRectFactory : public FactoryMethod {
public:
    MySquare* create(QRectF Rect, QPen Pen, QBrush Brush) override { // создание квадрата
        return new CRect(Rect, Pen, Brush);
    }
};

class InputFile { // сохранение файла
private:
    string namefile; // имя файла
    string CCircle = "СCircle = "; // вставка для файла
    string CRect = "CRect = "; // вставка для файла
    int numCircle = 0; // кол-во кругов
    int numRect = 0; // кол-во квадратов
public:
    InputFile() = default; // конуструктор со стандартными параметрами
    InputFile(string namefile); // установить название файла
    void Save(); // сохранение файла
    void setCircle(int numCircle); // установление кол-ва кругов
    void setRect(int numRect); // установление кол-ва квадратов
    ~InputFile(); // деструктор
};

class OutputFile : public InputFile {
private:
    string namefile = ""; // название выводимого файла
    string Shape = ""; // фигура
public:
    OutputFile(string namefile); // конструктор задающий название файла
    void Open(); // извлекает данные из файла
    string getShapes(); // возвращает фигуру
};
#endif // MYSQUARE_H
