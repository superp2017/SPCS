#ifndef TRANSFORM_H
#define TRANSFORM_H


class TransForm
{

public:
    explicit TransForm();

    int AddreToId(short row,short col);
    void IdToAddre(int id,short &row,short &col);

    int locationToId(short &row, short &col);
    void idToLocation(int id,short &row,short &col);



};

#endif // TRANSFORM_H
