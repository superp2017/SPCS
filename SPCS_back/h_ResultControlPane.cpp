#include "h_ResultControlPane.h"
#include <QDebug>
#include "_global.h"

h_ResultControlPane::h_ResultControlPane(QWidget *parent) :
    QWidget(parent)
{
    initWidget();
}


void h_ResultControlPane::initWidget()
{

    QGroupBox   *groupBox1 = new QGroupBox(CVTS::GBKToUnicode::toUnicode("曲线信息"), this);
    QLabel      *label_1 = new QLabel(CVTS::GBKToUnicode::toUnicode("阶段:"), groupBox1);
    QLabel      *label_2 = new QLabel(CVTS::GBKToUnicode::toUnicode("类型:"), groupBox1);
    QLabel      *label_3 = new QLabel(CVTS::GBKToUnicode::toUnicode("频率:"), groupBox1);


    m_stageComb = new QComboBox();
    m_typeComb = new  QComboBox();
    m_freqComb = new QComboBox();

    m_stageComb->addItem(BEFORE);
    m_stageComb->addItem(MIDDLE);
    m_stageComb->addItem(AFTER);
    m_stageComb->addItem(CAL_MP);

    m_stageComb->addItem(B_Phase);
    m_stageComb->addItem(M_Phase);
    m_stageComb->addItem(A_Phase);

    m_typeComb->addItem(S_1_1);
    m_typeComb->addItem(S_2_1);
    m_typeComb->addItem(S_2_2);

    QGridLayout *gridLayout_1 = new QGridLayout(groupBox1);
    gridLayout_1->addWidget(label_1,0,0);
    gridLayout_1->addWidget(label_2,1,0);
    gridLayout_1->addWidget(label_3,2,0);

    gridLayout_1->addWidget(m_stageComb, 0, 1);
    gridLayout_1->addWidget(m_typeComb, 1, 1);
    gridLayout_1->addWidget(m_freqComb, 2 , 1);



    QGroupBox   *groupBox2 = new QGroupBox(CVTS::GBKToUnicode::toUnicode("显示"), this);
    QVBoxLayout *dislayout = new QVBoxLayout(groupBox2);

    QGroupBox   *upgroup = new QGroupBox(CVTS::GBKToUnicode::toUnicode("幅相"), groupBox2);
    QGroupBox   *downgroup = new QGroupBox(groupBox2);

    QHBoxLayout *downlayout  = new QHBoxLayout(downgroup);

    leftGroup  = new QGroupBox(CVTS::GBKToUnicode::toUnicode("数据类型"), NULL);
    RightGroup = new QGroupBox(CVTS::GBKToUnicode::toUnicode("数据范围"), NULL);


    m_magn  = new QCheckBox(CVTS::GBKToUnicode::toUnicode("幅度"), upgroup);
    m_magn->setChecked(true);
    m_Phase = new QCheckBox(CVTS::GBKToUnicode::toUnicode("相位"), upgroup);
    m_Phase->setChecked(true);

    L_Liner = new QRadioButton(CVTS::GBKToUnicode::toUnicode("线性值"), leftGroup);
    L_Liner->setChecked(false);
    m_DB    = new QRadioButton(CVTS::GBKToUnicode::toUnicode("dB值"), leftGroup);
    m_DB->setChecked(true);

    m_360 = new QRadioButton(CVTS::GBKToUnicode::toUnicode("0~360"), RightGroup);
    m_180 = new QRadioButton(CVTS::GBKToUnicode::toUnicode("-180~180"), RightGroup);
    m_360->setChecked(true);
    m_180->setChecked(false);

    connect(m_360,SIGNAL(clicked()),this,SLOT(curSelectChange()));
    connect(m_180,SIGNAL(clicked()),this,SLOT(curSelectChange()));

    QVBoxLayout *leftLayout = new QVBoxLayout(leftGroup);
    leftLayout->addWidget(m_DB);
    leftLayout->addWidget(L_Liner);

    leftGroup->setLayout(leftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout(RightGroup);
    rightLayout->addWidget(m_360);
    rightLayout->addWidget(m_180);
    RightGroup->setLayout(rightLayout);


    QHBoxLayout *uplayout = new QHBoxLayout(upgroup);
    uplayout->addWidget(m_magn);
    uplayout->addWidget(m_Phase);
    upgroup->setLayout(uplayout);

    downlayout->addWidget(leftGroup);
    downlayout->addWidget(RightGroup);
    downlayout->setMargin(0);
    downlayout->setSpacing(0);
    downgroup->setLayout(downlayout);

    dislayout->addWidget(upgroup);
    dislayout->addWidget(downgroup);
    dislayout->setMargin(1);

    dislayout->setStretch(0,1);
    dislayout->setStretch(0,4);


    groupBox2->setLayout(dislayout);


    QGroupBox   *groupBox3 = new QGroupBox(CVTS::GBKToUnicode::toUnicode("后处理"), this);
    QVBoxLayout *vBoxLayout = new QVBoxLayout(groupBox3);

    QPushButton *btn_4 = new QPushButton(CVTS::GBKToUnicode::toUnicode("导入"), groupBox3);
    connect(btn_4, SIGNAL(clicked()), this, SIGNAL(on_import()));

    QPushButton *btn_3 = new QPushButton(CVTS::GBKToUnicode::toUnicode("导出"), groupBox3);
    connect(btn_3, SIGNAL(clicked()), this, SLOT(data_export()));

    QPushButton *btn_2 = new QPushButton(CVTS::GBKToUnicode::toUnicode("添加"), groupBox3);
    connect(btn_2, SIGNAL(clicked()), this, SIGNAL(on_add()));

    QPushButton *btn_6 = new QPushButton(CVTS::GBKToUnicode::toUnicode("清空"), groupBox3);
    connect(btn_6, SIGNAL(clicked()), this, SIGNAL(clear_all()));
    connect(btn_6, SIGNAL(clicked()), this, SLOT(clearItem()));

    btn_5 = new QPushButton(CVTS::GBKToUnicode::toUnicode("全屏"), groupBox3);
    connect(btn_5, SIGNAL(clicked()), this, SLOT(full_or_normal()));


    QVBoxLayout *layout = new QVBoxLayout(this);

    vBoxLayout->addWidget(btn_4);
    vBoxLayout->addWidget(btn_3);
    vBoxLayout->addWidget(btn_2);
    vBoxLayout->addWidget(btn_6);
    vBoxLayout->addWidget(btn_5);
    vBoxLayout->setSpacing(10);
    vBoxLayout->setMargin(1);
    layout->addWidget(groupBox1);
    layout->addWidget(groupBox2);
    layout->addWidget(groupBox3);
    layout->setStretch(0,2);
    layout->setStretch(1,3);
    layout->setStretch(2,3);
    layout->setMargin(2);
    layout->setSpacing(1);

    isfull = false;
    setLayout(layout);

    connect(m_Phase,SIGNAL(clicked()),this,SLOT(check_radio()), Qt::QueuedConnection);
    connect(m_magn,SIGNAL(clicked()),this,SLOT( check_radio()), Qt::QueuedConnection);


    connect(m_stageComb, SIGNAL(currentTextChanged(QString)), this, SLOT(curSelectChange()), Qt::QueuedConnection);
    connect(m_typeComb, SIGNAL(currentTextChanged(QString)), this, SLOT(curSelectChange()), Qt::QueuedConnection);
    connect(m_freqComb, SIGNAL(currentTextChanged(QString)), this, SLOT(curSelectChange()), Qt::QueuedConnection);
    connect(m_DB,SIGNAL(clicked()),this,SLOT(curSelectChange()), Qt::QueuedConnection);
    connect(L_Liner,SIGNAL(clicked()),this,SLOT( curSelectChange()), Qt::QueuedConnection);


    QString ls_sheet = QString::fromUtf8("font: 11pt \"\346\245\267\344\275\223\";");
    this->setStyleSheet(ls_sheet);
}


void h_ResultControlPane::curSelectChange()
{
    emit DataType(m_360->isChecked(),m_DB->isChecked());
    QString stage = m_stageComb->currentText();
    QString type  = m_typeComb->currentText();
    QString freq  = m_freqComb->currentText();

    if(stage == CAL_MP)
    {
        m_DB->setChecked(true);
        m_typeComb->setEnabled(false);
        leftGroup->setEnabled(false);
        type = CAL_MP;
    }

    if(stage == B_Phase)
    {
        m_DB->setChecked(true);
        leftGroup->setEnabled(false);
        m_typeComb->setEnabled(false);
        type = B_Phase;
    }

    if(stage == M_Phase)
    {
        m_DB->setChecked(true);
        leftGroup->setEnabled(false);
        m_typeComb->setEnabled(false);
        type = M_Phase;
    }


    if(stage == A_Phase)
    {
        m_DB->setChecked(true);
        leftGroup->setEnabled(false);
        m_typeComb->setEnabled(false);
        type = A_Phase;
    }
    if(stage != CAL_MP && stage != B_Phase &&  stage !=M_Phase && stage != A_Phase)
    {
        leftGroup->setEnabled(true);
        m_typeComb->setEnabled(true);
    }

    if(m_freqComb->count() <= 0)
    {
        return;
    }

    emit selectChange(stage, type, freq);
}

void h_ResultControlPane::addFreqItem(std::vector<QString> pFreq)
{
    for(size_t i = 0 ;i < pFreq.size(); ++i)
    {
        QString key ;
        DoubleFre_TO_QStringFreq::Double_TO_QString(pFreq.at(i).toDouble(),key);
        m_freqComb->addItem(key);
    }
    m_freqComb->setCurrentIndex(0);
    curSelectChange();
}

void h_ResultControlPane::change_btn_full()
{
    QString text =CVTS::GBKToUnicode::toUnicode("全屏");
    btn_5->setText(text);
    isfull = false;
}

void h_ResultControlPane::change_btn_normal()
{
    QString text =CVTS::GBKToUnicode::toUnicode("退出全屏");
    btn_5->setText(text);
    isfull = true;
}

void h_ResultControlPane::full_or_normal()
{
    if(isfull)
        emit on_show_normal();
    else
        emit on_fullscreen();
}

void h_ResultControlPane::check_radio()
{
    if(!(m_magn->isChecked() || m_Phase->isChecked()))
    {
        m_magn->setChecked(true);
        m_Phase->setChecked(true);
        leftGroup->setEnabled(true);
    }

    leftGroup->setEnabled(m_magn->isChecked());
    RightGroup->setEnabled(m_Phase->isChecked());
    bool showmagn = m_magn->isChecked();
    bool showphase = m_Phase->isChecked();
    emit show_chart(showmagn,showphase);
    // curSelectChange();
}

void h_ResultControlPane::data_export()
{
    emit on_export();
}


void h_ResultControlPane::clearItem()
{
    this->m_freqComb->clear();
}


void h_ResultControlPane::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRectF rt(rect().left(), rect().top(), rect().width() -1, rect().height() -1);
    painter.setPen(QPen(QColor(155,155,155), 0));
    painter.drawRect(rt);
}











