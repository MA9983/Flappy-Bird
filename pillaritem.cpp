#include "pillaritem.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>

PillarItem::PillarItem() : topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe3.png"))),
                           bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe3.png")))
{



    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2, topPillar->boundingRect().height() + 60) );
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2, 10));

    topPillar->setTransformOriginPoint(topPillar->boundingRect().width()/2, topPillar->boundingRect().height()-190);
    topPillar->setRotation(180);

    addToGroup(topPillar);
    addToGroup(bottomPillar);
//    topPillar->setScale(-0.6);
//    bottomPillar->setScale(-0.95);

    yPos = QRandomGenerator::global()->bounded(120);
    int xRandomizer = QRandomGenerator::global()->bounded(180);
    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));


    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(330);
    xAnimation->setEndValue(-380);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);

    connect(xAnimation, &QPropertyAnimation::finished, [=](){
        qDebug() << "Animation finished";
       scene()->removeItem(this);
       delete this;
    });

    xAnimation->start();








}

PillarItem::~PillarItem()
{
    qDebug() << "Pillar Item Deleted";

}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::setX(qreal x)
{
    m_x = x;
    setPos(QPointF(0,0) + QPointF(x, yPos));
}
