#include <iostream>
#include <pqxx/pqxx>
using namespace std;
int main() {
    try {
        cout << "SISTEMA ESCOLAR - PRUEBA DE CONEXION" << endl;
        cout << "========================================" << endl;


        string connection_string =
            "dbname=programacion "
            "user=postgres "
            "password=1234 "
            "host=localhost "
            "port=5432";

        cout << "Intentando conectar a la base de datos..." << endl;

        // Crear conexión
        pqxx::connection conn(connection_string);

        if (conn.is_open()) {
            cout << "Conexion exitosa a PostgreSQL" << endl;
            cout << "   Base de datos: " << conn.dbname() << endl;
        } else {
            cout << "No se pudo conectar a la base de datos" << endl;
            return 1;
        }

        // Probar una consulta simple
        cout << "\nEjecutando consulta de prueba..." << endl;
        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT version(), current_timestamp;");
        txn.commit();

        cout << " Resultado obtenido:" << endl;
        for (const auto& row : result) {
            cout << "   PostgreSQL: " << row[0].c_str() << endl;
            cout << "   Fecha/Hora: " << row[1].c_str() << endl;
        }

        cout << "\nTodo funciono correctamente" << endl;

    } catch (const exception& e) {
        cerr << " Error: " << e.what() << endl;
        return 1;
    }

    cout << "\nPresiona Enter para salir...";
    cin.get();
    return 0;
}