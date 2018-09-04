#include "m_calibrationmangerdlg.h"
#include "ui_m_calibrationmangerdlg.h"
#include "mainwindow.h"
#include <QFileInfo>

M_CalibrationMangerdlg::M_CalibrationMangerdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::M_CalibrationMangerdlg)
{
    ui->setupUi(this);
    init_lineedit();
    this->setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
}

M_CalibrationMangerdlg::~M_CalibrationMangerdlg()
{
    delete ui;
}


void M_CalibrationMangerdlg::init_lineedit()
{
    m_lineedits_match[1] = ui->lineEdit_p1_open;
    m_lineedits_match[2] = ui->lineEdit_p2_open;
    m_lineedits_match[3] = ui->lineEdit_p3_open;
    m_lineedits_match[4] = ui->lineEdit_p4_open;
    m_lineedits_match[5] = ui->lineEdit_p5_open;
    m_lineedits_match[6] = ui->lineEdit_p6_open;
    m_lineedits_match[7] = ui->lineEdit_p7_open;
    m_lineedits_match[8] = ui->lineEdit_p8_open;
    m_lineedits_match[9] = ui->lineEdit_p9_open;
    m_lineedits_match[10] = ui->lineEdit_p10_open;
    m_lineedits_match[11] = ui->lineEdit_p11_open;
    m_lineedits_match[12] = ui->lineEdit_p12_open;
    m_lineedits_match[13] = ui->lineEdit_p13_open;
    m_lineedits_match[14] = ui->lineEdit_p14_open;
    m_lineedits_match[15] = ui->lineEdit_p15_open;
    m_lineedits_match[16] = ui->lineEdit_p16_open;

    m_lineedits_short[1] = ui->lineEdit_p1_short;
    m_lineedits_short[2] = ui->lineEdit_p2_short;
    m_lineedits_short[3] = ui->lineEdit_p3_short;
    m_lineedits_short[4] = ui->lineEdit_p4_short;
    m_lineedits_short[5] = ui->lineEdit_p5_short;
    m_lineedits_short[6] = ui->lineEdit_p6_short;
    m_lineedits_short[7] = ui->lineEdit_p7_short;
    m_lineedits_short[8] = ui->lineEdit_p8_short;
    m_lineedits_short[9] = ui->lineEdit_p9_short;
    m_lineedits_short[10] = ui->lineEdit_p10_short;
    m_lineedits_short[11] = ui->lineEdit_p11_short;
    m_lineedits_short[12] = ui->lineEdit_p12_short;
    m_lineedits_short[13] = ui->lineEdit_p13_short;
    m_lineedits_short[14] = ui->lineEdit_p14_short;
    m_lineedits_short[15] = ui->lineEdit_p15_short;
    m_lineedits_short[16] = ui->lineEdit_p16_short;
}

void M_CalibrationMangerdlg::on_pushButton_reset_clicked()
{
    QMessageBox msgBox;
    QString text = CVTS::GBKToUnicode::toUnicode("这个操作恢复\n之前的校准库文件.");
    msgBox.setText(text);
    QString note =  CVTS::GBKToUnicode::toUnicode("是否继续恢复？");
    msgBox.setInformativeText(note);
    msgBox.setStandardButtons(QMessageBox::Ok |QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Ok:
        break;
    case QMessageBox::Cancel:
        return ;
        break;
    default:
        return ;
        break;
    }
    bool ret1 = false;
    for(int i =1;i<17;++i)
    {
        if(m_lineedits_match.count(i)>0)
        {
            QString name =QString("match_port%1").arg(i);
            QString org_path = QApplication::applicationDirPath() + "/Calibration/BEF/"+name+".s2p";
            bool ls_ret = repeat_file(org_path,name,false,false);
            ret1 |= ls_ret;
        }
    }

    for(int i =1;i<17;++i)
    {
        if(m_lineedits_short.count(i)>0)
        {
            QString name =QString("short_port%1").arg(i);
            QString org_path = QApplication::applicationDirPath() + "/Calibration/BEF/"+name+".s2p";
            bool ls_ret = repeat_file(org_path,name,false,false);
            ret1 |= ls_ret;
        }
    }

    if(ret1)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_rest_org_clicked()
{
    QMessageBox msgBox;
    QString text = CVTS::GBKToUnicode::toUnicode("这个操作恢复\n出厂的校准库文件.");
    msgBox.setText(text);
    QString note =  CVTS::GBKToUnicode::toUnicode("是否继续恢复？");
    msgBox.setInformativeText(note);
    msgBox.setStandardButtons(QMessageBox::Ok |QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIconPixmap(QPixmap(".\\image\\607logo-6464.png"));
    msgBox.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Ok:
        break;
    case QMessageBox::Cancel:
        return ;
        break;
    default:
        return ;
        break;
    }
    bool ret1 = false;
    for(int i =1;i<17;++i)
    {
        if(m_lineedits_match.count(i)>0)
        {
            QString name =QString("match_port%1").arg(i);
            QString org_path = QApplication::applicationDirPath() + "/config/ORGCALDAT/"+name+".s2p";
            bool ls_ret = repeat_file(org_path,name,true,false);
            ret1 |= ls_ret;
        }
    }
    for(int i =1;i<17;++i)
    {
        if(m_lineedits_short.count(i)>0)
        {
            QString name =QString("short_port%1").arg(i);
            QString org_path = QApplication::applicationDirPath() + "/config/ORGCALDAT/"+name+".s2p";
            bool ls_ret = repeat_file(org_path,name,true,false);
            ret1 |= ls_ret;
        }
    }

    if(ret1)
        note_sucess();
}



void M_CalibrationMangerdlg::on_pushButton_t_all_clicked()
{
    QMessageBox msgBox;
    QString text = CVTS::GBKToUnicode::toUnicode("这个操作将更新\n所有更改过的校准库文件.");
    msgBox.setText(text);
    QString note =  CVTS::GBKToUnicode::toUnicode("是否全部更新？");
    msgBox.setInformativeText(note);
    msgBox.setStandardButtons(QMessageBox::Ok |QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Ok:
        break;
    case QMessageBox::Cancel:
        return ;
        break;
    default:
        return ;
        break;
    }
    bool ret1 = false;
    for(int i =1;i<17;++i)
    {
        if(m_lineedits_match.count(i)>0)
        {
            QString name =QString("match_port%1").arg(i);
            bool ls_ret =   repeat_file(m_lineedits_match[i]->text(),name,true,false);
            ret1 |= ls_ret;
        }
    }
    for(int i =1;i<17;++i)
    {
        if(m_lineedits_short.count(i)>0)
        {
            QString name =QString("short_port%1").arg(i);
            bool ls_ret =   repeat_file(m_lineedits_short[i]->text(),name,true,false);
            ret1 |= ls_ret;
        }
    }

    if(ret1)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_exit_clicked()
{
    done(0);
}

void M_CalibrationMangerdlg::get_exist_file(QLineEdit *edit)
{
    QString  p_path = QFileDialog::getOpenFileName(this,tr("Cal File"),\
                                                   QApplication::applicationDirPath(), tr("Cal Files (*.s2p)"));

    if(p_path.isEmpty()) return;
    QFile ls_file(p_path);
    if(!ls_file.exists())
    {
        files_isnot_exist();
        return ;
    }
    edit->setText(p_path);
}

void M_CalibrationMangerdlg::files_isnot_exist(QString filename)
{
    QMessageBox mes;
    QString title = CVTS::GBKToUnicode::toUnicode("提示");

    QString text = " File is not exist!";
    if(!filename.isEmpty())
        text = filename + text;
    mes.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    mes.setWindowTitle(title);
    mes.setText(text);
    mes.exec();
}

void M_CalibrationMangerdlg::note_sucess()
{
    QMessageBox msgBox;
    QString text = CVTS::GBKToUnicode::toUnicode("校准库文件更新成功.");
    msgBox.setText(text);
    QString title =  CVTS::GBKToUnicode::toUnicode("提示");
    msgBox.setWindowTitle(title);
    msgBox.setWindowIcon(QIcon(".\\image\\607logo-6464-2.png"));
    msgBox.exec();
}




bool M_CalibrationMangerdlg::repeat_file(QString new_path,QString name,bool flag,bool isnote)
{
    if(new_path.isEmpty()) return false;
    QFile ls_file(new_path);
    if(!ls_file.exists())
    {
        if(flag)
            files_isnot_exist(name);
        return  false;
    }else
    {
        QString curname = QApplication::applicationDirPath() + "/Calibration/CUR/"+name+".s2p";
        QFile ls_cur_file(curname);

        QString  org_name = QApplication::applicationDirPath() + "/Calibration/BEF/"+name+".s2p";

        if(flag)
        {
            QFile ls_org_file(org_name);
            if(ls_org_file.exists()) ls_org_file.remove();
            if(ls_cur_file.exists())
                ls_cur_file.copy(org_name);
        }

        QFile ls_new_file(new_path);
        if(ls_cur_file.exists()) ls_cur_file.remove();
        if(ls_new_file.copy(curname))
        {
            if(isnote)
            {
                note_sucess();
            }
        }
        return  true;
    }
    return  true;
}


void M_CalibrationMangerdlg::on_pushButton_s1_clicked()
{
    return get_exist_file(ui->lineEdit_p1_open);
}

void M_CalibrationMangerdlg::on_pushButton_s2_clicked()
{
    return get_exist_file(ui->lineEdit_p2_open);
}

void M_CalibrationMangerdlg::on_pushButton_s3_clicked()
{
    return get_exist_file(ui->lineEdit_p3_open);
}

void M_CalibrationMangerdlg::on_pushButton_s4_clicked()
{
    return get_exist_file(ui->lineEdit_p4_open);
}

void M_CalibrationMangerdlg::on_pushButton_s5_clicked()
{
    return get_exist_file(ui->lineEdit_p5_open);
}

void M_CalibrationMangerdlg::on_pushButton_s6_clicked()
{
    return get_exist_file(ui->lineEdit_p6_open);
}

void M_CalibrationMangerdlg::on_pushButton_s7_clicked()
{
    return get_exist_file(ui->lineEdit_p7_open);
}

void M_CalibrationMangerdlg::on_pushButton_s8_clicked()
{
    return get_exist_file(ui->lineEdit_p8_open);
}

void M_CalibrationMangerdlg::on_pushButton_s9_clicked()
{
    return get_exist_file(ui->lineEdit_p9_open);
}

void M_CalibrationMangerdlg::on_pushButton_s10_clicked()
{
    return get_exist_file(ui->lineEdit_p10_open);
}

void M_CalibrationMangerdlg::on_pushButton_s11_clicked()
{
    return get_exist_file(ui->lineEdit_p11_open);
}

void M_CalibrationMangerdlg::on_pushButton_s12_clicked()
{
    return get_exist_file(ui->lineEdit_p12_open);
}

void M_CalibrationMangerdlg::on_pushButton_s13_clicked()
{
    return get_exist_file(ui->lineEdit_p13_open);
}

void M_CalibrationMangerdlg::on_pushButton_s14_clicked()
{
    return get_exist_file(ui->lineEdit_p14_open);
}

void M_CalibrationMangerdlg::on_pushButton_s15_clicked()
{
    return get_exist_file(ui->lineEdit_p15_open);
}

void M_CalibrationMangerdlg::on_pushButton_s16_clicked()
{
    return get_exist_file(ui->lineEdit_p16_open);
}

void M_CalibrationMangerdlg::on_pushButton_s1_2_clicked()
{
    return get_exist_file(ui->lineEdit_p1_short);
}

void M_CalibrationMangerdlg::on_pushButton_s2_2_clicked()
{
    return get_exist_file(ui->lineEdit_p2_short);
}

void M_CalibrationMangerdlg::on_pushButton_s3_2_clicked()
{
    return get_exist_file(ui->lineEdit_p3_short);
}

void M_CalibrationMangerdlg::on_pushButton_s4_2_clicked()
{
    return get_exist_file(ui->lineEdit_p4_short);
}

void M_CalibrationMangerdlg::on_pushButton_s5_2_clicked()
{
    return get_exist_file(ui->lineEdit_p5_short);
}

void M_CalibrationMangerdlg::on_pushButton_s6_2_clicked()
{
    return get_exist_file(ui->lineEdit_p6_short);
}

void M_CalibrationMangerdlg::on_pushButton_s7_2_clicked()
{
    return get_exist_file(ui->lineEdit_p7_short);
}

void M_CalibrationMangerdlg::on_pushButton_s8_2_clicked()
{
    return get_exist_file(ui->lineEdit_p8_short);
}

void M_CalibrationMangerdlg::on_pushButton_s9_2_clicked()
{
    return get_exist_file(ui->lineEdit_p9_short);
}

void M_CalibrationMangerdlg::on_pushButton_s10_2_clicked()
{
    return get_exist_file(ui->lineEdit_p10_short);
}

void M_CalibrationMangerdlg::on_pushButton_s11_2_clicked()
{
    return get_exist_file(ui->lineEdit_p11_short);
}

void M_CalibrationMangerdlg::on_pushButton_s12_2_clicked()
{
    return get_exist_file(ui->lineEdit_p12_short);
}

void M_CalibrationMangerdlg::on_pushButton_s13_2_clicked()
{
    return get_exist_file(ui->lineEdit_p13_short);
}

void M_CalibrationMangerdlg::on_pushButton_s14_2_clicked()
{
    return get_exist_file(ui->lineEdit_p14_short);
}

void M_CalibrationMangerdlg::on_pushButton_s15_2_clicked()
{
    return get_exist_file(ui->lineEdit_p15_short);
}

void M_CalibrationMangerdlg::on_pushButton_s16_2_clicked()
{
    return get_exist_file(ui->lineEdit_p16_short);
}


void M_CalibrationMangerdlg::on_pushButton_t1_clicked()
{
    bool ret =false;
    ret&=  repeat_file(ui->lineEdit_p1_open->text(),"match_port1",false);
    ret&=  repeat_file(ui->lineEdit_p1_short->text(),"short_port1",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t2_clicked()
{
    bool ret =false;
    ret&=  repeat_file(ui->lineEdit_p2_open->text(),"match_port2",false);
    ret&=  repeat_file(ui->lineEdit_p2_short->text(),"short_port2",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t3_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p3_open->text(),"match_port3",false);
    ret&= repeat_file(ui->lineEdit_p3_short->text(),"short_port3",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t4_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p4_open->text(),"match_port4",false);
    ret&= repeat_file(ui->lineEdit_p4_short->text(),"short_port4",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t5_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p5_open->text(),"match_port5",false);
    ret&= repeat_file(ui->lineEdit_p5_short->text(),"short_port5",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t6_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p6_open->text(),"match_port6",false);
    ret&= repeat_file(ui->lineEdit_p6_short->text(),"short_port6",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t7_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p7_open->text(),"match_port7",false);
    ret&= repeat_file(ui->lineEdit_p7_short->text(),"short_port7",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t8_clicked()
{
    bool ret =false;
    ret&=  repeat_file(ui->lineEdit_p8_open->text(),"match_port8",false);
    ret&= repeat_file(ui->lineEdit_p8_short->text(),"short_port8",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t9_clicked()
{
    bool ret =false;
    ret&=  repeat_file(ui->lineEdit_p9_open->text(),"match_port9",false);
    ret&=  repeat_file(ui->lineEdit_p9_short->text(),"short_port9",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t10_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p10_open->text(),"match_port10",false);
    ret&= repeat_file(ui->lineEdit_p10_short->text(),"short_port10",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t11_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p11_open->text(),"match_port11",false);
    ret&= repeat_file(ui->lineEdit_p11_short->text(),"short_port1",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t12_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p12_open->text(),"match_port12",false);
    ret&= repeat_file(ui->lineEdit_p12_short->text(),"short_port12",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t13_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p13_open->text(),"match_port13",false);
    ret&=  repeat_file(ui->lineEdit_p13_short->text(),"short_port13",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t14_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p14_open->text(),"match_port14",false);
    ret&= repeat_file(ui->lineEdit_p14_short->text(),"short_port14",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t15_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p15_open->text(),"match_port15",false);
    ret&= repeat_file(ui->lineEdit_p15_short->text(),"short_port15",false);
    if(ret)
        note_sucess();
}

void M_CalibrationMangerdlg::on_pushButton_t16_clicked()
{
    bool ret =false;
    ret&= repeat_file(ui->lineEdit_p16_open->text(),"match_port16",false);
    ret&= repeat_file(ui->lineEdit_p16_short->text(),"short_port16",false);
    if(ret)
        note_sucess();
}

























































//QString &M_CalibrationMangerdlg::get_current_calfile()
//{
//    return m_select_calfile_path;
//}

//void M_CalibrationMangerdlg::reset()
//{
//    init();
//}

//void M_CalibrationMangerdlg::init()
//{
//    add_base_item();
//    add_user_item();
//    m_select_calfile_path = "null";
//    current_tab = NON;
//}




//void M_CalibrationMangerdlg::add_base_item()
//{
//    ui->listWidget_base->clear();
//    QList<QString>  list_base = M_CalManager::instance()->BaseLib();
//    for(int i = 0;i<list_base.size() ;++i)
//    {
//        ui->listWidget_base->addItem(list_base.at(i));
//    }
//}

//void M_CalibrationMangerdlg::add_user_item()
//{
//    ui->listWidget_user->clear();
//    QList<QString> list_user = M_CalManager::instance()->UserLib();
//    for(int i = 0 ;i<list_user.size();++i)
//    {
//        ui->listWidget_user->addItem(list_user.at(i));
//    }
//}


//void M_CalibrationMangerdlg::on_pushButton_clicked()//添加
//{
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Add Libs"),
//                                                    QCoreApplication::applicationDirPath(),tr("Calibration (*.cal)"));
//    if (!fileName.isEmpty())
//    {
//        // system("");
//        QFile ls_file(fileName);
//        QFileInfo fileinfo(fileName);
//        QString name = fileinfo.fileName();
//        if(name.isEmpty())
//        {
//            QMessageBox::information(this, tr("Warnning"),
//                                     tr("Please select correct file!"));
//            return;
//        }
//        ls_file.copy(QString("./BaseLib/") + name);
//        QList<QString> list;
//        list.push_back(name);
//        update_baselibs(list,true);
//    }
//    else
//        QMessageBox::information(this, tr("Warnning"),
//                                 tr("Please select correct file!"));
//}

//void M_CalibrationMangerdlg::on_pushButton_2_clicked()//删除
//{
//    if(current_tab == BASE)
//    {
//        QString name =ui->listWidget_base->currentItem()->text();
//        QString path = QString("./BaseLib/")+name;
//        M_CalManager::instance()->rename_file(path);
//        QList<QString> list;
//        list.push_back(name);
//        add_base_item();
//    }else
//        return;

//}

//void M_CalibrationMangerdlg::on_pushButton_3_clicked()//确定
//{
//    m_select_calfile_path.clear();
//    if(current_tab == BASE)
//    {
//        QString name =ui->listWidget_base->currentItem()->text();
//        m_select_calfile_path = QString("./BaseLib/")+name;
//        done(0);
//    }else
//    {
//        QMessageBox::information(this, tr("Warnning"),
//                                 tr("Please select correct cal file!"));
//    }
//}

//void M_CalibrationMangerdlg::on_pushButton_4_clicked()//取消
//{
//    done(-1);
//}


//void M_CalibrationMangerdlg::update_baselibs(QList<QString> &list_item, bool add_)
//{
//    for(int i =0;i<list_item.size();++i)
//    {
//        if(add_)
//        {
//            for(int k=0;k<ui->listWidget_base->count();++k)
//            {
//                if(ui->listWidget_base->item(k)->text() == list_item.at(i))
//                {
//                    QMessageBox::information(this, tr("Failed"),
//                                             tr("Current selected libs is existed in BaseLib, Update failed !"));
//                    return;
//                }
//            }

//            ui->listWidget_base->addItem(list_item.at(i));
//        }
//        else
//        {
//            QList<QListWidgetItem *> item = ui->listWidget_base->findItems(list_item.at(i),Qt::MatchFixedString);
//            for(int j=0;j<item.size();++j)
//            {qDebug()<<item.at(j);
//                ui->listWidget_base->removeItemWidget(item.at(j));
//            }
//        }
//    }
//}



//void M_CalibrationMangerdlg::on_listWidget_base_doubleClicked(const QModelIndex &index)
//{
//    QString data = index.data().toString();
//    if(!data.isEmpty())
//        M_CalManager::instance()->open_calibration(data);
//    else
//        return ;
//}

//void M_CalibrationMangerdlg::on_listWidget_user_doubleClicked(const QModelIndex &index)
//{
//    QString data = index.data().toString();
//    if(!data.isEmpty())
//        M_CalManager::instance()->open_calibration(data);
//    else
//        return ;
//}



//void M_CalibrationMangerdlg::on_listWidget_base_itemPressed(QListWidgetItem *item)
//{
//    current_tab = BASE;
//}

//void M_CalibrationMangerdlg::on_listWidget_user_itemPressed(QListWidgetItem *item)
//{
//    current_tab = USER;
//}



