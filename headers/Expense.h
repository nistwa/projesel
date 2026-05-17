#include "Transaction.h"

class Expense : public Transaction {
public:
    Expense(double amt, QString cat, QDate dt) : Transaction(amt, cat, dt) {}
    QString getType() const override { return "Expense"; }
};
