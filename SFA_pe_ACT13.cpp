// Sergio Fabian Aguiar Matricula: 374317
// DESCRIP:
// SFA_PE_ACT12
// Fecha:17/05/2024 Ultima modificacion:20/05/2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_REGISTROS 5000
#define MAX_NOMBRE 34

typedef struct 
{
    char valido;   // S->Válido, N->Inválido
    int matricula; // Campo llave, no repetido
    char nombre[MAX_NOMBRE];
    int dato[4];
} Empleado;

Empleado empleados[MAX_REGISTROS];
int num_registros = 0;
bool archivo_binario_cargado = false;

int Menu();
void Agregar();
void EditarRegistro();
void EliminarRegistro();
void BuscarRegistro();
void OrdenarRegistros();
void ImprimirRegistros();
void GenerarArchivoTexto();
void MostrarArchivoTexto();
void CrearArchivoBinario();
void CargarArchivoBinario();
void MostrarEliminados();
long LeeNumero();
int BuscarMatricula(int matricula);
void MostrarRegistro(Empleado *reg);
void Listar(long n, Empleado *reg);


int main()
{

    FILE *fa;
    int opcion;
    long numero;
    fa = fopen("alea.dat", "r+b"); // Este modo permite leer y escribir
    if (!fa)
        fa = fopen("alea.dat", "w+b"); // si el fichero no existe, lo crea.pcion;
    do
    {
        opcion = Menu();
        switch (opcion)
        {
        case 1:
            Agregar();
            break;
        case 2:
            EditarRegistro();
            break;
        case 3:
            break;
        case 4:
            BuscarRegistro();
            break;
        case 5:
            OrdenarRegistros();
            break;
        case 6:
            ImprimirRegistros();
            break;
        case 7:
            GenerarArchivoTexto();
            break;
        case 8:
            MostrarArchivoTexto();
            break;
        case 9:
            CrearArchivoBinario();
            break;
        case 10:
            CargarArchivoBinario();
            break;
        case 11:
            MostrarEliminados();
            break;
        }
    } while (opcion != 0);
    return 0;
}

int Menu()
{
    int opcion;
    do
    {
        system("cls");
        printf("MENU PRINCIPAL\n");
        printf("--------------\n\n");
        printf("1- AGREGAR\n");
        printf("2- EDITAR REGISTRO\n");
        printf("3- ELIMINAR REGISTRO\n");
        printf("4- BUSCAR\n");
        printf("5- ORDENAR\n");
        printf("6- IMPRIMIR\n");
        printf("7- GENERAR ARCHIVO TEXTO\n");
        printf("8- VER ARCHIVO DE TEXTO\n");
        printf("9- CREAR ARCHIVO BINARIO\n");
        printf("10- CARGAR ARCHIVO BINARIO\n");
        printf("11- MOSTRAR ELIMINADOS\n");
        printf("0- Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
    } while (opcion < 0 || opcion > 11);
    return opcion;
}

void Agregar()
{
    if (num_registros + 100 > MAX_REGISTROS)
    {
    printf("No hay espacio suficiente para agregar 100 registros.\n");
    return;
    }
    for (int i = 0; i < 100; i++)
    {
    empleados[num_registros].valido = 'S';
    empleados[num_registros].matricula = num_registros + 1; 
    snprintf(empleados[num_registros].nombre, MAX_NOMBRE, "Empleado%d", num_registros + 1);
    for (int j = 0; j < 4; j++)
    {
    empleados[num_registros].dato[j] = rand() % 100; // Datos aleatorios
    }
    num_registros++;
    }
    printf("100 registros agregados.\n");
}

void EditarRegistro()
{
    int matricula;
    printf("Ingrese la matricula del registro a editar: ");
    scanf("%d", &matricula);
    int index = BuscarMatricula(matricula);
    if (index == -1)
    {
        printf("Registro no encontrado.\n");
        return;
    }
    Empleado *emp = &empleados[index];
    MostrarRegistro(emp);
    printf("Que campo desea editar? (1-Nombre, 2-Dato1, 3-Dato2, 4-Dato3, 5-Dato4): ");
    int opcion;
    scanf("%d", &opcion);
    getchar(); // Limpiar el buffer
    switch (opcion)
    {
    case 1:
        printf("Ingrese nuevo nombre: ");
        fgets(emp->nombre, MAX_NOMBRE, stdin);
        strtok(emp->nombre, "\n"); // Eliminar salto de línea
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        printf("Ingrese nuevo dato %d: ", opcion - 1);
        scanf("%d", &emp->dato[opcion - 2]);
        break;
    default:
        printf("Opcion invalida.\n");
        break;
    }
    printf("Registro editado.\n");
}

void EliminarRegistro()
{
    int matricula;
    printf("Ingrese la matricula del registro a eliminar: ");
    scanf("%d", &matricula);
    int index = BuscarMatricula(matricula);
    if (index == -1)
    {
    printf("Registro no encontrado.\n");
    return;
    }
    empleados[index].valido = 'N';
    printf("Registro eliminado.\n");
}

void BuscarRegistro()
{
    int matricula;
    printf("Ingrese la matricula del registro a buscar: ");
    scanf("%d", &matricula);
    int index = BuscarMatricula(matricula);
    if (index == -1)
    {
    printf("Registro no encontrado.\n");
    return;
    }
    MostrarRegistro(&empleados[index]);
}

void OrdenarRegistros()
{
    // Implementar ordenación por campo llave (matricula)
    for (int i = 0; i < num_registros - 1; i++)
    {
        for (int j = 0; j < num_registros - i - 1; j++)
        {
            if (empleados[j].matricula > empleados[j + 1].matricula)
            {
            Empleado temp = empleados[j];
            empleados[j] = empleados[j + 1];
            empleados[j + 1] = temp;
            }
        }
    }
    printf("Registros ordenados.\n");
}

void ImprimirRegistros()
{
    printf("Nombre                Datos\n");
    for (int i = 0; i < num_registros; i++)
    {
    if (empleados[i].valido == 'S')
    {
    Listar(i, &empleados[i]);
    }
    }
}

void GenerarArchivoTexto()
{
    char nombre_archivo[50];
    printf("Ingrese el nombre del archivo (sin extension): ");
    scanf("%s", nombre_archivo);
    strcat(nombre_archivo, ".txt");
    FILE *file = fopen(nombre_archivo, "w");
    if (!file)
    {
    printf("No se pudo crear el archivo.\n");
    return;
    }
    for (int i = 0; i < num_registros; i++)
    {
    if (empleados[i].valido == 'S')
    {
    fprintf(file, "Matricula: %d, Nombre: %s, Datos: %d %d %d %d\n",
    empleados[i].matricula, empleados[i].nombre,
    empleados[i].dato[0], empleados[i].dato[1],
    empleados[i].dato[2], empleados[i].dato[3]);
    }
    }
    fclose(file);
    printf("Archivo de texto generado.\n");
}

void MostrarArchivoTexto()
{
    char nombre_archivo[50];
    printf("Ingrese el nombre del archivo (sin extension): ");
    scanf("%s", nombre_archivo);
    strcat(nombre_archivo, ".txt");
    FILE *file = fopen(nombre_archivo, "r");
    if (!file)
    {
    printf("No se pudo abrir el archivo.\n");
    return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
    printf("%s", line);
    }
    fclose(file);
}

void CrearArchivoBinario()
{
    char nombre_archivo[50];
    printf("Ingrese el nombre del archivo binario (sin extension): ");
    scanf("%s", nombre_archivo);
    strcat(nombre_archivo, ".dat");
    FILE *file = fopen(nombre_archivo, "wb");
    if (!file)
    {
    printf("No se pudo crear el archivo.\n");
    return;
    }
    fwrite(empleados, sizeof(Empleado), num_registros, file);
    fclose(file);
    printf("Archivo binario generado.\n");
}

void CargarArchivoBinario()
{
    if (archivo_binario_cargado)
    {
    printf("El archivo binario ya ha sido cargado una vez.\n");
    return;
    }
    char nombre_archivo[50];
    printf("Ingrese el nombre del archivo binario (sin extension): ");
    scanf("%s", nombre_archivo);
    strcat(nombre_archivo, ".dat");
    FILE *file = fopen(nombre_archivo, "rb");
    if (!file)
    {
    printf("No se pudo abrir el archivo.\n");
    return;
    }
    num_registros = fread(empleados, sizeof(Empleado), MAX_REGISTROS, file);
    fclose(file);
    archivo_binario_cargado = true;
    printf("Archivo binario cargado.\n");
}

void MostrarEliminados()
{
    printf("Registros eliminados:\n");
    for (int i = 0; i < num_registros; i++)
    {
    if (empleados[i].valido == 'N')
    {
    MostrarRegistro(&empleados[i]);
    }
    }
}

long LeeNumero()
{
    long num;
    scanf("%ld", &num);
    getchar(); // Limpiar el buffer
    return num;
}

int BuscarMatricula(int matricula)
{
    for (int i = 0; i < num_registros; i++)
    {
    if (empleados[i].matricula == matricula)
    {
    return i;
    }
    }
    return -1; // No encontrado
}

void MostrarRegistro(Empleado *reg)
{
    printf("Matricula: %d\n", reg->matricula);
    printf("Nombre: %s\n", reg->nombre);
    printf("Datos: %d %d %d %d\n", reg->dato[0], reg->dato[1], reg->dato[2], reg->dato[3]);
}

void Listar(long n, Empleado *reg)
{
    if (reg->valido == 'S')
    {
    printf("%-34s %d %d %d %d\n", reg->nombre, reg->dato[0], reg->dato[1], reg->dato[2], reg->dato[3]);
    }
}
