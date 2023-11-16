CREATE TABLE habitacion (
    IdHabitacion INT NOT NULL PRIMARY KEY,
    tipo VARCHAR(50),
    precio DECIMAL(10, 2),
    estado VARCHAR(50)
);

CREATE TABLE cliente (
    IdCliente BIGINT NOT NULL PRIMARY KEY,
    nombre VARCHAR(50),
    apellido VARCHAR(50),
    email VARCHAR(100),
    telefono VARCHAR(20)
);


CREATE TABLE reservacion (
    IdReservacion INT AUTO_INCREMENT PRIMARY KEY,
    IdHabitacion INT,
    IdCliente BIGINT,
    fecha_ingreso DATE,
    fecha_salida DATE,
    estado VARCHAR(50),
    FOREIGN KEY (IdHabitacion) REFERENCES habitacion(IdHabitacion),
    FOREIGN KEY (IdCliente) REFERENCES cliente(IdCliente)
);


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

insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1035296865018, 'Brooks', 'Gallienne', 'bgallienne0@google.ru', '6246010110');
insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1256121534882, 'Almire', 'Clubley', 'aclubley1@icio.us', '4568962982');
insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1160491750810, 'Shandra', 'Capeling', 'scapeling2@xing.com', '6911455825');
insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1322099965297, 'Maxim', 'Stevens', 'mstevens3@deliciousdays.com', '9607386802');
insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1204801458366, 'Kathy', 'Zoane', 'kzoane4@chron.com', '6047976695');
insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1093170441173, 'Erny', 'Laurence', 'elaurence5@auda.org.au', '1234184388');
insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1076801627472, 'Reagan', 'Tash', 'rtash6@reuters.com', '7692133669');
insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1393952850586, 'Bartie', 'Pendrigh', 'bpendrigh7@irs.gov', '8523473997');
insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1147730524675, 'Julita', 'Paolinelli', 'jpaolinelli8@tiny.cc', '7642738306');
insert into cliente (IdCLiente, nombre, apellido, email, telefono) values (1057845557885, 'Carly', 'Dinsmore', 'cdinsmore9@mtv.com', '8593464149');

-- Obtener la fecha actual en formato yyyy-mm-dd
SET @fecha_actual = CURDATE();

-- Insertar reservaciones con fechas realistas
INSERT INTO reservacion (IdHabitacion, IdCliente, fecha_ingreso, fecha_salida, estado)
VALUES
    (1, 1035296865018, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 3 DAY), 'Confirmada'),
    (2, 1256121534882, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 5 DAY), 'Confirmada'),
    (3, 1160491750810, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 7 DAY), 'Confirmada'),
    (4, 1322099965297, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 10 DAY), 'Confirmada'),
    (5, 1204801458366, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 14 DAY), 'Confirmada'),
    (6, 1093170441173, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 16 DAY), 'Confirmada'),
    (7, 1076801627472, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 20 DAY), 'Confirmada'),
    (8, 1393952850586, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 22 DAY), 'Confirmada'),
    (9, 1147730524675, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 25 DAY), 'Confirmada'),
    (10, 1057845557885, @fecha_actual, DATE_ADD(@fecha_actual, INTERVAL 30 DAY), 'Confirmada');