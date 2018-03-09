FSM_DIR				:= $(shell find module_fsm/ -maxdepth 3 -type d -name "*" )
FSM_PATH			:= $(addprefix -I, $(FSM_DIR))

# Добавляем к общим переменным проекта.
PROJECT_PATH			+= $(FSM_PATH)