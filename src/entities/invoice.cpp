#include "invoice.hpp"

Invoice::Invoice(QObject *parent)
    : QObject(parent), XTableModel<Invoice>()
{
    m_uid = 0;
    m_customer = nullptr;
}

Invoice::Invoice(const quint64 &customerId, const QDateTime &timestamp, QObject *parent)
    : QObject(parent), XTableModel<Invoice>()
{
    m_uid = 0;
    m_customerId = customerId;
    m_timestamp = timestamp;
    m_customer = nullptr;
}

Invoice::Invoice(const quint64 &uid, const quint64 &customerId, const QDateTime &timestamp, QObject *parent)
    : QObject(parent), XTableModel<Invoice>()
{
    m_uid = uid;
    m_customerId = customerId;
    m_timestamp = timestamp;
    m_customer = nullptr;
}

Invoice::Invoice(const Invoice &other)
    : QObject(other.parent()), XTableModel<Invoice>()
{
    m_uid = other.m_uid;
    m_customerId = other.m_customerId;
    m_timestamp = other.m_timestamp;
    m_customer = other.m_customer;
    m_products.append(other.m_products);
}

Invoice::~Invoice()
{
    clearCustomer();
    clearProducts();
}

Invoice& Invoice::operator=(const Invoice &other)
{
    m_uid = other.m_uid;
    m_customerId = other.m_customerId;
    m_timestamp = other.m_timestamp;
    clearCustomer();
    clearProducts();
    m_customer = other.m_customer;
    m_products.append(other.m_products);

    setParent(other.parent());

    return *this;
}

quint64 Invoice::uid() const
{
    return m_uid;
}

QDateTime Invoice::timestamp() const
{
    return m_timestamp;
}

quint64 Invoice::customerId() const
{
    return m_customerId;
}

Customer *Invoice::customer() const
{
    return m_customer;
}

QList<Product *> Invoice::products() const
{
    return m_products;
}

void Invoice::setUid(const quint64 &uid)
{
    if (m_uid != uid)
    {
        m_uid = uid;
        emit uidChanged(m_uid);
        setProducts(QList<Product*>());
    }
}

void Invoice::setTimestamp(const QDateTime &timestamp)
{
    if (m_timestamp != timestamp)
    {
        m_timestamp = timestamp;
        emit timestampChanged(m_timestamp);
    }
}

void Invoice::setCustomerId(const quint64 &customerId)
{
    if (m_customerId != customerId)
    {
        m_customerId = customerId;
        emit customerIdChanged(m_customerId);
        setCustomer(nullptr);
    }
}

void Invoice::setCustomer(Customer *customer)
{
    if (m_customer != customer)
    {
        m_customer = customer;
        emit customerChanged(m_customer);
    }
}

void Invoice::setProducts(const QList<Product*> &products)
{
    m_products = products;
    emit productsChanged(m_products);
}

void Invoice::clearCustomer()
{
    if(m_customer != nullptr)
    {
        m_customer->deleteLater();
        m_customer = nullptr;
    }
}

void Invoice::clearProducts()
{
    if(!m_products.isEmpty())
    {
        foreach (Product* product, m_products)
        {
            if(product !=nullptr)
            {
                product->deleteLater();
                product = nullptr;
            }
        }
        m_products.clear();
    }
}
