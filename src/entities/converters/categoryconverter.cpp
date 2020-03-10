#include "categoryconverter.hpp"
#include "customer.hpp"


QVariant CategoryConverter::to(const QVariant &data)
{
    qint32 value = static_cast<qint32>(data.value<Customer::Category>());
    return QVariant(value);
}

QVariant CategoryConverter::from(const QVariant &data)
{
    Customer::Category value = static_cast<Customer::Category>(data.value<qint32>());
    return QVariant(value);
}
