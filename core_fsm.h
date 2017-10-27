#pragma once

#ifdef __cplusplus

#include <stdint.h>

#define REPEAT_STEP_MAX             0xFFFFFFFF

struct fsm_step {
    bool ( *func_step )     ( const fsm_step* previous_step );
    const fsm_step*     const number_step_true;
    const fsm_step*     const number_step_false;
    uint32_t            repeat_step;
};

class fsm {
public:
    constexpr fsm ( const fsm_step* const vector_fsm ) : vector_fsm( vector_fsm ) {}

    void    start       ( void ) const;

private:
    const fsm_step* const vector_fsm;
};

#endif
