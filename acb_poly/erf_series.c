/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2015 Fredrik Johansson

******************************************************************************/

#include "acb_poly.h"
#include "acb_hypgeom.h"

void
_acb_poly_erf_series(acb_ptr g, acb_srcptr h, slong hlen, slong n, slong prec)
{
    _acb_hypgeom_erf_series(g, h, hlen, n, prec);
}

void
acb_poly_erf_series(acb_poly_t g, const acb_poly_t h, slong n, slong prec)
{
    acb_hypgeom_erf_series(g, h, n, prec);
}

