
/*Menú ManejoHabitaciones*/

/*función verHabitacionesDisponibles();*/
    SELECT IdHabitacion, tipo, precio, estado FROM habitacion WHERE estado = 'Disponible';
/*función verHabitacionesOcupadas();*/
    SELECT IdHabitacion, tipo, precio, estado FROM habitacion WHERE estado = 'Ocupado';
/*función verHabitacionesEnMantenimiento();*/
    SELECT IdHabitacion, tipo, precio, estado FROM habitacion WHERE estado = 'En mantenimiento';
/*ModificarEstadoHabitacion();*/
    /*Verifica habitación seleccionada:*/
    SELECT * FROM habitacion WHERE IdHabitacion = '';
    /*Realiza el cambio*/
    UPDATE habitacion SET estado = '' WHERE IdHabitacion = '';


/*Menú ManejoCLientes*/

/*función  verClientes();*/
    SELECT IdCliente, nombre, apellido, email, telefono FROM cliente;
/*función agregaCliente();*/
    /*verifica el DPI(IdCliente)*/
    SELECT * FROM cliente WHERE IdCLiente = '';
    /*inserta*/
    INSERT INTO cliente (IdCliente, nombre, apellido, email, telefono) VALUES ('','','','','');
/*función eliminarCliente();*/
    /*verifica el DPI(IdCliente)*/
    SELECT * FROM cliente WHERE IdCLiente = '';
    /*elimina*/
    DELETE FROM cliente WHERE IdCliente = '';
/*función actualizarCliente();*/
    /*verifica el DPI(IdCliente)*/
    SELECT * FROM cliente WHERE IdCLiente = '';
    /*actualiza*/
    UPDATE cliente SET nombre = '', apellido '', email= '', telefono = '' WHERE IdCliente = '';


/*Menú ManejoReservaciones*/

/*función consultarReservasHabitacion();*/
    /*verifica la habitación(IdHabitacion)*/
    SELECT * FROM habitacion WHERE IdHabitacion = '';
    /*selecciona*/
    SELECT Reservacion, Habitacion, cliente, FechaIngreso, FechaSalida, Estado FROM verReservas WHERE Habitacion = '';
/*función verReservacionesFechaEspecifica();*/
    SELECT Reservacion, Habitacion, cliente, FechaIngreso, FechaSalida, Estado FROM verReservas WHERE DATE(FechaIngreso) = '';
/*función verReservacionesConfirmadasFecha();*/
    SELECT Reservacion, Habitacion, cliente, FechaIngreso, FechaSalida, Estado FROM verReservas WHERE DATE(FechaIngreso) = '' AND Estado = 'Confirmada';
/*función reservacionesClientesPorId();*/
    /*verifica el DPI(IdCliente)*/
    SELECT * FROM verCliente WHERE Dpi = '';
/*función agregarReservacion();*/
    /*verifica la habitación(IdHabitacion)*/
    SELECT * FROM habitacion WHERE IdHabitacion = '';
    /*Inserta*/
    INSERT INTO reservacion (IdHabitacion, IdCliente, fecha_ingreso, fecha_salida, estado) VALUES ('','','','','');
/*función actualizarReservacion();*/
    /*verifica la reservacion(IdReservacion)*/
    SELECT * FROM reservacion WHERE IdReservacion = '';
    /*actualiza*/
    UPDATE reservacion SET fecha_ingreso = '', fecha_salida = '' WHERE IdReservacion = '';
/*función cancelarReservacion();*/
    /*verifica la reservacion(IdReservacion)*/
    SELECT * FROM reservacion WHERE IdReservacion = '';
    /*actualiza*/
    UPDATE reservacion SET estado = 'Cancelada' WHERE IdReservacion = '';
/*función generarFactura();*/
   /*verifica la reservacion(IdReservacion)*/
    SELECT * FROM reservacion WHERE IdReservacion = '';
   /*selección*/
   SELECT * FROM verFactura WHERE Reservacion = '';
