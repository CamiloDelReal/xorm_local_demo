#include "product.hpp"

Product::Product(QObject *parent)
    : QObject(parent), XTableModel<Product>()
{
    m_uid = 0;
    m_price = 0.0f;
}

Product::Product(const QString &name, const float &price, QObject *parent)
    : QObject(parent), XTableModel<Product>()
{
    m_uid = 0;
    m_name = name;
    m_price = price;
}

Product::Product(const quint64 &uid, const QString &name, const float &price, QObject *parent)
    : QObject(parent), XTableModel<Product>()
{
    m_uid = uid;
    m_name = name;
    m_price = price;
}

Product::Product(const Product &other)
    : QObject(other.parent()), XTableModel<Product>()
{
    m_uid = other.m_uid;
    m_name = other.m_name;
    m_price = other.m_price;
}

Product::~Product()
{
}

Product& Product::operator=(const Product &other)
{
    m_uid = other.m_uid;
    m_name = other.m_name;
    m_price = other.m_price;

    setParent(other.parent());

    return *this;
}

quint64 Product::uid() const
{
    return m_uid;
}

QString Product::name() const
{
    return m_name;
}

float Product::price() const
{
    return m_price;
}

void Product::setUid(const quint64 &uid)
{
    if (m_uid != uid)
    {
        m_uid = uid;
        emit uidChanged(m_uid);
    }
}

void Product::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Product::setPrice(const float &price)
{
    if (!qFuzzyCompare(m_price, price))
    {
        m_price = price;
        emit priceChanged(m_price);
    }
}
