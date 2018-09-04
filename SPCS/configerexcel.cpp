#include "configerexcel.h"
#include "projectmanager.h"
#include "twoshorttoid.h"
ConfigerExcel::ConfigerExcel(QObject *parent) :
    QObject(parent)
{
}

void ConfigerExcel::Export_Excel(QString Path, Task_Cmp &p_CmpData, \
                                 std::vector<QString> &p_freq ,\
                                 std::vector<int> &p_id)
{
    if(p_CmpData.size() == 0)
    {
        qDebug()<<"Export_Excel save failed,data size 0";
        return;
    }
    QString name = Path;
    Book *book = xlCreateBook();
    Format* format_title = book->addFormat();
    Font* font = book->addFont();
    font->setSize(15);
    format_title->setAlignH(ALIGNH_CENTER);
    format_title->setAlignV(ALIGNV_CENTER);
    format_title->setNumFormat(NUMFORMAT_TEXT);
    format_title->setBorder(BORDERSTYLE_NONE);
    format_title->setFont(font);

    Format* format_contex = book->addFormat();
    Font* font1 = book->addFont();
    font1->setSize(13);
    format_contex->setAlignH(ALIGNH_CENTER);
    format_contex->setAlignV(ALIGNV_CENTER);
    format_contex->setNumFormat(NUMFORMAT_GENERAL);
    format_contex->setBorder(BORDERSTYLE_THIN);
    format_contex->setFont(font1);

    Format* format_fre = book->addFormat();
    Font* font2 = book->addFont();
    font2->setSize(13);
    format_fre->setAlignH(ALIGNH_CENTER);
    format_fre->setAlignV(ALIGNV_CENTER);
    format_fre->setNumFormat(NUMFORMAT_TEXT);
    format_fre->setBorder(BORDERSTYLE_NONE);
    format_fre->setFont(font2);

    if(book)
    {
        Sheet* sheetMag = book->addSheet("幅度数据输出");
        Sheet* sheetPhase= book->addSheet("相位数据输出");
        if(sheetPhase&&sheetMag)
        {
            sheetMag->writeStr(0,0,"列-n",format_title);
            sheetMag->writeStr(0,1,"行-m",format_title);
            sheetPhase->writeStr(0,0,"列-n",format_title);
            sheetPhase->writeStr(0,1,"行-m",format_title);

            for(size_t i =0;i<p_id.size();++i)
            {
                int id  = p_id.at(i);
                short ls_row = 0;
                short ls_col = 0;
                TwoShortToId::instance()->IdToAddr(id,ls_row,ls_col);

                sheetMag->writeNum(i+1,0,ls_col,format_contex);
                sheetMag->writeNum(i+1,1,ls_row,format_contex);

                sheetPhase->writeNum(i+1,0,ls_col,format_contex);
                sheetPhase->writeNum(i+1,1,ls_row,format_contex);
            }

            int col = 2;
            for(size_t i=0;i<p_freq.size();++i)
            {
                sheetMag->setCol(col,col,12);
                sheetPhase->setCol(col,col,12);
                QString cur_freq = p_freq.at(i);
                if(p_CmpData.count(cur_freq)>0)
                {
                    QString freq = QString::number(cur_freq.toDouble()/1000000,'f',0);
                    QString buf = freq + QString("MHz");
                    sheetMag->writeStr(0,col,buf.toLocal8Bit().data(),format_fre);
                    sheetPhase->writeStr(0,col,buf.toLocal8Bit().data(),format_fre);

                    std::map<int,std::pair<double,double> > ls_map =  p_CmpData[cur_freq];
                    int row =1;
                    for(size_t j =0 ;j<p_id.size();++j)
                    {
                        int id = p_id.at(j);
                        if(ls_map.count(id)>0)
                        {
//                            QString magn = QString::number(ls_map[id].first,'f',3);
//                            QString phase = QString::number(ls_map[id].second,'f',3);
                            sheetMag->writeNum(row,col,ls_map[id].first,format_contex);
                            sheetPhase->writeNum(row,col,ls_map[id].second,format_contex);
                        }else
                        {
                            qDebug()<<"ConfigerExcel id not exist !";
                        }
                        ++row;
                    }
                    ++col;
                }else qDebug()<<"ConfigerExcel freq not exist !"<<cur_freq;
            }
        }
        bool ret = book->save(name.toLocal8Bit().data());
        if(ret)
        {
            // REPORT_SUCCEED;
        }/*else
            FILE_IS_OPEN;*/
        book->release();
    }

}
