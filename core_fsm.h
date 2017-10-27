#pragma once

#ifdef __cplusplus

#include <stdint.h>

#define REPEAT_STEP_MAX             0xFFFFFFFF

struct fsm_step {
    bool ( *func_step )     ( uint32_t previous_step );
    uint32_t            number_step_true;
    uint32_t            number_step_false;
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
