#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <QObject>

#include "xtablemodel.hpp"

class Product : public QObject, public XTableModel<Product>
{
    Q_OBJECT

    Q_PROPERTY(quint64 uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(float price READ price WRITE setPrice NOTIFY priceChanged)

    X_TABLE_NAME("products")
    X_TABLE_FIELDS(X_FIELD(uid, X_PRIMARY_KEY),
                   X_FIELD(name, X_NOT_NULL),
                   X_FIELD(price, X_NOT_NULL))

public:
    explicit Product(QObject *parent = nullptr);
    Product(const QString &name, const float &price, QObject* parent = nullptr);
    Product(const quint64 &uid, const QString &name, const float &price, QObject* parent = nullptr);
    Product(const Product &other);

    ~Product();

    Product& operator=(const Product &other);

    quint64 uid() const;
    QString name() const;
    float price() const;

public slots:
    void setUid(const quint64 &uid);
    void setName(const QString &name);
    void setPrice(const float &price);

signals:
    void uidChanged(const quint64 &uid);
    void nameChanged(const QString &name);
    void priceChanged(const float &price);

private:
    quint64 m_uid;
    QString m_name;
    float m_price;
};

#endif // PRODUCT_HPP
