#include <iostream>
#include <pqxx/pqxx>

int main() {
    try {
        std::cout << "🔧 Iniciando conexión a PostgreSQL..." << std::endl;


        pqxx::connection conn(
            "dbname=postgres "
            "user=postgres "
            "password=1234 "
            "host=localhost "
            "port=5432"
        );

        if (conn.is_open()) {
            std::cout << "✅ Conexión exitosa!" << std::endl;
            std::cout << "   Base de datos: " << conn.dbname() << std::endl;
        } else {
            std::cout << "❌ No se pudo conectar" << std::endl;
            return 1;
        }

        // Crear transacción
        pqxx::work txn(conn);

        // Consulta simple
        std::cout << "🔍 Ejecutando consulta..." << std::endl;
        pqxx::result result = txn.exec("SELECT version(), current_timestamp;");

        // Mostrar resultados
        std::cout << "📊 Resultados (" << result.size() << " filas):" << std::endl;
        for (const auto& row : result) {
            std::cout << "   Versión: " << row[0].c_str() << std::endl;
            std::cout << "   Fecha: " << row[1].c_str() << std::endl;
        }

        txn.commit();
        std::cout << "🎉 ¡Todo funcionó correctamente!" << std::endl;

    } catch (const pqxx::sql_error& e) {
        std::cerr << "❌ Error SQL: " << e.what() << std::endl;
        std::cerr << "   Consulta: " << e.query() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }

    try {
        
    } catch (const pqxx::connection_error& e) {
        std::cerr << "Error de conexión: " << e.what() << std::endl;
    } catch (const pqxx::transaction_error& e) {
        std::cerr << "Error en transacción: " << e.what() << std::endl;
    } catch (const pqxx::sql_error& e) {
        std::cerr << "Error SQL: " << e.what() << std::endl;
        std::cerr << "Query: " << e.query() << std::endl;
    }
    return 0;
}