#ifndef DATETIMECONVERTER_HPP
#define DATETIMECONVERTER_HPP

#include <QObject>

#include "xfield.hpp"


static const QString TIMESTAMP_FORMAT = QStringLiteral("yyyy/MM/dd hh:mm:ss.zzz");

class DateTimeConverter : public XDataConverter
{
public:

    QVariant to(const QVariant &data) override;

    QVariant from(const QVariant &data) override;

};
Q_DECLARE_METATYPE(DateTimeConverter*)

#endif // DATETIMECONVERTER_HPP
