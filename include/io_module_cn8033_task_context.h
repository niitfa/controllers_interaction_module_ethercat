#ifndef IO_MODULE_CN8033_TASK_CONTEXT_H
#define IO_MODULE_CN8033_TASK_CONTEXT_H

#include "context_content_creator.h"
#include "io_module_cn8033_telemetry.h"

class IOModuleCN8033TaskContext : public ContextContentCreator<IOModuleCN8033TaskContext, class IOModuleCN8033TaskState, class IOModuleCN8033, IOModuleCN8033Telemetry>
{
};

#endif