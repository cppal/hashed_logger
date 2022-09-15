#pragma once

// This file contains the DO_ON_INIT utility, which allows local, possibly un-invoked code,
// to register an action (expressed as a stateless lambda) to be executed as part of the global init sequence.
//
// Implementation details (references are to numbers in inline comments):
//
// 1. void_fn_t - prototype of pointer to a trivial ( void(void) ) function
// 2. InitExec - a template class templated on void_fn_t (a.k.a it's instantiated by an instance of a trivial function)
// 3. InitExec::Impl - internal class whose default constructor executes the void_fn_t instance passed in as template parameter
// 4. InitExec::impl - class-static instance of type InitExec::Impl; inline so as to not require an out-of-class definition
// 
// Following is the description of the DO_ON_INIT macro (inline comments are impossible inside a multi-line macro definition):
// 
// 1. ... - variadic macro parameters, the statement/s to be executed during global init; 
//		a single statement may be specified as a simple expression, the closing <;> is optional
// 2. fn_on_init - a constexpr pointer (of type void_fn_t) to a stateless trivial lambda which executes ACT
//		Note: ACT itself (and accordingly the lambda code) is not constexpr. 
//		The lambda however has to be stateless, as only a stateless lambda can bind to a normal function pointer.
//		The resulting constexpr pointer may be used as NTTP (non type template parameter), in our case for creating an instance of InitExec.
// 3. Now we need to force the compiler to create an instantiation of InitExec parameterized on our lambda.
//		This is done by declaring an unused reference to the address of the static InitExec::impl member.
//		This address is available only at runtime, which forces the compiler to create the template instance required for producing it.
//		We prefix the unused reference with (void) to force the compiler to ignore the fact that it's unused.
// 4. With InitExec, and in particular InitExec::impl, instantiated with our lambda as NTTP, a concrete class with a static data member is being created.
//		As class static data members are constructed during the global init sequence before the call to main() (together with all the global objects),
//		our lambda is also called at that time.
// 5. The two statements are placed in their own scope for the purpose of slight code simplification 
//		(otherwise we would have to automatically generate a unique name for fn_on_init on each invocation of DO_ON_INIT)


using void_fn_t = void (*)(); // 1

template<void_fn_t F>
struct InitExec // 2
{
	struct Impl // 3
	{
		Impl() { F(); }
	};
	inline static Impl impl; // 4
};

#define DO_ON_INIT(...) \
	{ \
	constexpr void_fn_t fn_on_init = []() { __VA_ARGS__; }; \
	(void) &InitExec<fn_on_init>::impl; \
	}
