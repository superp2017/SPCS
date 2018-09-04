#ifndef RADARFACE_H
#define RADARFACE_H

#include <QtWidgets>
#include "radarview.h"
#include "radar.h"
#include "detector.h"
#include "bkarea.h"
#include "radarscene.h"
#include "sweepline.h"
#include "_global.h"
#include "statusoutput.h"
#include "m_setfreqdlg.h"
using namespace CVTS;

/*!
 * \brief The RadarFace class
 * ’Û√Ê
 */

class RadarFace : public QWidget
{
    Q_OBJECT
protected:
    explicit RadarFace(QWidget *parent = 0);

public:
    static RadarFace* instance()
    {
        static RadarFace *s_face = new RadarFace();
        return s_face;
    }

    static void destroy()
    {
        delete instance();
    }
    
    void set_title(std::string &title);
public slots:
    void reset();
    void close_all();
    void init(QRect &rt);
    void update_radars(const QString &file);
    void map_radars(const QString &file);
    void map();
    void face_import();
    void map_import();
    void save();
    void map_finish();
    void full_screen(bool bl);
    void gen_tools();
    void gen_finished(int code);
    void update_status_output();
    OUTPUT_STATUS_DATA &get_outputdata();
    std::map<int, Radar*>& get_map_radars();
    std::vector<int> &get_radars_id();
    void Search_unit();
    void update_unit_id(int id);
    void search_ids(QString p_path);
protected:
    virtual void paintEvent(QPaintEvent *e);


private:
    RadarView               *m_view;
    std::string             m_title;
    std::map<int, QString>  m_radars;
    QPushButton             *m_search_btn;
    QPushButton             *m_gen_tools_btn;
    QPushButton             *m_face_import_btn;
    QPushButton             *m_map_import_btn;
    QPushButton             *m_save_btn;
    QRect                   m_rt;
    QScrollArea             *m_area;
    int                     m_view_w;
    int                     m_view_h;
    QProcess                m_tools;
    RadarScene              *m_scene;
    OUTPUT_STATUS_DATA      m_outdata;
    std::vector<int>        m_radars_id;
    std::map<int,int>       m_load_id;


};

#endif // RADARFACE_H
