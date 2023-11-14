CREATE TABLE habitacion (
    IdHabitacion INT NOT NULL PRIMARY KEY,
    tipo VARCHAR(50),
    precio DECIMAL(10, 2),
    estado VARCHAR(50)
);

CREATE TABLE cliente (
    IdCliente INT NOT NULL PRIMARY KEY,
    nombre VARCHAR(50),
    apellido VARCHAR(50),
    email VARCHAR(100),
    telefono VARCHAR(20)
);


CREATE TABLE reservacion (
    IdReservacion INT PRIMARY KEY,
    IdHabitacion INT,
    IdCliente INT,
    fecha_ingreso DATE,
    fecha_salida DATE,
    estado VARCHAR(50),
    FOREIGN KEY (IdHabitacion) REFERENCES habitacion(IdHabitacion),
    FOREIGN KEY (IdCliente) REFERENCES cliente(IdCliente)
);

ALTER TABLE reservacion
MODIFY COLUMN IdReservacion INT AUTO_INCREMENT;


INSERT INTO habitacion (IdHabitacion, tipo, precio, estado)
VALUES
    (1, 'Individual', 100.00, 'Disponible'),
    (2, 'Doble', 150.00, 'Disponible'),
    (3, 'Suite', 200.00, 'Disponible'),
    (4, 'Doble', 150.00, 'Disponible'),
    (5, 'Individual', 100.00, 'Disponible'),
    (6, 'Suite', 200.00, 'Disponible'),
    (7, 'Doble', 150.00, 'Disponible'),
    (8, 'Individual', 100.00, 'Disponible'),
    (9, 'Doble', 150.00, 'Disponible'),
    (10, 'Suite', 200.00, 'Disponible');


INSERT INTO cliente (IdCliente, nombre, apellido, email, telefono)
VALUES
    (1, 'María', 'González', 'maria.gonzalez@email.com', '555-123-4567'),
    (2, 'Juan', 'Pérez', 'juan.perez@email.com', '555-987-6543'),
    (3, 'Carlos', 'Rodríguez', 'carlos.rodriguez@email.com', '555-456-7890'),
    (4, 'Laura', 'López', 'laura.lopez@email.com', '555-321-0987'),
    (5, 'Javier', 'Gómez', 'javier.gomez@email.com', '555-789-0123');


INSERT INTO reservacion (IdReservacion, IdHabitacion, IdCliente, fecha_ingreso, fecha_salida, estado)
VALUES
    (1, 3, 2, '2023-01-10', '2023-01-15', 'Confirmada'),
    (2, 1, 4, '2023-02-05', '2023-02-10', 'Confirmada'),
    (3, 2, 1, '2023-03-20', '2023-03-25', 'Confirmada'),
    (4, 4, 3, '2023-04-15', '2023-04-18', 'Cancelada'),
    (5, 5, 5, '2023-05-01', '2023-05-05', 'Cancelada');

CREATE VIEW verReservas AS
SELECT
    r.IdReservacion AS Reservacion,
    r.IdHabitacion AS Habitacion,
    c.nombre AS Cliente,
    r.fecha_ingreso AS FechaIngreso,
    r.fecha_salida AS FechaSalida,
    r.estado AS Estado
FROM
    reservacion r
JOIN
    cliente c ON r.IdCliente = c.IdCliente;


CREATE VIEW verCliente AS
SELECT
    r.IdReservacion AS Reservacion,
    r.IdHabitacion AS Habitacion,
    c.IdCliente AS Dpi,
    c.nombre AS Cliente,
    r.fecha_ingreso AS FechaIngreso,
    r.fecha_salida AS FechaSalida,
    r.estado
FROM
    reservacion r
JOIN
    cliente c ON r.IdCliente = c.IdCliente;


CREATE VIEW verFactura AS
SELECT
    r.IdReservacion AS Reservacion,
    c.nombre AS Nombre,
    c.apellido AS Apellido,
    h.tipo AS TipoHabitacion,
    h.precio AS PrecioHabitacion
FROM
    reservacion r
JOIN
    cliente c ON r.IdCliente = c.IdCliente
JOIN
    habitacion h ON r.IdHabitacion = h.IdHabitacion
WHERE
    r.estado = 'Confirmada';



