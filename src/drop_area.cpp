#include "drop_area.h"

DropArea::DropArea(const QSize &s, QWidget *parent)
    : QLabel(parent)
{
    setMinimumSize(s);
    setMaximumSize(s);
    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
}

void DropArea::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void DropArea::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void DropArea::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        emit dropped(mimeData->urls());
    }

    event->acceptProposedAction();
}

void DropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    clear();
    event->accept();
}
