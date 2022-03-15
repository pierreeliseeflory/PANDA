"""A module defining the third party dependency NTL"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def ntl_repositories():
    maybe(
        http_archive,
        name = "NTL_lib",
        build_file = Label("@//third_party/NTL:BUILD.ntl.bazel"),
        patch_args = ["-p1"],
        patches = ["@//third_party/NTL:ntl.patch"],
        sha256 = "210d06c31306cbc6eaf6814453c56c776d9d8e8df36d74eb306f6a523d1c6a8a",
        urls = ["https://libntl.org/ntl-11.5.1.tar.gz"],
    )
