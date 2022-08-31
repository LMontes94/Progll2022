/*
5) Con seis habitaciones repartidas en tres plantas, un hotel familiar abre sus puertas para
recibir turistas acaudalados.
El propietario necesita un sistema que le permita formular el checkin de las personas,
para lo cual le interesa identificar quién se aloja en qué habitación, el número de reserva
asociado y cantidad que días se hospedará.
También, porque a veces ocurre que las habitaciones no resultan del interés del turista,
necesita poder mover de una habitación a la otra a las personas y que eso se refleje en el
sistema.
Como todo sistema hotelero, este debe poder gestionar el checkout e imprimir por
pantalla los huéspedes.
*/

#include <iostream>

using namespace std;

#define CANT_PISOS 3
#define CANT_HABITACIONES_X_PISO 2
#define MAX_CANT_RESERVAS CANT_PISOS *CANT_HABITACIONES_X_PISO

struct ST_HABITACIONES
{
    int cantPersonas;
    bool ocupada = false;
};

struct ST_RESERVA
{
    int idReserva = 0;
    string nombre;
    int habitacion;
    int cantPersonas;
    int cantDias;
};

void disponibilidadHabitacion(ST_HABITACIONES hotel[CANT_PISOS][CANT_HABITACIONES_X_PISO], bool &hayDisponibilidad);
void cargaDeDatos(ST_RESERVA reservacion);
void reservaHabitacion(ST_HABITACIONES hotel[CANT_PISOS][CANT_HABITACIONES_X_PISO], int nroHabitacion);
void hacerReserva(char reserva, ST_RESERVA reservas[CANT_PISOS * CANT_HABITACIONES_X_PISO], ST_HABITACIONES hotel[CANT_PISOS][CANT_HABITACIONES_X_PISO]);
void cargarReserva(ST_RESERVA reserva[CANT_PISOS * CANT_HABITACIONES_X_PISO], ST_RESERVA persona);
void checkIn(ST_RESERVA reserva[CANT_PISOS * CANT_HABITACIONES_X_PISO]);
void checkOut(ST_RESERVA reserva[CANT_PISOS * CANT_HABITACIONES_X_PISO]);
void menu(int &opcion);
void imprimirReservas(ST_RESERVA reserva[CANT_PISOS * CANT_HABITACIONES_X_PISO]);
int main()
{

    ST_HABITACIONES hotel[CANT_PISOS][CANT_HABITACIONES_X_PISO];
    ST_RESERVA reservacion[CANT_PISOS * CANT_HABITACIONES_X_PISO];
    char reserva;
    int opcion = 0;

    while (opcion != 5)
    {
        menu(opcion);
        switch (opcion)
        {
        case 1:
            cout << "Hacer Reserva: [S/N]" << endl;
            cin >> reserva;

            hacerReserva(reserva, reservacion, hotel);
            break;
        case 2:
            checkIn(reservacion);
            break;
        case 3:
            checkOut(reservacion);
            break;
        case 4:
            imprimirReservas(reservacion);
            break;
        default:
            cout << "Opcion incorrecta...." << endl;
            break;
        }
    }

    cout << "Cerrando programa...." << endl;

    return 0;
}

void menu(int &opcion)
{
    cout << "     HOTEL FAMILIAR" << endl;
    cout << "-------------------------" << endl;
    cout << "Seleccione una opcion, ingresando el nro." << endl;
    cout << "1-Reserva" << endl;
    cout << "2-Checkin" << endl;
    cout << "3-Checkout" << endl;
    cout << "4-Mostrar todos los huespedes" << endl;
    cout << "5-Salir" << endl;
    cin >> opcion;
    cout << "-------------------------" << endl;
    return;
}
void cargaDeDatos(ST_RESERVA reservacion)
{
    cout << "Ingrese su nombre: " << endl;
    cin >> reservacion.nombre;

    cout << "Cantidad de personas: " << endl;
    cin >> reservacion.cantPersonas;

    cout << "Cantidad de dias: " << endl;
    cin >> reservacion.cantDias;

    return;
}
void disponibilidadHabitacion(ST_HABITACIONES hotel[CANT_PISOS][CANT_HABITACIONES_X_PISO], bool &hayDisponibilidad)
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; i < 2; j++)
        {
            if (!hotel[i][j].ocupada)
            {
                cout << "La Habitacion " << i << "esta disponible" << endl;
                hayDisponibilidad = true;
            }
        }
    }
    return;
}
void reservaHabitacion(ST_HABITACIONES hotel[CANT_PISOS][CANT_HABITACIONES_X_PISO], int nroHabitacion)
{

    for (int i = 0; i < CANT_PISOS; i++)
    {
        for (int j = 0; j < CANT_HABITACIONES_X_PISO; j++)
        {
            if (nroHabitacion == j)
            {
                hotel[i][j].ocupada = true;
                return;
            }
        }
    }
}
void hacerReserva(char reserva, ST_RESERVA reservas[CANT_PISOS * CANT_HABITACIONES_X_PISO], ST_HABITACIONES hotel[CANT_PISOS][CANT_HABITACIONES_X_PISO])
{
    ST_RESERVA persona;
    bool hayDisponibilidad = false;
    if (reserva == 's' || reserva == 'S')
    {
        cargaDeDatos(persona);
        disponibilidadHabitacion(hotel, hayDisponibilidad);

        if (hayDisponibilidad)
        {
            cout << "----------------------------------------------------" << endl;
            cout << "seleccione alguna de las habitaciones disponibles" << endl;
            cin >> persona.habitacion;
            reservaHabitacion(hotel, persona.habitacion);
            if (persona.idReserva < 7)
            {
                persona.idReserva++;
            }
            else
            {
                persona.idReserva = 0;
                persona.idReserva++;
            }

            cargarReserva(reservas, persona);
        }
        else
        {
            cout << "----------------------------------------------------" << endl;
            cout << "No hay habitaciones libres.";
        }
    }
    else
    {
        cout << "----------------------------------------------------" << endl;
        cout << "Nos vimos...!!";
    }
}
void cargarReserva(ST_RESERVA reserva[CANT_PISOS * CANT_HABITACIONES_X_PISO], ST_RESERVA persona)
{
    reserva[persona.idReserva - 1] = persona;
    return;
}
void checkIn(ST_RESERVA reserva[CANT_PISOS * CANT_HABITACIONES_X_PISO])
{

    int nroReserva;
    cout << "Ingrese su Nro de Reserva para hacer el checkin: " << endl;
    cin >> nroReserva;
    while (nroReserva > MAX_CANT_RESERVAS)
    {
        cout << "Ingreso mal su numero de reserva.... " << endl;
        cout << "-------------------------------------" << endl;
        cout << "Ingrese su Nro de Reserva para hacer el checkin: " << endl;
        cin >> nroReserva;
        cout << "-------------------------------------" << endl;
    }

    cout << "Check IN" << endl;
    cout << "Id Reserva: " << reserva[nroReserva - 1].idReserva;
    cout << "Nombre: " << reserva[nroReserva - 1].nombre << endl;
    cout << "Cantidad de dias que se quedara en el hotel: " << reserva[nroReserva - 1].cantDias;

    return;
}
void checkOut(ST_RESERVA reserva[CANT_PISOS * CANT_HABITACIONES_X_PISO])
{
    int nroReserva;
    cout << "Ingrese su Nro de Reserva para hacer el checkOut: " << endl;
    cin >> nroReserva;
    while (nroReserva > MAX_CANT_RESERVAS)
    {
        cout << "Ingreso mal su numero de reserva.... " << endl;
        cout << "-------------------------------------" << endl;
        cout << "Ingrese su Nro de Reserva para hacer el checkOut: " << endl;
        cin >> nroReserva;
        cout << "-------------------------------------" << endl;
    }

    cout << "Check OUT" << endl;
    cout << "Id Reserva: " << reserva[nroReserva - 1].idReserva;
    cout << "Nombre: " << reserva[nroReserva - 1].nombre << endl;
    cout << "Cantidad de dias que se quedara en el hotel: " << reserva[nroReserva - 1].cantDias;

    return;
}
void imprimirReservas(ST_RESERVA reserva[CANT_PISOS * CANT_HABITACIONES_X_PISO])
{

    for (int i = 0; i < MAX_CANT_RESERVAS; i++)
    {
        cout << "----------------------------------" << endl;
        cout << "Id Reserva: " << reserva[i].idReserva << endl;
        cout << "Nombre: " << reserva[i].nombre << endl;
        cout << "Cantidad de dias que se quedara en el hotel: " << reserva[i].cantDias << endl;
    }

    return;
}
