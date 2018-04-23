#pragma once

#include <stdint.h>

#ifdef __cplusplus

enum class fsmResult {
	funcError				= -1,
	overflowNumberStep		= -2,
	funcNullptr				= -3,
	stepNullptr				= -4
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

	fsmResult start ( void );

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
fsmResult fsmClass< objectType >::start ( void ) {
	const fsmStep< objectType >* nowStep			= &this->vector_fsm[ 0 ];						// Структура текущего шага.
	const fsmStep< objectType >* previousStep		= &this->vector_fsm[ 0 ];						// Структура предыдущего шага (из которого пришли в эту функцию).
	int	result = 0;																					// Результат выполнения шага.

	while( true ) {
		if ( nowStep == nullptr )					return fsmResult::stepNullptr;
		if ( nowStep->funcStep == nullptr )			return fsmResult::funcNullptr;
		result = nowStep->funcStep( previousStep, this->obj );										// Выполняем шаг.

		if ( result == FSM_RET_REPEAT ) continue;													// Если пришел запрос на повтор.
		if ( result == FSM_RET_ERROR )	return fsmResult::funcError;								// Если ошибка.

		if ( result >= nowStep->numberArray )														// Если приказали перейти туда, чего не существует.
			return fsmResult::overflowNumberStep;

		previousStep	= nowStep;
		nowStep		= nowStep->nextStepArray[ result ];
	}
}

#endif
