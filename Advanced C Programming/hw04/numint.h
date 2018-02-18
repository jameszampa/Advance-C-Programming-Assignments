#ifndef NUMINT_H
#define NUMINT_H 

/* complete your definition of structure Integrand below this line */
/* include the following three fields (and nothing else):          */
/* upper_limit, n_intervals, func_to_be_integrated                 */
/* it is important to have the correct types and field names for us*/
/* to evaluate your functions properly                             */

typedef struct _Integrand {
   double (*func_to_be_integrated)(double);
   double lower_limit;
   double upper_limit;
   int n_intervals;

} Integrand;

/* define your structure Integrand above this line */
/* DO NOT make changes at other locations          */
/* DO NOT declare other functions in this file     */

double simpson_numerical_integration(Integrand intg_arg);

#endif

