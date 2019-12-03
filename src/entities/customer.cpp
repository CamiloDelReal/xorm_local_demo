#include "customer.hpp"

Customer::Customer(QObject *parent)
    : QObject(parent), XTableModel<Customer>()
{
    m_uid = 0;
    m_account = nullptr;
    m_category = NONE;
}

Customer::Customer(const QString &name, const QString &lastName, const QString &email,
                   const Customer::Category &category, const bool vip, QObject *parent)
    : QObject(parent), XTableModel<Customer>()
{
    m_uid = 0;
    m_name = name;
    m_lastName = lastName;
    m_email = email;
    m_category = category;
    m_vip = vip;
    m_account = nullptr;
}

Customer::Customer(const quint64 &uid, const QString &name, const QString &lastName, const QString &email,
                   const Customer::Category &category, const bool vip, QObject *parent)
    : QObject(parent), XTableModel<Customer>()
{
    m_uid = uid;
    m_name = name;
    m_lastName = lastName;
    m_email = email;
    m_category = category;
    m_vip = vip;
    m_account = nullptr;
}

Customer::Customer(const Customer &other)
    : QObject(other.parent()), XTableModel<Customer>()
{
    m_uid = other.m_uid;
    m_name = other.m_name;
    m_lastName = other.m_lastName;
    m_email = other.m_email;
    m_category = other.m_category;
    m_vip = other.m_vip;
    m_account = other.m_account;
    m_invoices.append(other.m_invoices);
}

Customer::~Customer()
{
    clearAccount();
    clearInvoices();
}

Customer& Customer::operator=(const Customer &other)
{
    m_uid = other.m_uid;
    m_name = other.m_name;
    m_lastName = other.m_lastName;
    m_email = other.m_email;
    m_category = other.m_category;
    m_vip = other.m_vip;
    clearAccount();
    m_account = other.m_account;
    clearInvoices();
    m_invoices.append(other.m_invoices);

    setParent(other.parent());

    return *this;
}

quint64 Customer::uid() const
{
    return m_uid;
}

QString Customer::name() const
{
    return m_name;
}

QString Customer::lastName() const
{
    return m_lastName;
}

QString Customer::email() const
{
    return m_email;
}

Customer::Category Customer::category() const
{
    return m_category;
}

bool Customer::vip() const
{
    return m_vip;
}

Account* Customer::account() const
{
    return m_account;
}

QList<Invoice *> Customer::invoices() const
{
    return m_invoices;
}

void Customer::setUid(const quint64 &uid)
{
    if (m_uid != uid)
    {
        m_uid = uid;
        emit uidChanged(m_uid);
        setAccount(nullptr);
    }
}

void Customer::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Customer::setLastName(const QString &lastName)
{
    if (m_lastName != lastName)
    {
        m_lastName = lastName;
        emit lastNameChanged(m_lastName);
    }
}

void Customer::setEmail(const QString &email)
{
    if (m_email != email)
    {
        m_email = email;
        emit emailChanged(m_email);
    }
}

void Customer::setCategory(const Customer::Category &category)
{
    if (m_category != category)
    {
        m_category = category;
        emit categoryChanged(m_category);
    }
}

void Customer::setVip(const bool &vip)
{
    if (m_vip != vip)
    {
        m_vip = vip;
        emit vipChanged(m_vip);
    }
}

void Customer::setAccount(Account *account)
{
    if (m_account != account)
    {
        clearAccount();
        m_account = account;
        emit accountChanged(m_account);
    }
}

void Customer::setInvoices(const QList<Invoice *> &invoices)
{
    if (m_invoices != invoices)
    {
        clearInvoices();
        m_invoices = invoices;
        emit invoicesChanged(m_invoices);
    }
}

void Customer::clearAccount()
{
    if(m_account != nullptr)
    {
        m_account->deleteLater();
        m_account = nullptr;
    }
}

void Customer::clearInvoices()
{
    if(!m_invoices.isEmpty())
    {
        foreach (Invoice* invoice, m_invoices)
        {
            if (invoice != nullptr)
            {
                invoice->deleteLater();
                invoice = nullptr;
            }
        }
        m_invoices.clear();
    }
}
