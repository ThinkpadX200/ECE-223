
/* this uses log() from the math library, which might need the library */
/* linked in with -lm on the compile command line */

#define M1 5.0   /* median of the exponential function in seconds */
#define M2 60.0  /* median of the gaussian function in tracks */
#define D2 10.0  /* Std deviation of the gaussian function */

/* Uniform Distribution */
double randsim_uni();

#define TIME_CHECKOUT() (randsim_uni() * 10.0)

/* Exponential Distribution */
double randsim_exp();

#define TIME_ARRIVE randsim_exp

/* Gaussian Distribution */
double randsim_gauss();

#define TIME_SHOP randsim_gauss
