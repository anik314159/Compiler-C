/*This class is to specify the types of variables and constants 
in the language*/
class EvalType
{
	int integer_num;
	float float_num;
	public:
		EvalType()
		{
			integer_num = 0;
			float_num = 0.0;
		}
		EvalType(EvalType& cp)
		{
			integer_num = cp.integer_num;
			float_num = cp.float_num;
		}
		EvalType(int num)
		{
			integer_num = num;
			float_num = 0.0;
		}
		EvalType(float num)
		{
			float_num = num;
			integer_num = 0;
		}

		bool isZero()
		{
			return integer_num == 0
			&& float_num == 0.0;
		}
		bool isFloat()
		{
			return float_num != 0;
		}
		void showVal()
		{
			printf("\n%i\n",integer_num);
			printf("\n%f\n",float_num);
		}
		void typecastInt()
		{
			if(this->isFloat() == false)
				return;

			this->integer_num = (int) (this->float_num);
			this->float_num = 0.0;
		}

		void typecastFloat()
		{
			if(this->isFloat())
				return;
			
			this->float_num =  this->integer_num;
			this->integer_num = 0;
		}

		EvalType* Addfunc(EvalType* v1)
		{
			EvalType *var = new EvalType();

			//conditions for type checking
			if((this->isFloat() && v1->isFloat()) ||( !(this->isFloat()) && !(v1->isFloat())))
			{
				var->integer_num = (v1->integer_num) + (this->integer_num);
				var->float_num = (v1->float_num) + (this->float_num);
				
			}

			else if(this->isFloat())
			{
				var->float_num = (v1->integer_num) + (this->float_num);
				var->integer_num = 0;
			}

			else
			{
				var->float_num = (v1->float_num) + (this->integer_num);
				var->integer_num = 0;				
			}
			return var;

		}
		EvalType* Subfunc(EvalType* v1)
		{
			EvalType *var = new EvalType();

			if((this->isFloat() && v1->isFloat()) ||( !(this->isFloat()) && !(v1->isFloat())))
			{
				EvalType *var = new EvalType();
				var->integer_num = (this->integer_num) - (v1->integer_num);
				var->float_num = (this->float_num) - (v1->float_num);
			}

			else if(this->isFloat())
			{
				var->float_num = (this->integer_num) - (v1->float_num);
				var->integer_num = 0;
			}

			else
			{
				var->float_num = (this->float_num) - (v1->integer_num);
				var->integer_num = 0;				
			}
			return var;
		}
		EvalType* Mulfunc(EvalType* v1)
		{
			
			EvalType *var = new EvalType();
			//type checking conditions
			if((this->isFloat() && v1->isFloat()) ||( !(this->isFloat()) && !(v1->isFloat())))
			{

				var->integer_num = (v1->integer_num) * (this->integer_num);
				var->float_num = (v1->float_num) * (this->float_num);
				
			}
			else if(this->isFloat())
			{
				var->float_num = (v1->integer_num) * (this->float_num);
				var->integer_num = 0;
			}

			else
			{
				var->float_num = (v1->float_num) * (this->integer_num);
				var->integer_num = 0;				
			}
			return var;


		}
		EvalType* Divfunc(EvalType* v1)
		{
			EvalType *var = new EvalType();

			//type checking conditions
			if((this->isFloat() && v1->isFloat()) ||( !(this->isFloat()) && !(v1->isFloat())))
			{
				var->integer_num =  (this->integer_num) / (v1->integer_num) ;
				var->float_num = (this->float_num) / (v1->float_num);
			}
			else if(this->isFloat())
			{
				var->float_num = (this->integer_num) / (v1->float_num);
				var->integer_num = 0;
			}

			else
			{
				var->float_num = (this->float_num) / (v1->integer_num);
				var->integer_num = 0;				
			}
			return var;

		}

		EvalType* Expfunc(EvalType* v1)
		{
			EvalType *var = new EvalType();			
			int p1 = v1->integer_num;
		
			int num = 1;
			float num1 = 1.0;
			if (!(v1->isFloat()))
			{	
				while(p1--)
				{
					num = num * (this->integer_num);
					num1 = num1 * (this->float_num);
				}
				var->float_num = num1;
				var->integer_num = num;
			}
			return var;	
		}

		EvalType* EQfunc(EvalType *v1)
		{
			 EvalType *var = new EvalType();
			bool this_val = !(this->isZero());
			bool op_val = !(v1->isZero());

			var->integer_num = (op_val==this_val );
			
			return var;
			
		}

		EvalType* LEfunc(EvalType *v1)
		{
			EvalType *var = new EvalType();

			//type checking conditions
			if((this->isFloat() && v1->isFloat()) ||( !(this->isFloat()) && !(v1->isFloat())))
			{
				var->integer_num =  (this->integer_num) <= (v1->integer_num) ;
			}
			else if(this->isFloat())
			{
				var->float_num = (this->integer_num) <= (v1->float_num);
				var->integer_num = 0;
			}

			else
			{
				var->float_num = (this->float_num) <= (v1->integer_num);
				var->integer_num = 0;				
			}
			return var;

						
		}
		EvalType* GEfunc(EvalType *v1)
		{
			EvalType *var = new EvalType();
			//type checking conditions
			if((this->isFloat() && v1->isFloat()) ||( !(this->isFloat()) && !(v1->isFloat())))
			{
				var->integer_num =  (this->integer_num) >= (v1->integer_num) ;
			}
			else if(this->isFloat())
			{
				var->float_num = (this->integer_num) >= (v1->float_num);
				var->integer_num = 0;
			}

			else
			{
				var->float_num = (this->float_num) >= (v1->integer_num);
				var->integer_num = 0;				
			}
			return var;

			
		}
		EvalType* GTfunc(EvalType *v1)
		{
			EvalType *var = new EvalType();
			//type checking conditions
			if((this->isFloat() && v1->isFloat()) ||( !(this->isFloat()) && !(v1->isFloat())))
			{
				var->integer_num =  (this->integer_num) > (v1->integer_num) ;
			}
			else if(this->isFloat())
			{
				var->float_num = (this->integer_num) > (v1->float_num);
				var->integer_num = 0;
			}

			else
			{
				var->float_num = (this->float_num) > (v1->integer_num);
				var->integer_num = 0;				
			}
			return var;
			
		}
		EvalType* LTfunc(EvalType *v1)
		{
			 EvalType *var = new EvalType();
			//type checking conditions
			if((this->isFloat() && v1->isFloat()) ||( !(this->isFloat()) && !(v1->isFloat())))
			{
				var->integer_num =  (this->integer_num) < (v1->integer_num) ;
			}
			else if(this->isFloat())
			{
				var->float_num = (this->integer_num) < (v1->float_num);
				var->integer_num = 0;
			}

			else
			{
				var->float_num = (this->float_num) < (v1->integer_num);
				var->integer_num = 0;				
			}
			return var;			
		}
		
		EvalType* NEfunc(EvalType *v1)
		{
			 EvalType *var = new EvalType();
			bool this_val = !(this->isZero());
			bool op_val = !(v1->isZero());

			var->integer_num = (op_val != this_val);
		

			return var;
			
		}
			
};

