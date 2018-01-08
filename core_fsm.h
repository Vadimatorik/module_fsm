#pragma once

#ifdef __cplusplus

#include <stdint.h>

#define REPEAT_STEP_MAX             0xFFFFFFFF

#define FSM_RET_REPEAT				-1
#define FSM_RET_ERROR				-2

struct fsm_step {
    int ( *func_step )     ( const fsm_step* previous_step );
    const fsm_step**     const next_step_array;												// Массив возможных путей по выходе.
    const uint8_t     	number_array;														// Количество возможных путей по выходе.
};

class fsm {
public:
    constexpr fsm ( const fsm_step* const vector_fsm ) : vector_fsm( vector_fsm ) {}
    void start ( void ) const;

private:
    const fsm_step* const vector_fsm;
};

#endif
