#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <QObject>

#include "xtablemodel.hpp"


class Customer;

class Account : public QObject, public XTableModel<Account>
{
    Q_OBJECT

    Q_PROPERTY(quint64 uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(QString cardNumber READ cardNumber WRITE setCardNumber NOTIFY cardNumberChanged)
    Q_PROPERTY(quint64 customerId READ customerId WRITE setCustomerId NOTIFY customerIdChanged)

    Q_PROPERTY(Customer* customer READ customer WRITE setCustomer NOTIFY customerChanged)

    X_TABLE_NAME("accounts")
    X_TABLE_FIELDS(X_FIELD(uid, X_PRIMARY_KEY),
                   X_FIELD(cardNumber, "card_number", X_NOT_NULL),
                   X_FIELD(customerId, "customer_id", X_FOREIGN_KEY(Customer)))

    X_FOREIGN_OBJECTS(X_FOREIGN_OBJECT(Customer, uid, customerId, customer))

public:
    explicit Account(QObject *parent = nullptr);
    Account(const QString &cardNumber, const quint64 &customerId, QObject* parent = nullptr);
    Account(const quint64 &uid, const QString &cardNumber, const quint64 &customerId, QObject* parent = nullptr);
    Account(const Account &other);

    ~Account();

    Account& operator=(const Account &other);

    quint64 uid() const;
    QString cardNumber() const;
    quint64 customerId() const;

    Customer* customer() const;

public slots:
    void setUid(const quint64 &uid);
    void setCardNumber(const QString &cardNumber);
    void setCustomerId(const quint64 &customerId);

    void setCustomer(Customer* customer);

signals:
    void uidChanged(const quint64 &uid);
    void cardNumberChanged(const QString &cardNumber);
    void customerIdChanged(const quint64 &customerId);

    void customerChanged(Customer* customer);

private:
    quint64 m_uid;
    QString m_cardNumber;
    quint64 m_customerId;
    Customer* m_customer;

    void clearCustomer();
};


#include "customer.hpp"

#endif // ACCOUNT_HPP
