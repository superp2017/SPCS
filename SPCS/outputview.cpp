#include "outputview.h"

OutputView::OutputView(QWidget *parent) :
    QWidget(parent),
    m_gridLayout(this)
{
    m_listView.setModel(&m_listModel);
    m_gridLayout.addWidget(&m_ouTitle,0, 0);
    m_gridLayout.addWidget(&m_listView, 1, 0);

    m_gridLayout.setRowStretch(0,1);
    m_gridLayout.setRowStretch(1,8);
    m_gridLayout.setSpacing(0);
    m_ouTitle.setFixedHeight(20);
    m_gridLayout.setContentsMargins(0,0,0,0);

    setLayout(&m_gridLayout);

    QStandardItem *item = new QStandardItem(CVTS::GBKToUnicode::toUnicode(">> ³ÌÐòÆô¶¯..."));

    item->setEditable(false);
    m_listModel.setItem(0, item);
    connect(&m_ouTitle, SIGNAL(clean_output()), this, SLOT(clean_output_slot()), Qt::QueuedConnection);
    connect(this, SIGNAL(scroll_to_bottom()), &m_listView, SLOT(scrollToBottom()), Qt::QueuedConnection);
    QString ls_sheet = QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";");
    this->setStyleSheet(ls_sheet);

    connect(this, SIGNAL(append_sig(const char*)), this, SLOT(append_slot(const char*)), Qt::QueuedConnection);
    connect(this, SIGNAL(append_sig(QString)), this, SLOT(append_slot(QString)), Qt::QueuedConnection);
}

void OutputView::append_slot(QString text)
{
    if(m_listModel.rowCount() > MAX_OUTPUT)
    {
        m_listModel.clear();
    }

    QStandardItem *item = new QStandardItem(CVTS::GBKToUnicode::toUnicode(text));
    item->setEditable(false);
    m_listModel.appendRow(item);
    //m_listView.scrollToBottom();
    emit scroll_to_bottom();
}

void OutputView::append_slot(const char *text)
{
    if(m_listModel.rowCount() > MAX_OUTPUT)
    {
        m_listModel.clear();
    }

    sprintf(m_buf, ">> %s", text);
    QStandardItem *item = new QStandardItem(CVTS::GBKToUnicode::toUnicode(m_buf));
    item->setEditable(false);

    m_listModel.appendRow(item);

    emit scroll_to_bottom();
}

void OutputView::clean_output_slot()
{
    while(m_listModel.rowCount() > 0)
    {
        m_listModel.removeRow(0);
    }
}

void OutputView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF rt(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
    painter.setPen(QPen(QColor(155,155,155), 0));
    painter.drawRect(rt);
}

