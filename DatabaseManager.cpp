#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// ── Yapici / Yikici ──────────────────────────────────
DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager() {
    if (db.isOpen())
        db.close();
}

// ── Baglan ───────────────────────────────────────────
bool DatabaseManager::connect(const QString& dbPath) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Veritabani acilamadi:" << db.lastError().text();
        return false;
    }

    return createTables();
}

// ── Tablo olustur (private) ──────────────────────────
bool DatabaseManager::createTables() {
    QSqlQuery query;
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS transactions ("
        "  id       INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  type     TEXT    NOT NULL,"   // 'Income' veya 'Expense'
        "  amount   REAL    NOT NULL,"
        "  category TEXT    NOT NULL,"
        "  date     TEXT    NOT NULL"    // 'YYYY-MM-DD'
        ");"
    );

    if (!ok)
        qDebug() << "Tablo olusturulamadi:" << query.lastError().text();

    return ok;
}

// ── Kaydetme ─────────────────────────────────────────
bool DatabaseManager::saveTransaction(Transaction* t) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO transactions (type, amount, category, date) "
        "VALUES (:type, :amount, :category, :date);"
    );

    // Polymorphism: getType() hangi alt sinif olduguna gore "Income"/"Expense" doner
    query.bindValue(":type",     t->getType());
    query.bindValue(":amount",   t->getAmount());
    query.bindValue(":category", t->getCategory());
    query.bindValue(":date",     t->getDate().toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Kayit hatasi:" << query.lastError().text();
        return false;
    }
    return true;
}

// ── Silme ────────────────────────────────────────────
bool DatabaseManager::deleteTransaction(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM transactions WHERE id = :id;");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Silme hatasi:" << query.lastError().text();
        return false;
    }
    return true;
}

// ── Yukleme ──────────────────────────────────────────
QList<Transaction*> DatabaseManager::loadAll() {
    QList<Transaction*> liste;
    QSqlQuery query("SELECT id, type, amount, category, date FROM transactions;");

    while (query.next()) {
        int     id       = query.value(0).toInt();
        QString type     = query.value(1).toString();
        double  amount   = query.value(2).toDouble();
        QString category = query.value(3).toString();
        QDate   date     = QDate::fromString(query.value(4).toString(), "yyyy-MM-dd");

        Transaction* t = nullptr;

        // Polymorphism: type'a gore dogru alt sinif nesnesi olusturulur
        if (type == "Income")
            t = new Income(amount, category, date);
        else if (type == "Expense")
            t = new Expense(amount, category, date);

        if (t) {
            t->id = id;
            liste.append(t);
        }
    }

    return liste;
}
