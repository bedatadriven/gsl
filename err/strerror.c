#include <config.h>
#include <gsl_errno.h>

const char *
gsl_strerror (const int gsl_errno)
{
  switch (gsl_errno)
    {
    case GSL_SUCCESS:
      return "success" ;
    case GSL_FAILURE:
      return "failure" ;
    case GSL_EDOM:
      return "input domain error" ;
    case GSL_ERANGE:
      return "output range error" ;
    case GSL_EFAULT:
      return "invalid pointer" ;
    case GSL_EINVAL:
      return "invalid argument supplied by user" ;
    case GSL_EFAILED:
      return "generic failure" ;
    case GSL_EFACTOR:
      return "factorization failed" ;
    case GSL_ESANITY:
      return "sanity check failed - shouldn't happen" ;
    case GSL_ENOMEM:
      return "malloc failed" ;
    case GSL_EBADFUNC:
      return "problem with user-supplied function";
    case GSL_ERUNAWAY:
      return "iterative process is out of control";
    case GSL_EMAXITER:
      return "exceeded max number of iterations" ;
    case GSL_EZERODIV:
      return "tried to divide by zero" ;
    case GSL_EBADTOL:
      return "specified tolerance is invalid or theoretically unattainable" ;
    case GSL_ETOL:
      return "failed to reach the specified tolerance" ;
    case GSL_EUNDRFLW:
      return "underflow" ;
    case GSL_EOVRFLW:
      return "overflow" ;
    case GSL_ELOSS:
      return "loss of accuracy" ;
    case GSL_EROUND:
      return "roundoff error" ;
    case GSL_EBADLEN:
      return "matrix/vector sizes are not conformant" ;
    case GSL_ENOTSQR:
      return "matrix not square" ;
    case GSL_ESING:
      return "singularity or extremely bad function behavior detected" ;
    case GSL_EUNSUP:
      return "the required feature is not supported by this hardware platform";
    case GSL_EUNIMPL:
      return "the requested feature is not (yet) implemented";
    default:
      return "unknown error code" ;
    }
}
