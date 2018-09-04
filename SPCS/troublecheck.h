#ifndef TROUBLECHECK_H
#define TROUBLECHECK_H

#include <QtWidgets>
#include "_global.h"
#include "radarscene.h"
#include <QRect>
#include "radarview.h"
#include "bkarea.h"
#include "radarface.h"
#include "libxl.h"
#include "projectmanager.h"

using namespace CVTS;
using namespace libxl;

#define  Failed         CVTS::GBKToUnicode::toUnicode("保存失败")
#define  isopen         CVTS::GBKToUnicode::toUnicode("文件可能已经打开！")
#define  FILE_IS_OPEN   QMessageBox::information(NULL,Failed,isopen );

#define Trouble_all  CVTS::GBKToUnicode::toUnicode("移相全故障")
#define Trouble_0    CVTS::GBKToUnicode::toUnicode("无故障")
#define Trouble_1    CVTS::GBKToUnicode::toUnicode("1位移相器故障")
#define Trouble_2    CVTS::GBKToUnicode::toUnicode("2位移相器故障")
#define Trouble_3    CVTS::GBKToUnicode::toUnicode("3位移相器故障")
#define Trouble_4    CVTS::GBKToUnicode::toUnicode("4位移相器故障")
#define Trouble_5    CVTS::GBKToUnicode::toUnicode("5位移相器故障")

/*!
 * \brief The TroubleCheck class
 * 单元故障检测，目前没有使用
 */
class TroubleCheck : public QWidget
{
    Q_OBJECT
protected:
    explicit TroubleCheck(QWidget *parent = 0);
    ~TroubleCheck();
public:
    static TroubleCheck *instance()
    {
        static TroubleCheck *check = new TroubleCheck();
        return check;
    }
    static void destory()
    {
        delete instance();
    }
    void init(QRect &rt);
    void load_face(std::map<int,Radar *> &p_radars_map,std::vector<int> &p_radar_id,QString p_path);
signals:
    
public slots:
    void set_title(QString title);
    void full_screen(bool full);
    void export_excle();
    void reset();
protected:
    void paintEvent(QPaintEvent *e);
private:
    QString m_title;
    RadarView               *m_view;
    QRect                    m_rt;
    QScrollArea              *m_area;
    int                      m_view_w;
    int                      m_view_h;
    QProcess                 m_tools;
    QPushButton              *m_export_btn;
    RadarScene               *m_scene;
    std::vector<int>         m_radars_id;
    std::map<int, Radar*>    m_radars_map;
    std::map<int, Radar*>    m_default_radars_map;
    std::map<int,int>        m_trouble_table;
    QString                  m_save_path;
};

#endif // TROUBLECHECK_H
