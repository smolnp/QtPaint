/*
Copyright 2017 SillyLossy.
This program is free software; you can redistribute it and/or
modify it under the terms of the Lesser GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the Lesser GNU General Public License for more details.
You should have received a copy of the Lesser GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QOpenGLWidget>
#include <QScrollArea>
#include <QPen>
#include <QVector>
#include <QPixmap>
#include <QLabel>

#include "paintarea.h"
#include "paintwidget.h"
#include "brushtool.h"
#include "linetool.h"
#include "rectangletool.h"
#include "floodfilltool.h"
#include "erasertool.h"
#include "ellipsetool.h"
#include "layer.h"

class PaintArea : public QScrollArea {
    Q_OBJECT
public slots:
    void setPenColor(const QColor& color);
    void setPenWidth(int);

    void mouseMove(const QPoint&);

    void mousePress(const QPoint&, int);

    void mouseRelease(const QPoint&, int);

public:
    enum PaintLimits {
        MAX_PEN_WIDTH = 125,
        MAX_ZOOM = 400,
        MIN_PEN_WIDTH = 1,
        MAX_IMAGE_SIZE = 2000,
        MIN_IMAGE_SIZE = 1,
        DEFAULT_WIDTH = 800,
        DEFAULT_HEIGHT = 600
    };
    enum Transformations {
        ROTATE_LEFT = 270,
        ROTATE_RIGHT = 90,
        ROTATE_UPSIDE_DOWN = 180,
        FLIP_HORIZONTAL, FLIP_VERTICAL
    };
    explicit PaintArea(QWidget* parent = 0);

    ~PaintArea();

    QPen pen() const;

    void transform(int type);

    int increasePenWidth();

    int decreasePenWidth();

    bool loadImage(const QString&);

    void setDefaultLayer(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, QColor fill = QColor(Qt::white));

    bool pasteImage();

    void copyImage();

    QImage saveImage();

    QSize imageSize() const;

    void setLayerVisible(int, bool);

    QImage* selectedLayer();

    QImage* layerImageAt(int i);

    bool layerVisibleAt(int i);

    int layersCount() const;

    QPixmap* toolLayer();

    void setSelectedTool(int i);

    int selectedTool() const;

    QPoint prevPoint() const;

    const QVector<PaintTool*>* tools() const;

    bool antialiasingEnabled() const;

    void setAntialiasingEnabled(bool antialiasingEnabled);

    QBrush brush() const;

    void setBrushColor(const QColor&);

    int zoom() const;
    void setZoom(int zoom);
    void rezoom();
    QPoint adjustedPos(const QPoint&);

private slots:
    void _update_proxy();
private:
    void setRepaintTimer();
    void setDefaultPen();
    void setPaintWidgetBackground();
    void setToolLayer(const QSize&);
    void rotate(int);
    void flipHorizontal();
    void flipVertical();
private:
    bool m_collectMouseMove;
    int m_selectedTool;
    int m_selectedLayer;
    bool m_antialiasingEnabled;
    const QVector<PaintTool*> m_tools {
        new BrushTool(this),
        new EraserTool(this),
        new LineTool(this),
        new EllipseTool(this),
        new RectangleTool(this),
        new FloodFillTool(this)
    };

    int m_zoom;

    PaintWidget* m_paintWidget;

    QVector<Layer> m_layers;

    QPixmap m_toolLayer;

    QPoint m_prevPoint;

    QPen m_pen;

    QBrush m_brush;
};

#endif // PAINTAREA_H
