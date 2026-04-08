import ctypes
import os


class Solution(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_uint64),
        ("y", ctypes.c_uint64),
        ("hasSolution", ctypes.c_bool),
    ]


def setupLib(lib, prefix):
    func_gcd = getattr(lib, f"{prefix}_GCD")
    func_gcd.argtypes = [ctypes.c_uint64, ctypes.c_uint64]
    func_gcd.restype = ctypes.c_uint64

    func_spf = getattr(lib, f"{prefix}_smallestPrimeFactor")
    func_spf.argtypes = [ctypes.c_uint64]
    func_spf.restype = ctypes.c_uint64

    func_totient = getattr(lib, f"{prefix}_totient")
    func_totient.argtypes = [ctypes.c_uint64]
    func_totient.restype = ctypes.c_uint64

    func_dio = getattr(lib, f"{prefix}_solveDiophantine")
    func_dio.argtypes = [ctypes.c_uint64, ctypes.c_uint64, ctypes.c_uint64]
    func_dio.restype = Solution


def main():
    base_dir = os.path.abspath("..")

    try:
        lib_c = ctypes.CDLL(os.path.join(base_dir, "zad1", "libmy_lib_c.so"))
        lib_ada = ctypes.CDLL(os.path.join(base_dir, "zad2", "libmy_lib_ada.so"))
        lib_rust = ctypes.CDLL(
            os.path.join(base_dir, "zad3", "target", "release", "libmy_lib_rust.so")
        )
    except OSError as e:
        print(f"ERROR: Could not find .so file: {e}")
        return

    setupLib(lib_c, "c")
    setupLib(lib_ada, "ada")
    setupLib(lib_rust, "rust")

    lib_ada.adainit.restype = None
    lib_ada.adafinal.restype = None

    lib_ada.adainit()

    a, b = 48, 18
    print(f"NWD({a}, {b})")
    print(f"C    -> {lib_c.c_GCD(a, b)}")
    print(f"Ada  -> {lib_ada.ada_GCD(a, b)}")
    print(f"Rust -> {lib_rust.rust_GCD(a, b)}\n")

    n = 15
    print(f"smallestPrimeFactor({n})")
    print(f"C    -> {lib_c.c_smallestPrimeFactor(n)}")
    print(f"Ada  -> {lib_ada.ada_smallestPrimeFactor(n)}")
    print(f"Rust -> {lib_rust.rust_smallestPrimeFactor(n)}\n")

    m = 12
    print(f"totient({m})")
    print(f"C    -> {lib_c.c_totient(m)}")
    print(f"Ada  -> {lib_ada.ada_totient(m)}")
    print(f"Rust -> {lib_rust.rust_totient(m)}\n")

    da, db, dc = 21, 3, 15
    print(f"solveDiophantine({da}, {db}, {dc})")

    sol_c = lib_c.c_solveDiophantine(da, db, dc)
    print(f"C    -> x = {sol_c.x}, y = {sol_c.y}, hasSolution = {sol_c.hasSolution}")

    sol_ada = lib_ada.ada_solveDiophantine(da, db, dc)
    print(
        f"Ada  -> x = {sol_ada.x}, y = {sol_ada.y}, hasSolution = {sol_ada.hasSolution}"
    )

    sol_rust = lib_rust.rust_solveDiophantine(da, db, dc)
    print(
        f"Rust -> x = {sol_rust.x}, y = {sol_rust.y}, hasSolution = {sol_rust.hasSolution}"
    )

    lib_ada.adafinal()


if __name__ == "__main__":
    main()
