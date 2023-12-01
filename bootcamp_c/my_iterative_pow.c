/*
**
** QWASAR.IO -- my_iterative_pow
**
** @param {int} param_1
** @param {int} param_2
**
** @return {int}
**
*/
int my_iterative_pow(int param_1, int param_2)
{
	if(param_2 < 0){
      return 0;
      }
  	if(param_2 == 1){
    	return param_1;
    }
  	

  return param_1*my_iterative_pow(param_1,param_2-1);
}