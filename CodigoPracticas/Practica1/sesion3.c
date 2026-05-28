#include "pablo.h"

#define MAX_USER 32
#define MAX_DOC 48

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
} PrintJob_t;

typedef struct Node_t
{
    PrintJob_t job;
    struct Node_t *next;
} Node_t;

typedef struct
{
    Node_t *head; // frente
    Node_t *tail; // final
    int size;
} QueueDynamic_t;

void menu();
int msg();
void qd_init(QueueDynamic_t *q);
int qd_is_empty(const QueueDynamic_t *q);
PrintJob_t qd_job(int *id);
int qd_enqueue(QueueDynamic_t *q, PrintJob_t job);
Node_t *qd_nodo(PrintJob_t job);
int qd_peek(const QueueDynamic_t *q, PrintJob_t *out);
int qd_dequeue(QueueDynamic_t *q, PrintJob_t *out);
void qd_print(const QueueDynamic_t *q);
void qd_out(const PrintJob_t job);
void qd_destroy(QueueDynamic_t *q);
void qd_encabezado();
void qd_impresion(QueueDynamic_t *q);

int main()
{
    menu();
    return 0;
}

int msg()
{
    system("CLS");
    printf("(1) Agregar Trabajo\n");
    printf("(2) Descartar trabajo\n");
    printf("(3) Entregar trabajo\n");
    printf("(4) Listar Cola\n");
    printf("(5) Imprimir trabajo\n");
    printf("(6) Salir\n");
    return valida_int(1, 6, "Seleccione una opcion: ");
}

void menu()
{
    PrintJob_t out;
    QueueDynamic_t q;
    qd_init(&q);
    int id = 1;
    int op;

    do
    {
        op = msg();
        system("CLS");
        switch (op)
        {
        case 1:
            if (qd_enqueue(&q, qd_job(&id)))
            {
                printf("Trabajo agregado a la cola.\n");
                system("PAUSE");
            }
            else
            {
                printf("No se pudo agregar el trabajo a la cola\n");
            }
            break;
        case 2:
            if (!qd_is_empty(&q))
            {
                if (qd_peek(&q, &out))
                {
                    qd_encabezado();
                    qd_out(out);
                    system("PAUSE");
                }
                else
                {
                    printf("No se pudo crear el trabajo\n");
                    system("PAUSE");
                }
            }
            else
            {
                printf("La cola esta vacia\n");
                system("PAUSE");
            }
            break;
        case 3:
            if (!qd_is_empty(&q))
            {
                if (qd_dequeue(&q, &out))
                {
                    printf("SALIDA\n");
                    qd_encabezado();
                    qd_out(out);
                    system("PAUSE");
                }
            }
            else
            {
                printf("La cola esta vacia\n");
                system("PAUSE");
            }
            break;
        case 4:
            if (!qd_is_empty(&q))
            {
                qd_print(&q);
            }
            else
            {
                printf("La cola esta vacia\n");
                system("PAUSE");
            }
            break;
        case 5:
            if (!qd_is_empty(&q))
            {
                qd_impresion(&q);
            }
            else
            {
                printf("La cola esta vacia\n");
                system("PAUSE");
            }
        }
    } while (op != 6);
    qd_destroy(&q);
}

PrintJob_t qd_job(int *id)
{
    PrintJob_t job;
    printf("Introduzca el usuario: ");
    my_gets(job.usuario, MAX_USER);
    printf("Introduzca el nombre del documento: ");
    my_gets(job.documento, MAX_DOC);

    job.paginas_restantes = 0;
    job.estado = EN_COLA;
    job.id = *id;
    (*id)++;

    system("CLS");

    job.paginas_total = valida_int(1, 999, "Introduzca el numero de páginas del documento(MAX 999): ");
    job.copias = valida_int(1, 99, "Introduzca la cantidad de copias del documento(MAx 99):");

    system("CLS");

    job.prioridad = valida_int(0, 1, "Quiere asignar la prioridad de urgente a la impresion? (0)No (1)Si: ");
    job.paginas_restantes = job.paginas_total * job.copias;
    return job;
}

int qd_enqueue(QueueDynamic_t *q, PrintJob_t job)
{
    Node_t *nuevoNodo = qd_nodo(job);

    if (nuevoNodo == NULL)
    {
        return 0;
    }

    if (q->size == 0)
    {
        q->head = nuevoNodo;
        q->tail = nuevoNodo;
    }
    else
    {
        if (nuevoNodo->job.prioridad == 0)
        {
            q->tail->next = nuevoNodo;
            q->tail = nuevoNodo;
        }
        else
        {
            nuevoNodo->next = q->head;
            q->head = nuevoNodo;
        }
    }

    q->size++;
    return 1;
}

Node_t *qd_nodo(PrintJob_t job)
{
    Node_t *nuevoNodo = (Node_t *)malloc(sizeof(Node_t));
    nuevoNodo->job = job;
    nuevoNodo->next = NULL;
    return nuevoNodo;
}

int qd_peek(const QueueDynamic_t *q, PrintJob_t *out)
{
    *out = q->head->job;
    return 1;
}

int qd_dequeue(QueueDynamic_t *q, PrintJob_t *out)
{
    *out = q->head->job;

    if (q->size == 1)
    {
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
    }
    else
    {
        Node_t *aux = q->head;
        q->head = q->head->next;
        free(aux);
    }

    q->size--;
    return 1;
}

void qd_init(QueueDynamic_t *q)
{
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
}

int qd_is_empty(const QueueDynamic_t *q)
{
    if (q->size == 0)
    {
        return 1;
    }
    return 0;
}

void qd_print(const QueueDynamic_t *q)
{
    int i = 0;
    qd_encabezado();
    Node_t *aux = q->head;

    while (i < q->size || i < q->size)
    {
        qd_out(aux->job);
        aux = aux->next;
        i++;
    }

    system("PAUSE");
}

void qd_out(const PrintJob_t job)
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

void qd_encabezado()
{
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-15s | %-20s | %-6s | %-6s | %-6s | %-12s | %-10s |\n",
           "ID", "USUARIO", "DOCUMENTO", "TOT", "REST", "COP", "ESTADO", "PRIORIDAD");
    printf("-------------------------------------------------------------------------------------------------------\n");
}

void qd_destroy(QueueDynamic_t *q)
{
    if (q->size == 0)
    {
        return;
    }

    Node_t *aux = q->head;
    Node_t *actual = NULL;
    int i = 1;

    while (i <= q->size)
    {
        if (aux->next == NULL)
        {
            free(aux);
        }
        else
        {
            actual = aux->next;
            aux = aux->next;
            free(actual);
        }
        i++;
    }
}

void qd_impresion(QueueDynamic_t *q)
{
    if (q->head == NULL)
        return;

    Node_t *aux = q->head;

    while (aux != NULL && aux->job.estado == COMPLETADO)
    {
        aux = aux->next;
    }

    if (aux == NULL)
        return;

    PrintJob_t *job = &(aux->job);

    for (int i = 1; i < job->paginas_restantes; i++)
    {
        printf("imprimiendo pagina  %d / %d\n", i + 1, job->paginas_restantes);
        Sleep(300);
        if (i % 10 == 0)
        {
            system("CLS");
        }
    }
    printf("Impresion de %s completada\n", job->documento);
    system("PAUSE");

    job->estado = COMPLETADO;
}