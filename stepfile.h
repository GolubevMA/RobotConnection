#ifndef STEPFILE_H
#define STEPFILE_H

#include "QObject"
#include "QString"
#include <QStringList>
#include "expressschema.h"
#include <QRegularExpression>
#include <QStringBuilder>

class StepFile
{
public:
    
    QString filename;
    QMap<int, Entity> *Entitys;
    ExpressSchema *AP203;
    QMap<int, QList<int>> *parentData;
    
    StepFile();
    StepFile(QString fn, ExpressSchema *schema);
    ~StepFile();
    
    void EntityParse();
    QList<QVariant> GetFlattenedAttributes(QList<QVariant> inputList);
    QList<int> GetAllParents(int id);
    QList<int> GetChildren(int id);
    QList<int> GetAllChildren(int id);
    QString GetTypeOfEnt(int id);
    QList<int> searchTreeByType(int id, QString type);
    QList<int> GetFirstParent(int id);
    QVariant GetAttributeValueByName(int id, QString attributeName);
    //QVariant GetAttributeValueByNameComplex(EntityComplex cpe, QString attributeName);
    QList<int> GetTopLevelEntities();
    
};


class StepPrinter
{
public :
        StepFile stepFile;
        QString indentStringTerminator;
        QString indentStringSpaces;
        QList<QString> treeStrings;
        QString currentLine;
        QList<QString> tree;

        StepPrinter(StepFile stepFile);

        void FillLineRecursive(int y, int x);
        void PrintChildrenRecursive(int id, int depth);
        QList<QString> TreeToString();
};

#endif // STEPFILE_H
