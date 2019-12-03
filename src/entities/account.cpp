#include "account.hpp"

Account::Account(QObject *parent)
    : QObject(parent), XTableModel<Account>()
{
    m_uid = 0;
    m_customer = nullptr;
}

Account::Account(const QString &cardNumber, const quint64 &customerId, QObject *parent)
    : QObject(parent), XTableModel<Account>()
{
    m_uid = 0;
    m_cardNumber = cardNumber;
    m_customerId = customerId;
    m_customer = nullptr;
}

Account::Account(const quint64 &uid, const QString &cardNumber, const quint64 &customerId, QObject *parent)
    : QObject(parent), XTableModel<Account>()
{
    m_uid = uid;
    m_cardNumber = cardNumber;
    m_customerId = customerId;
    m_customer = nullptr;
}

Account::Account(const Account &other)
    : QObject(other.parent()), XTableModel<Account>()
{
    m_uid = other.m_uid;
    m_cardNumber = other.m_cardNumber;
    m_customerId = other.m_customerId;
    m_customer = other.m_customer;
}

Account::~Account()
{
    clearCustomer();
}

Account& Account::operator=(const Account &other)
{
    m_uid = other.m_uid;
    m_cardNumber = other.m_cardNumber;
    m_customerId = other.m_customerId;
    clearCustomer();
    m_customer = other.m_customer;

    setParent(other.parent());

    return *this;
}

quint64 Account::uid() const
{
    return m_uid;
}

QString Account::cardNumber() const
{
    return m_cardNumber;
}

quint64 Account::customerId() const
{
    return m_customerId;
}

Customer* Account::customer() const
{
    return m_customer;
}

void Account::setUid(const quint64 &uid)
{
    if (m_uid != uid)
    {
        m_uid = uid;
        emit uidChanged(m_uid);
    }
}

void Account::setCardNumber(const QString &cardNumber)
{
    if (m_cardNumber != cardNumber)
    {
        m_cardNumber = cardNumber;
        emit cardNumberChanged(m_cardNumber);
    }
}

void Account::setCustomerId(const quint64 &customerId)
{
    if (m_customerId != customerId)
    {
        m_customerId = customerId;
        emit customerIdChanged(m_customerId);
        setCustomer(nullptr);
    }
}

void Account::setCustomer(Customer *customer)
{
    if (m_customer != customer)
    {
        m_customer = customer;
        emit customerChanged(m_customer);
    }
}

void Account::clearCustomer()
{
    if(m_customer != nullptr)
    {
        m_customer->deleteLater();
        m_customer = nullptr;
    }
}
