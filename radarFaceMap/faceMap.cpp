#include "faceMap.h"


faceMap::faceMap()
{
    fileData.clear();
}

void faceMap::radarFaceTo()
{
      fileData.clear();
    genarray(1,20,1,12,true);
    genarray(21,24,1,11,true);
    genarray(25,28,1,10,true);
    genarray(29,32,1,9,true);
    genarray(33,36,1,8,true);
    genarray(37,40,1,6,true);


    genarray(1,20,-12,-1,false);
    genarray(21,24,-11,-1,false);
    genarray(25,28,-10,-1,false);
    genarray(29,32,-9,-1,false);
    genarray(33,36,-8,-1,false);
    genarray(37,40,-6,-1,false);

    qDebug() << "size" << fileData.size();
    saveFile();

}


void faceMap::genarray(int xstart,int xend,int ystart,int yend,bool isonesection)
{
    for(int i = xstart;i<=xend;++i)
    {
        for(int j =ystart;j<=yend;++j)
        {
            Data t_data_p;
            Data t_data_q;

            t_data_p.row = i;
            t_data_p.col = j;
            if(i >40 || i < -40 || j>12 || j < -12)
            return ;
            if(isonesection)
            {
                if(abs(i) % 2 == 0)
                    t_data_p.y  =  (abs(j)-1)*COL_WIDTH   +  0.25*COL_WIDTH ;
                else
                    t_data_p.y  =  (abs(j)-1)*COL_WIDTH   +  0.75*COL_WIDTH ;
            }else
            {
                if(abs(i) % 2 == 0)
                    t_data_p.y  =  -((abs(j)-1)*COL_WIDTH   +  0.75*COL_WIDTH );
                else
                    t_data_p.y  =  -((abs(j)-1)*COL_WIDTH   +  0.25*COL_WIDTH );
            }
            t_data_p.x   =  -( (abs(i)-1)*ROW_HEIGHT  +  0.5 *ROW_HEIGHT );
            t_data_p.z   =    0;
            fileData.push_back(t_data_p);

            t_data_q.row = - t_data_p.row;
            t_data_q.col = - t_data_p.col;
            t_data_q.x  =  - t_data_p.x;
            t_data_q.y  =  - t_data_p.y;
            t_data_q.z  =  0;
            fileData.push_back(t_data_q);
        }
    }
}


void faceMap::saveFile()
{
    TransForm t_;
    QFile file("./Array607.array");

    if(file.open(QFile::Text | QFile::WriteOnly))
    {
        QTextStream out(&file);
        out << "[COORDINATE]";
        out << endl;
        for(size_t i = 0; i < fileData.size(); ++i)
        {
            fileData[i].id = t_.locationToId(fileData[i].row,fileData[i].col);

            out << fileData[i].id;
            out << "=\"";
            //                                    out << fileData[i].row;
            //                                    out << ",";
            //                                    out << fileData[i].col;
            //                                    out << ",";
            out << fileData[i].x;
            out << ",";
            out << fileData[i].y;
            out << ",";
            out << fileData[i].z;
            out << "\"";
            out << endl;
        }
        out << "[OFFSET]";
        out << endl;
        out << "offset = \"";
        out <<  ROW_OFFSET;
        out << ",";
        out << COL_OFFSET;
        out << ",";
        out << HEI_OFFSET;
        out << "\"";
        out << endl;
        file.close();
    }
    else
    {
        qDebug() << "open fialed";
    }
}





