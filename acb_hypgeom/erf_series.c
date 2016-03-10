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

    Copyright (C) 2016 Fredrik Johansson

******************************************************************************/

#include "acb_hypgeom.h"

void
_acb_hypgeom_erf_series(acb_ptr g, acb_srcptr h, slong hlen, slong len, slong prec)
{
    acb_t c;
    acb_init(c);

    acb_hypgeom_erf(c, h, prec);

    hlen = FLINT_MIN(hlen, len);

    if (hlen == 1)
    {
        _acb_vec_zero(g + 1, len - 1);
    }
    else
    {
        acb_ptr t, u;
        slong ulen;

        t = _acb_vec_init(len);
        u = _acb_vec_init(len);

        /* erf(h(x)) = integral(h'(x) exp(-h(x)^2)) * (2/sqrt(pi)) */
        ulen = FLINT_MIN(len, 2 * hlen - 1);

        _acb_poly_mullow(u, h, hlen, h, hlen, ulen, prec);
        _acb_vec_neg(u, u, ulen);
        _acb_poly_exp_series(u, u, ulen, len, prec);
        _acb_poly_derivative(t, h, hlen, prec);
        _acb_poly_mullow(g, u, len, t, hlen - 1, len, prec);
        _acb_poly_integral(g, g, len, prec);

        arb_const_sqrt_pi(acb_realref(t), prec);
        arb_inv(acb_realref(t), acb_realref(t), prec);
        arb_mul_2exp_si(acb_realref(t), acb_realref(t), 1);
        _acb_vec_scalar_mul_arb(g, g, len, acb_realref(t), prec);

        _acb_vec_clear(t, len);
        _acb_vec_clear(u, len);
    }

    acb_swap(g, c);
    acb_clear(c);
}

void
acb_hypgeom_erf_series(acb_poly_t g, const acb_poly_t h, slong len, slong prec)
{
    slong hlen = h->length;

    if (hlen == 0 || len == 0)
    {
        acb_poly_zero(g);
        return;
    }

    acb_poly_fit_length(g, len);
    _acb_hypgeom_erf_series(g->coeffs, h->coeffs, hlen, len, prec);
    _acb_poly_set_length(g, len);
    _acb_poly_normalise(g);
}

