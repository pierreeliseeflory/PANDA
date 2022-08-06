# Private Anonymous Data Access

## Requirements

- Bazel

## Usage

### Run

```shell
bazel run @PANDA//src/polynomial:polynomial
```

### Test

```shell
bazel test --test_output=all ...
```

## References

- Reed-Muller Scheme : Canetti, R., Holmgren, J., Richelson, S. (2017). Towards Doubly Efficient Private Information Retrieval. In: Kalai, Y., Reyzin, L. (eds) Theory of Cryptography. TCC 2017. Lecture Notes in Computer Science(), vol 10678. Springer, Cham. https://doi.org/10.1007/978-3-319-70503-3_23 (Sec. 4.2)
- Low Degree Extension : J. Holmgren and R. Rothblum, "Delegating Computations with (Almost) Minimal Time and Space Overhead," 2018 IEEE 59th Annual Symposium on Foundations of Computer Science (FOCS), 2018, pp. 124-135, doi: 10.1109/FOCS.2018.00021. (Fact 3.4.)
