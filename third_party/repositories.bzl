"""A centralized module defining all repositories required through rules_foreign_cc"""

load("//third_party/GMP:gmp_repositories.bzl", "gmp_repositories")
load("//third_party/NTL:ntl_repositories.bzl", "ntl_repositories")

def load_repositories():
    gmp_repositories()
    ntl_repositories()
