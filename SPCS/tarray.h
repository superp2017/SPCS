#ifndef TARRAY_H
#define TARRAY_H

#include <QtWidgets>
#include "radarview.h"
#include "radarscene.h"
#include "_global.h"

/*!
 * \brief The TArray class
 * ¼à¿ØµÄÕóÃæ
 */
class  TArray : public QDialog
{
    Q_OBJECT
public:
    explicit TArray(QWidget *parent = 0);
    
    static TArray* instance()
    {
        static TArray *array = new TArray();
        return array;
    }

    static void destroy()
    {
        delete instance();
    }

signals:

public slots:
    void reset();
    void resetView();
    void init(QRect &rt);
    void init_data(std::map<int, Radar *> &p_radars,std::vector<int> &p_radar_id);
    void update_radars(int id);
  private:
    RadarView               *m_view;
    std::string             m_title;
    std::map<int, Radar *>  m_radars_map;
    QRect                   m_rt;
    QScrollArea             *m_area;
    int                     m_view_w;
    int                     m_view_h;
    RadarScene              *m_scene;
    std::vector<int>        m_radars_id;

};

#endif // TARRAY_H
