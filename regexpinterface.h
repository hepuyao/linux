#ifndef REGEXPINTERFACE_H
#define REGEXPINTERFACE_H


#include <QString>
#include <iostream>
using namespace std;
#define RegExpInterface_iid "hepuyao"
class RegExpInterface
{
public:
    virtual ~RegExpInterface(){}
    virtual QString  add_num(const QString &num)=0;

};
Q_DECLARE_INTERFACE (RegExpInterface, RegExpInterface_iid);
#endif // REGEXPINTERFACE_H
