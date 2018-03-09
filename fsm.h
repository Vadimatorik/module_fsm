#pragma once

#include <stdint.h>

#ifdef __cplusplus

enum class fsm_result {
	func_error				= -1,
	overflow_number_step	= -2,
	func_nullptr			= -3,
	step_nullptr			= -4
};

#define FSM_RET_REPEAT					-1
#define FSM_RET_ERROR					-2

// Если нет повторений, то по nullptr происходит аварийный выход.
template < class object_type >
struct fsm_step {
	int ( *func_step )					( const fsm_step< object_type >* previous_step, object_type* obj );
	const fsm_step< object_type >**		const next_step_array;												// Массив возможных путей по выходе.
	const uint8_t						number_array;														// Количество возможных путей по выходе.
};

template < class object_type >
class fsm_class {
public:
	fsm_class ( const fsm_step< object_type >* vector_fsm, object_type* obj ) : vector_fsm( vector_fsm ), obj( obj ) {}
	fsm_class () : vector_fsm( nullptr ), obj( nullptr ) {}

	void relinking( const fsm_step< object_type >* vector_fsm, object_type* obj );

	fsm_result start ( void ) const;

private:
	mutable const fsm_step< object_type >*		vector_fsm;
	mutable object_type*						obj;
};

template < class object_type >
void fsm_class< object_type >::relinking( const fsm_step< object_type >* vector_fsm, object_type* obj ) {
	this->vector_fsm		= vector_fsm;
	this->obj				= obj;
}

template < class object_type >
fsm_result fsm_class< object_type >::start ( void ) const {
	const fsm_step< object_type >* now_step			= &this->vector_fsm[ 0 ];						// Структура текущего шага.
	const fsm_step< object_type >* previous_step	= &this->vector_fsm[ 0 ];						// Структура предыдущего шага (из которого пришли в эту функцию).
	int	result = 0;																					// Результат выполнения шага.

	while( true ) {
		if ( now_step == nullptr )					return fsm_result::step_nullptr;
		if ( now_step->func_step == nullptr )		return fsm_result::func_nullptr;
		result = now_step->func_step( previous_step, this->obj );									// Выполняем шаг.

		if ( result == FSM_RET_REPEAT ) continue;													// Если пришел запрос на повтор.
		if ( result == FSM_RET_ERROR )	return fsm_result::func_error;								// Если ошибка.

		if ( result >= now_step->number_array )														// Если приказали перейти туда, чего не существует.
			return fsm_result::overflow_number_step;

		previous_step	= now_step;
		now_step		= now_step->next_step_array[ result ];
	}
}

#endif
