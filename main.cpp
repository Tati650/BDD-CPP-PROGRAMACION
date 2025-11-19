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

    void mostrarMaterias() {
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            pqxx::result result = txn.exec("SELECT id_materia, nombre_materia FROM materias ORDER BY id_materia");

            cout << "\n--- MATERIAS ---\n";
            for (const auto& row : result) {
                cout << "ID: " << row["id_materia"].as<int>()
                     << " | " << row["nombre_materia"].as<string>() << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void agregarMateria() {
        string nombre;

        cout << "\nNombre de la materia: ";
        cin.ignore();
        getline(cin, nombre);

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            txn.exec("INSERT INTO materias (nombre_materia) VALUES (" + txn.quote(nombre) + ")");
            txn.commit();
            cout << "Materia agregada" << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void eliminarMateria() {
        int id;
        cout << "\nID de la materia: ";
        cin >> id;

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            txn.exec("DELETE FROM materias WHERE id_materia = " + to_string(id));
            txn.commit();
            cout << "Materia eliminada!" << endl;
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

        // Mostrar alumnos disponibles
        cout << "\n--- ALUMNOS DISPONIBLES ---\n";
        mostrarAlumnos();

        cout << "\n--- MATERIAS DISPONIBLES ---\n";
        mostrarMaterias();

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
                "SELECT asi.id_asistencia, a.nombre_alumno, m.nombre_materia, asi.fecha, asi.estado "
                "FROM asistencias asi "
                "JOIN alumnos a ON asi.id_alumno = a.id_alumno "
                "JOIN materias m ON asi.id_materia = m.id_materia "
                "ORDER BY asi.fecha DESC, a.nombre_alumno"
            );

            cout << "\n--- ASISTENCIAS ---\n";
            for (const auto& row : result) {
                cout << "ID: " << row["id_asistencia"].as<int>() << " | "
                     << row["fecha"].as<string>() << " | "
                     << row["nombre_alumno"].as<string>() << " - "
                     << row["nombre_materia"].as<string>() << " | "
                     << row["estado"].as<string>() << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void agregarAsistencia() {
        int id_alumno, id_materia;
        string fecha, estado;

        cout << "\n--- ALUMNOS DISPONIBLES ---\n";
        mostrarAlumnos();

        cout << "\n--- MATERIAS DISPONIBLES ---\n";
        mostrarMaterias();

        cout << "\nID Alumno: ";
        cin >> id_alumno;
        cout << "ID Materia: ";
        cin >> id_materia;
        cout << "Fecha (YYYY-MM-DD): ";
        cin >> fecha;
        cout << "Estado (Presente/Ausente/Tardanza): ";
        cin >> estado;

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            txn.exec("INSERT INTO asistencias (id_alumno, id_materia, fecha, estado) VALUES (" +
                    to_string(id_alumno) + ", " + to_string(id_materia) + ", " +
                    txn.quote(fecha) + ", " + txn.quote(estado) + ")");
            txn.commit();
            cout << "Asistencia agregada" << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void eliminarAsistencia() {
        int id_asistencia;
        cout << "\nID de la asistencia a eliminar: ";
        cin >> id_asistencia;

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            txn.exec("DELETE FROM asistencias WHERE id_asistencia = " + to_string(id_asistencia));
            txn.commit();
            cout << "Asistencia eliminada" << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void buscarAsistenciasPorFecha() {
        string fecha;
        cout << "\nFecha a buscar (YYYY-MM-DD): ";
        cin >> fecha;

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            pqxx::result result = txn.exec(
                "SELECT asi.id_asistencia, a.nombre_alumno, m.nombre_materia, asi.fecha, asi.estado "
                "FROM asistencias asi "
                "JOIN alumnos a ON asi.id_alumno = a.id_alumno "
                "JOIN materias m ON asi.id_materia = m.id_materia "
                "WHERE asi.fecha = " + txn.quote(fecha) + " "
                "ORDER BY a.nombre_alumno"
            );

            cout << "\n--- ASISTENCIAS DEL " << fecha << " ---\n";
            if (result.size() == 0) {
                cout << "No hay asistencias registradas para esta fecha." << endl;
            } else {
                for (const auto& row : result) {
                    cout << "ID: " << row["id_asistencia"].as<int>() << " | "
                         << row["nombre_alumno"].as<string>() << " - "
                         << row["nombre_materia"].as<string>() << " | "
                         << row["estado"].as<string>() << endl;
                }
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void buscarAsistenciasPorAlumno() {
        int id_alumno;

        cout << "\n--- ALUMNOS DISPONIBLES ---\n";
        mostrarAlumnos();
        cout << "\nID del alumno: ";
        cin >> id_alumno;

        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            pqxx::result result = txn.exec(
                "SELECT asi.id_asistencia, a.nombre_alumno, m.nombre_materia, asi.fecha, asi.estado "
                "FROM asistencias asi "
                "JOIN alumnos a ON asi.id_alumno = a.id_alumno "
                "JOIN materias m ON asi.id_materia = m.id_materia "
                "WHERE asi.id_alumno = " + to_string(id_alumno) + " "
                "ORDER BY asi.fecha DESC"
            );

            cout << "\n--- ASISTENCIAS DEL ALUMNO ---\n";
            if (result.size() == 0) {
                cout << "No hay asistencias registradas para este alumno." << endl;
            } else {
                for (const auto& row : result) {
                    cout << "ID: " << row["id_asistencia"].as<int>() << " | "
                         << row["fecha"].as<string>() << " | "
                         << row["nombre_materia"].as<string>() << " | "
                         << row["estado"].as<string>() << endl;
                }
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    // Menús secundarios
    void menuGestionAlumnos() {
        int opcion;
        do {
            cout << "\n=== GESTION DE ALUMNOS ===\n";
            cout << "1. Mostrar alumnos\n";
            cout << "2. Agregar alumno\n";
            cout << "3. Eliminar alumno\n";
            cout << "4. Volver al menu principal\n";
            cout << "Opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1: mostrarAlumnos(); break;
                case 2: agregarAlumno(); break;
                case 3: eliminarAlumno(); break;
                case 4: cout << "Volviendo al menu principal...\n"; break;
                default: cout << "Opcion invalida!\n";
            }
        } while (opcion != 4);
    }

    void menuGestionMaterias() {
        int opcion;
        do {
            cout << "\n=== GESTION DE MATERIAS ===\n";
            cout << "1. Mostrar materias\n";
            cout << "2. Agregar materia\n";
            cout << "3. Eliminar materia\n";
            cout << "4. Volver al menu principal\n";
            cout << "Opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1: mostrarMaterias(); break;
                case 2: agregarMateria(); break;
                case 3: eliminarMateria(); break;
                case 4: cout << "Volviendo al menu principal...\n"; break;
                default: cout << "Opcion invalida!\n";
            }
        } while (opcion != 4);
    }

    void menuGestionNotas() {
        int opcion;
        do {
            cout << "\n=== GESTION DE NOTAS ===\n";
            cout << "1. Mostrar notas\n";
            cout << "2. Agregar nota\n";
            cout << "3. Eliminar nota\n";
            cout << "4. Volver al menu principal\n";
            cout << "Opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1: mostrarNotas(); break;
                case 2: agregarNota(); break;
                case 3: eliminarNota(); break;
                case 4: cout << "Volviendo al menu principal...\n"; break;
                default: cout << "Opcion invalida!\n";
            }
        } while (opcion != 4);
    }

    void menuGestionAsistencias() {
        int opcion;
        do {
            cout << "\n=== GESTION DE ASISTENCIAS ===\n";
            cout << "1. Mostrar todas las asistencias\n";
            cout << "2. Agregar asistencia\n";
            cout << "3. Eliminar asistencia\n";
            cout << "4. Buscar asistencias por fecha\n";
            cout << "5. Buscar asistencias por alumno\n";
            cout << "6. Volver al menu principal\n";
            cout << "Opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1: mostrarAsistencias(); break;
                case 2: agregarAsistencia(); break;
                case 3: eliminarAsistencia(); break;
                case 4: buscarAsistenciasPorFecha(); break;
                case 5: buscarAsistenciasPorAlumno(); break;
                case 6: cout << "Volviendo al menu principal...\n"; break;
                default: cout << "Opcion invalida!\n";
            }
        } while (opcion != 6);
    }

public:
    void menuPrincipal() {
        int opcion;
        string contra, nombreuser;
        cout << "Ingrese su nombre de usuario: \n";
        cin >> nombreuser;
        if (nombreuser=="Profesor") {
            cout << "Ingrese su contrasenia: \n";
            cin >> contra;
            if (contra=="banana") {
                do {
                    cout << "\n=== SISTEMA ESCOLAR ===\n";
                    cout << "1. Gestionar alumnos\n";
                    cout << "2. Gestionar materias\n";
                    cout << "3. Gestionar notas\n";
                    cout << "4. Gestionar asistencias\n";
                    cout << "5. Salir\n";
                    cout << "Opcion: ";
                    cin >> opcion;

                    switch(opcion) {
                        case 1: menuGestionAlumnos(); break;
                        case 2: menuGestionMaterias(); break;
                        case 3: menuGestionNotas(); break;
                        case 4: menuGestionAsistencias(); break;
                        case 5: cout << "Chau!\n"; break;
                        default: cout << "Opcion invalida!\n";
                    }

                } while (opcion != 5);
            }else cout << "Contrasenia invalida\n";
        }else cout << "Nombre invalido \n";
    }
};

int main() {
    SistemaEscolar sistema;
    sistema.menuPrincipal();
    return 0;
}