#ifndef __GSL_COMPLEX_MATH_H__
#define __GSL_COMPLEX_MATH_H__

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS		/* empty */
#define __END_DECLS		/* empty */
#endif

__BEGIN_DECLS

gsl_complex gsl_complex_xy (double real, double imag);  /* r= real+i*imag */
gsl_complex gsl_complex_polar (double r, double theta); /* r= r e^(i theta) */

gsl_complex gsl_complex_conjg (gsl_complex * z);        /* r=conj(z) */

double gsl_complex_arg (gsl_complex * a);       /* return arg(z) */
double gsl_complex_cabs (gsl_complex * z);      /* return |z|   */
double gsl_complex_cabs2 (gsl_complex * z);     /* return |z|^2 */

gsl_complex gsl_complex_add (gsl_complex * a, gsl_complex * b); /* r=a+b */
gsl_complex gsl_complex_sub (gsl_complex * a, gsl_complex * b); /* r=a-b */
gsl_complex gsl_complex_mul (gsl_complex * a, gsl_complex * b); /* r=a*b */
gsl_complex gsl_complex_div (gsl_complex * a, gsl_complex * b); /* r=a/b */

gsl_complex gsl_complex_add_real (gsl_complex * a, double b); /* r=a+b */
gsl_complex gsl_complex_sub_real (gsl_complex * a, double b); /* r=a-b */
gsl_complex gsl_complex_mul_real (gsl_complex * a, double b); /* r=a*b */
gsl_complex gsl_complex_div_real (gsl_complex * a, double b); /* r=a/b */

gsl_complex gsl_complex_inverse (gsl_complex * a); /* r=1/a */

gsl_complex gsl_complex_sqrt (gsl_complex * z); /* r=sqrt(z) */
gsl_complex gsl_complex_sqrt_real (double x);   /* r=sqrt(x) (x<0 ok) */

gsl_complex gsl_complex_pow (gsl_complex * a, gsl_complex * b); /* r=a^b */
gsl_complex gsl_complex_pow_real (gsl_complex * a, double b);   /* r=a^b */

gsl_complex gsl_complex_exp (gsl_complex * a);  /* r=exp(a) */
gsl_complex gsl_complex_log (gsl_complex * a);  /* r=log(a) (base e) */
gsl_complex gsl_complex_log10 (gsl_complex * a); /* r=log10(a) (base 10) */
gsl_complex gsl_complex_log_b (gsl_complex * a, gsl_complex * b); /* r=log(a,b) (b-base) */

/* Trig/Hyp. funcs */
gsl_complex gsl_complex_sin (gsl_complex * a);  /* r=sin(a) */
gsl_complex gsl_complex_cos (gsl_complex * a);  /* r=cos(a) */
gsl_complex gsl_complex_sec (gsl_complex * a);  /* r=sec(a) */
gsl_complex gsl_complex_csc (gsl_complex * a);  /* r=csc(a) */
gsl_complex gsl_complex_tan (gsl_complex * a);  /* r=tan(a) */
gsl_complex gsl_complex_cot (gsl_complex * a);  /* r=cot(a) */

gsl_complex gsl_complex_arcsin (gsl_complex * a);       /* r=arcsin(a) */
gsl_complex gsl_complex_arcsin_real (double a);         /* r=arcsin(a) */
gsl_complex gsl_complex_arccos (gsl_complex * a);       /* r=arccos(a) */
gsl_complex gsl_complex_arccos_real (double a);         /* r=arccos(a) */
gsl_complex gsl_complex_arcsec (gsl_complex * a);       /* r=arcsec(a) */
gsl_complex gsl_complex_arcsec_real (double a);         /* r=arcsec(a) */
gsl_complex gsl_complex_arccsc (gsl_complex * a);       /* r=arccsc(a) */
gsl_complex gsl_complex_arccsc_real (double a);         /* r=arccsc(a) */
gsl_complex gsl_complex_arctan (gsl_complex * a);       /* r=arctan(a) */
gsl_complex gsl_complex_arccot (gsl_complex * a);       /* r=arccot(a) */

gsl_complex gsl_complex_sinh (gsl_complex * a);         /* r=sinh(a) */
gsl_complex gsl_complex_cosh (gsl_complex * a);         /* r=coshh(a) */
gsl_complex gsl_complex_sech (gsl_complex * a);         /* r=sech(a) */
gsl_complex gsl_complex_csch (gsl_complex * a);         /* r=csch(a) */
gsl_complex gsl_complex_tanh (gsl_complex * a);         /* r=tanh(a) */
gsl_complex gsl_complex_coth (gsl_complex * a);         /* r=coth(a) */

gsl_complex gsl_complex_arcsinh (gsl_complex * a);      /* r=arcsinh(a) */
gsl_complex gsl_complex_arccosh (gsl_complex * a);      /* r=arccosh(a) */
gsl_complex gsl_complex_arccosh_real (double a);        /* r=arccosh(a) */
gsl_complex gsl_complex_arcsech (gsl_complex * a);      /* r=arcsech(a) */
gsl_complex gsl_complex_arccsch (gsl_complex * a);      /* r=arccsch(a) */
gsl_complex gsl_complex_arctanh (gsl_complex * a);      /* r=arctanh(a) */
gsl_complex gsl_complex_arctanh_real (double a);        /* r=arctanh(a) */
gsl_complex gsl_complex_arccoth (gsl_complex * a);      /* r=arccoth(a) */

__END_DECLS

#endif /* __GSL_COMPLEX_MATH_H__ */