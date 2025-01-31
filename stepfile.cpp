#include "stepfile.h"
#include "fstream"
#include <QVector>
#include <QTextDocument>
#include "math.h"
#include "qdebug.h"
#include "regex"
//------------------------------------------------------------------------------
StepFile::StepFile()
{
    Entitys = new QMap<int, Entity>();
    parentData = new QMap<int, QList<int>>;
    AP203 = NULL;
    this->filename = " ";
}
//------------------------------------------------------------------------------
StepFile::StepFile(QString fn, ExpressSchema *schema)
{
    Entitys = new QMap<int, Entity>;
    parentData = new QMap<int, QList<int>>;
    this->filename = fn;
    this->AP203 = schema;

    EntityParse();

    qDebug() << "consrtr end";
}
//------------------------------------------------------------------------------
StepFile::~StepFile()
{
    delete parentData;
    delete Entitys;
    delete AP203;

    parentData = NULL;
    Entitys= NULL;
    AP203 = NULL;
}
//------------------------------------------------------------------------------
//формриуем списки параматров и значений
//------------------------------------------------------------------------------
void StepFile::EntityParse()
{
    std::ifstream inputFile;
    inputFile.open(filename.toStdString());
    if (!inputFile.is_open()) {
        return;
    }

    qDebug() << "step open";

    QString stepstring = "";
    QString datastring;
    QList<QString> *stringarray = new QList<QString>;

    //читаем все строи друг за друнгом в строку step_string
    std::string buf;
    while (!inputFile.eof())    {
        std::getline(inputFile, buf);
        QString ln = QString::fromStdString(buf);
        if (!ln.isEmpty() && !ln.isNull()) stepstring += ln;
    }

    //читааем дату
    int i1 = stepstring.indexOf("DATA;");
    datastring = stepstring.mid(i1 + 7);
    int i2 = datastring.indexOf("ENDSEC;");
    datastring = datastring.mid(0, i2 - 1);
    datastring = datastring.replace("\r", "");
    datastring = datastring.replace("\n", "");

    stringarray->append(datastring.split(';'));

    QList<QString> str;
    QList<QString> identifier;
    //QVector<int> id_array;

    str.clear();
    identifier.clear();
    //id_array.clear();

    identifier.reserve(stringarray->length());
    //id_array.reserve(stringarray->length());

    //выражение для посика обьектов CAD
    QRegularExpression g("((?<=(= ))[^\\(]*(?=()))");
    //парсим параметры обьектов CAD
    QRegularExpression gData("(\\((?>[^()]+|(?1))*\\))");
    // выражение для посика  ккомплексных обьектов(обьекты сосотянщие из нескольких обьектов)
    QRegularExpression complexmatch("[=]s*[\\(].*[\\) ;]");
    QRegularExpressionMatch m1, m2, m_complex;


    QList<QString> datastr;

    QString str_name;
    QString str_dat;

    //проходимся по всем  строкам
    for (int i = 0; i < stringarray->length(); i++)
    {
        //парсим строки содеражащие обьявления точек и примитивовов
        if ((!stringarray->at(i).contains("#")) || (!stringarray->at(i).contains("="))) continue;

        QString data = stringarray->at(i);

        //парсим номер  (id) прмимтива
        str = data.split('=');
        str[0].replace("#", "");
        int id = str[0].toInt();

        m1 = g.match(data);
        m_complex = complexmatch.match(data);

        //парсим название примитива
        if (m1.hasMatch() && !m1.captured(0).isEmpty() && m_complex.captured(0).isEmpty())
        {
            str_name = m1.captured(0).trimmed(); //nam
            qDebug() << "pt " << str_name;

            //парсим аргументы примимтива
            m2 = gData.match(data);
            if (m2.hasMatch())
            {
                str_dat = m2.captured(0).trimmed();
                //удлаеоляем скобки
//                if (str_dat.startsWith('(')) str_dat.remove(0,1);
//                if (str_dat.endsWith(')')) str_dat.remove(str_dat.length()-1,1);

                qDebug() << " ARG " <<  str_dat;
                Entity ent(id, str_name, str_dat, AP203);
                Entitys->insert(id,ent);
            }
        }

        //парсим комплексиные обьекты
        if (m_complex.hasMatch() && !m_complex.captured(0).isEmpty())
        {
            str_dat = m_complex.captured(0).trimmed(); //даные

            qDebug() << " comlex data " << str_dat;

//            str_dat = str_dat.remove('=', '(');
//            str_dat = str_dat.remove(';');
//            str_dat = str_dat.remove(')');

//            QList<int> splitLocations;
//            splitLocations.append(0);
//            int level = 0;
//            for (int j = 0; j < str_dat.length(); j++)
//            {
//                if (str_dat[j] == '(') level++;
//                if (str_dat[j] == ')') level--;
//                if (str_dat[j] == ')' && level == 0)
//                {
//                    splitLocations.append(j + 1);
//                }
//            }
//            QList<QString> entList;
//            for (int j = 1; j < splitLocations.length(); j++)
//            {
//                entList.append(str_dat.mid(splitLocations[j - 1], splitLocations[j] - splitLocations[j - 1]).trimmed());
//            }

//            QList<QString> types;
//            for (int j = 0; j < entList.length(); j++)
//            {
//                int location1 = entList[j].indexOf(' ');
//                int location2 = entList[j].indexOf('(');
//                int location;

//                if (location1 > 0) {
//                    location = location1 < location2 ? location1 : location2;
//                }
//                else location = location2;

//                QString type = entList[j].mid(0, location);
//                types.append(type);
//            }

//            //добавляен entity
//            EntityComplex EntC(id, types, entList, this->AP203);
//            Entitys->insert(id, EntC);
        }
    }

    qDebug() << "paaed";

    delete stringarray;

//    //прохидмся по всем аттрибутам данныго entity
//    foreach (Entity entity, Entitys->values())
//    {
//        QList<QVariant> flattenedAttributeList = GetFlattenedAttributes(entity.attributesConverted);
//        foreach (QVariant item, flattenedAttributeList)
//        {
//            if (item.canConvert<RefID>())
//            {
//                RefID ref_item = item.value<RefID>();
//                //если ключ найден - добавиь в родительнсикй лист
//                QList<int>  existingList = parentData->value(ref_item, QList<int>());
//                if (!existingList.isEmpty())
//                {
//                    existingList.append(entity.entityID);
//                    parentData->insert(ref_item, existingList);
//                }
//                //если по данному ключу не найденно значение - добвим список с текущим entitiy
//                else
//                {
//                    //parentData[ref_item] = QList<int>{entity.entityID};
//                    parentData->insert(ref_item, QList<int>{entity.entityID});
//                }
//            }
//        }
//     }
}
//------------------------------------------------------------------------------
//получаем сглаженный список всех атрибутов, включая атрибуты в саблистах
//------------------------------------------------------------------------------
QList<QVariant> StepFile::GetFlattenedAttributes(QList<QVariant> inputList)
{
    if (inputList.isEmpty()) return QList<QVariant>();

    QList<QVariant> flattenedList;
    foreach (QVariant listItem, inputList)
    {
        if (listItem.canConvert<QVariantList>())
        {
            QVariantList list = listItem.value<QVariantList>();
            flattenedList.append(GetFlattenedAttributes(list));
        }
        else {
            flattenedList.append(listItem);
        }
    }
    return flattenedList;
}
//------------------------------------------------------------------------------
//получаем список родительсикх элментов
//------------------------------------------------------------------------------
QList<int> StepFile::GetAllParents(int id)
{
    return parentData->value(id, QList<int>());
}
//------------------------------------------------------------------------------
//получаем список дочерних элемнтов
//------------------------------------------------------------------------------
QList<int> StepFile::GetChildren(int id)
{
    if (id==-1) {
        return QList<int>();
    }

    Entity e1 = Entitys->value(id, Entity());
    QList<int> childIDs;

    if (e1.attributesConverted.isEmpty()) return QList<int>();

    foreach (const QVariant &item, e1.attributesConverted)
    {
        if (item.canConvert<RefID>())
        {
            RefID ref_it = item.value<RefID>();
            childIDs.append(ref_it);
        }
        else if (item.canConvert<QVariantList>())
        {
            QSequentialIterable iterable = item.value<QSequentialIterable>();
            foreach (const QVariant &v, iterable)
            {
                if (v.canConvert<RefID>())
                {
                    RefID ref_it = v.value<RefID>();
                    childIDs.append(ref_it);
                }
            }
        }
    }
    return childIDs;
}
//------------------------------------------------------------------------------
//получаем списко идентификаторов дочерних аттрибутов для текущего
//------------------------------------------------------------------------------
QList<int> StepFile::GetAllChildren(int id)
{
    Entity e1 = Entitys->value(id);
    QList<int> childIDs;

//    QSequentialIterable iterable = e1.attributesConverted;

    foreach (const QVariant &item, e1.attributesConverted)
    {
        if (item.canConvert<RefID>())
        {
            RefID id = item.value<RefID>();
            childIDs.append(id);
            childIDs.append(id);
        }

        else if (item.canConvert<QVariantList>())
        {
            QSequentialIterable iterable = item.value<QSequentialIterable>();
            foreach (const QVariant &element, iterable)
            {
                if (element.canConvert<RefID>())
                {
                    RefID id = element.value<RefID>();
                    childIDs.append(id);
                    childIDs.append(GetAllChildren(id));
                }
            }
        }
    }
    return childIDs;
}
//------------------------------------------------------------------------------
//получсем тип entity
//------------------------------------------------------------------------------
QString StepFile::GetTypeOfEnt(int id)
{
    return Entitys->value(id).type;
}
//------------------------------------------------------------------------------
//фомрруем дерево с текущего id и типа
//------------------------------------------------------------------------------
QList<int> StepFile::searchTreeByType(int id, QString type)
{
    QList<QString> typesToSearchFor = AP203->GetAllChildren(type);
    typesToSearchFor.append(type.toLower());
    QList<int> children = GetAllChildren(id);
    QList<int> found;

    foreach (int cid, children)
    {
        foreach (QString subtype, typesToSearchFor)
        {
            if (Entitys->value(cid).type.toLower() == subtype) found.append(cid);
        }
    }
    return found;
}
//------------------------------------------------------------------------------
//получаем id кордевого предка
//-----------------------------------------------------------------------------
QList<int> StepFile::GetFirstParent(int id)
{
    QList<int> parents = GetAllParents(id);

    if (parents.length() == 0)
    {
        return QList<int> {id};
    }
    else {
        QList<int> firstParents;
        foreach (int p,  parents)
        {
            firstParents.append(GetFirstParent(p));
        }
        return firstParents;
    }
}
//------------------------------------------------------------------------------
//получаем значение аттриьуа по имени и id
//------------------------------------------------------------------------------
QVariant StepFile::GetAttributeValueByName(int id, QString attributeName)
{
    if (id < 1) return QVariant();

    attributeName = attributeName.toLower();
    QList<AttributeDefinition> ADList = this->AP203->GetEntityByName(Entitys->value(id, Entity()).type).attributeDefinitionsFullTree;
    int foundID = -1;
    for (int i = 0; i < ADList.length(); i++)
    {
        if (ADList[i].name == attributeName) foundID = i;
    }
    if (foundID > -1) {
        return QVariant(Entitys->value(id, Entity()).attributesConverted[foundID]);
    }
    else {
        return QVariant();
    }
}
////------------------------------------------------------------------------------
////возвраеам список значений аттрбутов по набору ENtity и названию аттрибута
////------------------------------------------------------------------------------
//QVariant StepFile::GetAttributeValueByNameComplex(EntityComplex cpe, QString attributeName)
//{
//    for (int i = 0; i < cpe.attributeDefinitions.length(); i++)
//    {
//        if (cpe.attributeDefinitions[i].name == attributeName)
//        {
//            return QVariant(cpe.attributesConverted[i]);
//        }
//    }
//    return QVariant();
//}
//------------------------------------------------------------------------------
//получаем кориненвые entity
//------------------------------------------------------------------------------
QList<int> StepFile::GetTopLevelEntities()
{
    QList<int> topLevel;
    QList<int> hasParents;

    //формируем набор ключей Entuty
    foreach (int key, Entitys->keys())
    {
        topLevel.append(key);
    }
    //формируем набор родительсикх ключей
    foreach (int key, parentData->keys())
    {
        hasParents.append(key);
    }
    //удалеям ис списка элментов верхнего уровня элементы имющия родителей
    foreach (int it, hasParents) {
        topLevel.removeOne(it);
    }
    return topLevel;
}
//------------------------------------------------------------------------------
StepPrinter::StepPrinter(StepFile stepFile)
{
    this->stepFile = stepFile;
    indentStringTerminator = "└──";
    indentStringSpaces  = "      ";
}
//------------------------------------------------------------------------------
//выводим дерево визаулиции CAD
//------------------------------------------------------------------------------
QList<QString> StepPrinter::TreeToString()
{
    QList<int> topLevelIDs = stepFile.GetTopLevelEntities();

    treeStrings.clear();
    foreach (int id, topLevelIDs)
    {
        PrintChildrenRecursive(id, 0);
    }

    for (int y = 1; y < treeStrings.length(); y++)
    {
        for (int x = 0; x < treeStrings[y].length(); x++)
        {
            FillLineRecursive(y, x);
        }
    }

    tree.clear();
    for (int y = 0; y < treeStrings.size(); y++)
    {
        tree.append(treeStrings[y]);
    }

    return tree;
}
//------------------------------------------------------------------------------
void StepPrinter::FillLineRecursive(int y, int x)
{
    if (treeStrings[y][x] == '└' && treeStrings[y - 1][x] == ' ')
    {
        treeStrings[y - 1][x] = '│';
        FillLineRecursive(y - 1, x);
    }
    else if (treeStrings[y][x] == '└' && treeStrings[y - 1][x] == '└')
    {
        treeStrings[y - 1][x] = '├';
        FillLineRecursive(y - 1, x);
    }
    else if (treeStrings[y][x] == '│' && treeStrings[y - 1][x] == '└')
    {
        treeStrings[y - 1][x] = '├';
        FillLineRecursive(y - 1, x);
    }
    else if (treeStrings[y][x] == '│' && treeStrings[y - 1][x] == ' ')
    {
        treeStrings[y - 1][x] = '│';
        FillLineRecursive(y - 1, x);
    }
}
//------------------------------------------------------------------------------
void StepPrinter::PrintChildrenRecursive(int id, int depth)
{
    if (id == -1) return;

    QList<int> children = stepFile.GetChildren(id);
    currentLine = "";

    for (int i = 0; i < depth - 1; i++)
    {
        currentLine.append(indentStringSpaces);
    }

    if (depth > 0)
    {
        currentLine.append(indentStringTerminator);
    }
    currentLine.append(QString::number(stepFile.Entitys->value(id).entityID) + " " + stepFile.Entitys->value(id).type);
    treeStrings.append(currentLine);

    foreach (int cid, children)
    {
        PrintChildrenRecursive(cid, depth + 1);
    }
}
