/* blas/source_scal_c.h
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Gerard Jungman
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * Author:  G. Jungman
 * RCS:     $Id$
 */

{
    size_t n;
    size_t i;
    const BASE alpha_real = REAL0(alpha);
    const BASE alpha_imag = IMAG0(alpha);

    if (incX <= 0) {
	return;
    }

    i = OFFSET(N, incX);

    for (n = 0; n < N; n++) {
	const BASE x_real = REAL(X, i);
	const BASE x_imag = IMAG(X, i);
	REAL(X, i) = x_real * alpha_real - x_imag * alpha_imag;
	IMAG(X, i) = x_real * alpha_imag + x_imag * alpha_real;
	i += incX;
    }
}