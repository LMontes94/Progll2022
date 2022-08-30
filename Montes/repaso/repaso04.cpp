/*
4)El empleado administrativo de una empresa atiende durante su jornada laboral a una
indeterminada cantidad de personas; todas ellas deben indicar su nombre y número de
legajo para ser atendidos.
Todos los días al terminar el turno, se informa quién fue la primera persona en ser
atendida, quien poseía el legajo más bajo, la cantidad total de personas y cuántas
personas fueron atendidas por tipo de trámite; los empleados suelen acercarse a la
administración por temas relacionados al salario, vacaciones y cobertura médica.
*/

#include <iostream>
using namespace std;

struct ST_CLIENTE
{
    string nombre;
    int legajo;
    char tipoTramite;
};

void tramite(char tipoTramite, int &tramiteSalario, int &tramiteVacaciones, int &tramiteCobMedica);
ST_CLIENTE menorLegajo(int legajo, string nombre, char tipoTramite);
ST_CLIENTE primerAtendido(int legajo, string nombre, char tipoTramite, bool &primero);
int main()
{
    string nombre;
    int legajo;
    char tipoTramite;
    ST_CLIENTE primeroAtendido;
    ST_CLIENTE minLegajo;
    int cantTotal = 0;
    int tramiteSalario = 0;
    int tramiteVacaciones = 0;
    int tramiteCobMedica = 0;
    int i = 0;
    char finTurno;
    bool primero = false;

    cout << "Termino su turno? " << endl;
    cin >> finTurno;
    while (finTurno != 's')
    {
        cout << "Ingrese el nombre: " << endl;
        cin >> nombre;

        cout << "Ingrese el nro de legajo: " << endl;
        cin >> legajo;

        cout << "Tipo de tramite (Ingrese 'S', si es por salario, 'V' por vacaciones o 'C' por cobertura medica: ):" << endl;
        cin >> tipoTramite;

        primeroAtendido = primerAtendido(legajo,nombre,tipoTramite,primero);
        minLegajo = menorLegajo(legajo, nombre, tipoTramite);
        tramite(tipoTramite, tramiteSalario, tramiteVacaciones, tramiteCobMedica);

        cantTotal++;
        cout << "Termino su turno? " << endl;
        cin >> finTurno;
        i++;
    }
    cout << endl;
    cout << "-------------------------------------" << endl;
    cout << "Primer persona antendida:  " << primeroAtendido.nombre << primeroAtendido.legajo << endl;
    cout << "Legajo mas bajo: " << minLegajo.legajo << minLegajo.nombre << endl;
    cout << "Total de personas: " << cantTotal << endl;
    cout << "Personas que fueron atendidas por trámite:  " << endl;
    cout << "Salario: " << tramiteSalario << endl;
    cout << "Vacaciones: " << tramiteVacaciones << endl;
    cout << "Cobertura medica: " << tramiteCobMedica << endl;
    system("pause");
    return 0;
}

ST_CLIENTE menorLegajo(int legajo, string nombre, char tipoTramite)
{

    ST_CLIENTE minLegajo;
    minLegajo.legajo = 0;
    if (minLegajo.legajo < legajo || minLegajo.legajo == 0)
    {
        minLegajo.nombre = nombre;
        minLegajo.legajo = legajo;
        minLegajo.legajo = tipoTramite;
    }
    return minLegajo;
}

void tramite(char tipoTramite, int &tramiteSalario, int &tramiteVacaciones, int &tramiteCobMedica)
{
    if (tipoTramite == 's' || tipoTramite == 'S')
    {
        tramiteSalario++;
    }
    else if (tipoTramite == 'v' || tipoTramite == 'V')
    {
        tramiteVacaciones++;
    }
    else
    {
        tramiteCobMedica++;
    }
    return;
}

ST_CLIENTE primerAtendido(int legajo, string nombre, char tipoTramite, bool &primero)
{
    ST_CLIENTE primeroAtendido;
    if (primero == false)
    {
        primeroAtendido.nombre = nombre;
        primeroAtendido.legajo = legajo;
        primeroAtendido.tipoTramite = tipoTramite;
        primero = true;
    }
    return primeroAtendido;
}