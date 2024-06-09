#include <lib/dataDescriptor.h>
#include <pipe.h>
#include <pmm.h>
#include <scheduler.h>

data_descriptor_ptr create_dataDescriptor(DATA_TYPE type, mode_t mode) {

    if (!((mode == READ_MODE || mode == WRITE_MODE) &&
          (type == PIPE_T || type == STD_T)))
        return NULL;

    data_descriptor_ptr newDataD = kmalloc(sizeof(data_descriptor_t));

    if (newDataD != NULL) {
        newDataD->type = type;
        newDataD->mode = mode;
        newDataD->pipe = NULL;
    }

    return newDataD;
}

DATA_TYPE getDataType_dataDescriptor(data_descriptor_ptr dataD) {
    if (dataD == NULL)
        return -1;

    return dataD->type;
}

mode_t getMode_dataDescriptor(data_descriptor_ptr dataD) {
    return dataD->mode;
}

pipe_ptr getPipe_dataDescriptor(data_descriptor_ptr dataD) {
    if (dataD == NULL || dataD->type != PIPE_T)
        return NULL;

    return dataD->pipe;
}

int setPipe_dataDescriptor(data_descriptor_ptr dataD, pipe_ptr pipe) {
    if (dataD != NULL && dataD->type == PIPE_T) {
        dataD->pipe = pipe;
        return 0;
    } 
    return -1;
}

void close_dataDescriptor(data_descriptor_ptr dataD) {
    if (dataD == NULL)
        return;

    if (dataD->type == PIPE_T)
        close_pipe(dataD->pipe, dataD->mode == WRITE_MODE);

    kfree(dataD);
}

int dup2(unsigned int oldfd, unsigned int newfd) {
    process_t *process = get_current_process();

    if (newfd >= process->data_d_index || oldfd >= process->data_d_index)
        return -1;

    data_descriptor_ptr aux = process->data_descriptors[oldfd];
    process->data_descriptors[oldfd] = process->data_descriptors[newfd];
    process->data_descriptors[newfd] = aux;
   
    return 0;
}