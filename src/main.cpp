#include <QCoreApplication>
#include <QDebug>

#include "pathutils.hpp"
#include "xdatabase.hpp"
#include "xquerybuilder.hpp"
#include "invoice.hpp"
#include "product.hpp"
#include "invoiceproduct.hpp"
#include "customer.hpp"
#include "account.hpp"


static const QString DATABASE_FILE_NAME = QStringLiteral("database_%1.db");
static const QString DATABASE_CONNECTION_NAME = QStringLiteral("XOrmDemo");

void createDatabase(const QString &connectionName, const QString &filePath);
void dumpDatabase(const QString &connectionName, const QString &filePath);
void findItems(const QString &connectionName, const QString &filePath);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString databaseFilePath = PathUtils::appicationDataPath() + PathUtils::SEPARATOR
            + DATABASE_FILE_NAME.arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));
    PathUtils::makeParentPath(databaseFilePath);

    createDatabase(QString("%1_%2").arg(DATABASE_CONNECTION_NAME).arg(1), databaseFilePath);
    dumpDatabase(QString("%1_%2").arg(DATABASE_CONNECTION_NAME).arg(2), databaseFilePath);
    findItems(QString("%1_%2").arg(DATABASE_CONNECTION_NAME).arg(3), databaseFilePath);

    return a.exec();
}

void createDatabase(const QString &connectionName, const QString &filePath)
{
    XDatabase databaseMgr(filePath, connectionName, EMPTY_TEMPLATE);

    qDebug() << "[+] Creating database";

    bool opened = databaseMgr.open();

    if(!opened) {
        qDebug() << "[-] Database not opened";
        qDebug() << "[-] \tError: " << databaseMgr.lastError().text();
    }
    else {
        qDebug() << "[+] Database opened";
        qDebug() << "[+] Registering models";

        QSqlError error;
        error = databaseMgr.registerModel<Invoice>();
        if(error.isValid())
        {
            qDebug() << "[-] Could not register Invoice model";
            qDebug() << "[-] \tError: " << error.text();
        }
        else
        {
            qDebug() << "[+] Invoice model registered";
        }

        error = databaseMgr.registerModel<Product>();
        if(error.isValid())
        {
            qDebug() << "[-] Could not register Product model";
            qDebug() << "[-] \tError: " << error.text();
        }
        else
        {
            qDebug() << "[+] Product model registered";
        }

        error = databaseMgr.registerModel<InvoiceProduct>();
        if(error.isValid())
        {
            qDebug() << "[-] Could not register InvoiceProduct model";
            qDebug() << "[-] \tError: " << error.text();
        }
        else
        {
            qDebug() << "[+] InvoiceProduct model registered";
        }

        error = databaseMgr.registerModel<Customer>();
        if(error.isValid())
        {
            qDebug() << "[-] Could not register Customer model";
            qDebug() << "[-] \tError: " << error.text();
        }
        else
        {
            qDebug() << "[+] Customer model registered";
        }

        error = databaseMgr.registerModel<Account>();
        if(error.isValid())
        {
            qDebug() << "[-] Could not register Account model";
            qDebug() << "[-] \tError: " << error.text();
        }
        else
        {
            qDebug() << "[+] Account model registered";
        }

        qDebug() << "[+] Initializing DAOs";

        XDao<Customer> customersDao;
        XDao<Product> productsDao;
        XDao<Invoice> invoicesDao;
        XDao<InvoiceProduct> invoicesProductsDao;
        XDao<Account> accountsDao;

        customersDao.setDatabase(*databaseMgr.database());
        productsDao.setDatabase(*databaseMgr.database());
        invoicesDao.setDatabase(*databaseMgr.database());
        invoicesProductsDao.setDatabase(*databaseMgr.database());
        accountsDao.setDatabase(*databaseMgr.database());

        qDebug() << "[+] Creating customers";

        Customer* customer1 = new Customer("John", "Doe", "johndoe@mail.com", Customer::SECONDARY, false);
        Customer* customer2 = new Customer("Jane", "Doe", "janedoe@mail.com", Customer::PRIMARY, true);

        error = customersDao.createOne(customer1);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create customer 1";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = customersDao.createOne(customer2);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create customer 2";
            qDebug() << "[-] \tError: " << error.text();
        }

        qDebug() << "[+] Creating products";

        Product* product1 = new Product("Xiaomi Redmi Note 7 Pro", 310.0f);
        Product* product2 = new Product("Huawei MateBook X Pro", 1599.0f);
        Product* product3 = new Product("Toshiba HDD 5TB", 250.0f);
        Product* product4 = new Product("IPhone XR", 1020.0f);
        Product* product5 = new Product("MacBook Pro 15 (Early 2018)", 1450.0f);

        error = productsDao.createOne(product1);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create product 1";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = productsDao.createOne(product2);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create product 2";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = productsDao.createOne(product3);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create product 3";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = productsDao.createOne(product4);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create product 4";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = productsDao.createOne(product5);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create product 5";
            qDebug() << "[-] \tError: " << error.text();
        }

        qDebug() << "[+] Creating invoices";

        Invoice* invoice1 = new Invoice(customer1->uid(), QDateTime(QDate(2019, 6, 12), QTime(14, 44, 13)));
        Invoice* invoice2 = new Invoice(customer2->uid(), QDateTime(QDate(2019, 5, 2), QTime(9, 34, 41)));
        Invoice* invoice3 = new Invoice(customer2->uid(), QDateTime(QDate(2019, 7, 19), QTime(15, 59, 28)));

        error = invoicesDao.createOne(invoice1);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create invoice 1";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = invoicesDao.createOne(invoice2);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create invoice 2";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = invoicesDao.createOne(invoice3);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create invoice 3";
            qDebug() << "[-] \tError: " << error.text();
        }

        qDebug() << "[+] Creating relations of invoices and products";

        InvoiceProduct* invoiceProduct1 = new InvoiceProduct(invoice1->uid(), product1->uid());
        InvoiceProduct* invoiceProduct2 = new InvoiceProduct(invoice1->uid(), product2->uid());
        InvoiceProduct* invoiceProduct3 = new InvoiceProduct(invoice1->uid(), product5->uid());
        InvoiceProduct* invoiceProduct4 = new InvoiceProduct(invoice2->uid(), product2->uid());
        InvoiceProduct* invoiceProduct5 = new InvoiceProduct(invoice2->uid(), product3->uid());
        InvoiceProduct* invoiceProduct6 = new InvoiceProduct(invoice3->uid(), product4->uid());
        InvoiceProduct* invoiceProduct7 = new InvoiceProduct(invoice3->uid(), product5->uid());

        error = invoicesProductsDao.createOne(invoiceProduct1);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create relation invoice product 1";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = invoicesProductsDao.createOne(invoiceProduct2);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create relation invoice product 2";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = invoicesProductsDao.createOne(invoiceProduct3);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create relation invoice product 3";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = invoicesProductsDao.createOne(invoiceProduct4);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create relation invoice product 4";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = invoicesProductsDao.createOne(invoiceProduct5);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create relation invoice product 5";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = invoicesProductsDao.createOne(invoiceProduct6);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create relation invoice product 6";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = invoicesProductsDao.createOne(invoiceProduct7);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create relation invoice product 7";
            qDebug() << "[-] \tError: " << error.text();
        }

        qDebug() << "[+] Creating accounts";

        Account* account1 = new Account("32B7-1419-A390-0B17", customer1->uid());
        Account* account2 = new Account("45F3-0239-K491-6P87", customer2->uid());

        error = accountsDao.createOne(account1);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create account 1";
            qDebug() << "[-] \tError: " << error.text();
        }

        error = accountsDao.createOne(account2);

        if(error.isValid())
        {
            qDebug() << "[-] Could not create account 2";
            qDebug() << "[-] \tError: " << error.text();
        }

        if(customer1 != nullptr)
        {
            customer1->deleteLater();
            customer1 = nullptr;
        }
        if(customer2 != nullptr)
        {
            customer2->deleteLater();
            customer2 = nullptr;
        }
        if(product1 != nullptr)
        {
            product1->deleteLater();
            product1 = nullptr;
        }
        if(product2 != nullptr)
        {
            product2->deleteLater();
            product2 = nullptr;
        }
        if(product3 != nullptr)
        {
            product3->deleteLater();
            product3 = nullptr;
        }
        if(product4 != nullptr)
        {
            product4->deleteLater();
            product4 = nullptr;
        }
        if(product5 != nullptr)
        {
            product5->deleteLater();
            product5 = nullptr;
        }
        if(invoice1 != nullptr)
        {
            invoice1->deleteLater();
            invoice1 = nullptr;
        }
        if(invoice2 != nullptr)
        {
            invoice2->deleteLater();
            invoice2 = nullptr;
        }
        if(invoice3 != nullptr)
        {
            invoice3->deleteLater();
            invoice3 = nullptr;
        }
        if(invoiceProduct1 != nullptr)
        {
            invoiceProduct1->deleteLater();
            invoiceProduct1 = nullptr;
        }
        if(invoiceProduct2 != nullptr)
        {
            invoiceProduct2->deleteLater();
            invoiceProduct2 = nullptr;
        }
        if(invoiceProduct3 != nullptr)
        {
            invoiceProduct3->deleteLater();
            invoiceProduct3 = nullptr;
        }
        if(invoiceProduct4 != nullptr)
        {
            invoiceProduct4->deleteLater();
            invoiceProduct4 = nullptr;
        }
        if(invoiceProduct5 != nullptr)
        {
            invoiceProduct5->deleteLater();
            invoiceProduct5 = nullptr;
        }
        if(invoiceProduct6 != nullptr)
        {
            invoiceProduct6->deleteLater();
            invoiceProduct6 = nullptr;
        }
        if(invoiceProduct7 != nullptr)
        {
            invoiceProduct7->deleteLater();
            invoiceProduct7 = nullptr;
        }
        if(account1 != nullptr)
        {
            account1->deleteLater();
            account1 = nullptr;
        }
        if(account2 != nullptr)
        {
            account2->deleteLater();
            account2 = nullptr;
        }

        databaseMgr.close();
        qDebug() << "[+] Database closed";
    }
}

void dumpDatabase(const QString &connectionName, const QString &filePath)
{
    XDatabase databaseMgr(filePath, connectionName, EMPTY_TEMPLATE);

    qDebug() << "[+] Dump database";

    bool opened = databaseMgr.open();

    if(!opened) {
        qDebug() << "[-] Database not opened";
        qDebug() << "[-] \tError: " << databaseMgr.lastError().text();
    }
    else {
        qDebug() << "[+] Database opened";

        QSqlError error;

        XDao<Customer> customersDao;
        XDao<Invoice> invoicesDao;

        customersDao.setDatabase(*databaseMgr.database());
        invoicesDao.setDatabase(*databaseMgr.database());

        QList<Customer*> customers;

        error = customersDao.readAll(customers);

        if(!error.isValid())
        {
            foreach(Customer* customer, customers)
            {
                qDebug() << "[+] Customer info";
                qDebug() << "[+] \tUid        " << customer->uid();
                qDebug() << "[+] \tName       " << customer->name();
                qDebug() << "[+] \tLast Name  " << customer->lastName();
                qDebug() << "[+] \tEmail      " << customer->email();
                qDebug() << "[+] \tCategory   " << customer->category();

                error = customersDao.resolveForeigns(customer);

                if(!error.isValid())
                {
                    qDebug() << "[+] \tAccount info";
                    if(customer->account() != nullptr)
                    {
                        Account* account = customer->account();
                        qDebug() << "[+] \t\tUid         " << account->uid();
                        qDebug() << "[+] \t\tCard Number " << account->cardNumber();
                        account = nullptr;
                    }
                    else
                    {
                        qDebug() << "[-] \t\tNo account defined";
                    }

                    if(!customer->invoices().isEmpty())
                    {
                        QList<Invoice*> invoices = customer->invoices();
                        foreach(Invoice* invoice, invoices)
                        {
                            invoicesDao.resolveForeigns(invoice);
                            qDebug() << "[+] \tInvoice info";
                            qDebug() << "[+] \t\tUid       " << invoice->uid();
                            qDebug() << "[+] \t\tTimestamp " << invoice->timestamp().toString(TIMESTAMP_FORMAT);

                            if(!invoice->products().isEmpty())
                            {
                                QList<Product*> products = invoice->products();

                                foreach(Product* product, products)
                                {
                                    qDebug() << "[+] \t\tProduct info";
                                    qDebug() << "[+] \t\t\tUid   " << product->uid();
                                    qDebug() << "[+] \t\t\tName  " << product->name();
                                    qDebug() << "[+] \t\t\tPrice " << product->price();
                                }
                            }
                            else
                            {
                                qDebug() << "[-] \t\tNo products defined";
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "[-] \t\tNo invoices found";
                    }
                }
                else
                {
                    qDebug() << "[-] \tError: " << error.text();
                }
            }
        }
        else
        {
            qDebug() << "[-] Could not read customers";
        }

        if(!customers.isEmpty())
        {
            foreach(Customer* customer, customers)
            {
                customer->deleteLater();
                customer = nullptr;
            }
            customers.clear();
        }

        databaseMgr.close();
        qDebug() << "[+] Database closed";
    }
}

void findItems(const QString &connectionName, const QString &filePath)
{
    XDatabase databaseMgr(filePath, connectionName, EMPTY_TEMPLATE);

    qDebug() << "[+] Finding items";

    bool opened = databaseMgr.open();

    if(!opened) {
        qDebug() << "[-] Database not opened";
        qDebug() << "[-] \tError: " << databaseMgr.lastError().text();
    }
    else {
        qDebug() << "[+] Database opened";

        QSqlError error;

        XDao<Customer> customersDao;
        XDao<Product> productsDao;

        customersDao.setDatabase(*databaseMgr.database());
        productsDao.setDatabase(*databaseMgr.database());


        qDebug() << "[+] Finding customer(s) with name 'John'";

        XQueryBuilder<Customer> finder1;
        finder1.setLimit(1)
                .where()
                .appendEqual("name", "John");

        QList<Customer*> customers;

        error = customersDao.query(finder1, customers);

        if(error.isValid())
        {
            qDebug() << "[-] Could not search customers";
            qDebug() << "[-] \tError: " << error.text();
        }
        else
        {
            if(!customers.isEmpty())
            {
                qDebug() << "[+] Customer(s) found " << customers.size();
                foreach (Customer* customer, customers)
                {
                    qDebug() << "[+] Customer info";
                    qDebug() << "[+] \tUid        " << customer->uid();
                    qDebug() << "[+] \tName       " << customer->name();
                    qDebug() << "[+] \tLast Name  " << customer->lastName();
                    qDebug() << "[+] \tEmail      " << customer->email();
                    qDebug() << "[+] \tCategory   " << customer->category();
                }
            }
            else
            {
                qDebug() << "[+] No customer(s) found";
            }
        }

        qDebug() << "[+] Finding products with 'pro' sequence in their names";
        qDebug() << "[+] and price greater than 1000.0";

        XQueryBuilder<Product> finder2;
        finder2.where()
                .appendLike("name", "pro")
                .appendAnd()
                .appendGreatThan("price", 1000);

        QList<Product*> products;

        productsDao.query(finder2.raw(), products);

        if(error.isValid())
        {
            qDebug() << "[-] Could not search products";
            qDebug() << "[-] \tError: " << error.text();
        }
        else
        {
            if(!products.isEmpty())
            {
                qDebug() << "[+] Product(s) found " << products.size();
                foreach(Product* product, products)
                {
                    qDebug() << "[+] Product info";
                    qDebug() << "[+] \tUid   " << product->uid();
                    qDebug() << "[+] \tName  " << product->name();
                    qDebug() << "[+] \tPrice " << product->price();
                }
            }
            else
            {
                qDebug() << "[+] No product(s) found";
            }
        }

        databaseMgr.close();
        qDebug() << "[+] Database closed";
    }
}
