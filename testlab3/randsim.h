
/* this uses log() from the math library, which might need the library */
/* linked in with -lm on the compile command line */

#define M1 1.0    /* median of the exponential function in seconds */
#define M2 500.0  /* median of the gaussian function in tracks */
#define D2 200.0  /* Std deviation of the gaussian function */

/* Uniform Distribution */
double randsim_uni();

/* Exponential Distribution */
double randsim_exp();

/* Gaussian Distribution */
double randsim_gauss();
