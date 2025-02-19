#ifndef QUEUE_H
#define QUEUE_H

#include <ntifs.h>
#include "common.h"

#define MAX_REPORTS_PER_IRP 20

typedef struct _QUEUE_NODE
{
        struct _QUEUE_NODE* next;
        PVOID               data;

} QUEUE_NODE, *PQUEUE_NODE;

typedef struct QUEUE_HEAD
{
        struct _QUEUE_NODE* start;
        struct _QUEUE_NODE* end;
        KGUARDED_MUTEX      lock;
        INT                 entries;

} QUEUE_HEAD, *PQUEUE_HEAD;

typedef struct _GLOBAL_REPORT_QUEUE_HEADER
{
        INT count;

} GLOBAL_REPORT_QUEUE_HEADER, *PGLOBAL_REPORT_QUEUE_HEADER;

typedef struct _REPORT_HEADER
{
        INT report_id;

} REPORT_HEADER, *PREPORT_HEADER;

#define LIST_POOL_TAG 'list'

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Lock_kind_mutex_)
_Releases_lock_(_Lock_kind_mutex_)
VOID
QueuePush(_Inout_ PQUEUE_HEAD Head, _In_ PVOID Data);

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Lock_kind_mutex_)
_Releases_lock_(_Lock_kind_mutex_)
PVOID
QueuePop(_Inout_ PQUEUE_HEAD Head);

VOID
InitialiseGlobalReportQueue(_Out_ PBOOLEAN Status);

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Lock_kind_mutex_)
_Releases_lock_(_Lock_kind_mutex_)
VOID
InsertReportToQueue(_In_ PVOID Report);

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Lock_kind_mutex_)
_Releases_lock_(_Lock_kind_mutex_)
NTSTATUS
HandlePeriodicGlobalReportQueueQuery(_Inout_ PIRP Irp);

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Lock_kind_mutex_)
_Releases_lock_(_Lock_kind_mutex_)
VOID
FreeGlobalReportQueueObjects();

VOID
ListInit(_Inout_ PSINGLE_LIST_ENTRY Head, _Inout_ PKGUARDED_MUTEX Lock);

_Acquires_lock_(_Lock_kind_mutex_)
_Releases_lock_(_Lock_kind_mutex_)
VOID
ListInsert(_Inout_ PSINGLE_LIST_ENTRY Head,
           _Inout_ PSINGLE_LIST_ENTRY NewEntry,
           _In_ PKGUARDED_MUTEX       Lock);

_Acquires_lock_(_Lock_kind_mutex_)
_Releases_lock_(_Lock_kind_mutex_)
BOOLEAN
ListFreeFirstEntry(_Inout_ PSINGLE_LIST_ENTRY Head,
                   _In_ PKGUARDED_MUTEX       Lock,
                   _In_opt_ PVOID             CallbackRoutine);

_Acquires_lock_(_Lock_kind_mutex_)
_Releases_lock_(_Lock_kind_mutex_)
VOID
ListRemoveEntry(_Inout_ PSINGLE_LIST_ENTRY Head,
                _Inout_ PSINGLE_LIST_ENTRY Entry,
                _In_ PKGUARDED_MUTEX       Lock);

#endif