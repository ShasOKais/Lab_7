#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this); // инициалищация графической сцены
    ui->graphicsView->setScene(scene); // установка графической сцены
    ui->graphicsView->setRenderHints(QPainter::Antialiasing); // сглаживание сцены
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    ui->RB_RED->setChecked(true);
}

void MainWindow::CreateCircle(QRectF rect, QPen pen, QBrush br){ // функция создания круга
    CCircleFactory Circle; // использование фабрики
    FactoryMethod *m = &Circle; // передаем ссылку на указатель фабрики
    stor.push_back(m->create(rect, pen, br)); // создаем круг через фабрику
    scene->addItem(stor.back()); // помещаем его на сцену
    repaint(); // отрисовываем
}

void MainWindow::CreateRectangle(QRectF rect, QPen pen, QBrush br){
    CRectFactory Rect; // использование фабрики
    FactoryMethod *m = &Rect;  // передаем ссылку на указатель фабрики
    stor.push_back(m->create(rect, pen, br)); // создаем квадрат через фабрику
    scene->addItem(stor.back()); // помещаем его на сцену
    repaint(); // отрисовываем
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_activated(int index) // комбобокс с выбором создаваемого объекта
{
    QPen pen(Qt::black); // стандартная обводка
    pen.setWidth(3); // толщина обводки
    QBrush br(Qt::red); // цвет заливки
    QRectF rect(0,0,100,100); // стандартные параметры рабочей матрицы
    switch (index) {
    case 0:
    {
        CreateCircle(rect, pen, br); // создается круг через функцию
        break;
    }
    case 1:
    {
        CreateRectangle(rect, pen, br); // создается квадрат через функцию
        break;
    }
    }
}
void MainWindow::on_RB_RED_clicked() // при выборе окращивает выделенные фигуры в красный
{
    for(int i = 0; i < stor.size(); i++){
        if(stor[i]->ThisAlloc()){
            stor[i]->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        }
    }
    scene->update();
    repaint();
}

void MainWindow::on_RB_BLUE_clicked() // при выборе окращивает выделенные фигуры в синий
{
    for(int i = 0; i < stor.size(); i++){
        if(stor[i]->ThisAlloc()){
            stor[i]->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        }
    }
    scene->update();
    repaint();
}

void MainWindow::on_RB_GREEN_clicked() // при выборе окращивает выделенные фигуры в зеленый
{
    for(int i = 0; i < stor.size(); i++){
        if(stor[i]->ThisAlloc()){
            stor[i]->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        }
    }
    scene->update();
    repaint();
}


void MainWindow::keyPressEvent(QKeyEvent *d) // при нажатии клавиш происходит триггер
{
    if(d->key() == Qt::Key_Delete) { // при нажатии клавиши Delete
        for(int i = stor.size() - 1; i >= 0; i--){ // удаляет выделенные фигуры
            if(stor[i]->ThisAlloc()){
                delete stor[i];
                stor.Delete(i);
            }
        }
        scene->update();
        repaint();
    }
    if(d->key() == Qt::Key_W){ // при нажатии "W" - перемещает выделенные фигуры вверх
        for(int i = stor.size() - 1; i >= 0; i--){
            if(stor[i]->ThisAlloc()){
                QPointF a = stor[i]->pos();
                a.ry()--;
                stor[i]->setPos(a);
            }
            scene->update();
            repaint();
        }
    }
    if(d->key() == Qt::Key_S){ // при нажатии "Ы" - перемещает выделенные фигуры вниз
        for(int i = stor.size() - 1; i >= 0; i--){
            if(stor[i]->ThisAlloc()){
                QPointF a = stor[i]->pos();
                a.ry()++;
                stor[i]->setPos(a);
            }
            scene->update();
            repaint();
        }
    }
    if(d->key() == Qt::Key_A){ // при нажатии "Ф" - перемещает выделенные фигуры влево
        for(int i = stor.size() - 1; i >= 0; i--){
            if(stor[i]->ThisAlloc()){
                QPointF a = stor[i]->pos();
                a.rx()--;
                stor[i]->setPos(a);
            }
            scene->update();
            repaint();
        }
    }
    if(d->key() == Qt::Key_D){ // при нажатии "В" - перемещает выделенные фигуры вправо
        for(int i = stor.size() - 1; i >= 0; i--){
            if(stor[i]->ThisAlloc()){
                QPointF a = stor[i]->pos();
                a.rx()++;
                stor[i]->setPos(a);
            }
            scene->update();
            repaint();
        }
    }
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1) // при изменении значения, меняет размер выделенных фигур относительно единицы
{
    for(int i = stor.size() - 1; i >= 0; i--){
        if(stor[i]->ThisAlloc()){
            stor[i]->setScale(arg1);
        }
        scene->update();
        repaint();
    }
    ui->progressBar->setValue(arg1);
}

void MainWindow::on_pushButton_Delete_clicked() // при нажатии кнопки "Очистить" удаляет все фигуры с формы
{
    for(int i = stor.size() - 1; i >= 0; i--){ // удаляет выделенные фигуры
        delete stor[i];
        stor.Delete(i);
    }
    scene->update();
    repaint();
}

void MainWindow::on_pushButton_Save_clicked() // сохраняют выделенные фигуры в человеко-читаемый файл
{
    InputFile File("Output");
    int NumCircle = 0, NumRect = 0;
    for(int i = 0; i < stor.size(); i++){
        if(stor[i]->whatThis() == "Circle"){
            NumCircle++;
        } else {
            NumRect++;
        }
    }
    File.setCircle(NumCircle);
    File.setRect(NumRect);
    File.Save();
}

void MainWindow::on_pushButton_Out_clicked() // извлекает из файла фигуры на форму
{
    QPen pen(Qt::black);
    pen.setWidth(3);
    QBrush br(Qt::red);
    QRectF rect(0,0,100,100);

    OutputFile Out("Output");
    Out.Open();
    string s = Out.getShapes();
    for(int j = 0; j < s[0] - '0'; j++){
        CreateCircle(rect, pen, br);
    }
    for(int j = 0; j < s[1] - '0'; j++){
        CreateRectangle(rect, pen, br);
    }
}
