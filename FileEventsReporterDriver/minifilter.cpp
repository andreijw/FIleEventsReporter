#include <fltKernel.h>

// Global variables
PFLT_FILTER gFilterHandle;
ULONG_PTR OperationStatusCtx = 1;

// Function prototypes
NTSTATUS
DriverEntry(
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