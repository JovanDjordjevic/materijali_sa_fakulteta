#include "student.h"
#include "courseitem.h"

#include <qalgorithms.h>

Student::Student()
    : m_name(""), m_surname(""), m_index(""), m_personalNumber("")
    , m_enrolled(false), m_courseItems()
{

}

Student::~Student()
{
    //posto student ima vektor pokazivaca na CourseItems, on je duzan i da ihs ve dealocira
    //mozemo standarno da prodjemo kroz sve i da rucno pozivamo delete, a mozemo i ovako, iz QAlgorithm da
    //uzmemo funckciju koja prima kolekciju (ili iteratore na interval kolekcije) i za nas poziva delete
    qDeleteAll(m_courseItems);
}

QVariant Student::toVariant() const
{
    QVariantMap map;
    //ove trivijalne podatke mozemo u mapu isto kao sto smo imali u course item klasi
    map.insert("name", m_name);
    map.insert("surname", m_surname);
    map.insert("index", m_index);
    map.insert("pno", m_personalNumber);
    map.insert("endrolled", m_enrolled);

    //ali pokazivace na course items moramo drugacije
    if(m_enrolled){
        QVariantList courseItemList;    //ovo je typedef za QList<QVariant>

        for(const CourseItem* course : m_courseItems){
            QVariant v = course->toVariant();
            courseItemList.push_back(v);
        }

        map.insert("courseItems", courseItemList);
    }

    return map;
}

void Student::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    m_name = map.value("name").toString();
    m_surname = map.value("surname").toString();
    m_index = map.value("index").toString();
    m_personalNumber = map.value("pno").toString();
    m_enrolled = map.value("enrolled").toBool();

    if(m_enrolled){
        //za slucaj da istog studenta 2 puta dobijamo iz nekog fromVariant() poziva, desice se da ce se nove vrednosti kurseva
        //samo appendovati an vec postojeci vektor, tj ako je bilo A B C bice A B C A B C, zato je ptorebno na ovom mestu nekako da ocistimo
        //sadrzaj ovog vektora. I to moramo obavezno i da obrisemo podatke iz memorije (ako samo uradimo clear, oni se nece obirsati iz memorije)
        qDeleteAll(m_courseItems);
        m_courseItems.clear();

        QVariantList courseItemList = map.value("courseItems").toList();
        for(const QVariant &course : courseItemList){
           CourseItem*  courseItem = new CourseItem();
           courseItem->fromVariant(course);
           m_courseItems.push_back(courseItem);
        }
    }
}
