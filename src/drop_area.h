#ifndef DROPAREA_H
#define DROPAREA_H

#include <QtGui>

class DropArea : public QLabel
{
    Q_OBJECT

public:
    DropArea(const QSize &, QWidget *parent = 0);

signals:
    void dropped(const QList<QUrl> list);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // DROPAREA_H
