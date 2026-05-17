#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDate>

// Temel Sınıf (Abstract Class)
class Transaction {
protected:
    int id;
    double amount;
    QString category;
    QDate date;

public:
    Transaction(double amt, QString cat, QDate dt) 
        : amount(amt), category(cat), date(dt) {}
    
    virtual ~Transaction() {}

    // Saf sanal fonksiyon (Çok biçimlilik için)
    virtual QString getType() const = 0; 

    // Getter Metotları
    double getAmount() const { return amount; }
    QString getCategory() const { return category; }
    QDate getDate() const { return date; }
    int getId() const { return id; }
 void setId(int i) { id = i; }
} ;

#endif
