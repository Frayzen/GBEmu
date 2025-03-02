#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "parser/operand_accessor.h"
#include "parser/operators_list.h"

void execute_operator(operator* op, operand *v1, operand *v2);

#endif /* !EXECUTOR_H */
