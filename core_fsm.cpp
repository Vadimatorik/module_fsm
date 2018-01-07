#include "core_fsm.h"

void fsm::start ( void ) const {
    uint32_t    repeat_loop             = this->vector_fsm[ 0 ].repeat_step;            // Количество попыток повтора команды в случае неудачи.
    const fsm_step* now_step            = &this->vector_fsm[ 0 ];                       // Структура текущего шага.
    const fsm_step* previous_step       = &this->vector_fsm[ 0 ];                       // Структура предыдущего шага (из которого пришли в эту функцию).
    bool        result                  = false;                                        // Результат выполнения шага.

    while( true ) {
        result = now_step->func_step( previous_step );                                  // Выполняем шаг.

        if ( result == true ) {                                                         // В случае успеха переходим на следующий.
            previous_step   = now_step;
            now_step        = now_step->number_step_true;
            repeat_loop     = now_step->repeat_step;
            continue;
        };

        if ( repeat_loop == REPEAT_STEP_MAX ) continue;                                 // Если мы должны ждать успеха вечность.

        if ( repeat_loop != 0 ) {
            repeat_loop--;
            continue;
        }

        now_step       	= now_step->number_step_false;                                  // Если успеха достичь не удалось.
        repeat_loop     = now_step->repeat_step;
    }
}
