#include "pablo.h"

#define MAX_USER 32
#define MAX_DOC 48
#define MAX_JOBS 10

typedef enum
{
    NORMAL = 0,
    URGENTE = 1
} Prioridad_t;

typedef enum
{
    EN_COLA = 0,
    IMPRIMIENDO = 1,
    COMPLETADO = 2,
    CANCELADO = 3,
} Estado_t;

typedef struct
{
    int id;                  // autoincremental
    char usuario[MAX_USER];  // quien imprime
    char documento[MAX_DOC]; // nombre del documento
    int paginas_total;       // total de paginas
    int paginas_restantes;   // para simular progreso
    int copias;              // opcional (>=1)
    Estado_t estado;         // en cola/imprimiendo/...
    Prioridad_t prioridad;
    // int ms_por_pagina; opcional para simulacion
} PrintJob_t;

typedef struct
{
    PrintJob_t data[MAX_JOBS];
    int size; // cantidad actual de elementos
} QueueStatic_t;


void menu();
int msg();
void qs_init(QueueStatic_t *q);
int qs_is_empty(const QueueStatic_t *q);
int qs_is_full(const QueueStatic_t *q);
PrintJob_t qs_job(int *id);
int qs_enqueue(QueueStatic_t *q, PrintJob_t job);
int qs_peek(const QueueStatic_t *q, PrintJob_t *out);
int qs_dequeue(QueueStatic_t *q, PrintJob_t *out);
void qs_print(const QueueStatic_t *q);
void qs_out(const PrintJob_t job);
void qs_encabezado();

int main()
{
    menu();
    return 0;
}

int msg()
{
    system("CLS");
    printf("(1) Agregar Trabajo\n");
    printf("(2) ver siguiente trabajo\n");
    printf("(3) Procesar Trabajo\n");
    printf("(4) Listar Cola\n");
    printf("(5) Salir\n");
    return valida_int(1, 5, "Seleccione una opcion: ");
}

void menu()
{
    PrintJob_t out;
    QueueStatic_t q[10];
    qs_init(q);
    int id = 1;
    int op;

    do
    {
        op = msg();
        system("CLS");
        switch (op)
        {
        case 1:
            if (!qs_is_full(q))
            {
                qs_enqueue(q, qs_job(&id));
                printf("Trabajo agregado a la cola.\n");
                system("PAUSE");
            }
            else
            {
                printf("La cola esta llena\n");
                system("PAUSE");
            }
            break;
        case 2:
            if (!qs_is_empty(q))
            {
                qs_peek(q, &out);
                qs_encabezado();
                qs_out(out);
                system("PAUSE");
            }
            else
            {
                printf("La cola esta vacia\n");
                system("PAUSE");
            }
            break;
        case 3:
            if (!qs_is_empty(q))
            {
                qs_dequeue(q, &out);
                printf("SALIDA\n");
                qs_encabezado();
                qs_out(out);
                system("PAUSE");
            }
            else
            {
                printf("La cola esta vacia\n");
                system("PAUSE");
            }
            break;
        case 4:
            if (!qs_is_empty(q))
            {
                qs_print(q);
            }
            else
            {
                printf("La cola esta vacia\n");
                system("PAUSE");
            }
            break;
        }
    } while (op != 5);
}

PrintJob_t qs_job(int *id)
{
    PrintJob_t job;
    printf("Introduzca el usuario: ");
    my_gets(job.usuario, MAX_USER);
    printf("Introduzca el nombre del documento: ");
    my_gets(job.documento, MAX_DOC);
    job.paginas_restantes = 0;
    job.estado = EN_COLA;
    job.prioridad = NORMAL;
    job.id = *id;
    (*id)++;
    system("CLS");
    job.paginas_total = valida_int(1, 9999, "Introduzca el numero de paginas del documento(MAX 10000): ");
    job.copias = valida_int(1, 999, "Introduzca la cantidad de copias del documento(MAx 1000)");
    job.paginas_restantes = job.paginas_total * job.copias;
    return job;
}

int qs_enqueue(QueueStatic_t *q, PrintJob_t job)
{
    if (q->size == MAX_JOBS)
    {
        return 0; // cola llena
    }

    q->data[q->size] = job;
    q->size++;
    return 1;
}

int qs_peek(const QueueStatic_t *q, PrintJob_t *out)
{
    if (q->size == 0)
    {
        return 0;
    }
    *out = q->data[0];
    return 1;
}

int qs_dequeue(QueueStatic_t *q, PrintJob_t *out)
{
    if (q->size == 0)
        return 0; // cola vacia

    *out = q->data[0];
    out->estado = COMPLETADO;

    for (int i = 1; i < q->size; i++)
    {
        q->data[i - 1] = q->data[i]; // desplazar hacia la izquierda
    }
    q->size--;
    return 1;
}

void qs_init(QueueStatic_t *q)
{
    q->size = 0;
}

int qs_is_empty(const QueueStatic_t *q)
{
    if (q->size == 0)
    {
        return 1;
    }
    return 0;
}

int qs_is_full(const QueueStatic_t *q)
{
    if (q->size == MAX_JOBS)
    {
        return 1;
    }

    return 0;
}

void qs_print(const QueueStatic_t *q)
{
    int i = 0;
    qs_encabezado();
    while (i < q->size || i < q->size)
    {
        qs_out(q->data[i]);
        i++;
    }
    system("PAUSE");
}

void qs_out(const PrintJob_t job)
{
    printf("| %-3d | %-15s | %-20s | %-6d | %-6d | %-6d | %-12d | %-10d |\n",
           job.id,
           job.usuario,
           job.documento,
           job.paginas_total,
           job.paginas_restantes,
           job.copias,
           job.estado,
           job.prioridad);
}

void qs_encabezado()
{
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-15s | %-20s | %-6s | %-6s | %-6s | %-12s | %-10s |\n",
           "ID", "USUARIO", "DOCUMENTO", "TOT", "REST", "COP", "ESTADO", "PRIORIDAD");
    printf("-------------------------------------------------------------------------------------------------------\n");
}