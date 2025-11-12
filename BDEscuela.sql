-- Database: escuela

-- DROP DATABASE IF EXISTS escuela;

CREATE DATABASE "BDEscuela"
    WITH
    OWNER = postgres
    ENCODING = 'UTF8'
    LC_COLLATE = 'Spanish_Argentina.1252'
    LC_CTYPE = 'Spanish_Argentina.1252'
    LOCALE_PROVIDER = 'libc'
    TABLESPACE = pg_default
    CONNECTION LIMIT = -1
    IS_TEMPLATE = False;

CREATE TABLE alumnos(
	Id_alumno serial primary key,
	Nombre_alumno varchar(255) not null,
	edad_alumno int not null,
	curso_alumno varchar(20) not null
)

CREATE TABLE materias (
    id_materia SERIAL PRIMARY KEY,
    nombre_materia VARCHAR(100) NOT NULL
)

CREATE TABLE notas(
	Id_nota serial primary key,
	Id_alumno int not null,
	Id_materia int not null,
	Nota int not null,
	tipo_evaluacion VARCHAR(50),
	observaciones TEXT
)

CREATE TABLE asistencias (
    id_asistencia SERIAL PRIMARY KEY,
    id_alumno INT NOT NULL,
    id_materia INT NOT NULL,
    fecha DATE NOT NULL,
    estado VARCHAR(20) NOT NULL CHECK (estado IN ('Presente', 'Ausente', 'Tarde', 'Justificado')),
    observaciones TEXT
)

INSERT INTO alumnos (
	nombre_alumno, edad_alumno, curso_alumno
	)
VALUES 
	('Juan Pérez', 15, '3A'),
	('María López', 16, '4B');

INSERT INTO materias (nombre_materia)
VALUES 
	('Matemática'),
	('Historia');
	
INSERT INTO notas (id_alumno, id_materia, nota, tipo_evaluacion, observaciones)
VALUES
	(1, 1, 8.50, 'Examen Parcial', 'Buen desempeño'),
	(1, 2, 6.75, 'Trabajo Práctico', 'Entregado con retraso'),
	(2, 1, 9.25, 'Examen Final', 'Excelente presentación');

INSERT INTO asistencias (id_alumno, id_materia, fecha, estado, observaciones)
VALUES
    (1, 1, '2025-11-01', 'Presente', 'Llegó a tiempo y participó activamente'),
    (1, 1, '2025-11-02', 'Tarde', 'Llegó 10 minutos tarde'),
    (1, 1, '2025-11-03', 'Ausente', 'Ausente'),

    (1, 2, '2025-11-01', 'Presente', 'Buena participación'),
    (1, 2, '2025-11-02', 'Presente', 'Atento en clase'),

    (2, 1, '2025-11-01', 'Presente', 'Muy buena actitud'),
    (2, 1, '2025-11-02', 'Justificado', 'Ausencia por consulta médica'),
    (2, 1, '2025-11-03', 'Presente', 'Entregó tarea correctamente'),

    (2, 2, '2025-11-01', 'Presente', 'Atenta y participativa'),
    (2, 2, '2025-11-02', 'Ausente', 'Sin aviso');

ALTER TABLE notas ADD CONSTRAINT fk_notas_alumno
FOREIGN KEY (id_alumno) REFERENCES alumnos(id_alumno);

ALTER TABLE notas ADD CONSTRAINT fk_notas_materia
FOREIGN KEY (id_materia) REFERENCES materias(id_materia);

ALTER TABLE asistencias ADD CONSTRAINT fk_asistencias_alumno
FOREIGN KEY (id_alumno) REFERENCES alumnos(id_alumno);

ALTER TABLE asistencias ADD CONSTRAINT fk_asistencias_materia
FOREIGN KEY (id_materia) REFERENCES materias(id_materia);

SELECT 
    a.nombre_alumno,
    m.nombre_materia,
    n.nota,
    n.tipo_evaluacion,
    asis.fecha,
    asis.estado
FROM notas n
JOIN alumnos a ON n.id_alumno = a.id_alumno
JOIN materias m ON n.id_materia = m.id_materia
LEFT JOIN asistencias asis 
    ON a.id_alumno = asis.id_alumno AND m.id_materia = asis.id_materia
ORDER BY a.nombre_alumno, m.nombre_materia, asis.fecha
