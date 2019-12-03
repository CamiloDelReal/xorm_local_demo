#include <QDateTime>

#include "datetimeconverter.hpp"


QVariant DateTimeConverter::to(const QVariant &data)
{
    QDateTime timestamp = data.value<QDateTime>();
    return QVariant(timestamp.toString(TIMESTAMP_FORMAT));
}

QVariant DateTimeConverter::from(const QVariant &data)
{
    QDateTime timestamp = QDateTime::fromString(data.value<QString>(), TIMESTAMP_FORMAT);
    return QVariant(timestamp);
}
