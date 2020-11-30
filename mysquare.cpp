#include "mysquare.h"

//MySquare - mouse

//CRect - mouse
MySquare::MySquare()
{
    setFlag(ItemIsMovable);
}

void MySquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    this->setCursor(QCursor(Qt::ClosedHandCursor)); // установить курсор "сжатый кулак"
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MySquare::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    this->setCursor(QCursor(Qt::ArrowCursor)); // вернуть обычный курсор "стрелка"
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

CCircle::CCircle() : MySquare() {

}

CCircle::CCircle(QRectF Rect, QPen Pen, QBrush Brush) : MySquare(){
    this->rect_ = Rect;
    this->pen_  = Pen;
    this->brush_ = Brush;
}

QRectF CCircle::boundingRect() const
{
    qreal penWidth = 300;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2, 20 + penWidth / 2, 20 + penWidth / 2);
}

CRect::CRect() : MySquare(){
    // по приколу, и чтобы не ругался компилятор
    // но в основном из за наследования
}

CRect::CRect(QRectF Rect, QPen Pen, QBrush Brush) : MySquare(){
    this->rect_= Rect;
    this->pen_ = Pen;
    this->brush_ = Brush;
}

QRectF CRect::boundingRect() const
{
    qreal penWidth = 300;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2, 20 + penWidth / 2, 20 + penWidth / 2);
}

QPen MySquare::TempPen(){
    QPen tempPen(Qt::yellow);
    tempPen.setWidth(5);
    return tempPen;
}

QBrush MySquare::AllocSquare(){
    QBrush allocSquare(Qt::yellow, Qt::SolidPattern);
    return allocSquare;
}

void CRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    rect_ = boundingRect(); // переприсваивание для манипуляции с объектом
    painter->setPen(this->pen_);
    painter->setBrush(this->brush_);
    if(Pressed){ // Если выбрана фигура
        painter->setBrush(AllocSquare());
    } else {
        painter->setBrush(this->brush_);
    }
    if(ThisAlloc()){ // Если выделена фигура
        painter->setPen(TempPen());
    } else {
        painter->setPen(this->pen_);
    }
    painter->drawEllipse(rect_);
    update();
}


void CRect::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    isAlloc = this->isAlloc ? false : true;
    update();
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void CRect::setBrush(QBrush brush)
{
    this->brush_ = brush;
}

string CRect::whatThis() {
    return this->WhatThis;
}

bool CRect::ThisAlloc()
{
    return this->isAlloc;
}

void CCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    rect_ = boundingRect(); // переприсваивание для манипуляции с объектом
    painter->setPen(this->pen_);
    painter->setBrush(this->brush_);
    if(Pressed){
        painter->setBrush(AllocSquare());
    } else {
        painter->setBrush(this->brush_);
    }
    if(ThisAlloc()){
        painter->setPen(TempPen());
    } else {
        painter->setPen(this->pen_);
    }
    painter->drawRect(rect_);
    update();
}

void CCircle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    isAlloc = this->isAlloc ? false : true;
    update();
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void CCircle::setBrush(QBrush brush)
{
    this->brush_ = brush;
}

string CCircle::whatThis() {
    return this->WhatThis;
}

bool CCircle::ThisAlloc() {
    return this->isAlloc;
}

InputFile::InputFile(string namefile){
    this->namefile = namefile;
}

void InputFile::Save(){
    ofstream fout(namefile + ".txt");
    fout << CRect << numCircle << endl << CCircle << numRect;
    fout.close(); // закрываем файл
}

void InputFile::setCircle(int numCircle){
    this->numCircle = numCircle;
}

void InputFile::setRect(int numRect){
    this->numRect = numRect;
}

InputFile::~InputFile(){}

OutputFile::OutputFile(string namefile){
    this->namefile = namefile + ".txt";
}

void OutputFile::Open(){
    ifstream fin(namefile);
    while(fin){
        string s;
        getline(fin, s);
        Shape += s.back();
    }
    fin.close();
}

string OutputFile::getShapes(){
    return this->Shape;
}
