#ifndef DBCONNECT
#define DBCONNECT

#include <QtSql>

#endif // DBCONNECT

class DBConnect {
    public:
        QSqlDatabase db;
        void dbClose() {
            /*
             * Cierra y remueve la conexion a la BD
            */
            db.close();
            db.removeDatabase(QSqlDatabase::defaultConnection);
        }
        bool dbOpen() {
            /*
             * Crea la conexion con la base de datos (SQLite)
             * y carga la base de datos "inventario.db"
            */
            QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("../database/inventario.db");

            if (!db.open()) {
                return false;
            } else {
                return true;
            }
        }
};
