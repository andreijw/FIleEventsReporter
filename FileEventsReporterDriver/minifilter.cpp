#include <fltKernel.h>

// Global variables
PFLT_FILTER gFilterHandle;
ULONG_PTR OperationStatusCtx = 1;

// Function prototypes
extern "C" NTSTATUS
FxDriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
);

NTSTATUS
InstanceSetupCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
);

NTSTATUS
InstanceTeardownCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
);

FLT_PREOP_CALLBACK_STATUS
PreOperationCallback(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
);

FLT_POSTOP_CALLBACK_STATUS
PostOperationCallback(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
);

NTSTATUS
UnloadDriver(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
);

// Registration structure
// IRP events https://learn.microsoft.com/en-us/previous-versions/windows/drivers/ifs/completing-the-irp
const FLT_OPERATION_REGISTRATION Callbacks[] = {
    { IRP_MJ_CREATE,
      0,
      PreOperationCallback,
      PostOperationCallback },

    { IRP_MJ_WRITE,
      0,
      PreOperationCallback,
      PostOperationCallback },

    { IRP_MJ_READ,
      0,
      PreOperationCallback,
      PostOperationCallback },

    { IRP_MJ_SET_INFORMATION,
      0,
      PreOperationCallback,
      PostOperationCallback },

    { IRP_MJ_OPERATION_END }
};

const FLT_REGISTRATION FilterRegistration = {
    sizeof(FLT_REGISTRATION),         // Size
    FLT_REGISTRATION_VERSION,         // Version
    0,                                // Flags
    NULL,                             // Context
    Callbacks,                        // Operation callbacks
    UnloadDriver,                     // MiniFilterUnload
    InstanceSetupCallback,            // InstanceSetup
    InstanceTeardownCallback,         // InstanceTeardownStart
    NULL,                             // InstanceTeardownComplete
    NULL,                             // GenerateFileName
    NULL,                             // GenerateDestinationFileName
    NULL                              // NormalizeNameComponent
};

// Implementation
extern "C" NTSTATUS
FxDriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    NTSTATUS status;
    UNREFERENCED_PARAMETER(RegistryPath);

    DbgPrint("DriverEntry: Initializing FileEventsReporterDriver\n");
    status = FltRegisterFilter(DriverObject, &FilterRegistration, &gFilterHandle);
    DbgPrint("DriverEntry: Registration status = 0x%08X\n", status);

    if (NT_SUCCESS(status)) {
        status = FltStartFiltering(gFilterHandle);
        DbgPrint("DriverEntry: Start status = 0x%08X\n", status);
        if (!NT_SUCCESS(status)) {
            FltUnregisterFilter(gFilterHandle);
        }
    }
    return status;
}

NTSTATUS
UnloadDriver(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
)
{
    UNREFERENCED_PARAMETER(Flags);
    DbgPrint("UnloadDriver: Unloading FileEventsReporterDriver\n");
    FltUnregisterFilter(gFilterHandle);
    return STATUS_SUCCESS;
}

NTSTATUS
InstanceSetupCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
)
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    UNREFERENCED_PARAMETER(VolumeDeviceType);
    UNREFERENCED_PARAMETER(VolumeFilesystemType);
    DbgPrint("InstanceSetupCallback: Instance setup for volume\n");
    return STATUS_SUCCESS;
}

NTSTATUS
InstanceTeardownCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
)
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Reason);
    DbgPrint("InstanceTeardownCallback: Instance teardown for volume\n");
	return STATUS_SUCCESS;
}

FLT_PREOP_CALLBACK_STATUS
PreOperationCallback(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
)
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

    // Log the operation
    DbgPrint("PreOperation: MajorFunction = %u\n", Data->Iopb->MajorFunction);
    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
PostOperationCallback(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
)
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);
    UNREFERENCED_PARAMETER(Flags);

    // Log the operation
    DbgPrint("PostOperation: MajorFunction = %u\n", Data->Iopb->MajorFunction);
    return FLT_POSTOP_FINISHED_PROCESSING;
}
