#ifndef EXPRESSSCHEMA_H
#define EXPRESSSCHEMA_H

#include "QObject"
#include "QString"
#include "regex"
#include <QStringList>
#include <QVariant>

//индетчификатор графического прримитива
typedef  int RefID;

//описание аттрибута (переменной)
class AttributeDefinition
{
public :
    QString name; //назание ерменной
    QString type; //тип данных
    int id; //?

    AttributeDefinition(QString name, QString dataType);
    AttributeDefinition();
};

class Attribute
{
public :
    QString name;
    QString type;
    QVariant value;
    Attribute(AttributeDefinition attributeDefinition, QVariant value);
};

/*
   Класс инкапсулирует описаниие ENtity
*/
class EntityDefinition
{
public :
    QString name;
    QList<AttributeDefinition> attributeDefinitions;
    QList<AttributeDefinition> attributeDefinitionsFullTree;
    QList<QString>subtypes;
    QList<QString> supertypes;
};


/*
    Класс инкапсулирующий схему Express Schema , которая содержит правилва по котороым необходимо производить
    синтаксичечкий анализ STEP файла
    Schema храниться в файле с расширением .exp
*/

class ExpressSchema
{
public:

    QString schemaFileName;

    QMap<QString, EntityDefinition> *entityDefinitionList;
    QList<QString> *typeAliasesReal;
    QList<QString> *typeAliasesInt;

    ExpressSchema();
    ExpressSchema(QString filename);
    //ExpressSchema (QStringList filenames);
    ~ExpressSchema();

    void ParseSchema();
    void ParseType();

    QList<QString> GetAllParents(QString name);
    QList<QString> GetAllChildren(QString name);
     QList<QVariant> StringToListRec(QString data);
    QList<int> AllIndexesOf(QString haystack, QString needle);
    QList<int> AllIndexesOf(QString haystack, QList<QString> needles);
    EntityDefinition GetEntityByName(QString name);
    QVariant StringToMappedType(QVariant attributeValue, QString attributeType, ExpressSchema *AP203);

};



/*
    класс инкапсулириующий струкутру параметров Entity
*/
class Entity
{
public :
    int entityID;
    QString type;                           //тип
    QList<QVariant> attributesConverted;   //набор аттрибутов
    int status;
    bool isComplex;

    Entity();
    Entity(int id, QString type, QString attributeString, ExpressSchema *AP203);
    ~Entity();
};
\

/*
    класс инкапсулириующий набор Entity
*/
class EntityComplex: public Entity
{
public :
    QList<QString> types;
    QList<QVariant> attributeValues;
    QList<AttributeDefinition> attributeDefinitions;
    EntityComplex(int id, QList<QString> types, QList<QString> attributeStrings, ExpressSchema *AP203);
};



#endif // EXPRESSSCHEMA_H
