#ifndef INVOICE_HPP
#define INVOICE_HPP

#include <QObject>
#include <QDateTime>

#include "xtablemodel.hpp"
#include "datetimeconverter.hpp"

class Customer;
class Product;
class InvoiceProduct;

class Invoice : public QObject, public XTableModel<Invoice>
{
    Q_OBJECT

    Q_PROPERTY(quint64 uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(quint64 customerId READ customerId WRITE setCustomerId NOTIFY customerIdChanged)
    Q_PROPERTY(QDateTime timestamp READ timestamp WRITE setTimestamp NOTIFY timestampChanged)

    Q_PROPERTY(Customer* customer READ customer WRITE setCustomer NOTIFY customerChanged)
    Q_PROPERTY(QList<Product*> products READ products WRITE setProducts NOTIFY productsChanged)

    X_TABLE_NAME("invoices")
    X_TABLE_FIELDS(X_FIELD(uid, X_PRIMARY_KEY),
                   X_FIELD(customerId, "customer_id", X_FOREIGN_KEY(Customer)),
                   X_FIELD(timestamp, QMetaType::QString, X_DATA_CONVERTER(DateTimeConverter)))

    X_FOREIGN_OBJECTS(X_FOREIGN_OBJECT(Customer, uid, customerId, customer))
    X_FOREIGN_LISTS(X_INTERMEDIATED_FOREIGN_LIST(Product, uid, Invoice, uid, InvoiceProduct, productId, invoiceId, products))

public:
    explicit Invoice(QObject *parent = nullptr);
    Invoice(const quint64 &customerId, const QDateTime &timestamp, QObject* parent = nullptr);
    Invoice(const quint64 &uid, const quint64 &customerId, const QDateTime &timestamp, QObject* parent = nullptr);
    Invoice(const Invoice &other);

    ~Invoice();

    Invoice& operator=(const Invoice &other);

    quint64 uid() const;
    quint64 customerId() const;
    QDateTime timestamp() const;

    Customer* customer() const;
    QList<Product*> products() const;

public slots:
    void setUid(const quint64 &uid);
    void setCustomerId(const quint64 &customerId);
    void setTimestamp(const QDateTime &timestamp);

    void setCustomer(Customer* customer);
    void setProducts(const QList<Product*> &products);

signals:
    void uidChanged(const quint64 &uid);
    void customerIdChanged(const quint64 &customerId);
    void timestampChanged(const QDateTime &timestamp);

    void customerChanged(Customer* customer);
    void productsChanged(const QList<Product*> &products);

private:
    quint64 m_uid;
    quint64 m_customerId;
    QDateTime m_timestamp;

    Customer* m_customer;
    QList<Product*> m_products;

    void clearCustomer();
    void clearProducts();
};


#include "customer.hpp"
#include "product.hpp"
#include "invoiceproduct.hpp"

#endif // INVOICE_HPP
