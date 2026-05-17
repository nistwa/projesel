#include "Transaction.h"

class Income : public Transaction {
public:
    Income(double amt, QString cat, QDate dt) : Transaction(amt, cat, dt) {}
    QString getType() const override { return "Income"; }
};
