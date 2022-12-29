#ifndef SAVEURLS_H
#define SAVEURLS_H

//#include "SaveUrls_global.h"

//class QStringList;

#include <QStringList>

class SaveUrls
{
public:
    SaveUrls();

    void save(QStringList);
    QStringList load();
};

#endif // SAVEURLS_H
