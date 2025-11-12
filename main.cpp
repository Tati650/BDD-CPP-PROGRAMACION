#include <iostream>
#include <pqxx/pqxx>

using namespace std;

int main() {
int numero = 0;
    try {
        cout << "SISTEMA ESCOLAR - PRUEBA DE CONEXION" << endl;
        cout << "========================================" << endl;

        // Configuración de conexión
        const string connection_string =
            "dbname= bdescuela "
            "user=postgres "
            "password=1234 "
            "host=localhost "
            "port=5432";

        cout << "Intentando conectar a la base de datos..." << endl;

        // Crear conexión
        pqxx::connection conn(connection_string);

        if (!conn.is_open()) {
            cout << "No se pudo conectar a la base de datos" << endl;
            return 1;
        }

        cout << "Conexion exitosa a PostgreSQL" << endl;
        cout << "Base de datos: " << conn.dbname() << endl;

        // Consulta de prueba
        cout << "\nEjecutando consulta de prueba..." << endl;
        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT version(), current_timestamp");
        txn.commit();

        cout << "Resultado obtenido:" << endl;
        for (const auto& row : result) {
            cout << "PostgreSQL: " << row[0].c_str() << endl;
            cout << "Fecha/Hora: " << row[1].c_str() << endl;
        }

        cout << "\nTodo funciono correctamente" << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    cout << "----------Menu----------" << endl;
    cout << "Presione: (1), (2), (3) o (4)" << endl;
    cout << "(1)Ver alumnos" << endl;
    cout << "(2)gestionar alumnos" << endl;
    cout << "(3)gestionar notas" << endl;
    cout << "(4)gestionar asistencias" << endl;
    cout << "------------------------" << endl;
    cin >> numero;
    switch (numero) {
        case 1: cout << "zz" << endl;
            break;
    }

    cout << "\nPresiona Enter para salir...";
    cin.get();
    return 0;

}