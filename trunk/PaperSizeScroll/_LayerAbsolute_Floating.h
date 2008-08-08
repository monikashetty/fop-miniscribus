#ifndef ABSOLUTELAYEREXTENDED_H
#define ABSOLUTELAYEREXTENDED_H


#include <QtGui>
#include <QtCore>
#include <QDebug>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "Layer_CommandStorage.h"
#include "scribemime.h"
#include "SessionManager.h"
#include "_LayerApi.h"

    ///////qDebug() << "###  width" << boundingRect().height();
    /////qDebug() << "###  largo" << alto;

#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265



static const qreal MinimumHightLayer = 15.0;
static const qreal MinimumWhidhLayer = 15.0;

static const qreal MAXLargoTmp = 1000.0;


/* drag point to rotate and resize absolute layer */

class FWButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
    public:
        FWButton( QGraphicsItem * parent, const QBrush & brush , const QString msg );
        QRectF boundingRect() const;
        
        void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
        void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
        void mousePressEvent( QGraphicsSceneMouseEvent * event );
        void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );
        void mouseDoubleClickEvent( QGraphicsSceneMouseEvent * event );
        void allow( bool e );

    Q_SIGNALS:
        void dragging(const QPointF & point);
        void reset();

    private:
        QGraphicsItem *    m_parent;
        QBrush      m_brush;
        QPointF     m_startPos;
        bool permission;
        QString txt;
};



Q_DECLARE_METATYPE(FWButton *)




class AbsText;

class AbsoluteLayer : public QObject, public QGraphicsRectItem
{
   Q_OBJECT 

public:
    
    AbsoluteLayer( QGraphicsItem *parent );
    ~AbsoluteLayer();
    QRectF boundingRect() const;
    QRectF absoluteRect();
    QLineF LineTops();
    QLineF Diagonal();

    QTextDocument *document();
    void setDocument( const QTextDocument * doc , FileHandlerType Type = FOP );
    QTextCursor textCursor();
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool sceneEvent(QEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event); 
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void keyPressEvent( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void focusInEvent ( QFocusEvent * event );
    void focusOutEvent ( QFocusEvent * event );
    void inputMethodEvent ( QInputMethodEvent * event );

private:
    FWButton  *Angle_1;
    FWButton  *Angle_2;
    FWButton  *Angle_4;
    qreal Rotate;
    QRectF lastUpdateRequest;
    AbsText *dev;
signals:
void close_main_cursor();

private slots:
void slotModpos_1( const QPointF posi );
void slotResize_1( const QPointF posi );
void slotRotate_1( const QPointF posi );

void updatearea( const QRect areas );

};


Q_DECLARE_METATYPE(AbsoluteLayer *)




class AbsText: public QObject
{
    Q_OBJECT 
    
public:
   AbsText();
   LayerText *txtControl() const;
   AbsoluteLayer *q;
   private:
   mutable LayerText *device;
   
};

Q_DECLARE_METATYPE(AbsText *)


















//
#endif // LAYEREXTENDED_H
