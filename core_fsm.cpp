#include "core_fsm.h"

void fsm::start ( void ) const {
    const fsm_step* now_step            = &this->vector_fsm[ 0 ];                       // Структура текущего шага.
    const fsm_step* previous_step       = &this->vector_fsm[ 0 ];                       // Структура предыдущего шага (из которого пришли в эту функцию).
    int8_t	result						= 0;											// Результат выполнения шага.

    while( true ) {
    	if ( now_step == nullptr ) return;
    	result = now_step->func_step( previous_step );                                  // Выполняем шаг.

    	if ( result == -1 ) continue;													// Если пришел запрос на повтор.
    	if ( result == -2 ) return;														// Если ошибка.

    	if ( result >= now_step->number_array ) return;									// Если приказали перейти туда, чего не существует.

        previous_step   = now_step;
        now_step        = now_step->next_step_array[ result ];
    }
}
