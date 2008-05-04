/*******************************************************************************
 * class TextLayer
 *******************************************************************************
 * Copyright (C) 2007 by Peter Hohl
 * e-Mail: ppkciz@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *******************************************************************************/

#ifndef TEXTLAYER_H
#define TEXTLAYER_H

#include "mounttextprivate.h"
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QSharedData>
#include "GraphicsScene.h"



typedef enum {DIV_ABSOLUTE = 50,DIV_AUTO,/* 51 */DIV_FLOAT,/* 52 */DIV_HEADER,DIV_FOOTER} LAYERTYPE;



class TextController;
class LogData;

class TextLayer : public QObject, public QGraphicsItem
{
   Q_OBJECT 

public:
    enum CurrentModus{ Show, Edit, Move , Lock };
    TextLayer(const int layer_id , QGraphicsItem *parent = 0 , QGraphicsScene *scene = 0);
    ~TextLayer();
    void setSelected( bool selected );
    void setModus( CurrentModus  e);
    QRectF boundingRect() const;
    QTextDocument *document();
    void setDocument ( QTextDocument * document );
    QTextCursor textCursor();
    void LayerHightChecks();
    RichDoc ReadActualItem();
    void insert( RichDoc Rdoc );
    void setZValue(qreal index );
    bool contains(const QPointF &point) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    enum { Type = 22 };
    int type() const;
    LAYERTYPE Ltype() const;
    void setStyle( QStringList syle , bool fromclone );
    QTextDocument *_doc;
    bool currentprintrender;
    inline void SetDimension( qreal w , qreal h ) { 
    wi = w;
    hi = h;
    LayerHightChecks();
    }
protected:
    RichDoc guiwait;
    QSettings setter;
    QAction *actionSwapEdit,
             *actionSwapLock;
    void init();
    void read();
    void RestoreMoveAction();
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void timerEvent(QTimerEvent *event);
    ////void inputMethodEvent(QInputMethodEvent *event);
    void keyPressEvent( QKeyEvent * event );
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QMenu *RootMenu;
    QAbstractTextDocumentLayout *DLayout;
    LAYERTYPE format;
    CurrentModus modus;
    uint evesum;
    bool IsSelectActive;
    int id;
    bool sceneEvent(QEvent *event);
private:
    TextController *mount;
    QMap<uint,QString> history;
    QColor bgcolor;
    QColor bordercolor;
    qreal border;
    qreal wi;
    qreal hi;
    qreal text_hight;
    qreal text_width;
    QRectF TextboundingRect;
public slots:
    void updatearea( const QRectF areas );
    void cursor_wake_up();
    void cursorPositionChanged( const QTextCursor cur);
    void CommitLayer();
    void InsertRevision();
    void EditModus();
    void SetNewBGColor();
    void SetNewBorderColor();
    void SaveFilelayer();
    void OpenFilelayer();
    void SwapEdit();
    void Borderwidht();
    void SwapLockmodus();
    void ShowInfos();
    void E_Reload();
};

Q_DECLARE_METATYPE(TextLayer *)

class TextController: public QObject
{
    Q_OBJECT 
    
public:
   TextController();
   TextWriter *txtControl() const;
   mutable TextWriter *device;
   TextLayer *q;
   public slots:
};

Q_DECLARE_METATYPE(TextController *)






//
#endif // TEXTLAYER_H
