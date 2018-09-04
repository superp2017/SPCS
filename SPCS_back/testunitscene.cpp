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

//! 又长又臭，最好不要看它
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
    QString string = codec->toUnicode("启动软件");
    TestUnit *rt = new TestUnit(string, QRectF((m_w-100)/2,begin,100,50), TestUnit::RoundRect);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    ///////////////////////////////////////////////////////////////////////////////////////////
    //!
    TestUnitLine    *tLine = new TestUnitLine;
    tLine->setZValue(6);
    tLine->push_back(rt->bottom());


    string = codec->toUnicode("初始化衰减器\n(-70dB)");
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

    string = codec->toUnicode("初始化电子开关\n(开，即不通电)");
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

    string = codec->toUnicode("初始化16分1开关\n(全关)");
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

    string = codec->toUnicode("初始化波控分机\n(全关)");
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

    string = codec->toUnicode("配置矢网");
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

    string = codec->toUnicode("矢网连接检测");
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

    string = codec->toUnicode("设置测试频段");
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

    string = codec->toUnicode("待测天线S11检测");
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

    string = codec->toUnicode("探头组S11检测");
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

    string = codec->toUnicode("设置衰减量");
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


    string = codec->toUnicode("锁定扫描架范围\n及探头采集时序");
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

    string = codec->toUnicode("建立测试坐标系");
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

    string = codec->toUnicode("映射文件");
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
    string = codec->toUnicode("设置待测天线状态");
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
    string = codec->toUnicode("接收测试");
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
    string = codec->toUnicode("发射测试");
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

    string = codec->toUnicode("确认衰减器连接");
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

    string = codec->toUnicode("启动测试");
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

    string = codec->toUnicode("初始化扫描架");
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

    string = codec->toUnicode("电子开关切换到\n初始化位");
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

    string = codec->toUnicode("16分1开关切换到\n初始化位");
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

    string = codec->toUnicode("矢网频段");
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

    string = codec->toUnicode("采集测试数据");
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

    string = codec->toUnicode("修改波控分机\n(待测单元)");
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

    string = codec->toUnicode("n个单元");
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

    string = codec->toUnicode("关闭探头\n电子开关");
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

    string = codec->toUnicode("关闭波控\n电子开关");
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

    string = codec->toUnicode("切换矢网测试\n为单端口");
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

    string = codec->toUnicode("采集两端口\n测试数据");
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

    string = codec->toUnicode("切换电子开关");
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

    string = codec->toUnicode("切换16切1开关");
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

    string = codec->toUnicode("n个探头");
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

    string = codec->toUnicode("移动扫描架");
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

    string = codec->toUnicode("n次");
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

    string = codec->toUnicode("单元配相");
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

    string = codec->toUnicode("扫描架反向移动");
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

    string = codec->toUnicode("二维相位分布图");
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

    string = codec->toUnicode("配相检测");
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

    string = codec->toUnicode("配相后二维\n相位分布图");
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

    string = codec->toUnicode("测试结束");
    rt = new TestUnit(string, QRectF((m_w-100)/2 + 25, begin+=step, 50, 50), TestUnit::Ecllipse);
    rt->set_status(TestUnit::Unit_Normal);
    rt->show();
    rt->setZValue(5);
    addItem(rt);

    tLine->push_back(rt->top());
    tLine->valid_line();
    addItem(tLine);
}
