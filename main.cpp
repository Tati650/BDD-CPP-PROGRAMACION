#include <iostream>
#include <pqxx/pqxx>

int main() {
    try {
        // Conectarse a la base de datos PostgreSQL
        pqxx::connection conn("dbname=tu_base user=tu_usuario password=tu_contraseña host=localhost port=5432");

        if (conn.is_open()) {
            std::cout << "Conexión exitosa a la base de datos: " << conn.dbname() << std::endl;
        } else {
            std::cout << "No se pudo conectar a la base de datos." << std::endl;
            return 1;
        }

        // Crear una transacción
        pqxx::work txn(conn);

        // Ejecutar una consulta (ejemplo: seleccionar datos)
        pqxx::result result = txn.exec("SELECT version();");

        // Mostrar el resultado
        for (auto row : result) {
            std::cout << "Versión de PostgreSQL: " << row[0].c_str() << std::endl;
        }

        // Confirmar la transacción (commit)
        txn.commit();

        // La conexión se cierra automáticamente al destruir el objeto `conn`
        std::cout << "Transacción completada y conexión cerrada." << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
