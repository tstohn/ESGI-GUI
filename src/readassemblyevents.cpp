#include "readassemblyevents.h"


RedSeqGraphicsView::RedSeqGraphicsView(QWidget* widget) : QGraphicsView(widget)
{
    setAcceptDrops(true);
}

void RedSeqGraphicsView::dragEnterEvent(QDragEnterEvent* event)
{
    event->accept();
    event->acceptProposedAction();
}

void RedSeqGraphicsView::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

void RedSeqGraphicsView::dragMoveEvent(QDragMoveEvent* event)
{
    event->accept();
    event->acceptProposedAction();
}

void RedSeqGraphicsView::dropEvent(QDropEvent* event)
{
    SeqBlockLabel* seqLabel = qobject_cast<SeqBlockLabel*>(event->source());
    QPixmap seqlImage = seqLabel->pixmap();
    SeqBlockInformation info(seqlImage, seqLabel->get_type());

    emit itemdrop(info);
}


SeqBlockInformation::SeqBlockInformation(QPixmap image, std::string type) :
    barcodeType(type), barcodeImage(image)
{

}

SeqBlockLabel::SeqBlockLabel(QWidget* widget)
{

}

void SeqBlockLabel::create_drag(const QPoint& pos, QWidget* widget)
{
    QByteArray byteArray(reinterpret_cast<char*>(&widget), sizeof (QWidget*));

    QMimeData* mimedata = new QMimeData();
    mimedata->setData("Label", byteArray);

    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimedata);

    QPoint globalPos = mapToGlobal(pos);
    QPoint p = widget->mapFromGlobal(globalPos);

    drag->setHotSpot(p);
    drag->setPixmap(widget->grab());
    drag->exec();

}

void SeqBlockLabel::mousePressEvent(QMouseEvent* event)
{
    create_drag(event->pos(), this);
}

