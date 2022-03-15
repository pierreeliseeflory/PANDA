"""A module defining the third party dependency GMP"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def gmp_repositories():
    maybe(
        http_archive,
        name = "GMP_lib",
        build_file = Label("@//third_party/GMP:BUILD.gmp.bazel"),
        sha256 = "258e6cd51b3fbdfc185c716d55f82c08aff57df0c6fbd143cf6ed561267a1526",
        strip_prefix = "gmp-6.2.0",
        # Be compliant with what NTL expects (otherwise version mismatch)
        urls = ["https://ftp.gnu.org/gnu/gmp/gmp-6.2.0.tar.xz"],
    )
