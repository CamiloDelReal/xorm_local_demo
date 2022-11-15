#include "invoiceproduct.hpp"

InvoiceProduct::InvoiceProduct(QObject *parent)
    : QObject(parent), XTableModel<InvoiceProduct>()
{
    m_uid = 0;
    m_invoiceId = 0;
    m_productId = 0;
    m_invoice = nullptr;
    m_product = nullptr;
}

InvoiceProduct::InvoiceProduct(const quint64 &invoiceId, const quint64 &productId, QObject *parent)
    : QObject(parent), XTableModel<InvoiceProduct>()
{
    m_uid = 0;
    m_invoiceId = invoiceId;
    m_productId = productId;
    m_invoice = nullptr;
    m_product = nullptr;
}

InvoiceProduct::InvoiceProduct(const quint64 &uid, const quint64 &invoiceId, const quint64 &productId, QObject *parent)
    : QObject(parent), XTableModel<InvoiceProduct>()
{
    m_uid = uid;
    m_invoiceId = invoiceId;
    m_productId = productId;
    m_invoice = nullptr;
    m_product = nullptr;
}

InvoiceProduct::InvoiceProduct(const InvoiceProduct &other)
    : QObject(other.parent()), XTableModel<InvoiceProduct>()
{
    m_uid = other.m_uid;
    m_invoiceId = other.m_invoiceId;
    m_productId = other.m_productId;
    m_invoice = other.m_invoice;
    m_product = other.m_product;
}

InvoiceProduct::~InvoiceProduct()
{
    clearInvoice();
    clearProduct();
}

InvoiceProduct& InvoiceProduct::operator=(const InvoiceProduct &other)
{
    m_uid = other.m_uid;
    m_invoiceId = other.m_invoiceId;
    m_productId = other.m_productId;
    clearInvoice();
    clearProduct();
    m_invoice = other.m_invoice;
    m_product = other.m_product;

    setParent(other.parent());

    return *this;
}

quint64 InvoiceProduct::uid() const
{
    return m_uid;
}

quint64 InvoiceProduct::invoiceId() const
{
    return m_invoiceId;
}

quint64 InvoiceProduct::productId() const
{
    return m_productId;
}

Invoice* InvoiceProduct::invoice() const
{
    return m_invoice;
}

Product* InvoiceProduct::product() const
{
    return m_product;
}

void InvoiceProduct::setUid(const quint64 &uid)
{
    if (m_uid != uid)
    {
        m_uid = uid;
        emit uidChanged(m_uid);
    }
}

void InvoiceProduct::setInvoiceId(const quint64 &invoiceId)
{
    if (m_invoiceId != invoiceId)
    {
        m_invoiceId = invoiceId;
        emit invoiceIdChanged(m_invoiceId);
        setInvoice(nullptr);
    }
}

void InvoiceProduct::setProductId(const quint64 &productId)
{
    if (m_productId != productId)
    {
        m_productId = productId;
        emit productIdChanged(m_productId);
        setProduct(nullptr);
    }
}

void InvoiceProduct::setInvoice(Invoice *invoice)
{
    if (m_invoice != invoice)
    {
        if(m_invoice != nullptr)
        {
            m_invoice->deleteLater();
            m_invoice = nullptr;
        }
        m_invoice = invoice;
        emit invoiceChanged(m_invoice);
    }
}

void InvoiceProduct::setProduct(Product *product)
{
    if (m_product != product)
    {
        if(m_product != nullptr)
        {
            m_product->deleteLater();
            m_product = nullptr;
        }
        m_product = product;
        emit productChanged(m_product);
    }
}

void InvoiceProduct::clearInvoice()
{
    if(m_invoice != nullptr)
    {
        m_invoice->deleteLater();
        m_invoice = nullptr;
    }
}

void InvoiceProduct::clearProduct()
{
    if(m_product != nullptr)
    {
        m_product->deleteLater();
        m_product = nullptr;
    }
}
