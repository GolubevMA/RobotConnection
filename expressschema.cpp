#include "fstream"
#include <QVector>
#include <QTextDocument>
#include <QStringList>
#include "qdebug.h"
#include "expressschema.h"
//------------------------------------------------------------------------------
ExpressSchema::ExpressSchema()
{
    //иницниализация
    entityDefinitionList = new QMap<QString, EntityDefinition>();
    typeAliasesReal = new QList<QString>();
    typeAliasesInt = new QList<QString>();

    schemaFileName = "";

    ParseSchema();
    ParseType();
}
//------------------------------------------------------------------------------
ExpressSchema::ExpressSchema(QString filename)
{
    //иницниализация
    entityDefinitionList = new QMap<QString, EntityDefinition>();
    typeAliasesReal = new QList<QString>();
    typeAliasesInt = new QList<QString>();

    schemaFileName = filename;

    ParseSchema();
    ParseType();

//    watch.Stop();
//    var elapsedMs = watch.ElapsedMilliseconds;
//    qDebug() << "Schema Parsed in " + elapsedMs.ToQString() + " ms";
}
//------------------------------------------------------------------------------
ExpressSchema::~ExpressSchema()
{
    delete entityDefinitionList;
    delete typeAliasesReal;
    delete typeAliasesInt;
}
//------------------------------------------------------------------------------
//функция заполняет списко номеров вхождений needle в haystack
//------------------------------------------------------------------------------
QList<int> ExpressSchema::AllIndexesOf(QString haystack, QString needle)
{
    int index1, index2;
    if (needle.isEmpty() || needle.isNull()) return QList<int>();
    QList<int> indexes;
    for (int index = 0; ; index += needle.length())
    {
        index1 = haystack.indexOf(" " + needle, index);
            index2 = haystack.indexOf("\n" + needle, index);
        if (index1 != -1) index = index1;
        else if (index2 != -1) index = index2;
        else index = -1;
        if (index == -1)
            break;
        indexes.append(index);
    }
    return indexes;
}
//------------------------------------------------------------------------------
QList<int> ExpressSchema::AllIndexesOf(QString haystack, QList<QString> needles)
{
    QList<int> indexes;
    QString needle = "";
    for (int j = 0; j < needles.length(); j++)
    {
        needle = needles[j];
        for (int index = 0; ; index += needle.length())
        {
            index = haystack.indexOf(needle, index);
            if (index == -1)
                break;

            indexes.append(index);
        }
    }

    //сортируем по возрастанию
    for (int i =0; i < indexes.length() - 1; i++)
    {
        for (int j = 0; j < indexes.length() - i - 1; j++)
        {
            if (indexes[j] > indexes[j+1]) {
                int tmp = indexes[j];
                indexes[j+1] = indexes[j];
                indexes[j] = tmp;
            }
        }
    }

    return indexes;
}
//------------------------------------------------------------------------------
//загружаем типы графических примитивово
//------------------------------------------------------------------------------
void ExpressSchema::ParseType()
{
    std::ifstream inputFile;
    inputFile.open(schemaFileName.toStdString());
    if (!inputFile.is_open()) {
        qDebug() << "oprne rrroror";
        return;
    }

    qDebug() << "Read sucxes";

    QVector<QString> string_array;

    std::string buf;
    while (!inputFile.eof())    {
        //полузаем строку таблицы
        std::getline(inputFile, buf);
        QString line = QString::fromStdString(buf);
        string_array.append(line);
    }

    QString value;
    QString name_type;
    int idx;

    //заполням список назавний протсых типов
    for (int i = 0; i < string_array.length(); i++)
    {
        string_array[i] = string_array[i].trimmed();
        if (string_array[i].startsWith("TYPE") && string_array[i].contains('='))
        {
            string_array[i].replace(';', ' ');
            idx = string_array[i].indexOf("=");
            name_type = string_array[i].mid(4,idx-4).trimmed();
            value = string_array[i].mid(idx+1, string_array[i].length() - idx - 1 ).trimmed();

            if (value == "REAL") typeAliasesReal->append(name_type);
            if (value == "INTEGER") typeAliasesInt->append(name_type);
        }
    }

    //заполням список назавний сложных типов
    for (int i = 0; i < string_array.length(); i++)
    {
        string_array[i] = string_array[i].trimmed();
        if (string_array[i].startsWith("TYPE") && string_array[i].contains('='))
        {
            string_array[i].replace(';', ' ');
            idx = string_array[i].indexOf("=");
            name_type = string_array[i].mid(4, idx - 4).trimmed();
            value = string_array[i].mid(idx + 1, string_array[i].length() - idx - 1).trimmed();

            if (typeAliasesReal->contains(value)) typeAliasesReal->append(name_type);
            if (typeAliasesInt->contains(value)) typeAliasesInt->append(name_type);
        }
    }

    //переводим названия типво в врехний регистр
    for (int i =0; i < typeAliasesReal->length(); i++) {
        typeAliasesReal->replace(i, typeAliasesReal->value(i).toUpper());
        qDebug() << "REL" << typeAliasesReal->at(i);
    }

    for (int i =0; i < typeAliasesInt->length(); i++) {
        typeAliasesInt->replace(i, typeAliasesInt->value(i).toUpper());
        qDebug() <<  "int "<< typeAliasesInt->at(i);
    }
}
//------------------------------------------------------------------------------
// парсим схему
//------------------------------------------------------------------------------
void  ExpressSchema::ParseSchema()
{
//    TextReader tr = new StreamReader(schemaFileName);
//    QString infile_string;
//    infile_string = tr.ReadToEnd();

    std::ifstream inputFile;
    inputFile.open(schemaFileName.toStdString());
    if (!inputFile.is_open()) {
        return;
    }

    //читаем файл
    QString infile_string = "";
    std::string buf;
    while (!inputFile.eof())    {
        //полузаем строку таблицы
        std::getline(inputFile, buf);
        infile_string += QString::fromStdString(buf);
    }

    //формурием список всех Entity
    QList<int> indexesStart = AllIndexesOf(infile_string, "ENTITY");
    QList<int> indexesEnd = AllIndexesOf(infile_string, "END_ENTITY");

    QList<QString> *entries = new QList<QString>();
    for (int i = 0;  i <  indexesStart.length(); i++ )
    {
        QString substr = infile_string.mid(indexesStart[i], indexesEnd[i] - indexesStart[i]);
        entries->append(substr);
    }

    QList<QString> sections = QList<QString>{ "SUBTYPE OF", "SUPERTYPE OF", "ABSTRACT SUPERTYPE", "WHERE", "DERIVE", "UNIQUE", ";" };

    //читаем параматры каждог etity
    for (int i = 0;  i < entries->length(); i++ )
    {
        QList<int> indexesSplit = AllIndexesOf(entries->at(i), sections);
        indexesSplit.insert(0,0);
        indexesSplit.append(entries->at(i).length());

        //парсим подразделы
        QList<QString> subsections;
        for (int j = 1; j < indexesSplit.length(); j++)
        {
            QString subsection = entries->at(i).mid(indexesSplit[j - 1], indexesSplit[j] - indexesSplit[j - 1]).replace(';', ' ').trimmed();
            if (!subsection.isEmpty() && !subsection.isNull())  {
                subsections.append(subsection);
                //qDebug() << "susbesx " << subsection;
            }
        }

        QString name = subsections[0].mid(7, subsections[0].length() - 7).trimmed();
        QString supertypes="";
        QString subtypes="";

        int endOfAttributes;
        for (endOfAttributes = 1; endOfAttributes < subsections.length(); endOfAttributes++)
        {
            if (subsections[endOfAttributes].contains("WHERE")) break;
            if (subsections[endOfAttributes].contains("DERIVE")) break;
            if (subsections[endOfAttributes].contains("UNIQUE")) break;
            if (subsections[endOfAttributes].contains("INVERSE")) break;
            
        }
        endOfAttributes--;


        QList<AttributeDefinition> attributeList;
        QList<QString> supertypesList;
        QList<QString> subtypesList;
       
        for (int j = 1; j <= endOfAttributes; j++)
        {

            if (subsections[j].contains("SUBTYPE OF"))
            {
                subtypes = subsections[j].mid(11,subsections[j].length()-11) ;
                //supertypes = subsections[j].mid(12, subsections[j].length() - 12);
            }
            else if (subsections[j].contains("SUPERTYPE OF"))
            {
                supertypes = subsections[j].mid(12, subsections[j].length() - 12);
                //subtypes = subsections[j].mid(11,subsections[j].length()-11) ;
            }
            else if (subsections[j].contains("ABSTRACT SUPERTYPE"))
            {
                //TODO
            }
            else //предпоожим сто это аттрибут
            {
                int indexof = subsections[j].indexOf(':');
                if (indexof >1)
                {
                    //парсим название и тип даных аттрибута
                    QString str1 = subsections[j].mid(0, indexof).trimmed();
                    QString  str2 = subsections[j].mid(indexof+1, subsections[j].length()-indexof-1).trimmed();

                    if (str1.startsWith("OPTIONAL"))
                    {
                        str1 = str1.replace("OPTIONAL", "").trimmed();
                    }
                    
                    AttributeDefinition at(str1, str2);
                    attributeList.append(at);
                }
            }

            //заполнят типы и подтипы
            subtypesList.clear();
            supertypesList.clear();

            if (subtypes.length() > 1)
            {
                subtypes = subtypes.replace("\r\n", "");
                subtypes = subtypes.replace("ONEOF", "");
                subtypes = subtypes.replace("ANDOR", "");
                subtypes = subtypes.replace("AND", "");
                subtypes = subtypes.replace("OR", "");

                //QList<QString> parts = subtypes.split(new Char[] { ',', '(', ')' }).ToList();
                //QList<QString> parts = subtypes.split(',');
                QList<QString> parts = subtypes.split(QRegExp("[,()]"), QString::SkipEmptyParts);
                for (int k = parts.length() - 1; k >=0 ; k--)
                {
                    parts[k] = parts[k].trimmed();
                    if (parts[k].length() < 1) parts.removeAt(k);
                    qDebug() << "subtype " << parts[k];
                }

                subtypesList=parts;
            }

            if (supertypes.length() > 1)
            {
                supertypes = supertypes.replace("\r\n", "");
                supertypes = supertypes.replace("ONEOF", "");
                supertypes = supertypes.replace("ANDOR", "");
                supertypes = supertypes.replace("AND", "");
                supertypes = supertypes.replace("OR", "");

                //QList<QString> parts = supertypes.Split(new Char[] { ',', '(', ')' }).ToList();
                //QList<QString> parts = subtypes.split(',');
                QList<QString> parts = supertypes.split(QRegExp("[,()]"), QString::SkipEmptyParts);
                for (int k = parts.length() - 1; k >= 0; k--)
                {
                    parts[k] = parts[k].trimmed();
                    if (parts[k].isNull() || parts[k].isEmpty()) parts.removeAt(k);
                    qDebug() << "supertite " << parts[k];
                }

                supertypesList.append(parts);
            }
        }

        EntityDefinition e1;
        e1.name = name;
        e1.attributeDefinitions = attributeList;
        e1.subtypes = subtypesList;
        e1.supertypes = supertypesList;

        entityDefinitionList->insert(name, e1);
    }

    delete entries;


    //перебирвем пары ключ - занчение
    for (auto it = entityDefinitionList->begin(); it != entityDefinitionList->end(); ++it)
    {
        //получаем ссылку на знчениие
        EntityDefinition &definition = it.value();
        QList<QString> parents = definition.supertypes;
        if (parents.length() == 0) //nothing to inherit
        {
            definition.attributeDefinitionsFullTree = definition.attributeDefinitions;
        }
        else  //traverse tree
        {
            QList<QString> allParents = GetAllParents(definition.name);
            definition.attributeDefinitionsFullTree.clear();
            for (int j = allParents.length() - 1; j >= 0; j--)
            {
                EntityDefinition e1 = GetEntityByName(allParents[j]);
                if (e1.name  != "")
                {
                    definition.attributeDefinitionsFullTree.append(e1.attributeDefinitions); //parents' attibutes
                }
            }
            definition.attributeDefinitionsFullTree.append(definition.attributeDefinitions); //this entity's attibutes
        }

        //получаем ключ
//        //мене\ям элмкент item на отрдактированный элмент defifnition
//        entityDefinitionList->insert(key, definition);
    }
}
//------------------------------------------------------------------------------
//формируем список аргметнов строки
//------------------------------------------------------------------------------
QList<QVariant> ExpressSchema::StringToListRec(QString data)
{
    data = data.trimmed();
    QString buffer = "";
    int bufferLength = 0;
    int startidx = 0;
    QList<QVariant> DL;
    int index = 0;
    bool escaping=false;

    //определяем число аргуметнов в скобках
    int count1 = data.split('(').length() - 1;
    int count2 = data.split(')').length() - 1;
    int count3 = data.split(',').length() - 1;

    if (count1 == 1 && count2 == 1 && count3 == 0)
    {
        buffer = "";
        int start = data.indexOf('(');
        int end = data.indexOf(')');
        if (start < end)
        {
            buffer = data.mid(start+1, end - start -1).trimmed();
        }

        //qDebug() << "tagett " <<  buffer;
        DL.append(QVariant(buffer));
        return DL;
    }

    while (index < data.length())
    {
        if (data[index] == '\'')
        {
            if (escaping == false) escaping = true;
            else {
                escaping = false;
            }
        }        
        if (data[index] == '(')
        {
            if (escaping) break;

            int level = 0;
            startidx = index + 1;
            while ((data[index] != ')' || level != 0) && index < data.length() - 1)
            {
                if (data[index] == '(') level++;
                if (data[index + 1] == ')') level--;
                index++;
            }

            buffer = data.mid(startidx, index - startidx);
            startidx = index + 1;
            if (!buffer.contains('(') && !buffer.contains(','))
            {
                qDebug() << "tagett " <<  buffer.trimmed();
                DL.append(QVariant(buffer.trimmed()));
            }
            else
            {
                QList<QVariant> tmp = StringToListRec(buffer);
                foreach (const QVariant &ss, tmp) {
                    if (ss.canConvert<QString>())
                        qDebug() << "slist " << ss.toString();
                }
                DL.append(QVariant(tmp));
            }

            buffer = "";
            bufferLength = 0;
        }
        else if (data[index] == ')')
        {
            if (escaping) break;
            startidx = index + 1;
            bufferLength = 0;
        }
        else if (data[index] == ',')
        {
            if (escaping) break;
            if (bufferLength > 0)
            {
                buffer = data.mid(startidx, bufferLength);
                qDebug() << "tagett " <<  buffer;
                DL.append(QVariant(buffer));
            }
            startidx = index + 1;
            buffer = "";
            bufferLength = 0;
        }
        else
        {
            bufferLength++;
        }

        if (index == data.length() - 1 && bufferLength > 0)
            //if (bufferLength > 1)
        {
            //int testlen = data.length();
            if (startidx + bufferLength > data.length()) bufferLength = data.length() - startidx - 1;
            if (bufferLength > 0)
            {
                buffer = data.mid(startidx, bufferLength);
                DL.append(QVariant(buffer));
            }
        }

        index++;
    }


    return DL;
}
//------------------------------------------------------------------------------
//получм дочерние элменты
//------------------------------------------------------------------------------
QList<QString> ExpressSchema::GetAllChildren(QString name)
{
    name = name.toLower();

    QStringList subTypeList;

    foreach (EntityDefinition item, entityDefinitionList->values())
    {
        if (item.supertypes.contains(name))
        {
            subTypeList.append(item.name);
        }
    }

    subTypeList.append(GetEntityByName(name).subtypes);
    subTypeList.removeDuplicates();

    QStringList allChildren(subTypeList);

    for (int i = 0; i < subTypeList.length(); i++)
    {
        QList<QString> subTypeList2 = GetAllChildren(subTypeList[i]);
        allChildren.append(subTypeList2);
    }

    //удалеям дубликаты
    subTypeList.removeDuplicates();
    QList<QString> unique = subTypeList;
    return unique;
}
//------------------------------------------------------------------------------
//получаем родитедсике элменты
//------------------------------------------------------------------------------
QList<QString> ExpressSchema::GetAllParents(QString name)
{
    EntityDefinition entity = GetEntityByName(name);
    if (entity.attributeDefinitions.isEmpty()) return QList<QString>();

    QStringList superTypeList = entity.supertypes;
    QStringList allParents;
    for (int i = 0; i < superTypeList.length(); i++)
    {
        QList<QString> superTypeList2 = GetAllParents(superTypeList[i]);
        allParents.append(superTypeList2);
    }

    allParents.removeDuplicates();
    QList<QString> unique = allParents;
    return unique;
}
//-----------------------------------------------------------------------------
QVariant ExpressSchema::StringToMappedType(QVariant attributeValue, QString attributeType, ExpressSchema *AP203)
{
    attributeType=attributeType.toUpper();
    if (attributeValue.canConvert<QString>())
    {
        //парисм номер обьектка
        QString s = attributeValue.value<QString>().trimmed();
        if (s.startsWith("#"))
        {
            s = s.mid(1, s.length() - 1);
            bool conv = false;
            int result = s.toInt(&conv);
            if (conv) {
                return QVariant(RefID(result));
            }
            else {
                qDebug() << "pasre  error";
                return QVariant();
            }
        }
        else if (attributeType == "LABEL")
        {
            s = s.replace("\"", "");
            s = s.replace("\'", "");
            return QVariant(s);
        }
        else if (AP203->typeAliasesReal->contains(attributeType) || (attributeType == "REAL"))
        {
            double result;
            bool conv = false;
            result = attributeValue.toDouble(&conv);

            if (conv) {
                return QVariant(RefID(result));
            }
            else {
                qDebug() << "aprse ERROR";
            }
        }
        else if (AP203->typeAliasesInt->contains(attributeType) || (attributeType == "INTEGER"))
        {
            int result;
            bool conv = false;
            result = attributeValue.toDouble(&conv);

            if (&conv) {
                return QVariant(RefID(result));
            }
            else {
                qDebug() << "aprse ERROR";
            }
        }
        else if ((attributeType == "BOOLEAN") || (attributeType == "LOGICAL"))
        {
            if (s.contains('T')) return QVariant(false);
            if (s.contains('F')) return QVariant(false);
            return QVariant();
        }
        else
        {
            return QVariant(s);
        }
    }

    if (attributeValue.canConvert<QVariantList>())
    {
        if (attributeType.startsWith("LIST") || attributeType.startsWith("SET") )
        {
            QList<QVariant> attributeList = attributeValue.value<QVariantList>();
            QList<QVariant> newList;
            int idx = attributeType.indexOf("OF");
            QString type = attributeType.mid(idx + 2, attributeType.length() - idx - 2).trimmed().toLower();
            for (int i = 0; i < attributeList.length(); i++)
            {
                newList.append(StringToMappedType(attributeList[i], type, AP203));
            }
            return newList;
        }
    }
    return QString("");
}
//-----------------------------------------------------------------------------
//почаем entyty по имени
//------------------------------------------------------------------------------
EntityDefinition ExpressSchema::GetEntityByName(QString name)
{
    name = name.toLower();
    //сделать провеку исключеия
    return entityDefinitionList->value(name, EntityDefinition());
}
//-----------------------------------------------------------------------------
Entity::Entity(int id, QString type, QString attributeString, ExpressSchema *AP203)
{
    this->entityID = id;
    this->type = type;
    this->isComplex = false;

    EntityDefinition ed = AP203->GetEntityByName(type);
    QList<QVariant> attributes = AP203->StringToListRec(attributeString);

    if  (attributes.length() != ed.attributeDefinitionsFullTree.length())
    {
        qDebug() << "parsing error on entity #" <<  id;
        this->status=-1;
        return;
    }

    for (int i = 0; i < attributes.length(); i++)
    {
        QVariant a = AP203->StringToMappedType(attributes[i], ed.attributeDefinitionsFullTree[i].type, AP203);
        attributesConverted.append(a);
    }
}
//-----------------------------------------------------------------------------
Entity::Entity()
{
    this->entityID = 0;
    this->type = type;
    this->isComplex = false;
    attributesConverted.clear();
}
//-----------------------------------------------------------------------------
Entity::~Entity()
{
    //delete attributesConverted;
}
//-----------------------------------------------------------------------------
EntityComplex::EntityComplex(int id, QList<QString> types, QList<QString> attributeStrings, ExpressSchema *AP203)
{
    this->entityID = id;
    this->types = types;
    this->isComplex = true;
    this->type = "COMPLEX";

    attributeValues.clear();
    attributeDefinitions.clear();
    attributesConverted.clear();

    for (int i = 0; i < types.length(); i++)
    {
        EntityDefinition ed = AP203->GetEntityByName(types[i]);
        attributeDefinitions.append(ed.attributeDefinitions);

        QList<QVariant> values = AP203->StringToListRec(attributeStrings[i]);
        QVariant value = values.at(0);
        if (value.canConvert<QVariantList>())
        {
            attributeValues.append(value);
        }
        else if (value.canConvert<QString>())
        {
            QString str = value.toString();
            if (!str.isNull() && !str.isEmpty()) {
                attributeValues.append(value);
            }
        }
    }

    if (attributeValues.length() != attributeDefinitions.length())
    {
        //TODO
    }

    for (int i = 0; i < attributeDefinitions.length(); i++)
    {
        QVariant a = AP203->StringToMappedType(attributeValues[i], attributeDefinitions[i].type, AP203);
        attributesConverted.append(a);
    }

}
//-----------------------------------------------------------------------------
AttributeDefinition::AttributeDefinition(QString name, QString dataType)
{
    this->name = name;
    this->type = dataType;
}
//-----------------------------------------------------------------------------
Attribute::Attribute(AttributeDefinition attributeDefinition, QVariant value)
{
    this->value = value;
    this->name = attributeDefinition.name;
    this->type = attributeDefinition.type;
}

