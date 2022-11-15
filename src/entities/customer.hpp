#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <QObject>

#include "xtablemodel.hpp"
#include "categoryconverter.hpp"


class Account;
class Invoice;

class Customer : public QObject, public XTableModel<Customer>
{
    Q_OBJECT

    Q_PROPERTY(quint64 uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(Category category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(bool vip READ vip WRITE setVip NOTIFY vipChanged)

    Q_PROPERTY(Account* account READ account WRITE setAccount NOTIFY accountChanged)
    Q_PROPERTY(QList<Invoice*> invoices READ invoices WRITE setInvoices NOTIFY invoicesChanged)

    X_TABLE_NAME("customers")
    X_TABLE_FIELDS(X_FIELD(uid, X_PRIMARY_KEY),
                   X_FIELD(name, X_NOT_NULL),
                   X_FIELD(lastName, "last_name", X_NOT_NULL),
                   X_FIELD(email, X_NOT_NULL | X_UNIQUE),
                   X_FIELD(category, QMetaType::Int, X_DATA_CONVERTER(CategoryConverter)),
                   X_FIELD(vip))

    X_FOREIGN_OBJECTS(X_FOREIGN_OBJECT(Account, customerId, uid, account))
    X_FOREIGN_LISTS(X_FOREIGN_LIST(Invoice, customerId, uid, invoices))

public:
    enum Category
    {
        NONE = 0,
        SECONDARY,
        PRIMARY
    };
    Q_ENUM(Category)

    explicit Customer(QObject *parent = nullptr);
    Customer(const QString &name, const QString &lastName, const QString &email, const Category &category,
             const bool vip, QObject* parent = nullptr);
    Customer(const quint64 &uid, const QString &name, const QString &lastName, const QString &email,
             const Category &category, const bool vip, QObject* parent = nullptr);
    Customer(const Customer &other);

    ~Customer();

    Customer& operator=(const Customer &other);

    quint64 uid() const;
    QString name() const;
    QString lastName() const;
    QString email() const;
    Category category() const;
    bool vip() const;

    Account* account() const;
    QList<Invoice*> invoices() const;

public slots:
    void setUid(const quint64 &uid);
    void setName(const QString &name);
    void setLastName(const QString &lastName);
    void setEmail(const QString &email);
    void setCategory(const Category &category);
    void setVip(const bool &vip);

    void setAccount(Account* account);
    void setInvoices(const QList<Invoice*> &invoices);

signals:
    void uidChanged(const quint64 &uid);
    void nameChanged(const QString &name);
    void lastNameChanged(const QString &lastName);
    void emailChanged(const QString &email);
    void categoryChanged(const Category &category);
    void vipChanged(const bool &vip);

    void accountChanged(Account* account);
    void invoicesChanged(const QList<Invoice*> &invoices);

private:
    quint64 m_uid;
    QString m_name;
    QString m_lastName;
    QString m_email;
    Category m_category;
    bool m_vip;

    Account* m_account;
    QList<Invoice*> m_invoices;

    void clearAccount();
    void clearInvoices();
};
Q_DECLARE_METATYPE(Customer::Category)


#include "account.hpp"
#include "invoice.hpp"

#endif // CUSTOMER_HPP
