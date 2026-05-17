#include "TransactionManager.h"
#include <QDebug>

// ── Yapici / Yikici ──────────────────────────────────
TransactionManager::TransactionManager() {}

TransactionManager::~TransactionManager() {
    // Heap'teki nesneleri temizle (bellek sizintisi onleme)
    qDeleteAll(transactions);
    transactions.clear();
}

// ── Ekleme ───────────────────────────────────────────
void TransactionManager::addIncome(double amount,
                                    const QString& category,
                                    const QDate& date) {
    // Polymorphism: Income* -> Transaction* olarak listeye eklenir
    Income* inc = new Income(amount, category, date);
    inc->id = transactions.size() + 1;  // basit id atama
    transactions.append(inc);
}

void TransactionManager::addExpense(double amount,
                                     const QString& category,
                                     const QDate& date) {
    // Polymorphism: Expense* -> Transaction* olarak listeye eklenir
    Expense* exp = new Expense(amount, category, date);
    exp->id = transactions.size() + 1;
    transactions.append(exp);
}

// ── Silme ────────────────────────────────────────────
bool TransactionManager::removeTransaction(int id) {
    for (int i = 0; i < transactions.size(); ++i) {
        if (transactions[i]->getId() == id) {
            delete transactions[i];
            transactions.removeAt(i);
            return true;
        }
    }
    return false;  // bulunamadi
}

// ── Sorgular ─────────────────────────────────────────
double TransactionManager::totalIncome() const {
    double toplam = 0;
    for (Transaction* t : transactions)
        if (t->getType() == "Income")
            toplam += t->getAmount();
    return toplam;
}

double TransactionManager::totalExpense() const {
    double toplam = 0;
    for (Transaction* t : transactions)
        if (t->getType() == "Expense")
            toplam += t->getAmount();
    return toplam;
}

double TransactionManager::netBalance() const {
    return totalIncome() - totalExpense();
}

// ── Listeleme ────────────────────────────────────────
QList<Transaction*> TransactionManager::getAll() const {
    return transactions;
}

QList<Transaction*> TransactionManager::getByType(const QString& type) const {
    QList<Transaction*> sonuc;
    for (Transaction* t : transactions)
        if (t->getType() == type)
            sonuc.append(t);
    return sonuc;
}

QList<Transaction*> TransactionManager::getByCategory(const QString& cat) const {
    QList<Transaction*> sonuc;
    for (Transaction* t : transactions)
        if (t->getCategory() == cat)
            sonuc.append(t);
    return sonuc;
}

// ── Ozet ─────────────────────────────────────────────
QString TransactionManager::getMonthlySummary(int month, int year) const {
    double gelir  = 0;
    double gider  = 0;

    for (Transaction* t : transactions) {
        if (t->getDate().month() == month && t->getDate().year() == year) {
            if (t->getType() == "Income")
                gelir += t->getAmount();
            else
                gider += t->getAmount();
        }
    }

    return QString("%1/%2 Ozet:\n"
                   "Toplam Gelir : %3 TL\n"
                   "Toplam Gider : %4 TL\n"
                   "Net Bakiye   : %5 TL")
        .arg(month).arg(year)
        .arg(gelir,  0, 'f', 2)
        .arg(gider,  0, 'f', 2)
        .arg(gelir - gider, 0, 'f', 2);
}
