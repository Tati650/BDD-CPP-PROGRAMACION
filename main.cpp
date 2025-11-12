#include <iostream>
#include <string>
#include <pqxx/pqxx>

using namespace std;

class SistemaEscolar {
private:
    string connection_string = "dbname=bdescuela user=postgres password=1234 host=localhost port=5432";

    void mostrarAlumnos() {
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            pqxx::result result = txn.exec("SELECT id_alumno, nombre_alumno, edad_alumno FROM alumnos ORDER BY id_alumno");

            cout << "\n--- ALUMNOS ---\n";
            for (const auto& row : result) {
                cout << "ID: " << row["id_alumno"].as<int>()
                     << " | " << row["nombre_alumno"].as<string>()
                     << " | " << row["edad_alumno"].as<int>() << " años" << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void agregarAlumno() {
        string nombre;
        int edad;

        cout << "\nNombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Edad: ";
        cin >> edad;

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            txn.exec("INSERT INTO alumnos (nombre_alumno, edad_alumno) VALUES (" + txn.quote(nombre) + ", " + to_string(edad) + ")");
            txn.commit();
            cout << "Alumno agregado" << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void eliminarAlumno() {
        int id;
        cout << "\nID del alumno: ";
        cin >> id;

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            txn.exec("DELETE FROM alumnos WHERE id_alumno = " + to_string(id));
            txn.commit();
            cout << "Alumno eliminado!" << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void mostrarNotas() {
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            pqxx::result result = txn.exec(
                "SELECT n.id_nota, a.nombre_alumno, m.nombre_materia, n.nota "
                "FROM notas n "
                "JOIN alumnos a ON n.id_alumno = a.id_alumno "
                "JOIN materias m ON n.id_materia = m.id_materia"
            );

            cout << "\n--- NOTAS ---\n";
            for (const auto& row : result) {
                cout << "ID: " << row["id_nota"].as<int>() << " | "
                     << row["nombre_alumno"].as<string>() << " - "
                     << row["nombre_materia"].as<string>() << ": "
                     << row["nota"].as<string>() << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void agregarNota() {
        int id_alumno, id_materia, nota;

        cout << "\nID Alumno: ";
        cin >> id_alumno;
        cout << "ID Materia: ";
        cin >> id_materia;
        cout << "Nota: ";
        cin >> nota;

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            txn.exec("INSERT INTO notas (id_alumno, id_materia, nota) VALUES (" +
                    to_string(id_alumno) + ", " + to_string(id_materia) + ", " + to_string(nota) + ")");
            txn.commit();
            cout << "Nota agregada" << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    void eliminarNota() {
        int id_nota;
        cout << "\nID de la nota a eliminar: ";
        cin >> id_nota;

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            txn.exec("DELETE FROM notas WHERE id_nota = " + to_string(id_nota));
            txn.commit();
            cout << "Nota eliminada" << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void mostrarAsistencias() {
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            pqxx::result result = txn.exec(
                "SELECT a.nombre_alumno, m.nombre_materia, asi.fecha, asi.estado "
                "FROM asistencias asi "
                "JOIN alumnos a ON asi.id_alumno = a.id_alumno "
                "JOIN materias m ON asi.id_materia = m.id_materia "
                "ORDER BY asi.fecha DESC LIMIT 10"
            );

            cout << "\n--- ASISTENCIAS ---\n";
            for (const auto& row : result) {
                cout << row["fecha"].as<string>() << " | "
                     << row["nombre_alumno"].as<string>() << " - "
                     << row["nombre_materia"].as<string>() << " | "
                     << row["estado"].as<string>() << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }


public:
    void menuPrincipal() {
        int opcion;
        do {
            cout << "\n=== SISTEMA ESCOLAR ===\n";
            cout << "1. Mostrar alumnos\n";
            cout << "2. Agregar alumno\n";
            cout << "3. Eliminar alumno\n";
            cout << "4. Mostrar notas\n";
            cout << "5. Agregar nota\n";
            cout << "6. Eliminar nota\n";
            cout << "7. Mostrar asistencias\n";
            cout << "8. Salir\n";
            cout << "Opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1: mostrarAlumnos(); break;
                case 2: agregarAlumno(); break;
                case 3: eliminarAlumno(); break;
                case 4: mostrarNotas(); break;
                case 5: agregarNota(); break;
                case 6: eliminarNota(); break;
                case 7: mostrarAsistencias(); break;
                case 8: cout << "Chau!\n"; break;
                default: cout << "Opcion invalida!\n";
            }

        } while (opcion != 8);
    }
};

int main() {
    SistemaEscolar sistema;
    sistema.menuPrincipal();
    return 0;
}