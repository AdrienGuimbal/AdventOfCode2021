#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifndef STACK_V1
#define STACK_V1

#define STACK(Type) \
typedef struct Type##_stack_elt {		\
	Type val;							\
	struct Type##_stack_elt * next;		\
} Type##_stack_elt;						\
\
typedef struct {						\
	Type##_stack_elt * top;				\
} Type##_stack;							\
\
Type##_stack new_##Type##_stack () {	\
	return (Type##_stack) {NULL};		\
}\
\
Type##_stack* new_##Type##_stack_pointer () {		\
	Type##_stack* p = malloc(sizeof(Type##_stack));	\
	p->top = NULL;									\
	return p;										\
}\
\
Type##_stack_elt* new_##Type##_stack_elt (Type val, Type##_stack_elt * next) {\
	Type##_stack_elt* nv = malloc(sizeof(Type##_stack_elt));\
	nv->val  = val;								\
	nv->next = next;							\
	return nv;									\
}\
\
_Bool empty_##Type##_stack(Type##_stack stack) {\
	return stack.top == NULL;\
}\
\
void Type##_stack_push (Type new, Type##_stack* stack) {	\
	stack->top = new_##Type##_stack_elt(new, stack->top);	\
}\
\
Type Type##_stack_pop (Type##_stack* stack) {	\
	assert(! empty_##Type##_stack(*stack));		\
	Type##_stack_elt head = *(stack->top);		\
	free(stack->top);							\
	stack->top = head.next;						\
	return head.val;							\
}\
\
Type Type##_stack_peek (Type##_stack stack) {	\
	assert(! empty_##Type##_stack(stack));		\
	return stack.top->val;						\
}

#endif // STACK_V1