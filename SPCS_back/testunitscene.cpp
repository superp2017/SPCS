#include "testunitscene.h"
#include "testunit.h"
#include "testunitline.h"

TestUnitScene::TestUnitScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent)
{
    m_x = x;
    m_y = y;
    m_w = width;
    m_h = height;
    init();


}

//! �ֳ��ֳ�����ò�Ҫ����
void TestUnitScene::init()
{
    int step = 80;
    int begin = 50;
    int right = 130;
    int left = 130;
    QPointF     rt_left;
    QPointF     rt_right;
    QPointF     rt_top;
    QPointF     rt_bottom;
    QPointF     rt_temp_1;
    QPointF     rt_temp_2;
    QPointF     rt_temp_3;
    QPointF     rt_temp_4;

    QTextCodec *codec = QTextCodec::codecForName("GBK");

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    QString string = codec->toUnicode("�������");
    TestUnit *rt = new TestUnit(string, QRectF((m_w-100)/2,begin,100,50), TestUnit::RoundRect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    TestUnitLine    *tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());


    string = codec->toUnicode("��ʼ��˥����\n(-70dB)");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("��ʼ�����ӿ���\n(��������ͨ��)");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("��ʼ��16��1����\n(ȫ��)");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("��ʼ�����طֻ�\n(ȫ��)");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("����ʸ��");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("ʸ�����Ӽ��");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("���ò���Ƶ��");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("��������S11���");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("̽ͷ��S11���");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("����˥����");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());


    string = codec->toUnicode("����ɨ��ܷ�Χ\n��̽ͷ�ɼ�ʱ��");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);
    rt_left = rt->left();

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);


    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("������������ϵ");
    rt = new TestUnit(string, QRectF((m_w-100)/2 - left,begin-step/2,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!

    TestUnitLine *tLine_left_1 = new TestUnitLine;
    tLine_left_1->setZValue(6);
    tLine_left_1->push_back(rt->right());
    tLine_left_1->push_back(QPointF(rt->right().x() + 15, rt->right().y()));
    tLine_left_1->push_back(QPointF(rt->right().x() + 15, rt_left.y()));

    string = codec->toUnicode("ӳ���ļ�");
    rt = new TestUnit(string, QRectF((m_w-100)/2 - left,begin+step/2,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    TestUnitLine *tLine_left_2 = new TestUnitLine;
    tLine_left_2->setZValue(6);
    tLine_left_2->push_back(rt->right());
    tLine_left_2->push_back(QPointF(rt->right().x() + 15, rt->right().y()));
    tLine_left_2->push_back(QPointF(rt->right().x() + 15, rt_left.y()));

    tLine_left_1->push_back(rt_left);
    tLine_left_1->valid_line();
    addItem(tLine_left_1);

    tLine_left_2->push_back(rt_left);
    tLine_left_2->valid_line();
    addItem(tLine_left_2);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    string = codec->toUnicode("���ô�������״̬");
    rt = new TestUnit(string, QRectF((m_w-100)/2,begin+=step,100,50), TestUnit::Rect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);
    rt_right = rt->right();
    rt_bottom = rt->bottom();

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);


    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    string = codec->toUnicode("���ղ���");
    rt = new TestUnit(string, QRectF((m_w-100)/2 + right, begin-step/2, 100, 50), TestUnit::Ecllipse);
    rt->show();
    rt->setZValue(5);
    addItem(rt);
    tLine_left_1 = new TestUnitLine;
    tLine_left_1->setZValue(6);
    tLine_left_1->push_back(rt->left());
    tLine_left_1->push_back(QPointF(rt->left().x() - 15, rt->left().y()));
    tLine_left_1->push_back(QPointF(rt->left().x() - 15, rt_right.y()));

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    string = codec->toUnicode("�������");
    rt = new TestUnit(string, QRectF((m_w-100)/2 + right, begin+step/2, 100, 50), TestUnit::Ecllipse);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine_left_2 = new TestUnitLine;
    tLine_left_2->setZValue(6);
    tLine_left_2->push_back(rt->left());
    tLine_left_2->push_back(QPointF(rt->left().x() - 15, rt->left().y()));
    tLine_left_2->push_back(QPointF(rt->left().x() - 15, rt_right.y()));

    tLine_left_1->push_back(rt_right);
    tLine_left_1->valid_line();
    addItem(tLine_left_1);

    tLine_left_2->push_back(rt_right);
    tLine_left_2->valid_line();
    addItem(tLine_left_2);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt_bottom);

    string = codec->toUnicode("ȷ��˥��������");
    rt = new TestUnit(string, QRectF((m_w-100)/ 2 - 10, (begin+=step) -5, 120, 60), TestUnit::Prismatic);
    rt->set_status(TestUnit::Unit_Error);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("��������");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Finish);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("��ʼ��ɨ���");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!

    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("���ӿ����л���\n��ʼ��λ");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("16��1�����л���\n��ʼ��λ");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!

    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("ʸ��Ƶ��");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!

    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("�ɼ���������");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("�޸Ĳ��طֻ�\n(���ⵥԪ)");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("n����Ԫ");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("�ر�̽ͷ\n���ӿ���");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("�رղ���\n���ӿ���");
    rt = new TestUnit(string, QRectF((m_w-100)/2 ,  begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);


    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("�л�ʸ������\nΪ���˿�");
    rt = new TestUnit(string, QRectF((m_w-100)/2 ,  begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("�ɼ����˿�\n��������");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("�л����ӿ���");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!

    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("�л�16��1����");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("n��̽ͷ");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("�ƶ�ɨ���");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("n��");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    rt_temp_1 = rt->bottom();
    rt_temp_1.setY(rt_temp_1.y()+15);


    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("��Ԫ����");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);
    rt_temp_2 = rt->bottom();

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->left());

    string = codec->toUnicode("ɨ��ܷ����ƶ�");
    rt = new TestUnit(string, QRectF((m_w-100)/2 - left, begin, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->right());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt_temp_1);

    string = codec->toUnicode("��ά��λ�ֲ�ͼ");
    rt = new TestUnit(string, QRectF((m_w-100)/2 + right, begin, 100, 50), TestUnit::Rect);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(QPointF(rt->top().x(), rt_temp_1.y()));
    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt_temp_2);

    string = codec->toUnicode("������");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Prismatic);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("������ά\n��λ�ֲ�ͼ");
    rt = new TestUnit(string, QRectF((m_w-100)/2, begin+=step, 100, 50), TestUnit::Prismatic);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());

    string = codec->toUnicode("���Խ���");
    rt = new TestUnit(string, QRectF((m_w-100)/2 + 25, begin+=step, 50, 50), TestUnit::Ecllipse);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);
}
