# Private Anonymous Data Access

## Requirements

- Bazel

## Usage

```shell
bazel run @PANDA//src/polynomial:polynomial
```

## Locally Decodable Codes - Reed-Muller

- evaluation vectors of multivariate polynomials over the binary field F2
- information bits stored in the polynomial coefficients to the polynomial evaluation vector
- polynomial ring F2[x1,x2,...,xm] with m variables
- f ∈ F2[x1,x2,...,xm] and a binary vector z = (z1,z2,...,zm) ∈ Fm2 , let Evalz(f) := f(z1,z2,...,zm)
- Eval(f) := (Evalz(f) : z ∈ Fm2 )
- Reed-Muller codes with parameters m and r consist of all the evaluation vectors of polynomials with m variables and degree no larger than r.
