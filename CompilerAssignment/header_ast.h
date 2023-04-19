#ifndef __HEADER1__
#include <cstdio>
#include <cstring>
#include <utility>
#include<vector>
#include <cstdlib>

#include "Types.h"
char *strdup (char *);

typedef enum
{
	op_plus,
	op_minus,
	op_multiply,
	op_divide,
	op_exp,
	op_gt,
	op_ge,
	op_lt,
	op_le,
	op_eq,
	op_ne
}opType;
class expr
{
	public:
		expr() {}
		virtual EvalType* evaluate()
		{
			return NULL;
		}			
		
};
class identifier: public expr
{
	char* _name;
	EvalType *_value;

	public :
		identifier(char *name, EvalType *value)
		{
			_name = name;
			_value = value;
		}
		char* getName()
		{
			return _name;
		}
		EvalType* evaluate()
		{
			return _value;
		}
};
class constant: public expr
{
	EvalType *_val;

	public:
		constant(EvalType *val)
		{
			_val = val;
		};

		EvalType* evaluate()
		{
			return _val;
		}

};

class bin_expr: public expr
{
	expr *_lhs;
	expr *_rhs;
	opType _op;
	public:
		bin_expr(expr* lhs,expr* rhs,opType op)
		{
			_lhs = lhs;
			_rhs = rhs;
			_op = op;
		}

		EvalType* evaluate()
		{
			switch(_op)
			{
				EvalType *val; 
				case op_plus:
					val = (_lhs->evaluate())->Addfunc(_rhs->evaluate());
					return val;
					
				case op_minus:
					val = (_lhs->evaluate())->Subfunc(_rhs->evaluate());
					return val;

				case op_multiply:
					val = (_lhs->evaluate())->Mulfunc(_rhs->evaluate());
					return val;

				case op_divide:
					if(_rhs->evaluate()->isZero())
					{
						printf("Div by zero error\n");
						exit(1);
					}
					val = (_lhs->evaluate())->Divfunc(_rhs->evaluate());
					return val;

				case op_exp:
					if(_rhs->evaluate()->isFloat())
					{
						printf("floating powers not supported\n");
						exit(1);
					}
					val = (_lhs->evaluate())->Expfunc(_rhs->evaluate());
					return val;


				case op_gt:
					val = (_lhs->evaluate())->GTfunc(_rhs->evaluate());
					return val;

				case op_ge:
					val = (_lhs->evaluate())->GEfunc(_rhs->evaluate());
					return val;
				
				case op_lt:
					val = (_lhs->evaluate())->LTfunc(_rhs->evaluate());
					return val;
			
				case op_le:
					val = (_lhs->evaluate())->LEfunc(_rhs->evaluate());
					return val;

				case op_eq:
					val = (_lhs->evaluate())->EQfunc(_rhs->evaluate());
					return val;

				case op_ne:
					val = (_lhs->evaluate())->NEfunc(_rhs->evaluate());
					return val;


			}
			return NULL;
		}	


};


/*function signatures for actions*/
void assignaction(char*,EvalType*);
expr* verifyVal(char *name);
expr* create_flt(float);
expr* create_int(int);
expr* operation_control(expr*,expr*,opType);


#endif
