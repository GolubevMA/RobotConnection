#ifndef AUTOSCANCONTROLLER_H
#define AUTOSCANCONTROLLER_H

#include <QObject>

class AutoScanController : public QObject
{
    Q_OBJECT
public:
    explicit AutoScanController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // AUTOSCANCONTROLLER_H
