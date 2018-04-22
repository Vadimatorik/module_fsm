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
template < class objectType >
struct fsmStep {
	int ( *funcStep )					( const fsmStep< objectType >* previousStep, objectType* obj );
	const fsmStep< objectType >**		const nextStepArray;												// Массив возможных путей по выходе.
	const uint8_t						numberArray;														// Количество возможных путей по выходе.
};

template < class objectType >
class fsmClass {
public:
	fsmClass ( const fsmStep< objectType >* vectorFsm, objectType* obj ) : vector_fsm( vectorFsm ), obj( obj ) {}
	fsmClass () : vector_fsm( nullptr ), obj( nullptr ) {}

	void relinking( const fsmStep< objectType >* vector_fsm, objectType* obj );

	fsm_result start ( void );

private:
	const fsmStep< objectType >*		vector_fsm;
	objectType*						obj;
};

template < class objectType >
void fsmClass< objectType >::relinking( const fsmStep< objectType >* vectorFsm, objectType* obj ) {
	this->vector_fsm		= vectorFsm;
	this->obj				= obj;
}

template < class objectType >
fsm_result fsmClass< objectType >::start ( void ) {
	const fsmStep< objectType >* nowStep			= &this->vector_fsm[ 0 ];						// Структура текущего шага.
	const fsmStep< objectType >* previousStep	= &this->vector_fsm[ 0 ];						// Структура предыдущего шага (из которого пришли в эту функцию).
	int	result = 0;																					// Результат выполнения шага.

	while( true ) {
		if ( nowStep == nullptr )					return fsm_result::step_nullptr;
		if ( nowStep->funcStep == nullptr )		return fsm_result::func_nullptr;
		result = nowStep->func_step( previousStep, this->obj );									// Выполняем шаг.

		if ( result == FSM_RET_REPEAT ) continue;													// Если пришел запрос на повтор.
		if ( result == FSM_RET_ERROR )	return fsm_result::func_error;								// Если ошибка.

		if ( result >= nowStep->numberArray )														// Если приказали перейти туда, чего не существует.
			return fsm_result::overflow_number_step;

		previousStep	= nowStep;
		nowStep		= nowStep->nextStepArray[ result ];
	}
}

#endif
