#include <dataDescriptor.h>
#include <memory_manager.h>

data_descriptor_ptr create_data_descriptor(DATA_TYPE type, mode_t mode) {

    if (!((mode == READ_MODE || mode == WRITE_MODE) &&
          (type == PIPE_T || type == STD_T)))
        return NULL;

    data_descriptor_ptr new_data_d = mem_alloc(sizeof(data_descriptor_t));

    if (new_data_d != NULL) {
        new_data_d->type = type;
        new_data_d->mode = mode;
        new_data_d->pipe = NULL;
    }

    return new_data_d;
}

DATA_TYPE get_data_type(data_descriptor_ptr data_d) {
    if (data_d == NULL) return -1;

    return data_d->type;
}

mode_t get_mode(data_descriptor_ptr data_d) {
    return data_d->mode;
}

pipe_ptr get_pipe(data_descriptor_ptr data_d) {
    if (data_d == NULL || data_d->type != PIPE_T)
        return NULL;

    return data_d->pipe;
}

int set_pipe(data_descriptor_ptr data_d, pipe_ptr pipe) {
    if (data_d != NULL && data_d->type == PIPE_T)
    {
        data_d->pipe = pipe;
        return 0;
    }
    return -1;
}

void close(data_descriptor_ptr data_d) {
    if (data_d == NULL)
        return;

    // if (data_d->type == PIPE_T)
    //     close_pipe(data_d->pipe, data_d->mode == WRITE_MODE);

    free(data_d);
}

// int dup2(unsigned int oldfd, unsigned int newfd)
// {
//     process_t *process = get_current_process();

//     if (newfd >= process->data_d_index || oldfd >= process->data_d_index)
//         return -1;

//     data_descriptor_ptr aux = process->data_descriptors[oldfd];
//     process->data_descriptors[oldfd] = process->data_descriptors[newfd];
//     process->data_descriptors[newfd] = aux;

//     return 0;
// }