#ifndef INVOICEPRODUCT_HPP
#define INVOICEPRODUCT_HPP

#include <QObject>

#include "xtablemodel.hpp"


class Invoice;
class Product;

class InvoiceProduct : public QObject, public XTableModel<InvoiceProduct>
{
    Q_OBJECT

    Q_PROPERTY(quint64 uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(quint64 invoiceId READ invoiceId WRITE setInvoiceId NOTIFY invoiceIdChanged)
    Q_PROPERTY(quint64 productId READ productId WRITE setProductId NOTIFY productIdChanged)

    Q_PROPERTY(Invoice* invoice READ invoice WRITE setInvoice NOTIFY invoiceChanged)
    Q_PROPERTY(Product* product READ product WRITE setProduct NOTIFY productChanged)

    X_TABLE_NAME("invoices_products")
    X_TABLE_FIELDS(X_FIELD(uid, X_PRIMARY_KEY),
                   X_FIELD(invoiceId, "invoice_id", X_FOREIGN_KEY(Invoice)),
                   X_FIELD(productId, "product_id", X_FOREIGN_KEY(Product)))

    X_FOREIGN_OBJECTS(X_FOREIGN_OBJECT(Invoice, uid, invoiceId, invoice),
                      X_FOREIGN_OBJECT(Product, uid, productId, product))

public:
    explicit InvoiceProduct(QObject *parent = nullptr);
    InvoiceProduct(const quint64 &invoiceId, const quint64 &productId, QObject* parent = nullptr);
    InvoiceProduct(const quint64 &uid, const quint64 &invoiceId, const quint64 &productId, QObject* parent = nullptr);
    InvoiceProduct(const InvoiceProduct &other);

    ~InvoiceProduct();

    InvoiceProduct& operator=(const InvoiceProduct &other);

    quint64 uid() const;
    quint64 invoiceId() const;
    quint64 productId() const;

    Invoice* invoice() const;
    Product* product() const;

public slots:
    void setUid(const quint64 &uid);
    void setInvoiceId(const quint64 &invoiceId);
    void setProductId(const quint64 &productId);

    void setInvoice(Invoice* invoice);
    void setProduct(Product* product);

signals:
    void uidChanged(const quint64 &uid);
    void invoiceIdChanged(const quint64 &invoiceId);
    void productIdChanged(const quint64 &productId);

    void invoiceChanged(Invoice* invoice);
    void productChanged(Product* product);

private:
    quint64 m_uid;
    quint64 m_invoiceId;
    quint64 m_productId;

    Invoice* m_invoice;
    Product* m_product;

    void clearInvoice();
    void clearProduct();
};


#include "invoice.hpp"
#include "product.hpp"

#endif // INVOICEPRODUCT_HPP
