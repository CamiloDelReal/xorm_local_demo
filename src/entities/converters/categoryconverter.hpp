#ifndef CATEGORYCONVERTER_HPP
#define CATEGORYCONVERTER_HPP

#include <QObject>

#include "xfield.hpp"


class CategoryConverter : public XDataConverter
{
public:

    QVariant to(const QVariant &data);

    QVariant from(const QVariant &data);

};
Q_DECLARE_METATYPE(CategoryConverter*)

#endif // CATEGORYCONVERTER_HPP
